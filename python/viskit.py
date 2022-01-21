import configparser
import os
import pandas as pd

from viskit.embedding.ivhd import IVHD
from pylab import *

from viskit.metrics.local_score import LocalMetrics


def draw_2d(X, Y, labels):
    unique = list(set(labels))
    colors = [plt.cm.jet(float(i) / max(unique)) for i in unique]

    for i, u in enumerate(unique):
        xi = [X[j] for j in range(len(X)) if labels[j] == u]
        yi = [Y[j] for j in range(len(X)) if labels[j] == u]
        plt.scatter(xi, yi, color=colors[i], label=str(u), s=2)


def format_title(dataset_name: str, method) -> str:
    if method["name"] != "IVHD":
        generated_title = "{}_{}".format(dataset_name, method["name"])
    else:
        ivhd = method["object"]
        generated_title = "{}_{}_opt={}_iter={}_nn={}_rn={}_l1steps={}_reverse_neighbors_steps={}_reverse_neighbors_count={}".format(
            dataset_name,
            method["name"],
            ivhd.optimizer,
            ivhd.n_iter,
            ivhd.nn,
            ivhd.rn,
            ivhd.l1_steps,
            ivhd.reverse_neighbors_steps,
            ivhd.reverse_neighbors_count,
        )
    return generated_title


def set_dataframe_columns(dataframe: pd.DataFrame) -> None:
    # set up dataset columns id
    columns = []
    for i in range(0, dataframe.shape[1] - 1):
        columns.append("col{}".format(i))
    columns.append("label")
    dataframe.columns = columns


def main():
    config = configparser.ConfigParser()
    script_path = os.path.dirname(__file__)
    config.read(script_path + "/config.ini")

    logging.basicConfig(level=logging.INFO, filename=config["Paths"]["LogsPath"])

    dataset_files = [
        # "/home/bminch/Repositories/centroids/output/mnist_70k_pca30_50_2_all.csv",
        # "/Users/bartoszminch/Documents/Repositories/dataset_viskit/mnist.csv",
        "/Users/bartoszminch/Documents/Repositories/viskit/python/viskit/graph_generation/mnist_pca_100.csv",
        # "/home/bminch/Repositories/dataset_viskit/mnist_7k.csv",
        # "/home/bminch/Repositories/dataset_viskit/mnist_7k.csv"
    ]

    USE_METRICS = False

    methods = [
        {
            "name": "IVHD",
            "object": IVHD(
                optimizer="force-directed",
                n_iter=1000,
                nn=2,
                rn=1,
                l1_steps=0,
                reverse_neighbors_steps=0,
                reverse_neighbors_count=0,
                graph_path="/Users/bartoszminch/Documents/Repositories/viskit/python/graphs/mnist_pca_100.bin",
            ),
        },
        {
            "name": "IVHD",
            "object": IVHD(
                optimizer="force-directed",
                n_iter=1000,
                nn=2,
                rn=1,
                l1_steps=0,
                reverse_neighbors_steps=500,
                reverse_neighbors_count=3,
                graph_path="/Users/bartoszminch/Documents/Repositories/viskit/python/graphs/mnist_pca_100.bin",
            ),
        },
        {
            "name": "IVHD - force directed",
            "object": IVHD(
                optimizer="force-directed",
                n_iter=1000,
                nn=2,
                rn=1,
                l1_steps=0,
                reverse_neighbors_steps=500,
                reverse_neighbors_count=4,
                graph_path="/Users/bartoszminch/Documents/Repositories/viskit/python/graphs/mnist_pca_100.bin",
            ),
        },
        {
            "name": "IVHD - force directed",
            "object": IVHD(
                optimizer="force-directed",
                n_iter=1000,
                nn=2,
                rn=1,
                l1_steps=0,
                reverse_neighbors_steps=500,
                reverse_neighbors_count=6,
                graph_path="/Users/bartoszminch/Documents/Repositories/viskit/python/graphs/mnist_pca_100.bin",
            ),
        },
        {
            "name": "IVHD - force directed",
            "object": IVHD(
                optimizer="force-directed",
                n_iter=1000,
                nn=2,
                rn=1,
                l1_steps=0,
                reverse_neighbors_steps=500,
                reverse_neighbors_count=8,
                graph_path="/Users/bartoszminch/Documents/Repositories/viskit/python/graphs/mnist_pca_100.bin",
            ),
        },
        {
            "name": "IVHD - force directed",
            "object": IVHD(
                optimizer="force-directed",
                n_iter=1000,
                nn=2,
                rn=1,
                l1_steps=0,
                reverse_neighbors_steps=500,
                reverse_neighbors_count=10,
                graph_path="/Users/bartoszminch/Documents/Repositories/viskit/python/graphs/mnist_pca_100.bin",
            ),
        },
        # {"name": "UMAP", "object": UMAP()},
        # {"name": "t-SNE (distance variant)", "object": IVHD(optimizer="tsne", nn=5)},
        # {"name": "bh t-SNE", "object": TSNE(n_components=2, n_iter=2000)},
    ]

    if not os.path.exists("results"):
        os.makedirs("results")
    os.chdir("results")

    if USE_METRICS:
        metrics = LocalMetrics()

    for dataset in dataset_files:
        dataset_name = dataset.split("/")[-1].strip(".csv")

        if not os.path.exists(dataset_name):
            os.makedirs(dataset_name)
        os.chdir(dataset_name)

        X = pd.read_csv(dataset, delimiter=",", header=None, index_col=False)
        set_dataframe_columns(X)

        labels = X["label"]
        X = X.drop(labels=["label"], axis=1)

        created = False
        for method in methods:
            if not created and not os.path.exists(method["name"]):
                os.makedirs(method["name"])
            if not created:
                os.chdir(method["name"])
            created = True

            fig, ax = plt.subplots()
            fig.set_figheight(16)
            fig.set_figwidth(16)
            fig.patch.set_visible(False)
            ax.axis("off")

            fig.suptitle(
                format_title(dataset_name=dataset_name, method=method).replace(
                    "_l1steps", "\nl1steps"
                ),
                fontsize=20,
            )

            X_embedded = method["object"].fit_transform(X)
            draw_2d(X_embedded[:, 0], X_embedded[:, 1], labels)

            fig.legend(labels=labels, markerscale=8.0, loc="right", fontsize=20)

            if USE_METRICS:
                metrics.calculate_knn_gain_and_dr_quality(
                    X_lds=X_embedded,
                    X_hds=X.values,
                    labels=labels.values,
                    method_name="{} {}".format(dataset_name, method["name"]),
                )

            plt.savefig(format_title(dataset_name=dataset_name, method=method))
            plt.show()

    if USE_METRICS and len(methods) > 1:
        metrics.visualize()


if __name__ == "__main__":
    main()
