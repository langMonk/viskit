from pyviskit import IVHD, LargeVis, Random, TSNE, types
import matplotlib.pyplot as plt


def visualize(df, type):
    classes = [i for i in range(10)]

    for cls in classes:
        indices = df.loc[(df["class"] == cls)]
        plt.scatter(indices["x"], indices["y"], label=f"{cls}", s=10)

    plt.legend()
    print(f"Saving {type}")
    plt.savefig(f"results/{type}")
    plt.clf()


def invoke_fit_transform(caster, idx=None):
    output_file = None if idx is None else f"visualization{idx}.csv"
    return caster.fit_transform(
        "../mnist_data.csv",
        "../mnist_targets_2.csv",
        "../mnist_euclidean.bin",
        output_file,
    )


visualize(invoke_fit_transform(Random.Random(types.OptimizerType.NONE)), "RANDOM_NONE")
visualize(
    invoke_fit_transform(IVHD.IVHD(types.OptimizerType.Momentum)), "IVHD_MOMENTUM"
)
visualize(
    invoke_fit_transform(IVHD.IVHD(types.OptimizerType.ForceDirected)),
    "IVHD_FORCEDIRECTED",
)
visualize(
    invoke_fit_transform(IVHD.IVHD(types.OptimizerType.Adadelta)), "IVHD_Adadelta"
)
visualize(invoke_fit_transform(IVHD.IVHD(types.OptimizerType.Adam)), "IVHD_Adam")
visualize(
    invoke_fit_transform(IVHD.IVHD(types.OptimizerType.Nesterov)), "IVHD_Nesterov"
)
visualize(invoke_fit_transform(IVHD.IVHD(types.OptimizerType.tSNE)), "IVHD_tSNE")
visualize(
    invoke_fit_transform(LargeVis.LargeVis(types.OptimizerType.NONE)), "Largevis_None"
)
print("done")
