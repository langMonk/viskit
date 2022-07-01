import pyviskit_bindings

DATASET_FILE_PATH = "./mnist_data.csv"
LABELS_FILE_PATH = "./mnist_targets_2.csv"
GRAPH_FILE_PATH = "./mnist_euclidean.bin"
OUTPUT_FILE_PATH = "./visualization.txt"

ITERATIONS = 2500
NEAREST_NEIGHBORS_COUNT = 2
RANDOM_NEIGHBORS_COUNT = 1
BINARY_DISTANCES = True
REVERSE_NEIGHBORS_STEPS = 0
REVERSE_NEIGHBORS_COUNT = 0
L1_STEPS = 0
CASTER_NAME = "force-directed"


def perform_visualization(
        dataset_file_path,
        labels_file_path,
        graph_file_path,
        output_file_path,
        iterations,
        nearest_neighbors_count,
        random_neighbors_count,
        binary_distances,
        reverse_neighbors_steps,
        reverse_neighbors_count,
        l1_steps,
        caster_type,
        optimizer_type
):
    print("creating viskit...")
    viskit = pyviskit_bindings.create_viskit()
    resource_factory = viskit.resourceFactory()
    print("creating parser...")
    parser = resource_factory.createParser(pyviskit_bindings.ParserType.Csv)
    print("creating particle system...")
    particle_system = resource_factory.createParticleSystem()
    print("creating graph...")
    graph = resource_factory.createGraph()
    print("creating graph_helper...")
    graph_helper = resource_factory.createGraph()
    print("creating random graph generator...")
    random_graph_generator = resource_factory.createGraphGenerator(pyviskit_bindings.GraphGeneratorType.Random)
    print("creating caster...")
    caster = resource_factory.createCaster(caster_type, optimizer_type)
    print("creating caster random...")
    caster_random = resource_factory.createCaster(pyviskit_bindings.CasterType.Random, pyviskit_bindings.OptimizerType.NONE)

    print("loading file...")
    parser.loadFile(dataset_file_path, labels_file_path, particle_system)
    print("loading nearest neighbors from cache...")
    graph.loadNearestNeighborsFromCache(graph_file_path, nearest_neighbors_count, binary_distances)

    if reverse_neighbors_count > 0:
        graph_helper.loadNearestNeighborsFromCache(graph_file_path, reverse_neighbors_count, binary_distances)

    print("generating random graph...")
    random_graph_generator.generate(particle_system, graph, random_neighbors_count, binary_distances)
    print("calculating positions...")
    caster_random.calculatePositions(particle_system)

    print("initializing caster...")
    caster.initialize(particle_system, graph)

    print(f"computing casting steps: {iterations}")
    for i in range(iterations):
        print(f"computation {i}")
        viskit.computeCastingStep(particle_system, graph, caster)

    if reverse_neighbors_steps > 0:
        reverse_graph_generator = resource_factory.createGraphGenerator(pyviskit_bindings.GraphGeneratorType.Reverse)
        reverse_graph_generator.generate(particle_system, graph, graph_helper)
        graph.removeRandomNeighbors()
        random_graph_generator.generate(particle_system, graph, graph_helper, random_neighbors_count, binary_distances)
        for i in range(reverse_neighbors_steps):
            viskit.computeCastingStep(particle_system, graph, caster)

    print("finalizing caster")
    caster.finalize()

    print(f"computing steps in l1 phase: {l1_steps}")
    for i in range(l1_steps):
        viskit.computeCastingStep(particle_system, graph, caster)

    print("saving results to file")
    particle_system.saveToFile(output_file_path, graph)

    print("done")


if __name__ == "__main__":
    caster_type = pyviskit_bindings.CasterType.IVHD
    optimizer_type = pyviskit_bindings.OptimizerType.NONE
    if CASTER_NAME == "force-directed":
        optimizer_type = pyviskit_bindings.OptimizerType.ForceDirected

    perform_visualization(
        DATASET_FILE_PATH,
        LABELS_FILE_PATH,
        GRAPH_FILE_PATH,
        OUTPUT_FILE_PATH,
        ITERATIONS,
        NEAREST_NEIGHBORS_COUNT,
        RANDOM_NEIGHBORS_COUNT,
        BINARY_DISTANCES,
        REVERSE_NEIGHBORS_STEPS,
        REVERSE_NEIGHBORS_COUNT,
        L1_STEPS,
        caster_type,
        optimizer_type
    )

    perform_visualization(
        DATASET_FILE_PATH,
        LABELS_FILE_PATH,
        GRAPH_FILE_PATH,
        "./visualization2.txt",
        ITERATIONS,
        NEAREST_NEIGHBORS_COUNT,
        RANDOM_NEIGHBORS_COUNT,
        BINARY_DISTANCES,
        REVERSE_NEIGHBORS_STEPS,
        REVERSE_NEIGHBORS_COUNT,
        L1_STEPS,
        caster_type,
        optimizer_type
    )
