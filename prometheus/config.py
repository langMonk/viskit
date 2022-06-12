import json
import optparse

def key_error_handling(key):
    global data, parsed_data
    try:
        parsed_data[key] = data[key]
    except KeyError as e:
        print(f"{key} was not provided. Exiting app.")
        raise e

def general_parameters_handling():
    global data, parsed_data
    try:
        parsed_data["scriptFilePath"] = data["scriptFilePath"]
    except KeyError as e:
        print(f"Path to viskit_offline was not provided. Exiting app.")
        raise e
    try:
        parsed_data["download_image"] = data["download_image"]
    except KeyError as e:
        parsed_data["download_image"] = False
        print(f"download_image was not provided. Using default 'false'.")
    try:
        parsed_data["image_name"] = data["image_name"]
    except KeyError as e:
        parsed_data["image_name"] = 'viskit_builder'
        print(f"image_name was not provided. Using default name 'viskit_builder'.")
    try:
        parsed_data["docker_repo"] = data["docker_repo"]
    except KeyError as e:
        parsed_data["docker_repo"] = 'docker://maciejsikora2302/viskit'
        print(f"docker_repo was not provided. Using default 'docker://maciejsikora2302/viskit'.")
    try:
        parsed_data["verbose"] = data["verbose"]
    except KeyError as e:
        parsed_data["verbose"] = False

def common_parameters_handling(key):
    global data, parsed_data
    try:
        parsed_data["common_parameters"][key] = data["common_parameters"][key]
    except KeyError as e:
        if key != "iterations":
            print(f"{key} was not provided as a common parameter. If this is not provided in each invocation the parser will throw an error.")
        else:
            print(f"{key} was not provided as a common parameter. If this is not provided in each invocation the parser will use default value.")

def raiser(ex):
    raise ex

def invocation_handling(currnet_invocation):
    global parsed_data, INVOATION_ARGUMENTS
    
    try:
        datasetFilePath = currnet_invocation["datasetFilePath"]
    except KeyError as e:
        datasetFilePath = parsed_data["common_parameters"]["datasetFilePath"] if parsed_data["common_parameters"]["datasetFilePath"] else raiser(KeyError("datasetFilePath not provided"))
    try:
        labelsFilePath = currnet_invocation["labelsFilePath"]
    except KeyError as e:
        labelsFilePath = parsed_data["common_parameters"]["labelsFilePath"] if parsed_data["common_parameters"]["labelsFilePath"] else raiser(KeyError("labelsFilePath not provided"))
    try:
        graphFilePath = currnet_invocation["graphFilePath"]
    except KeyError as e:
        graphFilePath = parsed_data["common_parameters"]["graphFilePath"] if parsed_data["common_parameters"]["graphFilePath"] else raiser(KeyError("graphFilePath not provided"))
    try:
        outputFilePath = currnet_invocation["outputFilePath"]
    except KeyError as e:
        outputFilePath = parsed_data["common_parameters"]["outputFilePath"] if parsed_data["common_parameters"]["outputFilePath"] else raiser(KeyError("outputFilePath not provided"))

    try:
        iterations = currnet_invocation["iterations"]
    except KeyError as e:
        iterations = ITERATIONS
    try:
        nearestNeighborsCount = currnet_invocation["nearestNeighborsCount"]
    except KeyError as e:
        nearestNeighborsCount = NEARESTNEIGHBORSCOUNT
    try:
        randomNeighborsCount = currnet_invocation["randomNeighborsCount"]
    except KeyError as e:
        randomNeighborsCount = RANDOMNEIGHBORSCOUNT
    try:
        binaryDistances = currnet_invocation["binaryDistances"]
    except KeyError as e:
        binaryDistances = BINARYDISTANCES
    try:
        reverseNeighborsSteps = currnet_invocation["reverseNeighborsSteps"]
    except KeyError as e:
        reverseNeighborsSteps = REVERSENEIGHBORSSTEPS
    try:
        reverseNeighborsCount = currnet_invocation["reverseNeighborsCount"]
    except KeyError as e:
        reverseNeighborsCount = REVERSENEIGHBORSCOUNT
    try:
        l1Steps = currnet_invocation["l1Steps"]
    except KeyError as e:
        l1Steps = L1STEPS
    try:
        casterType = currnet_invocation["casterType"]
    except KeyError as e:
        casterType = CASTERTYPE

    return datasetFilePath, labelsFilePath, graphFilePath, outputFilePath, iterations, nearestNeighborsCount, randomNeighborsCount, binaryDistances, reverseNeighborsSteps, reverseNeighborsCount, l1Steps, casterType

def elapsed_time_start(file):
    file.write(f"start_time=$(date +%s.%3N)\n")

def elapsed_time_end(file):
    file.write("end_time=$(date +%s.%3N)\n")
    file.write("elapsed=$(echo \"scale=3; $end_time - $start_time\" | bc)\n")
    file.write("echo \"Elapsed time: $elapsed\"\n")

