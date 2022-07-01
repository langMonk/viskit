# PYVISKIT

## Introduction
`pyviskit` library is a python interface for `viskit` library.

## Sample usage
Sample usage of `pyviskit` library was presented in `pyviskit_sample_usage` notebook. As for clarity, we're providing an example here:

```python
from pyviskit import types, IVHD
import pandas as pd
import matplotlib.pyplot as plt

optimizer = types.OptimizerType.ForceDirected
IVHD = IVHD.IVHD(optimizer)

# data
input_data = "../../mnist_data.csv"
labels = "../../mnist_targets_2.csv"
graph_file = "../../mnist_euclidean.bin"
output_file = "visualization.csv"

# fit transform
IVHD.fit_transform(input_data, labels, graph_file, output_file)

# plot data
df = pd.read_csv(output_file, header=None)
df.to_csv("to.csv",index=False,header=False)
for target in df[2].unique():
    indices_to_keep = df.loc[df[2] == target]
    plt.scatter(indices_to_keep[0], indices_to_keep[1], label=f"{target}", s=10)

plt.legend()
plt.show()
```

## Local installation
If you want to install `pyviskit` library locally, you need to know, what are you doing. If you've changed something in bindings, you need to also install `pyviskit_bindings`
library. To do so, go to the root directory of `viskit` project and type `python3 -m pip install .` (for Linux).

To install just `pyviskit` library, go to `viskit/viskit/python/pyviskit_bindings_wrapper` directory and type the same command (`python3 -m pip install .`).
It will install `pyviskit` locally in your environment.

## Available methods
As searching in someone's code isn't something you'd like to do in near future, we're presenting here list of methods that you can invoke.
To make things simpler, we've created wrapper for bindings, so we're showing methods with the division into packages that you can find them in.

### From pyviskit
To import library:
```python
import pyviskit
```

Available classes:
* `AbstractCaster` - if you want to create new one. Don't use it, as it's abstract. We're sure you know what that means.
* `IVHD` - `from pyviskit import IVHD` - see sample usage
* `Random` - `from pyviskit import Random`
* `LargeVis` - `from pyviskit import LargeVis`

Each of these casters take required parameter `optimizer_type` which is type of optimizer you want to use:
* NONE
* SGD
* ForceDirected
* Momentum
* Adadelta
* Adam
* Nesterov
* tSNE

| :memo:         Take note of this                                                                                                                                                       |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Not all optimizers will work with IVHD caster. Usage of NONE and SGD optimizers will change those optimizers to ForceDirected, as there's not such combination in `viskit` library yet |

Aside of that, caster in constructor can take:
* `parser type` - file paser type, default to `ParserType.Csv` (the only one available as for moment of writing this tutorial).
* `graph_generator_type` - with default to `GraphGeneratorType.Random` (to see other types, see documentation for pyviskit_bindings)

In form of `kwargs` (this thing that looks like `some_method(kwarg1=value1)`):
* iterations -  number of iterations to perform - default to 2500
* nearest_neighbors_count - count of nearest neighbors - default to 2
* random_neighbors_count - count of random neighbors to use - default to 1
* binary_distances - whether you want to use binary distances - default to `True`
* reverse_neighbors_steps - default to 0
* reverse_neighbors_count - default to 0
* l1_steps - default to 0

| :exclamation:         Be careful                                                                                                                    |
|-----------------------------------------------------------------------------------------------------------------------------------------------------|
| Make sure to know what you're doing while changing this parameters. As it's Python code, there's no type checking, so you can really hurt yourself. |


Then, to obtain results you can invoke `fit_transform` method, that takes four arguments:
* `dataset_file_path` - path to file with dataset
* `labels_file_path` - path to file with labels for data
* `graph_file_path` - path to file with generated graph
* `output_file_path` - path to file with performed visualization

If you want to take advantage of some low-level methods, you can import `pyviskit_bindings` library (needed to install `pyviskit` library)
or use `from pyviskit import types` - it will also allow you to use more low-level methods.

### pyviskit_bindings
As the list of bound structures, enums, classes and methods is long, we're presenting it at the end of this file.


