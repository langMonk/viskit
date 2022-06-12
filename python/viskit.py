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
    unique = list(set(labels))
    colors = []
    for i in unique:
        if i == 10:
            colors.append((0.0, 0.0, 0.0, 1.0))
        else:
            colors.append(plt.cm.jet(float(i) / max(unique)))

    for i, u in enumerate(unique):
        xi = [X[j] for j in range(len(X)) if labels[j] == u]
        yi = [Y[j] for j in range(len(X)) if labels[j] == u]
        plt.scatter(xi, yi, color=colors[i], label=str(u), s=2)


def draw_2d_sns(X, Y, labels):
    df = pd.DataFrame()
    df["X"] = X
    df["Y"] = Y
    df["labels"] = labels

    df_main = df[df["labels"] != 10]
    color_palette = sns.color_palette("muted", len(df_main["labels"].unique()))

    sns.scatterplot(
        x="X",
        y="Y",
        hue="labels",
        palette=color_palette,
        data=df_main,
        legend="full",
        alpha=0.8,
        edgecolor=None,
    )

    df_border = df[df["labels"] == 10]
    color_palette = sns.color_palette("muted", 1)
    color_palette[-1] = (0.0, 0.0, 0.0)

    sns.scatterplot(
        x="X",
        y="Y",
        hue="labels",
        palette=color_palette,
        data=df_border,
        legend="full",
        alpha=0.8,
        edgecolor=None,
    )

    plt.legend(loc="right", markerscale=3.0, fontsize=16)


