import pyviskit_bindings as viskit

DATASET_FILE_PATH = (
    "/Users/bartoszminch/Documents/Repositories/dataset_viskit/datasets/mnist_data.csv"
)
LABELS_FILE_PATH = "/Users/bartoszminch/Documents/Repositories/dataset_viskit/datasets/mnist_labels.csv"
GRAPH_FILE_PATH = "/Users/bartoszminch/Documents/Repositories/dataset_viskit/graphs/mnist_euclidean.bin"
OUTPUT_FILE_PATH = "./visualization.txt"

ITERATIONS = 1000
NEAREST_NEIGHBORS_COUNT = 2
RANDOM_NEIGHBORS_COUNT = 1
BINARY_DISTANCES = True
REVERSE_NEIGHBORS_STEPS = 0
REVERSE_NEIGHBORS_COUNT = 0
L1_STEPS = 0
CASTER_NAME = "force-directed"


def handler(level: viskit.LogLevel, message: str):
    if level == viskit.LogLevel.Info:
        print("[Info]: {0}".format(message))


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
        optimizer_type,
):
    print("creating viskit...")
    viskit_engine = viskit.create_viskit()

    print("creating parser...")
    parser = viskit_engine.resourceFactory().createParser(viskit.ParserType.Csv)

    print("creating particle system...")
    particle_system = viskit_engine.resourceFactory().createParticleSystem()

    print("creating graph...")
    graph = viskit_engine.resourceFactory().createGraph()

    print("creating graph_helper...")
    graph_helper = viskit_engine.resourceFactory().createGraph()

    print("creating random graph generator...")
    random_graph_generator = viskit_engine.resourceFactory().createGraphGenerator(
        viskit.GraphGeneratorType.Random
    )

    print("creating caster...")
    caster = viskit_engine.resourceFactory().createCaster(caster_type, optimizer_type)

    # print("creating caster random...")
    # caster_random = viskit_engine.resourceFactory().createCaster(
    #     viskit.CasterType.Random, viskit.OptimizerType.NONE
    # )

    print("loading file...")
    parser.loadFile(dataset_file_path, labels_file_path, particle_system)

    print("loading nearest neighbors from cache...")
    graph.loadNearestNeighborsFromCache(
        graph_file_path, nearest_neighbors_count, binary_distances
    )

    if reverse_neighbors_count > 0:
        graph_helper.loadNearestNeighborsFromCache(
            graph_file_path, reverse_neighbors_count, binary_distances
        )

    print("generating random graph...")
    random_graph_generator.generate(
        particle_system, graph, random_neighbors_count, binary_distances
    )
    # print("calculating positions...")
    # caster_random.calculatePositions(particle_system)

    print("initializing caster...")
    caster.initialize(particle_system, graph)

    print(f"computing casting steps: {iterations}")
    for i in range(iterations):
        print(f"computation {i}")
        viskit_engine.computeCastingStep(particle_system, graph, caster)

    if reverse_neighbors_steps > 0:
        reverse_graph_generator = viskit_engine.resourceFactory().createGraphGenerator(
            viskit.GraphGeneratorType.Reverse
        )
        reverse_graph_generator.generate(particle_system, graph, graph_helper)
        graph.removeRandomNeighbors()
        random_graph_generator.generate(
            particle_system,
            graph,
            graph_helper,
            random_neighbors_count,
            binary_distances,
        )
        for i in range(reverse_neighbors_steps):
            viskit_engine.computeCastingStep(particle_system, graph, caster)

    print("finalizing caster")
    caster.finalize()

    print(f"computing steps in l1 phase: {l1_steps}")
    for i in range(l1_steps):
        viskit_engine.computeCastingStep(particle_system, graph, caster)

    print("saving results to file")
    particle_system.saveToFile(output_file_path)

    print("done")


if __name__ == "__main__":
    caster_type = viskit.CasterType.IVHD
    optimizer_type = viskit.OptimizerType.NONE
    if CASTER_NAME == "force-directed":
        optimizer_type = viskit.OptimizerType.ForceDirected

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
        optimizer_type,
    )

    # perform_visualization(
    #     DATASET_FILE_PATH,
    #     LABELS_FILE_PATH,
    #     GRAPH_FILE_PATH,
    #     "./visualization2.txt",
    #     ITERATIONS,
    #     NEAREST_NEIGHBORS_COUNT,
    #     RANDOM_NEIGHBORS_COUNT,
    #     BINARY_DISTANCES,
    #     REVERSE_NEIGHBORS_STEPS,
    #     REVERSE_NEIGHBORS_COUNT,
    #     L1_STEPS,
    #     caster_type,
    #     optimizer_type,
    # )