## Contributing
Project is divided in two parts: if you change something in `c++` side, make sure it doesn't change API. In case it does - you need to update bindings
to be up-to-date. You can find bindings code in `viskit/viskit/python/bindings`. Here are some scenarios of what could you do in `c++` code and what you need to do then:

### Adding new Caster
Congratulations. It's probably the easiest one, so you don't have to worry much about it. What you need to do in order to make it work on Python side:
* Add new binding for your caster in file `viskit/viskit/python.bindings/PyFacadeCasterBinding.cpp`. You can do this by copy-pasting one of existing casters bindings
and changing: first and second argument of py::class_ template, changing name of Python class and changing addresses of functions. Sounds rough? Here's an example for, let's say `UMAP` caster:
```c++
py::class_<viskit::facade::FacadeCasterUMAP, std::shared_ptr<viskit::facade::FacadeCasterUMAP>, viskit::facade::FacadeCaster>(m, "FacadeCasterUMAP")
        .def(py::init<const std::shared_ptr<core::Core>&>())
        .def("calculatePositions", &viskit::facade::FacadeCasterUMAP::calculatePositions)
        .def("calculateForces", &viskit::facade::FacadeCasterUMAP::calculateForces)
        .def("type", &viskit::facade::FacadeCasterUMAP::type)
        .def("optimizerType", &viskit::facade::FacadeCasterUMAP::optimizerType)
        .def("step", &viskit::facade::FacadeCasterUMAP::step)
        .def("initialize", &viskit::facade::FacadeCasterUMAP::initialize)
        .def("finalize", &viskit::facade::FacadeCasterUMAP::finalize);
```

You also needed to add new `CasterType` field in enum. Don't forget to add this new kind in `py::enum` in `viskit/viskit/python/bindings/PyStructuresBinding.h` file. Example:
```c++
py::enum_<viskit::CasterType>(m, "CasterType")
        .value("IVHD", viskit::CasterType::IVHD)
        .value("LargeVis", viskit::CasterType::LargeVis)
        .value("tSNE", viskit::CasterType::tSNE)
        .value("Random", viskit::CasterType::Random)
        // added line
        .value("UMAP", viskit::CasterType::UMAP)
        .export_values();
```

Then you need to only reinstall library and everything _SHOULD_ work on bindings side.

Don't forget to update `pyviskit` wrapper. In `viskit/viskit/python/pyviskit_bindings_wrapper/pyviskit` you should create file `UMAP.py`, copy-paste code from `IVHD.py` and change it a little:
```python
import pyviskit_bindings as bindings
from pyviskit.AbstractCaster import AbstractCaster


class UMAP(AbstractCaster):
    def __init__(self,
                 optimizer_type: bindings.OptimizerType,
                 parser_type: bindings.ParserType = bindings.ParserType.Csv,
                 graph_generator_type: bindings.GraphGeneratorType = bindings.GraphGeneratorType.Random,
                 **kwargs
                 ):
        super().__init__(bindings.CasterType.UMAP, optimizer_type, parser_type, graph_generator_type, **kwargs)

    # TODO - maybe it would be better to read dataset and labels in form of dataframes and write it to files ourselves??
    def fit_transform(self, dataset_file_path, labels_file_path, graph_file_path, output_file_path=None):
        return super().fit_transform(dataset_file_path, labels_file_path, graph_file_path, output_file_path)
```
| :memo:         Take note of this                                                      |
|---------------------------------------------------------------------------------------|
| Notice that we only changed class name and caster type in invoking `super().__init__` |


### Adding new method for virtual class
Ok, that's more complicated. You need to make sure, that this method has trampoline in binding class and all its virtual descendants
(e.g. if you added virtual method in `ITransformer`, you need to add trampoline not only to this class, but also to `ICaster` and `FacadeCaster`,
as all those classes are virtual and need a trampoline). Pybind11 shows that there's a method for not doing that, but we decided not to use it
as it was too complicated for such few methods. We've also left some comments on existing trampolines, so you'll know what to do, when adding new one.
After doing that, you need to add method by calling `.def()` on each `FacadeCaster*`, so Pybind11 will know that you want to expose this method.

