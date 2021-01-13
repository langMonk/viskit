import sys
import numpy as np
from collections import defaultdict 
import networkx as nx
import matplotlib.pyplot as plt


def read_knn_file_to_graph(filename):
    with open(filename, "rb") as binary_file:
        data = binary_file.readline()
        N, k, longSize = data.decode("ascii").split(sep=";")
        N = int(N)
        k = int(k)

        graph = nx.DiGraph()

        binary_data = binary_file.read(8)
        test = int.from_bytes(binary_data, byteorder="little")
        assert test == 0x01020304

        for i in range(0, N):
            for j in range(0, k):
                binary_data = binary_file.read(4)
                data = int.from_bytes(binary_data, byteorder="little")
                graph.add_edge(i, data)
                binary_data = binary_file.read(4)


        return graph


if __name__== "__main__":
    datasets = ["mnist", "smallnorb", "rcv"]
    nn = ["2", "3", "4", "6", "8", "10", "30"]


    for dataset in datasets:
        print("*** "+str(dataset).upper()+" ***")
        print("nn, components, largest_component, largest_component_%")
        for n in nn:
            knn_file = str(dataset) + str("_") + str(n)
            graph = read_knn_file_to_graph(knn_file+".knn")
            size_overall = len(graph.nodes())

            largest_cc = len(max(nx.weakly_connected_components(graph), key=len))     
            comps = nx.number_weakly_connected_components(graph)
            percentage = 100*largest_cc/size_overall

            print(str(n) + ", " + str(comps) + ", " + str(largest_cc) + ", " + str("%.2f" % percentage))