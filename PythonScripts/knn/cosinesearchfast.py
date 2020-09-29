#!/usr/bin/python
 
import numpy as np
import csv
import sys
from datetime import datetime
from math import sqrt
import faiss

X = []
Y = []

M = 300
N = 0

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

X = np.array(X, dtype=float).astype('float32')

start = datetime.now()

print('start faiss')
print(N)
print(M)
print(X.shape)

res = faiss.StandardGpuResources()
quantizer = faiss.IndexFlatIP(M)
index_flat = faiss.IndexIVFFlat(quantizer, M, int(sqrt(X.shape[0])))
index_flat.nprobe = 10

gpu_index_flat = faiss.index_cpu_to_gpu(res, 0, index_flat)
assert not gpu_index_flat.is_trained
gpu_index_flat.train(X)
assert gpu_index_flat.is_trained

gpu_index_flat.add(X)  # add vectors to the index
print('after add')
print(gpu_index_flat.ntotal)

k = int(sys.argv[3])
gpu_index_flat.nprobe = 10
D, I = gpu_index_flat.search(X, k + 1)  # actual search, might find the same index
print('after search')

print(datetime.now() - start, file=sys.stderr)

with open(sys.argv[2], "wb") as binary_file:
    binary_file.write("{};{};{}\n".format(N, k, 8).encode("ascii"))
    binary_file.write(0x01020304.to_bytes(8, byteorder="little"))
    for i in range(0, N):
        skipped = False
        for j in range(0, k + 1):
            if j == k:
                if not skipped:
                    break
            if I[i][j] == i:
                skipped = True
                continue
            binary_file.write(int(I[i][j]).to_bytes(8, byteorder="little"))

print('written')

metricsum = 0
for i in range(0, N):
    skipped = False
    for j in range(0, k + 1):
        if j == k:
            if not skipped:
                break
        if I[i][j] == i:
            skipped = True
            continue
        if Y[I[i][j]] == Y[i]:
            metricsum = metricsum + 1

print(float(metricsum) / (100.0 * N))