### Changes that made new files in bindings directory
So... that's a big one, right? You've added new files in bindings directory with maybe new class bound. Don't forget everything that you've learned (and copied) so far,
check out also our (insights on working with pybind)[#Pybind11-tricks]. Anyway, here's something you won't hear anywhere other:
* if you've added `.h` file, you need to add it to `viskit/viskit/python/CMakeLists.txt`'s `PYVISKIT_HEADERS` variable.
* if you've added `.cpp` file, you need to add it to `viskit/viskit/python/CMakeLists.txt`'s `PYVISKIT_SRC` variable.
* most probably you have `static void bind` function with all your binding code. The thing is... it won't work until you invoke it in `viskit/viskit/python/module_binder.cpp` file.

### Changes in pyviskit wrapper
That's a bit easier, as you won't write any line in c++. Let's say that you want to add some function or something like that. Nothing easier than that.
The only thing you need to do is to add this function (please, don't destroy anything by accident or not) and then test it locally (you don't have to reinstall
`pyviskit_bindings` library if your changes were only in wrapper).

And we think that's it. Happy contributing! 

P.S. Don't forget to bump version of libraries each time you push it to pip!

### Pybind11 tricks
Some insights of our work, that may spare you lots of debugging:
* If your function returns smart pointer, make sure to change default holder of bound class, e.g.:
```c++
py::class_<viskit::ICaster, std::shared_ptr<viskit::ICaster>, viskit::ITransformer, python::bindings::PyCasterBinding>(m, "ICaster")
```
* If you need to overload methods, it's possible by using this line of code:
```c++
//   |method name|            |returned type|       |from which class|          |parameter types|                   |address of method|
.def("saveToFile", static_cast<bool (viskit::facade::FacadeParticleSystem::*)(const std::string&, IGraph&)>(&viskit::facade::FacadeParticleSystem::saveToFile));
```
* Binding virtual classes - it's possible, but in order for them to be usable (and extendable) from Python, you need to add trampoline class - (more about them here)[https://pybind11.readthedocs.io/en/stable/advanced/classes.html#overriding-virtual-functions-in-python].
An example of trampoline classes can be found in `viskit/viskit/python/bindings/PyFacadeCasterBinding.cpp`. Also note, that if you have multiple virtual classes in 
inheritance tree, you need to create trampoline method for ALL virtual functions (for example `FacadeCaster` inherits from `ICaster` which inherits from `ITransformer`)
so `FacadeCaster` needs to "bounce" all methods from `ICaster` and `ITransformer` classes. 
* When you add child classes for virtual classes, you need to define methods for them (even though documentation won't say anything about it) - for example see `viskit/viskit/python/bindings/PyFacadeCasterBinding.cpp`
* Virtual classes also should have constructors - if you won't add them, you won't be able to extend them in Python.
* Most segfaults we've dealt with was originated from either wrong holder type (first dot here) or not callable functions. Second problem is still not solved but you can see example of it
by creating viskit with lambda representing logger (e.g. `create_viskit(lambda x,y: print(x))`).
* Sometimes, when you're creating trampoline, type you want to return from method is too complex. Use typealias instead (e.g. `viskit/viskit/python/bindings/PyInteractiveVisualizationBinding.cpp#calculateBoundingBox`).

## Pyviskit bindings
### Enums
#### CasterType
* IVHD
* LargeVis
* tSNE
* Random

#### NeighborsType
* Near
* Far
* Random
* Reverse
* ToRemove

#### OptimizerType
* NONE
* SGD
* ForceDirected
* Momentum
* Adadelta
* Adam
* Nesterov
* tSNE

#### ParserType
* Csv

#### GraphGeneratorType
* BruteForce
* KDTreeBased
* Random
* Faiss
* Reverse

#### MetricType
* Euclidean
* Cosine

#### LogLevel
* Debug
* Info
* Warning
* Error

### Structures
#### DatasetInfo
* empty constructor
* path
* fileName
* count
* dimensionality

#### Neighbors
* empty constructor
* constructor with two `size_t` variables
* constructor with two `size_t` variables, float and `NeighborsType` enum value
* i
* j
* type

#### NeighborsCounter
* empty constructor
* nearestNeighbors
* reverseNeighbors
* randomNeighbors

#### DataPoint
* constructor with size_t
* constructor with vector of floats
* constructor with vector of floats and int
* size method
* getId method
* m_currentId read-only field

### Caster Class
#### ICaster
Interface implemented by `FacadeCaster`. Methods:
* empty constructor (to be used as parent class of python class)
* calculatePositions
* calculateForces
* type - getter
* optimizerType - getter

### FacadeCaster Class
Interface implemented by `FacadeCaster*` classes. Children:
* FacadeCasterRandom
* FacadeCasterAdadelta
* FacadeCasterAdam
* FacadeCasterForceDirected
* FacadeCasterLargeVis
* FacadeCasterMomentum
* FacadeCasterNesterov
* FacadeCasterSGD
* FacadeCasterTSNE

Methods:
* step
* initialize
* finalize

Methods in `FacadeCaster*` classes (inherited from ICaster and ITransformer):
* calculatePositions(IParticleSystem) -> None
* calculateForces(IParticleSystem, IGraph) -> None
* type() -> CasterType
* optimizerType() -> OptimizerType
* step(IParticleSystem, IGraph) -> None
* initialize(IParticleSystem, IGraph) -> None
* finalize() -> None

### Graph
Interface - IGraph. Children:
* FacadeGraph

Methods:
* initialize(size: int) -> None
* getNeighbors(index: int) -> list[Neighbors]
* addNeighbors(list[Neighbors]) -> None
* addNeighbors(Neighbors) -> None
* neighborsCounter() -> NeighborsCounter
* overallNeighborsCount() -> int
* size() -> int
* sort() -> None
* saveNearestNeighborsToCache(fileName: str) -> bool
* removeRandomNeighbors() -> None
* loadNearestNeighborsFromCache(fileName: string, nearestNeighborsCountToRead: int, binaryDistances: bool) -> bool
* dump(filePath: string, fileName: string) -> void

### GraphGenerator
Interface - IGraph. Children:
* FacadeGraphGenerator
* FacadeGraphGeneratorRandom
* FacadeGraphGeneratorBruteForce
* FacadeGraphGeneratorKDTree
* FacadeGraphGeneratorReverse

Methods:
* generate(IParticleSystem, IGraph, k: int, distancesEqualOne: bool) -> None
* generate(IParticleSystem, IGraph, graphHelper: IGraph) -> None
* generate(IParticleSystem, IGraph, graphHelper: IGraph, k: int, distancesEqualOne: bool) -> None

### InteractiveVisualization
Interface - IInteractiveVisualization. Children:
* FacadeInteractiveVisualization

Methods:
* resourceFactory() -> IResourceFactory
* computeCastingStep(IParticleSystem, IGraph, ICaster) -> None
* calculateBoundingBox() -> list[tuple(int, int)]

Also in this binding but not as member is method `create_viskit` that will create `FacadeInteractiveVisualization`.

### Parser
Interface - IParser. Children:
* FacadeParserCSV

Methods:
* loadFile(datasetFilePath: string, labelsFilePath: string, IParticleSystem) -> None

### ParticleSystem
Interface - IParticleSystem. Children:
* FacadeParticleSystem

Methods:
* dataset() -> DatasetInfo
* originalCoordinates() -> list[tuple(DataPoint, int)]
* labels() -> list[int]
* setPosition(index: int, x: float, y: float) -> None
* countAlive() -> int
* countParticles() -> int
* clear() -> None
* empty() -> bool
* saveToFile(fileName: string) -> bool
* saveToFile(fileName: string, IGraph) -> bool

### ResourceFactory
Interface: IResourceFactory. Children:
* FacadeResourceFactory

Methods:
* createParser(ParserType) -> IParser
* createGraphGenerator(GraphGeneratorType) -> IGraphGenerator
* createCaster(CasterType, OptimizerType) -> ICaster
* createParticleSystem() -> IParticleSystem
* createGraph() -> IGraph

### ITransformer
Interface only to be extended on Python side. It isn't using anywhere else, but here are its methods:
* initialize(IParticleSystem, IGraph) -> None
* finalize() -> None
* step(IParticleSystem, IGraph) -> None