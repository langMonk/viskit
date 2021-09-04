import sys
import numpy as np

global kNN

with open(sys.argv[1], "rb") as binary_file:
    global kNN

    data = binary_file.readline()
    N, k, longSize = data.decode("ascii").split(sep=";")
    N = int(N)
    k = int(k)

    k_to_read = int(sys.argv[3])
    kNN = np.ndarray(shape=(N, k_to_read), dtype="int")

    binary_data = binary_file.read(8)
    test = int.from_bytes(binary_data, byteorder="little")
    assert test == 0x01020304

    for i in range(0, N):
        for j in range(0, k):
            binary_data = binary_file.read(4)
            data = int.from_bytes(binary_data, byteorder="little")
            if j < k_to_read:
                kNN[i][j] = data
            binary_data = binary_file.read(4)


with open(sys.argv[2], "wb") as binary_file:
    binary_file.write("{};{};{}\n".format(N, k_to_read, 8).encode("ascii"))
    binary_file.write(0x01020304 .to_bytes(8, byteorder="little"))
    for i in range(0, N):
        for j in range(0, k_to_read):
            binary_file.write(int(kNN[i][j]).to_bytes(8, byteorder="little"))
