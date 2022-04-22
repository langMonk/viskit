# VisKit
This repository contains a library (and method) for Interactive Visualization of High-Dimensional Data (IVHD). 
The main purpose of this library is to provide a framework for rapid development and testing of new data embedding (DE) 
and data visualization (DV) methods.


### Setup and installation
Download the repository. Easiest way to set everything up is by using `CLion`, which operates on `cmake` projects formats.
You should be able to open the project with `CLion` automatically. Then, it's necessary to initialize projects dependencies. 
Use following commands (which will set up glm in your `/libraries` folder):
```shell
git submodule init
git submodule update
```
After submodule initialization - you should be able to your build VisKit project. You can do this in two ways: 
- in `CLion` by simply clicking build solution/project, 
- manually, by using `cmake` and `make` commands:
    ```shell
    # Assuming you are currently in main folder of your repository
    cmake ./CMakeLists.txt
    make
    ```

### Notes: 
- You could also use `make install` which would install `VisKit` headers and binaries into your `/local/bin` and `/local/include` folders, 
but I am not 100% sure it works properly, so... On your own risk.

- Also, not sure how compilation works on Windows. For last 2-3 years this library was used only on Linux/MacOS.

### Usage
Easiest way to use VisKit is through Python interface (`/python` folder). It contains a wrapper for `viskit_offline` binary.
You can also use `viskit_offline` directly. Just compile whole project with cmake and run it from `command-line.`

```shell
Example usage:
viskit_offline "./datasets/mnist_data.csv" "./labels/mnist_labels.csv" "./graphs/mnist.bin" ./visualization.txt 2500 2 1 1 0 0 0 "force-directed"
viskit_offline "./datasets/mnist_data.csv" "./labels/mnist_labels.csv" "./graphs/mnist.bin" ./visualization.txt
```


### Python 

Main python script is located in `/python/viskit.py` and the wrapper for IVHD method is located in `/python/viskit/embedding/ivhd.py`. 
There are appropriate config files (config.ini) utilized by `ivhd.py`, which specify locations for temp files generated 
while using algorithm (e.g. temporary input file generated from python, temporary labels file, temporary file with graph, 
which will be generated, if none graph will be provided as input).

```shell
[Paths]
BinaryPath = {your_viskit_repository_path}/cmake-build-release/viskit_offline/viskit_offline
InputDatasetPath = {your_viskit_repository_path}/python/viskit/input_data.csv
InputLabelsPath = {your_viskit_repository_path}/python/viskit/input_labels.csv
OutputPath = {your_viskit_repository_path}/python/viskit/output.csv
GraphPath = {your_viskit_repository_path}/python/graphs/output.bin
```

### Current methods and optimizers

VisKit currently contains IVHD, LargeVis and t-SNE modified with possibility to use distances instead of probabilities.
Also, there multiple optimizers, that can be used by IVHD method:
- adadelta,
- adam,
- force-directed (default),
- momentum,
- nesterov,
- sgd (in doing),

There is also a random caster, which assigns random positions in 2-D space.


### License and credits
Whole VisKit is 3-clause BSD licensed.
- t-SNE: https://lvdmaaten.github.io
- LargeVis: https://github.com/lferry007/LargeVis
- UMAP: https://umap-learn.readthedocs.io/en/latest/
- HUMAP: https://github.com/wilsonjr/humap


### Contributions
Contributions are more than welcome! There are lots of opportunities for potential projects, so please get in touch if you would like to help out.