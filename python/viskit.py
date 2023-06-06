import configparser
import pandas as pd
import seaborn as sns
import os
from pylab import *
from sklearn.manifold import TSNE

from viskit.embedding.ivhd import Ivhd
from viskit.scoring.local_score import LocalMetric
from viskit.scoring.global_score import GlobalMetric
from viskit.knn_graph.graph import Graph

USE_GLOBAL_METRICS = True
USE_LOCAL_METRICS = False

if USE_GLOBAL_METRICS:
    global_metrics = GlobalMetric()

if USE_LOCAL_METRICS:
    local_metrics = LocalMetric()


def draw_2d(X, Y, labels):
    labels = labels.to_numpy().flatten()
    unique = list(set(labels))
    colors = [plt.cm.jet(float(i) / max(unique)) for i in unique]

    for i, u in enumerate(unique):
        xi = [X[j] for j in range(len(X)) if labels[j] == u]
        yi = [Y[j] for j in range(len(X)) if labels[j] == u]
        plt.scatter(xi, yi, color=colors[i], label=str(u), s=2)


def draw_2d_sns(X, Y, labels):
    df = pd.DataFrame()
    df["X"] = X
    df["Y"] = Y
    df["labels"] = labels

    color_palette = sns.color_palette("muted", len(df["labels"].unique()))

    fig, ax = plt.subplots()
    fig.set_figheight(16)
    fig.set_figwidth(16)
    fig.patch.set_visible(False)
    ax.axis("off")

    sns.scatterplot(
        x="X",
        y="Y",
        hue="labels",
        palette=color_palette,
        data=df,
        legend=False,
        alpha=0.8,
        edgecolor=None,
    )


def format_title(dataset_name: str, method) -> str:
    if method["name"] != "Ivhd":
        generated_title = "{}_{}".format(dataset_name, method["name"])
    else:
        ivhd = method["object"]
        generated_title = "{}_{}_opt={}_iter={}_nn={}_rn={}_l1steps={}_reverse_neighbors_steps={}_reverse_neighbors_count={}_binary_distances={}".format(
            dataset_name,
            method["name"],
            ivhd.optimizer,
            ivhd.n_iter,
            ivhd.nn,
            ivhd.rn,
            ivhd.l1_steps,
            ivhd.reverse_neighbors_steps,
            ivhd.reverse_neighbors_count,
            ivhd.binaryDistances
        )
    return generated_title


def set_dataframe_columns(dataframe: pd.DataFrame) -> None:
    # set up dataset columns id
    columns = []
    for i in range(0, dataframe.shape[1] - 1):
        columns.append("col{}".format(i))
    columns.append("label")
    dataframe.columns = columns


def print_matrix_info():
    logging.info("----EMBEDDING CONFUSION MATRIX-----")
    logging.info(global_metrics.embedding_confusion_matrix)
    logging.info("----ORIGINAL CONFUSION MATRIX-----")
    logging.info(global_metrics.original_confusion_matrix)
    logging.info("----FORBENIUS NORM-----")
    logging.info(global_metrics.calculate_forbenius())


def main():
    config = configparser.ConfigParser()
    script_path = os.path.dirname(os.path.abspath(__file__))
    config.read(script_path + "/config.ini")

    logging.basicConfig(level=logging.INFO, filename=config["Paths"]["LogsPath"])

    dataset_files = [
        {
            "dataset": "/Users/bartoszminch/Documents/Repositories/dataset_viskit/datasets/mnist_7k_data.csv",
            "labels": "/Users/bartoszminch/Documents/Repositories/dataset_viskit/datasets/mnist_7k_labels.csv"
        },
    ]

    methods = [
        # {
        #     "name": "IVHD_binary_distances",
        #     "object": Ivhd(
        #         optimizer="force-directed",
        #         n_iter=4000,
        #         nn=2,
        #         rn=1,
        #         binaryDistances=True,
        #         graph_path="/Users/bartoszminch/Documents/Repositories/dataset_viskit/graphs/mnist_7k_euclidean.bin",
        #         l1_steps=5
        #     ),
        # },
        # {
        #     "name": "IVHD_euclidean_distances",
        #     "object": Ivhd(
        #         optimizer="force-directed",
        #         n_iter=4000,
        #         nn=2,
        #         rn=1,
        #         binaryDistances=False,
        #         l1_steps=20,
        #         graph_path="/Users/bartoszminch/Documents/Repositories/dataset_viskit/graphs/mnist_7k_euclidean.bin",
        #     ),
        # },
        {
            "name": "Largevis",
            "object": Ivhd(
                optimizer="largevis",
                n_iter=1,
                nn=3,
                rn=1,
                l1_steps=0,
                reverse_neighbors_steps=0,
                reverse_neighbors_count=0,
            ),
        },
    ]

    if not os.path.exists("results"):
        os.makedirs("results")
    os.chdir("results")

    for element in dataset_files:
        dataset = element["dataset"]
        labels = element["labels"]

        # graph = Graph()
        # graph.load_from_binary_file(element["graph"], 2)
        dataset_name = dataset.split("/")[-1].strip(".csv")

        if not os.path.exists(dataset_name):
            os.makedirs(dataset_name)
        os.chdir(dataset_name)

        X = pd.read_csv(dataset, delimiter=",", header=None, index_col=False)
        labels = pd.read_csv(labels, delimiter=",", header=None, index_col=False)

        set_dataframe_columns(X)

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

            start = time.time()
            X_embedded = method["object"].fit_transform(X, labels)
            end = time.time()
            logging.info("Embedding time: {}".format(end - start))
            print("Embedding time: {}".format(end - start))

            draw_2d(X_embedded[:, 0], X_embedded[:, 1], labels)

            if USE_LOCAL_METRICS:
                print("Calculate metrics...")

                local_metrics.calculate_knn_gain_and_dr_quality(
                    X_lds=X_embedded,
                    X_hds=X.values,
                    labels=labels.values,
                    method_name="{} {}".format(dataset_name, method["name"]),
                )

                # global_metrics.calculate_embedding_confusion_matrix(X_embedded, labels)

            os.system('pwd')
            os.system('cp ./../../../viskit/output.csv ./'.format(dataset_name))

            plt.savefig(format_title(dataset_name=dataset_name, method=method))
            plt.show()

    if USE_LOCAL_METRICS:
        local_metrics.visualize()


if __name__ == "__main__":
    main()
