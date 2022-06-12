#!/bin/bash -l
#SBATCH --nodes 1
#SBATCH --ntasks 12
#SBATCH --time=00:20:00
#SBATCH --sockets-per-node=2
#SBATCH --partition=plgrid-testing
#SBATCH --account=plgmpr22

##############
#Modules that might be required during sbatch on prometheus go here
##############


if [ -f 'viskit_builder.sif' ]; then
     echo 'File viskit_builder.sif exists.'
else
     echo "File viskit_builder.sif not found. pwd: $(pwd) "
     echo "Exiting."
     exit 1
fi
#Run docker container here

#This lines will be modified to send request to dockermicro service

if [ -f './data/datasets/mnist.csv' ]; then
     echo 'File ./data/datasets/mnist.csv exists.'
else
     echo "File ./data/datasets/mnist.csv not found. pwd: $(pwd) "
     echo "Exiting."
     exit 1
fi
if [ -f './data/labels/mnist_label.txt' ]; then
     echo 'File ./data/labels/mnist_label.txt exists.'
else
     echo "File ./data/labels/mnist_label.txt not found. pwd: $(pwd) "
     echo "Exiting."
     exit 1
fi
if [ -f './data/graphs/mnist_cosine.bin' ]; then
     echo 'File ./data/graphs/mnist_cosine.bin exists.'
else
     echo "File ./data/graphs/mnist_cosine.bin not found. pwd: $(pwd) "
     echo "Exiting."
     exit 1
fi
start_time=$(date +%s.%3N)

echo 'singularity exec viskit_builder.sif    /opt/viskit/viskit_offline/viskit_offline ./data/datasets/mnist.csv ./data/labels/mnist_label.txt ./data/graphs/mnist_cosine.bin ./visualization_0.txt 100 2 1 1 0 0 0 force-directed'
singularity exec viskit_builder.sif    /opt/viskit/viskit_offline/viskit_offline ./data/datasets/mnist.csv ./data/labels/mnist_label.txt ./data/graphs/mnist_cosine.bin ./visualization_0.txt 100 2 1 1 0 0 0 force-directed

end_time=$(date +%s.%3N)
elapsed=$(echo "scale=3; $end_time - $start_time" | bc)
echo "Elapsed time: $elapsed"
if [ -f './data/datasets/mnist.csv' ]; then
     echo 'File ./data/datasets/mnist.csv exists.'
else
     echo "File ./data/datasets/mnist.csv not found. pwd: $(pwd) "
     echo "Exiting."
     exit 1
fi
if [ -f './data/labels/mnist_label.txt' ]; then
     echo 'File ./data/labels/mnist_label.txt exists.'
else
     echo "File ./data/labels/mnist_label.txt not found. pwd: $(pwd) "
     echo "Exiting."
     exit 1
fi
if [ -f './data/graphs/mnist_cosine.bin' ]; then
     echo 'File ./data/graphs/mnist_cosine.bin exists.'
else
     echo "File ./data/graphs/mnist_cosine.bin not found. pwd: $(pwd) "
     echo "Exiting."
     exit 1
fi
start_time=$(date +%s.%3N)

echo 'singularity exec viskit_builder.sif    /opt/viskit/viskit_offline/viskit_offline ./data/datasets/mnist.csv ./data/labels/mnist_label.txt ./data/graphs/mnist_cosine.bin ./visualization_1.txt 300 2 1 1 0 0 0 force-directed'
singularity exec viskit_builder.sif    /opt/viskit/viskit_offline/viskit_offline ./data/datasets/mnist.csv ./data/labels/mnist_label.txt ./data/graphs/mnist_cosine.bin ./visualization_1.txt 300 2 1 1 0 0 0 force-directed

end_time=$(date +%s.%3N)
elapsed=$(echo "scale=3; $end_time - $start_time" | bc)
echo "Elapsed time: $elapsed"
if [ -f './data/datasets/mnist.csv' ]; then
     echo 'File ./data/datasets/mnist.csv exists.'
else
     echo "File ./data/datasets/mnist.csv not found. pwd: $(pwd) "
     echo "Exiting."
     exit 1
fi
if [ -f './data/labels/mnist_label.txt' ]; then
     echo 'File ./data/labels/mnist_label.txt exists.'
else
     echo "File ./data/labels/mnist_label.txt not found. pwd: $(pwd) "
     echo "Exiting."
     exit 1
fi
if [ -f './data/graphs/mnist_cosine.bin' ]; then
     echo 'File ./data/graphs/mnist_cosine.bin exists.'
else
     echo "File ./data/graphs/mnist_cosine.bin not found. pwd: $(pwd) "
     echo "Exiting."
     exit 1
fi
start_time=$(date +%s.%3N)

echo 'singularity exec viskit_builder.sif    /opt/viskit/viskit_offline/viskit_offline ./data/datasets/mnist.csv ./data/labels/mnist_label.txt ./data/graphs/mnist_cosine.bin ./visualization_2.txt 2500 2 1 1 0 0 0 force-directed'
singularity exec viskit_builder.sif    /opt/viskit/viskit_offline/viskit_offline ./data/datasets/mnist.csv ./data/labels/mnist_label.txt ./data/graphs/mnist_cosine.bin ./visualization_2.txt 2500 2 1 1 0 0 0 force-directed

end_time=$(date +%s.%3N)
elapsed=$(echo "scale=3; $end_time - $start_time" | bc)
echo "Elapsed time: $elapsed"
if [ -f './data/datasets/mnist.csv' ]; then
     echo 'File ./data/datasets/mnist.csv exists.'
else
     echo "File ./data/datasets/mnist.csv not found. pwd: $(pwd) "
     echo "Exiting."
     exit 1
fi
if [ -f './data/labels/mnist_label.txt' ]; then
     echo 'File ./data/labels/mnist_label.txt exists.'
else
     echo "File ./data/labels/mnist_label.txt not found. pwd: $(pwd) "
     echo "Exiting."
     exit 1
fi
if [ -f './data/graphs/mnist_cosine.bin' ]; then
     echo 'File ./data/graphs/mnist_cosine.bin exists.'
else
     echo "File ./data/graphs/mnist_cosine.bin not found. pwd: $(pwd) "
     echo "Exiting."
     exit 1
fi
start_time=$(date +%s.%3N)

echo 'singularity exec viskit_builder.sif    /opt/viskit/viskit_offline/viskit_offline ./data/datasets/mnist.csv ./data/labels/mnist_label.txt ./data/graphs/mnist_cosine.bin ./visualization_3.txt 2500 2 1 1 0 0 0 force-directed'
singularity exec viskit_builder.sif    /opt/viskit/viskit_offline/viskit_offline ./data/datasets/mnist.csv ./data/labels/mnist_label.txt ./data/graphs/mnist_cosine.bin ./visualization_3.txt 2500 2 1 1 0 0 0 force-directed

end_time=$(date +%s.%3N)
elapsed=$(echo "scale=3; $end_time - $start_time" | bc)
echo "Elapsed time: $elapsed"


