#!/usr/bin/python

import matplotlib.pyplot as plt
import sys
import math
import numpy as np
from sklearn.preprocessing import normalize
from sklearn.neighbors import KDTree
from scipy.spatial import distance
from scipy.stats import spearmanr


def algorithm_output_create_distances():
    X = []
    Y = []
    distances = []

    f = open(sys.argv[1])

    line = f.readline()

    while line:
        [x, y, label] = line.split(" ")
        X.append([float(x), float(y)])
        Y.append(label)
        line = f.readline()
    f.close()

    X = np.array(X)
    tree = KDTree(X)

    kneighbours = int(sys.argv[3])
    distances = np.empty([len(X), kneighbours])

    _, ind = tree.query(X, k=(1 + kneighbours))

    i = 0
    while i < len(X):
        label = Y[i]
        j = 0
        for k in ind[i]:
            if i != k:
                distances[i][j] = distance.euclidean(X[i], X[k])
                j += 1

        i = i + 1

    return distances.flatten()


def kNN_graph_create_distances():
    with open(sys.argv[2], "rb") as binary_file:
        data = binary_file.readline()
        N, k, longSize = data.decode("ascii").split(sep=";")
        N = int(N)
        k = int(sys.argv[3])

        distances = np.ndarray(shape=(N, k), dtype="float")

        binary_data = binary_file.read(8)
        test = int.from_bytes(binary_data, byteorder="little")
        assert test == 0x01020304

        for i in range(0, N):
            for j in range(0, k):
                binary_data = binary_file.read(4)
                data = int.from_bytes(binary_data, byteorder="little")
                distances[i][j] = data
                binary_data = binary_file.read(4)

        return distances.flatten()


if __name__ == "__main__":
    d_red = algorithm_output_create_distances()
    d_org = kNN_graph_create_distances()

    d_org = np.sqrt(d_org)

    d_red = (d_red - min(d_red)) / (max(d_red) - min(d_red))
    d_org = (d_org - min(d_org)) / (max(d_org) - min(d_org))

    # d_red = d_red / np.linalg.norm(d_red)
    # d_org = d_org / np.linalg.norm(d_org)

    print(spearmanr(d_org, d_red))

    plt.plot(d_org, d_red, ".")
    plt.xlabel("Original distances")
    plt.ylabel("Reduced distances")
    plt.show()
