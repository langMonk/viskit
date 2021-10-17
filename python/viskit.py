import numpy as np
import pandas as pd

from viskit.ivhd import IVHD
from pylab import *

from sklearn.manifold import TSNE
from umap import UMAP


def draw_2d(X, Y, labels, ax):
    unique = list(set(labels))
    colors = [plt.cm.jet(float(i) / max(unique)) for i in unique]

    for i, u in enumerate(unique):
        xi = [X[j] for j in range(len(X)) if labels[j] == u]
        yi = [Y[j] for j in range(len(X)) if labels[j] == u]
        ax.scatter(xi, yi, color=colors[i], label=str(u), s=2)


def set_dataframe_columns(dataframe: pd.DataFrame) -> None:
    # set up dataset columns id
    columns = []
    for i in range(0, dataframe.shape[1] - 1):
        columns.append("col{}".format(i))
    columns.append("label")
    dataframe.columns = columns


def main():
    dataset_file = (
        "/home/bminch/Repositories/centroids/output/mnist_70k_pca30_25_4_all.csv"
    )
    # dataset_file = '/home/bminch/Repositories/dataset_viskit/mnist_70k_pca30.csv'
    X = pd.read_csv(dataset_file, delimiter=",", header=None, index_col=False)
    set_dataframe_columns(X)

    labels = X["label"]
    X = X.drop(labels=["label"], axis=1)

    methods = {
        # 'IVHD - force directed': IVHD(graph_path="../graphs/mnist_7k_graph.bin", n_iter=2500),
        "IVHD - force directed": IVHD(optimizer="forcedirected"),
        # 'IVHD - nesterov': IVHD(optimizer="nesterov"),
        # 'IVHD - adadelta': IVHD(graph_path="../graphs/mnist_7k_graph.bin", n_iter=2500, optimizer="adadelta"),
        # 't-SNE with distances': IVHD(optimizer="tsne"),
        "UMAP": UMAP(),
        # 'bh t-SNE': TSNE(n_components=2, n_iter=2000)
    }

    keys = []
    for k, v in methods.items():
        keys.append(k)

    fig = plt.figure()

    fig.set_figheight(16)
    fig.set_figwidth(16)

    number_of_subplots = len(methods)

    it = 0
    for i, v in enumerate(range(0, number_of_subplots)):
        v = v + 1
        ax = subplot(int(number_of_subplots / 2), 2, v)
        ax.set_title(keys[it])
        X_embedded = methods[keys[it]].fit_transform(X)
        draw_2d(X_embedded[:, 0], X_embedded[:, 1], labels, ax)
        it = it + 1
        plt.legend(fontsize=20)

    plt.show()


if __name__ == "__main__":
    main()
