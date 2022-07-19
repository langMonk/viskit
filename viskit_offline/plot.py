# Simple script for visually checking algorithm output. Filename variable is for adjustment.

import csv

import matplotlib.pyplot as plt

filename = 'visualization.txt'

plt.rcParams["figure.figsize"] = [16, 12]
plt.rcParams["font.size"] = 20

xs = []
ys = []
Targets = []

with open(filename, 'r') as csvfile:
    lines = csv.reader(csvfile, delimiter=',')
    for row in lines:
        xs.append(float(row[0]))
        ys.append(float(row[1]))
        Targets.append(int(row[2]))

for i in range(10):
    matching_class_xs = []
    matching_class_ys = []
    for j in range(len(xs)):
        if Targets[j] == i:
            matching_class_xs.append(xs[j])
            matching_class_ys.append(ys[j])
    print(len(matching_class_ys))
    plt.scatter(matching_class_xs, matching_class_ys, label=str(i), s=1)

plt.show()
# plt.savefig('points.png')
