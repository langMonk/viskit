import numpy as np
from sklearn.neighbors import KDTree
import sys

X = []
Y = []

embedding_file = open(sys.argv[1])
label_file = open(sys.argv[2])

line_embedding = embedding_file.readline()
line_label = label_file.readline()

while line_embedding:
    [x, y] = line_embedding.split(",")
    label = line_label.split(",")

    X.append([x, y])
    Y.append(label)

    line_embedding = embedding_file.readline()
    line_label = label_file.readline()

embedding_file.close()
label_file.close()

X = np.array(X)

tree = KDTree(X)

k_neighbours = int(sys.argv[3])


_, ind = tree.query(X, k=(1 + k_neighbours))


i = 0
s = 0

while i < len(X):
    label = Y[i]
    neighbors_labels = [Y[k] for k in ind[i]]
    s = s + neighbors_labels.count(label) - 1
    i = i + 1

print(s / (len(X) * k_neighbours))
