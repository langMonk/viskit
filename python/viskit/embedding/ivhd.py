import configparser
import os
import subprocess
import logging

import numpy as np
import pandas as pd

from viskit.knn_graph.faiss_generator import FaissGenerator


def run_command(command):
    process = subprocess.Popen(args=command, stdout=subprocess.PIPE)
    while True:
        output = process.stdout.readline()
        if output == b"" and process.poll() is not None:
            break
        if output:
            msg = output.strip()
            print(msg)
            logging.info(msg)

    rc = process.poll()
    return rc


class Ivhd:
    def __init__(
        self,
        graph_path: str = None,
        n_iter: int = 500,
        nn: int = 2,
        rn: int = 1,
        binaryDistances: bool = True,
        reverse_neighbors_steps: int = 0,
        reverse_neighbors_count: int = 4,
        l1_steps: int = 50,
        optimizer: str = "force-directed",
    ):
        self.graph_path = graph_path
        self.n_iter = n_iter
        self.nn = nn
        self.rn = rn
        self.l1_steps = l1_steps
        self.optimizer = optimizer
        self.reverse_neighbors_steps = reverse_neighbors_steps
        self.reverse_neighbors_count = reverse_neighbors_count

        if binaryDistances:
            self.binaryDistances = 1
        else:
            self.binaryDistances = 0

        self.config = configparser.ConfigParser()
        script_path = os.path.dirname(__file__)
        self.config.read(script_path + "/config.ini")

    def fit_transform(self, X: pd.DataFrame, labels: pd.DataFrame):
        """Fit X into an embedded space and return that transformed
        output.
        Parameters
        ----------
        X : ndarray of shape (n_samples, n_features) containing feature vectors
        labels : ndarray of shape (n_sample, 1) containing labels
        Returns
        -------
        X_new : ndarray of shape (n_samples, n_components)
            Embedding of the training data in low-dimensional space.
        """
        input_dataset_path = self.config["Paths"]["InputDatasetPath"]
        input_labels_path = self.config["Paths"]["InputLabelsPath"]
        output_path = self.config["Paths"]["OutputPath"]
        binary_path = self.config["Paths"]["BinaryPath"]
        graph_path = self.config["Paths"]["GraphPath"]

        X.to_csv(input_dataset_path, index=False, header=False)
        labels.to_csv(input_labels_path, index=False, header=False)

        if self.graph_path is None:
            print("Generating kNN graph...")
            generator = FaissGenerator(csv_file=input_dataset_path, cosine_metric=False)
            generator.run(nn=self.nn)
            generator.save_to_binary_file(output_file_path=graph_path)

        args = (
            binary_path,
            input_dataset_path,
            input_labels_path if input_labels_path is not None else "",
            self.graph_path if self.graph_path is not None else graph_path,
            output_path,
            str(self.n_iter),
            str(self.nn),
            str(self.rn),
            str(self.binaryDistances),
            str(self.reverse_neighbors_steps),
            str(self.reverse_neighbors_count),
            str(self.l1_steps),
            self.optimizer,
        )

        run_command(args)

        X, Y, labels, nn, rn = np.loadtxt(
            output_path,
            delimiter=",",
            unpack=True,
        )

        return [np.column_stack((X, Y)), np.column_stack((nn, rn))]
