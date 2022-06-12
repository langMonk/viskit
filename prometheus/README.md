# Introduction

Following README file describes all assumptions made while creating this wrapper, structures of configurate files and high-level overview of scripts.

Wrapper created by Maciej Sikora for viskit library.

# How it works

In main directory you can find a Docerfile containing formula for creating a docker image with all tools necesary for compilation and usage of viskit library. It is advised to run it for yourself and upload it to your public repository from which you will be able to download a docker image to a PROMETHEUS environment.

After that you will be able to provide a configuration file in _.json_ format which is described below and create a script for running library on PROMETHEUS.

On supercomputer there is no docker, but there is a sibling library called 'singularity' that provides utilities for running docker images. For some reason downloading it and creating all necessary things for it can take some time. 

It is strongly advised to download docker image manually. Instructions on how to do in are at the end of this README.

# General usage

User should provide configuration _.json_ file with a structure discribed below. After that user should execute python script with _.json_ file as an input which should result in a bash script file that should be transfered to PROMETHEUS environment. Lastly user should make sure that all datasets are uploaded and in correct path on PROMETHEUS environment.

1. Create _.json_ config file.
2. Run **config.py** script.
```bash
python config.py --input-config './config_file.json' --output './start_script.sh'
```
3. Upload _start_script.sh_ file and datasets to PROMETHEUS. (f.e. via WinSCP)
4. Run _start_script.sh_ file.
```bash
chmod +x ./start_script.sh
dos2unix ./start_script.sh
sbatch start_script.sh
```

# JSON config structure

Below you can find and example on a correct _.json_ file with required structure.

```json
{
    "nodes": 1,
    "ntasks": 12,
    "time": "01:00:00",
    "sockets-per-node": 2,
    "partition": "plgrid-short",
    "account": "plgmpr22",

    "download_image": false,
    "image_name": "viskit_builder",
    "docker_repo": "docker://maciejsikora2302/viskit",
    "scriptFilePath": "./viskit_offline/viskit_offline",

    "common_parameters":
    {
        "datasetFilePath": "/opt/data/datasets/mnist.csv" ,
        "labelsFilePath": "/opt/data/labels/mnist_label.txt" ,
        "graphFilePath": "/opt/data/graphs/mnist_cosine.bin" ,
        "outputFilePath": "./visualization.txt",
        "iterations": "200"
    },

    "invocations": [
        {
            "datasetFilePath": "./datasets/mnist.csv",
            "labelsFilePath": "./labels/mnist_label.txt",
            "graphFilePath": "./graphs/mnist_cosine.bin" ,
            "outputFilePath": "./visualization.txt",
            "iterations": 2500 ,
            "nearestNeighborsCount": 2,
            "randomNeighborsCount": 1,
            "binaryDistances": 1,
            "reverseNeighborsSteps": 0,
            "reverseNeighborsCount": 0,
            "l1Steps": 0,
            "casterType": "adam"
        },
        {
            "datasetFilePath": "./datasets/mnist.csv",
            "labelsFilePath": "./labels/mnist_label.txt",
            "graphFilePath": "./graphs/mnist_cosine.bin" ,
            "outputFilePath": "./visualization.txt",
            "iterations": 2500 ,
            "nearestNeighborsCount": 2,
            "randomNeighborsCount": 1,
            "binaryDistances": 1
        },
        {

            "iterations": 134523645 ,
            "nearestNeighborsCount": 234,
            "randomNeighborsCount": 11,
            "binaryDistances": 100000000
        }
    ]
}
```

## Explanation of fields

```json
"nodes": 1 REQUIRED [INT] 
"ntasks": 12 REQUIRED [INT] 
"time": "01:00:00" REQUIRED [STRING] 
"sockets-per": "2-node" REQUIRED [INT] 
"partition": "plgrid-short" REQUIRED [STRING] 
"account": "plgmpr22" REQUIRED [STRING] 
```
Parameters required by PROMETHEUS to work. More info on: https://kdm.cyfronet.pl/portal/Prometheus:Basics#Running%20jobs

---

```json
"download_image": false OPTIONAL [BOOL] {default false}
"image_name": "viskit_builder" OPTIONAL [STRING] {default "viskit_builder"}
"docker_repo": "docker://maciejsikora2302/viskit" OPTIONAL [STRING] {default "docker://maciejsikora2302/viskit"}
"scriptFilePath": "./viskit_offline/viskit_offline" REQUIRED [STRING]
```

