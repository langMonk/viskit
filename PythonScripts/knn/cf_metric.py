import sys
import numpy as np
import csv

X = []
Y = []
M = 300
kNN = np.empty(2, dtype=int)

with open(sys.argv[1]) as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    n = 0
    for row in csv_reader:
        n = n + 1
        if n == 1:
            N = int(row[0])
            continue
        if n == 2:
            M = int(row[0])
            continue

        if len(row) != M + 1:
            print(n, file=sys.stderr)
        else:
            flatten = [float(item) for item in row[0:M]]
            norm = sum([a ** 2 for a in flatten]) ** 0.5
            normalized = [a / norm for a in flatten]
            X.append(normalized)
            Y.append(row[M])

with open(sys.argv[2], "rb") as binary_file:
    data = binary_file.readline()
    N, k, longSize = data.decode("ascii").split(sep=";")
    N = int(N)
    k = int(k)

    kNN = np.ndarray(shape=(N, k), dtype='int')

    binary_data = binary_file.read(8)
    test = int.from_bytes(binary_data, byteorder="little")
    assert test == 0x01020304

    for i in range(0, N):
        for j in range(0, k):
            binary_data = binary_file.read(4)
            data = int.from_bytes(binary_data, byteorder="little")
            kNN[i][j] = data
            binary_data = binary_file.read(4)

k_list = [2, 4]
print("YAHOO Results")

for k in k_list:
    metric_sum = 0
    for i in range(0, N):
        skipped = False
        for j in range(0, k + 1):
            if j == k:
                if not skipped:
                    break
            if kNN[i][j] == i:
                skipped = True
                continue
            if Y[kNN[i][j]] == Y[i]:
                metric_sum = metric_sum + 1
    print("Metric for k = {} is equal {}".format(k, float(metric_sum) / (float(k) * N)))
