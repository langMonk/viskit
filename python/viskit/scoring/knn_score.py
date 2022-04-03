import numpy as np
from sklearn.neighbors import KDTree
import sys

X = []
Y = []

f = open(sys.argv[1])

line = f.readline()

while line:
    [x, y, label] = line.split(" ")
    X.append([x, y])
    Y.append(label)
    line = f.readline()
f.close()

X = np.array(X)

tree = KDTree(X)

k_neighbours = int(sys.argv[2])


_, ind = tree.query(X, k=(1 + k_neighbours))


i = 0
s = 0

while i < len(X):
    label = Y[i]
    neighbors_labels = [Y[k] for k in ind[i]]
    s = s + neighbors_labels.count(label) - 1
    i = i + 1

# print(s)
# print(len(X) * k_neighbours)
print(s / (len(X) * k_neighbours))
