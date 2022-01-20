import pandas as pd

from viskit.ivhd import IVHD
from pylab import *

from sklearn.manifold import TSNE
from umap import UMAP
from viskit.metrics import MetricCalculator


def draw_2d(X, Y, labels, ax):
    unique = list(set(labels))
    colors = [plt.cm.jet(float(i) / max(unique)) for i in unique]

    for i, u in enumerate(unique):
        xi = [X[j] for j in range(len(X)) if labels[j] == u]
        yi = [Y[j] for j in range(len(X)) if labels[j] == u]
        if len(ax) < 1:
            plt.scatter(xi, yi, color=colors[i], label=str(u), s=2)
        else:
            ax.scatter(xi, yi, color=colors[i], label=str(u), s=2)


def set_dataframe_columns(dataframe: pd.DataFrame) -> None:
    # set up dataset columns id
    columns = []
    for i in range(0, dataframe.shape[1] - 1):
        columns.append("col{}".format(i))
    columns.append("label")
    dataframe.columns = columns


def main():
    dataset_files = [
        # "/home/bminch/Repositories/centroids/output/mnist_70k_pca30_50_2_all.csv",
        "/Users/bartoszminch/Documents/Repositories/dataset_viskit/mnist.csv",
        # "/home/bminch/Repositories/dataset_viskit/mnist_7k.csv",
        # "/home/bminch/Repositories/dataset_viskit/mnist_7k.csv"
    ]

    methods = [
        {
            "name": "IVHD - force directed",
            "object": IVHD(
                optimizer="force-directed",
                n_iter=1000,
                nn=2,
                rn=1,
                l1_steps=50,
                reverse_neighbors_steps=500,
                graph_path="/Users/bartoszminch/Documents/Repositories/viskit/python/graphs/mnist_cosine.bin",
            ),
        },
        # {"name": "UMAP", "object": UMAP()},
        # {"name": "t-SNE (distance variant)", "object": IVHD(optimizer="tsne", nn=5)},
        # {"name": "bh t-SNE", "object": TSNE(n_components=2, n_iter=2000)},
    ]

    v = 0
    metrics = MetricCalculator()
    for dataset in dataset_files:
        dataset_name = dataset.split("/")[-1]
        X = pd.read_csv(dataset, delimiter=",", header=None, index_col=False)
        set_dataframe_columns(X)

        labels = X["label"]
        X = X.drop(labels=["label"], axis=1)

        fig = plt.figure()

        fig.set_figheight(16)
        fig.set_figwidth(16)
        ax = []

        if len(methods) > 1:
            for method in methods:
                v = v + 1
                ax = subplot(int(len(methods) / 2), 2, v)
                ax.set_title("{} \n {}".format(dataset_name, method["name"]))

                # fit_transform of specific method
                X_embedded = method["object"].fit_transform(X)

                # draw 2d representation of the method
                draw_2d(X_embedded[:, 0], X_embedded[:, 1], labels, ax)

                # calculate metrics
                metrics.calculate(
                    X_lds=X_embedded,
                    X_hds=X.values,
                    labels=labels.values,
                    method_name="{} {}".format(dataset_name, method["name"]),
                )
        else:
            for method in methods:
                X_embedded = method["object"].fit_transform(X)
                draw_2d(X_embedded[:, 0], X_embedded[:, 1], labels, ax)

        if len(ax) != 0:
            handles, legend_labels = ax.get_legend_handles_labels()
            fig.legend(labels=legend_labels, markerscale=8.0, loc="right", fontsize=20)
        plt.show()
        v = 0

    if len(methods) > 1:
        metrics.visualize()


if __name__ == "__main__":
    main()