def format_title(dataset_name: str, method) -> str:
    if method["name"] != "Ivhd":
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
            "dataset": "/Users/bartoszminch/Documents/Repositories/viskit/python/viskit/knn_graph"
            "/mnist_pca_100.csv",
            "graph": "/Users/bartoszminch/Documents/Repositories/viskit/python/graphs/mnist_pca_100.bin",
        },
        # "/home/bminch/Repositories/centroids/output/mnist_70k_pca30_50_2_all.csv",
        # "/Users/bartoszminch/Documents/Repositories/dataset_viskit/mnist.csv",
        # "/home/bminch/Repositories/dataset_viskit/mnist_7k.csv",
        # "/home/bminch/Repositories/dataset_viskit/mnist_7k.csv"
    ]

    methods = [
        # {
        #     "name": "Ivhd",
        #     "object": Ivhd(
        #         optimizer="force-directed",
        #         n_iter=1000,
        #         nn=2,
        #         rn=1,
        #         l1_steps=0,
        #         reverse_neighbors_steps=0,
        #         reverse_neighbors_count=0,
        #         graph_path="/Users/bartoszminch/Documents/Repositories/viskit/python/graphs/mnist_pca_100.bin",
        #     ),
        # },
        # {
        #     "name": "Ivhd",
        #     "object": Ivhd(
        #         optimizer="force-directed",
        #         n_iter=1000,
        #         nn=2,
        #         rn=1,
        #         l1_steps=0,
        #         reverse_neighbors_steps=500,
        #         reverse_neighbors_count=3,
        #         graph_path="/Users/bartoszminch/Documents/Repositories/viskit/python/graphs/mnist_pca_100.bin",
        #     ),
        # },
        # {
        #     "name": "Ivhd",
        #     "object": Ivhd(
        #         optimizer="force-directed",
        #         n_iter=1000,
        #         nn=2,
        #         rn=1,
        #         l1_steps=0,
        #         reverse_neighbors_steps=500,
        #         reverse_neighbors_count=4,
        #         graph_path="/Users/bartoszminch/Documents/Repositories/viskit/python/graphs/mnist_pca_100.bin",
        #     ),
        # },
        # {
        #     "name": "Ivhd",
        #     "object": Ivhd(
        #         optimizer="force-directed",
        #         n_iter=1000,
        #         nn=2,
        #         rn=1,
        #         l1_steps=0,
        #         reverse_neighbors_steps=500,
        #         reverse_neighbors_count=6,
        #         graph_path="/Users/bartoszminch/Documents/Repositories/viskit/python/graphs/mnist_pca_100.bin",
        #     ),
        # },
        # {
        #     "name": "Ivhd",
        #     "object": Ivhd(
        #         optimizer="force-directed",
        #         n_iter=3000,
        #         nn=2,
        #         rn=1,
        #         l1_steps=0,
        #         reverse_neighbors_steps=0,
        #         reverse_neighbors_count=0,
        #         graph_path="/Users/bartoszminch/Documents/Repositories/viskit/python/graphs/mnist_pca_100.bin",
        #     ),
        # },
        # {
        #     "name": "Ivhd",
        #     "object": Ivhd(
        #         optimizer="nesterov",
        #         n_iter=8000,
        #         nn=2,
        #         rn=1,
        #         l1_steps=0,
        #         reverse_neighbors_steps=0,
        #         reverse_neighbors_count=0,
        #         graph_path="/Users/bartoszminch/Documents/Repositories/viskit/python/graphs/mnist_pca_100.bin",
        #     ),
        # },
        # {
        #     "name": "Ivhd",
        #     "object": Ivhd(
        #         optimizer="adam",
        #         n_iter=8000,
        #         nn=2,
        #         rn=1,
        #         l1_steps=0,
        #         reverse_neighbors_steps=0,
        #         reverse_neighbors_count=0,
        #         graph_path="/Users/bartoszminch/Documents/Repositories/viskit/python/graphs/mnist_pca_100.bin",
        #     ),
        # },
        {
            "name": "Ivhd",
            "object": Ivhd(
                optimizer="force-directed",
                n_iter=2500,
                nn=3,
                rn=1,
                l1_steps=0,
                reverse_neighbors_steps=500,
                reverse_neighbors_count=6,
                graph_path="/Users/bartoszminch/Documents/Repositories/viskit/python/graphs/mnist_pca_100.bin",
            ),
        },
        # {
        #     "name": "Ivhd",
        #     "object": Ivhd(
        #         optimizer="nesterov",
        #         n_iter=7500,
        #         nn=2,
        #         rn=1,
        #         l1_steps=0,
        #         reverse_neighbors_steps=500,
        #         reverse_neighbors_count=6,
        #         graph_path="/Users/bartoszminch/Documents/Repositories/viskit/python/graphs/mnist_pca_100.bin",
        #     ),
        # },
        # {
        #     "name": "Ivhd",
        #     "object": Ivhd(
        #         optimizer="adam",
        #         n_iter=7500,
        #         nn=2,
        #         rn=1,
        #         l1_steps=0,
        #         reverse_neighbors_steps=500,
        #         reverse_neighbors_count=6,
        #         graph_path="/Users/bartoszminch/Documents/Repositories/viskit/python/graphs/mnist_pca_100.bin",
        #     ),
        # },
        # {"name": "UMAP", "object": UMAP()},
        # {"name": "t-SNE (distance variant)", "object": Ivhd(optimizer="tsne", nn=5)},
        # {"name": "bh t-SNE", "object": TSNE(n_components=2, n_iter=2000)},
    ]

    if not os.path.exists("results"):
        os.makedirs("results")
    os.chdir("results")

    for element in dataset_files:
        dataset = element["dataset"]

        graph = Graph()
        graph.load_from_binary_file(element["graph"], 2)
        dataset_name = dataset.split("/")[-1].strip(".csv")

        if not os.path.exists(dataset_name):
            os.makedirs(dataset_name)
        os.chdir(dataset_name)

        X = pd.read_csv(dataset, delimiter=",", header=None, index_col=False)
        set_dataframe_columns(X)

        labels = X["label"]
        X = X.drop(labels=["label"], axis=1)

        # indexes_of_points_with_conflicting_neighbors = graph.get_conflicting_neighbors(labels)
        # logging.info("Borderline points: {0}".format(len(indexes_of_points_with_conflicting_neighbors)))
        # print("Borderline points: {0}".format(len(indexes_of_points_with_conflicting_neighbors)))

        # label_to_append = len(unique(labels))
        # for index in indexes_of_points_with_conflicting_neighbors:
        #     labels[index] = label_to_append

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
            X_embedded = method["object"].fit_transform(X)
            end = time.time()
            logging.info("Embedding time: {}".format(end - start))

            draw_2d_sns(X_embedded[:, 0], X_embedded[:, 1], labels)

            # fig.legend(labels=labels, markerscale=4.0, loc="right", fontsize=20)

            if USE_LOCAL_METRICS:
                local_metrics.calculate_knn_gain_and_dr_quality(
                    X_lds=X_embedded,
                    X_hds=X.values,
                    labels=labels.values,
                    method_name="{} {}".format(dataset_name, method["name"]),
                )

                global_metrics.calculate_embedding_confusion_matrix(X_embedded, labels)
                # print_matrix_info()

            plt.savefig(format_title(dataset_name=dataset_name, method=method))
            plt.show()

    if USE_LOCAL_METRICS:
        local_metrics.visualize()


if __name__ == "__main__":
    main()
