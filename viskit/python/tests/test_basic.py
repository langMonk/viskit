import pyviskit_bindings as viskit


def test_assert_version():
    assert viskit.__version__ == "0.0.1"


def test_resource_creation():
    def handler(level: viskit.LogLevel, message: str):
        if level == viskit.LogLevel.Info:
            print("[Info]: {0}".format(message))

    print("creating viskit...")
    viskit_engine = viskit.create_viskit(handler)
    assert type(viskit_engine) == viskit.FacadeInteractiveVisualization

    print("creating parser...")
    parser = viskit_engine.resourceFactory().createParser(viskit.ParserType.Csv)
    assert type(parser) == viskit.FacadeParserCSV

    print("creating particle system...")
    particle_system = viskit_engine.resourceFactory().createParticleSystem()
    assert type(particle_system) == viskit.FacadeParticleSystem

    print("creating graph...")
    graph = viskit_engine.resourceFactory().createGraph()
    assert type(graph) == viskit.FacadeGraph

    print("creating random graph generator...")
    random_graph_generator = viskit_engine.resourceFactory().createGraphGenerator(
        viskit.GraphGeneratorType.Random
    )
    assert type(random_graph_generator) == viskit.FacadeGraphGeneratorRandom

    # print("creating caster...")
    # caster = viskit_engine.resourceFactory().createCaster(viskit.CasterType.IVHD, viskit.OptimizerType.ForceDirected)
    # assert type(caster) == viskit.FacadeCasterForceDirected
    #
    # print("creating caster random...")
    # caster_random = viskit_engine.resourceFactory().createCaster(
    #     viskit.CasterType.Random, viskit.OptimizerType.NONE
    # )
    # assert type(caster_random) == viskit.FacadeCasterRandom

