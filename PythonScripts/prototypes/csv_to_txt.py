#!/usr/bin/python

import csv
import sys

csv_file = sys.argv[1]
txt_file = sys.argv[2]

with open(txt_file + "_label.txt", "w") as my_output_file_vectors:
    with open(csv_file, "r") as my_input_file:
        [
            my_output_file_vectors.write(" ".join(row[-1]) + "\n")
            for row in csv.reader(my_input_file)
        ]
    my_output_file_vectors.close()
