import configparser
import os
import subprocess

import numpy as np
import pandas as pd

from viskit.faiss_graph_generator import FaissGenerator


def run_command(command):
    process = subprocess.Popen(args=command, stdout=subprocess.PIPE)
    while True:
        output = process.stdout.readline()
        if output == b"" and process.poll() is not None:
            break
        if output:
            print(output.strip())
    rc = process.poll()
    return rc


class IVHD:
    def __init__(
        self,
        graph_path: str = None,
        n_iter: int = 500,
        nn: int = 2,
        rn: int = 1,
        distancesEqualToOne: bool = True,
        l1_steps: int = 50,
        optimizer: str = "force-directed",
    ):
        self.graph_path = graph_path
        self.n_iter = n_iter
        self.nn = nn
        self.rn = rn
        self.l1_steps = l1_steps
        self.optimizer = optimizer
        if distancesEqualToOne:
            self.distanceEqualToOne = 1
        else:
            self.distanceEqualToOne = 0

        self.config = configparser.ConfigParser()
        script_path = os.path.dirname(__file__)
        self.config.read(script_path + "/config.ini")

    def fit_transform(self, X: pd.DataFrame):
        """Fit X into an embedded space and return that transformed
        output.
        Parameters
        ----------
        X : ndarray of shape (n_samples, n_features)
        Returns
        -------
        X_new : ndarray of shape (n_samples, n_components)
            Embedding of the training data in low-dimensional space.
        """
        input_path = self.config["Paths"]["InputPath"]
        output_path = self.config["Paths"]["OutputPath"]
        binary_path = self.config["Paths"]["BinaryPath"]
        graph_path = self.config["Paths"]["GraphPath"]

        X.to_csv(input_path, index=False, header=False)

        if self.graph_path is None:
            print("Generating kNN graph...")
            generator = FaissGenerator(csv_file=input_path, cosine_metric=False)
            generator.run(nn=self.nn)
            generator.save_to_binary_file(output_file_path=graph_path)

        args = (
            binary_path,
            input_path,
            self.graph_path,
            output_path,
            str(self.n_iter),
            str(self.nn),
            str(self.rn),
            str(self.distanceEqualToOne),
            str(self.l1_steps),
            self.optimizer,
        )

        run_command(args)

        X, Y, labels = np.loadtxt(
            output_path,
            delimiter=",",
            unpack=True,
        )

        # os.remove(output)

        return np.column_stack((X, Y))