"download_image" - if this is set to false script will attempt to use downloaded image_name.sif image. Will throw an error if it doesnt exist.  
"image_name" - name of _.sif_ image from singularity, will throw an error if doesnt exist  
"docker_repo" - from where to download docker image  
"scriptFilePath" - path to compiled viskit code, should already exits in docker image created base on provided Docker file

---

```json
"common_parameters":
{
    "datasetFilePath": OPTIONAL [STRING] 
    "labelsFilePath": OPTIONAL [STRING]
    "graphFilePath": OPTIONAL [STRING] 
    "outputFilePath": OPTIONAL [STRING]
    "iterations": OPTIONAL [STRING]
}
```
"common_parameters" - is an objects that holds common parameters required by viskit library

If any of those parameters will not be provided here, they need to be provided in every invocation or the script will fail.

"datasetFilePath" - path to dataset used by docker image  
"labelsFilePath" - path to labels used by docker image  
"graphFilePath" - path to graph used by docker image  
"outputFilePath" - path to output used by docker image  
"iterations" - number of itarations used by viskit library  

---

```json
"invocations": [
    {},
    {},
    {}
]
```

"invocations" - the command will be run for every entry in 'invoke' with parameters listed in each entry

Possible parameters to provide:

"datasetFilePath"  
"labelsFilePath"  
"graphFilePath"  
"outputFilePath"  
"iterations"  
"nearestNeighborsCount"  
"randomNeighborsCount"  
"binaryDistances"  
"reverseNeighborsSteps"  
"reverseNeighborsCount"  
"l1Steps"  
"casterType"  
"optimizerType"

If parameter is provided in "invocations" it will always override default parameters.

Below you can find a table of which parameter is required and in what form without explanations

##  Required parameters for prometheus

    Int     nodes 
    Int     ntasks
    String  time
    Int     sockets-per-node
    String  partition
    String  account

## Optional general parameters

    Bool    download_image 
    Bool    verbose 
    String  image_name
    String  docker_repo
    String  scriptFilePath

Verbose in regard to created script, not for cration of this script.

##  Required parameters for viskit
If they are not provided in common_parameters or in invocation the parser will throw an error

    String  datasetFilePath
    String  labelsFilePath
    String  graphFilePath
    String  outputFilePath

## Optional parameters with their default values
If they are not provided they will be taken from inside python code

    Int     iterations = 2500
    Int     nearestNeighborsCount = 2
    Int     randomNeighborsCount = 1
    Bool    binaryDistances = true
    Int     reverseNeighborsSteps = 0
    Int     reverseNeighborsCount = 0
    Int     l1Steps = 0
    String  caster_name = "force-directed"


# Singularity

Docker is not avaiable on Prometheus, but singularity is, which is a framework that can work with docker images. For this script to work you will need to download viskit image from repo REPO LINK. You can provide it in script or run command youself.

I strongly advise to pull image manually since it might take some time. It should work without allocating job on grid, but just in case you can start and interactive mode and then proceed to download.

plgrid-testing might have a shorter access queue, but might not have enough time to compleat image pull.

```bash
srun -p plgrid-testing -N 1 --ntasks=2 -n 1 -A grant_name --time=01:00:00 --pty /bin/bash -l
```
```bash
srun -p plgrid -N 1 --ntasks=2 -n 1 -A grant_name --time=02:30:00 --pty /bin/bash -l
```
After allocating run
```
singularity pull img_name.sif repo_name
```
For example:
```bash
singularity pull viskit_builder.sif docker://maciejsikora2302/viskit
```

# Running script on Prometheus
After _.sif_ image has been create, and all datasets and start_script.sh have been copied to prometheus, run script created by config.py in batch mode and remember to add it executable permission.

```bash
chmod +x ./start_script.sh
dos2unix ./start_script.sh
sbatch start_script.sh
```

## Extra info

---
1. Remember to add '.txt' to 'outputFilePath'.
---
2. Remember to manually upload data to process to prometheus. you can do it easly with WinSCP.
---
3. If you want to provide any of:

    - nearestNeighborsCount
    - randomNeighborsCount
    - binaryDistances
    - reverseNeighborsSteps
    - reverseNeighborsCount
    - l1Steps
    - casterType  

    The ones not provided will have default values
---