def write_command(file, image_name, datasetFilePath, labelsFilePath, graphFilePath, outputFilePath, iterations, nearestNeighborsCount, randomNeighborsCount, binaryDistances, reverseNeighborsSteps, reverseNeighborsCount, l1Steps, casterType):
    global parsed_data

    command_string = f"""
    singularity exec {image_name}.sif
    {parsed_data['scriptFilePath']} 
    {datasetFilePath} 
    {labelsFilePath} 
    {graphFilePath} 
    {outputFilePath} 
    {iterations} 
    {nearestNeighborsCount} 
    {randomNeighborsCount} 
    {binaryDistances} 
    {reverseNeighborsSteps} 
    {reverseNeighborsCount} 
    {l1Steps} 
    {casterType} 
    """.strip().replace('\n', '').replace('     ', ' ')
    file.write('\n')
    file.write(f"echo '{command_string}'\n")
    file.write(command_string)
    file.write('\n')
    file.write('\n')

def make_sure_file_exists(file, filename):
    global parsed_data
    file.write(f"if [ -f '{filename}' ]; then\n")
    if parsed_data['verbose']:
        file.write(f"     echo 'File {filename} exists.'\n")
    else:
        file.write(f"     :'\n")
    file.write(f"else\n")
    file.write(f"     echo \"File {filename} not found. pwd: $(pwd) \"\n")
    file.write(f"     echo \"Exiting.\"\n")
    file.write(f"     exit 1\n")
    file.write(f"fi\n")



op = optparse.OptionParser()

op.add_option("-i", "--input-config", dest='input_path', default='./config_file.json', help="Provide path to input config file in relation to directory of this script or absolute path")
op.add_option("-o", "--output", dest='output_path', default='./start_script.sh', help="Provide path to output file in relation to directory of this script or absolute path")

(options, args) = op.parse_args()

#Default values 
ITERATIONS = 2500
NEARESTNEIGHBORSCOUNT = 2
RANDOMNEIGHBORSCOUNT = 1
BINARYDISTANCES = 1
REVERSENEIGHBORSSTEPS = 0
REVERSENEIGHBORSCOUNT = 0
L1STEPS = 0
CASTERTYPE = "force-directed"

INVOATION_ARGUMENTS = ["datasetFilePath","labelsFilePath","graphFilePath","outputFilePath","iterations","nearestNeighborsCount","randomNeighborsCount","binaryDistances","reverseNeighborsSteps","reverseNeighborsCount","l1Steps","casterType"]


data = json.loads(open(options.input_path).read())
parsed_data = {}
parsed_data["common_parameters"] = {}

# print(data)

key_error_handling("nodes")
key_error_handling("ntasks")
key_error_handling("time")
key_error_handling("sockets-per-node")
key_error_handling("partition")
key_error_handling("account")

general_parameters_handling()

common_parameters_handling("datasetFilePath")
common_parameters_handling("labelsFilePath")
common_parameters_handling("graphFilePath")
common_parameters_handling("outputFilePath")
common_parameters_handling("iterations")

with open(options.output_path, 'w') as f:
    f.write("#!/bin/bash -l\n")
    f.write(f"#SBATCH --nodes {parsed_data['nodes']}\n")
    f.write(f"#SBATCH --ntasks {parsed_data['ntasks']}\n")
    f.write(f"#SBATCH --time={parsed_data['time']}\n")
    f.write(f"#SBATCH --sockets-per-node={parsed_data['sockets-per-node']}\n")
    f.write(f"#SBATCH --partition={parsed_data['partition']}\n")
    f.write(f"#SBATCH --account={parsed_data['account']}\n")
    f.write(f"\n")

    # f.write(f"##############\n")
    # f.write(f"#Modules that might be required during sbatch on prometheus go here\n")
    f.write(f"##############\n\n\n")

    #Start time mearurement

    if parsed_data['download_image']:
        f.write(f"echo 'Downloading image...'\n\n")
        f.write(f"singularity pull {parsed_data['image_name']}.sif {parsed_data['docker_repo']}\n")
        f.write(f"echo 'Downloading image compleate.'\n\n")

    make_sure_file_exists(f, parsed_data['image_name']+'.sif')

    # f.write(f"#Run docker container here\n\n")

    # f.write(f"#This lines will be modified to send request to dockermicro service\n\n")

    for i, invocation in enumerate(data['invocations']):
        datasetFilePath, labelsFilePath, graphFilePath, outputFilePath, iterations, nearestNeighborsCount, randomNeighborsCount, binaryDistances, reverseNeighborsSteps, reverseNeighborsCount, l1Steps, casterType = invocation_handling(invocation)
        make_sure_file_exists(f, datasetFilePath)
        make_sure_file_exists(f, labelsFilePath)
        make_sure_file_exists(f, graphFilePath)
        elapsed_time_start(f)
        write_command(f, parsed_data['image_name'], datasetFilePath, labelsFilePath, graphFilePath, outputFilePath.replace('.txt', f'_{i}.txt'), iterations, nearestNeighborsCount, randomNeighborsCount, binaryDistances, reverseNeighborsSteps, reverseNeighborsCount, l1Steps, casterType)
        elapsed_time_end(f)

    f.write("\n\n")