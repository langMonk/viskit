FROM ubuntu:20.04 as builder

# Get dependencies
RUN apt update

# Install cpp compiler, lapack, make
RUN apt-get install build-essential libssl-dev liblapack-dev wget make -y

# Boost required by CMakeList
    # Boost need configured tzdata, but usually it runs in an interactive mode, following lines ommit that
    RUN DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends tzdata
    RUN dpkg-reconfigure tzdata
    # Normal Boost instalation
    RUN apt-get install libboost-all-dev -y

# Install rest of dependencies
RUN apt install git -y 
# Making sure python is installed
RUN apt install python3 -y

# Get viskit library (possibly change later to download from gitlab repositiory [https://gitlab.com/bminch/viskit.git])
RUN mkdir -p /opt/viskit
WORKDIR /opt/viskit
COPY . .

# Get Python dependencies
RUN apt install python3-pip -y
RUN pip install -r ./requirements.txt
RUN pip install faiss-cpu

# Initialize submodules
RUN git submodule init
RUN git submodule update

# Install CMake
WORKDIR /opt
RUN mkdir -p /opt/temp 
WORKDIR /opt/temp 
RUN wget https://github.com/Kitware/CMake/releases/download/v3.23.1/cmake-3.23.1.tar.gz 
RUN tar -zxvf cmake-3.23.1.tar.gz
WORKDIR /opt/temp/cmake-3.23.1
RUN ./bootstrap 
RUN make 
RUN make install

# Build application

WORKDIR /opt/viskit
RUN cmake ./CMakeLists.txt
RUN make

# Start app that exposes API for running tasks

# Utilities and test sets
# Tree print
RUN apt install tree -y
# Downloading from gdrive
# RUN pip install gdown
# WORKDIR /opt/viskit/datasets
# RUN gdown 1pwwzA45pajw3H2sxJI3H8RQ6mbzuicjz
# WORKDIR /opt/viskit/graphs
# RUN gdown 1-QycFXaIcXc9bb1tP6IIWrkcqu_IzcW9
# WORKDIR /opt/viskit/labels
# RUN gdown 1RVMP5bzjZraNnBjyIPoxroo9E9iM5Ips

FROM alpine:latest as app
WORKDIR /opt
RUN mkdir /opt/viskit
WORKDIR /opt/viskit
COPY --from=builder /opt/* /opt/viskit

# ./viskit_offline/viskit_offline "/opt/datasets/mnist.csv" "/opt/labels/mnist_label.txt" "/opt/graphs/mnist_cosine.bin" ./visualization.txt 2500 2 1 1 0 0 0 "force-directed"
# ./viskit_offline/viskit_offline "/opt/data/datasets/mnist.csv" "/opt/data/labels/mnist_label.txt" "/opt/data/graphs/mnist_cosine.bin" ./visualization.txt 200 2 1 1 0 0 0 "force-directed"
# tree -AC -L 3 -I 'CMake*|_deps|Testing|facade|lib*'
# mnist dataset gdown 1pwwzA45pajw3H2sxJI3H8RQ6mbzuicjz
# mnist_cosine graph gdown 1-QycFXaIcXc9bb1tP6IIWrkcqu_IzcW9
# /g/Studia/"Semestr VIII"/semestr-8/wizualizacja_duzych_zbiorow_danych/lab3
# docker container run -it --name viskit_trimmed_test -v /g/Studia/"Semestr VIII"/semestr-8/wizualizacja_duzych_zbiorow_danych/lab3:/opt/remote_vol viskit_trimmed
# singularity exec viskit_builder.sif /opt/viskit/viskit_offline/viskit_offline ./data/datasets/mnist.csv ./data/labels/mnist_label.txt ./data/graphs/mnist_cosine.bin ./visualization.txt 2500 2 1 1 0 0 0 force-directed
# singularity exec viskit_builder.sif    /opt/viskit/viskit_offline/viskit_offline ./data/datasets/mnist.csv ./data/labels/mnist_label.txt ./data/graphs/mnist_cosine.bin ./visualization_0.txt 100 2 1 1 0 0 0 force-directed
# singularity exec viskit_builder.sif    /opt/viskit/viskit_offline/viskit_offline ./data/datasets/mnist.csv ./data/labels/mnist_label.txt ./data/graphs/mnist_cosine.bin ./visualization_1.txt 300 2 1 True 0 0 0 force-directed
# singularity exec viskit_builder.sif    /opt/viskit/viskit_offline/viskit_offline ./data/datasets/mnist.csv ./data/labels/mnist_label.txt ./data/graphs/mnist_cosine.bin ./visualization_2.txt 2500 2 1 True 0 0 0 force-directed
