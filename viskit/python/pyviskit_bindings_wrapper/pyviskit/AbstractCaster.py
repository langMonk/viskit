import pandas as pd
import pyviskit_bindings as bindings
from pyviskit.constants import *


class AbstractCaster:
    def __init__(
        self,
        caster_type: bindings.CasterType,
        optimizer_type: bindings.OptimizerType,
        parser_type: bindings.ParserType = bindings.ParserType.Csv,
        graph_generator_type: bindings.GraphGeneratorType = bindings.GraphGeneratorType.Random,
        **kwargs,
    ):
        self.viskit = bindings.create_viskit()
        self.resource_factory = self.viskit.resourceFactory()
        self.particle_system = self.resource_factory.createParticleSystem()
        self.graph = self.resource_factory.createGraph()
        self.graph_helper = self.resource_factory.createGraph()
        self.caster_random = self.resource_factory.createCaster(
            bindings.CasterType.Random, bindings.OptimizerType.NONE
        )
        self.parser = self.resource_factory.createParser(parser_type)
        self.random_graph_generator = self.resource_factory.createGraphGenerator(
            graph_generator_type
        )
        self.caster = self.resource_factory.createCaster(caster_type, optimizer_type)
        if self.caster is None:
            raise NotImplementedError(
                f"Pair {caster_type} and {optimizer_type} is not supported. Check out library README to see which "
                f"combinations are supported"
            )

        self.additional_args = kwargs

    def get_arg_or_default(self, key):
        return self.additional_args.get(key, DEFAULTS[key])

    def fit_transform(
        self, dataset_file_path, labels_file_path, graph_file_path, output_file_path
    ):
        self.parser.loadFile(dataset_file_path, labels_file_path, self.particle_system)
        self.graph.loadNearestNeighborsFromCache(
            graph_file_path,
            self.get_arg_or_default(NEAREST_NEIGHBORS_COUNT),
            self.get_arg_or_default(BINARY_DISTANCES),
        )

        reverse_neighbors_count = self.get_arg_or_default(REVERSE_NEIGHBORS_COUNT)

        if reverse_neighbors_count > 0:
            self.graph_helper.loadNearestNeighborsFromCache(
                graph_file_path,
                reverse_neighbors_count,
                self.get_arg_or_default(BINARY_DISTANCES),
            )

        random_neighbors_count = self.get_arg_or_default(RANDOM_NEIGHBORS_COUNT)
        self.random_graph_generator.generate(
            self.particle_system,
            self.graph,
            random_neighbors_count,
            self.get_arg_or_default(BINARY_DISTANCES),
        )

        self.caster_random.calculatePositions(self.particle_system)
        self.caster.initialize(self.particle_system, self.graph)

        for _ in range(self.get_arg_or_default(ITERATIONS)):
            self.viskit.computeCastingStep(
                self.particle_system, self.graph, self.caster
            )

        if self.get_arg_or_default(REVERSE_NEIGHBORS_STEPS) > 0:
            reverse_graph_generator = self.resource_factory.createGraphGenerator(
                bindings.GraphGeneratorType.Reverse
            )
            reverse_graph_generator.generate(
                self.particle_system, self.graph, self.graph_helper
            )
            self.graph.removeRandomNeighbors()
            self.random_graph_generator.generate(
                self.particle_system,
                self.graph,
                self.graph_helper,
                random_neighbors_count,
                self.get_arg_or_default(BINARY_DISTANCES),
            )
            for i in range(self.get_arg_or_default(REVERSE_NEIGHBORS_STEPS)):
                self.viskit.computeCastingStep(
                    self.particle_system, self.graph, self.caster
                )

        self.caster.finalize()

        for _ in range(self.get_arg_or_default(L1_STEPS)):
            self.viskit.computeCastingSteps(
                self.particle_system, self.graph, self.caster
            )

        if output_file_path is not None:
            return self.particle_system.saveToFile(output_file_path, self.graph)
        else:
            data = zip(self.particle_system.positions(), self.particle_system.labels())
            positions = [(vec.x, vec.y, label) for vec, label in data]
            return pd.DataFrame(positions, columns=["x", "y", "class"])
