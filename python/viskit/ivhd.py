import subprocess
import os
import numpy as np
import pandas as pd

from viskit.faiss_graph_generator import FaissGenerator


class IVHD:
    def __init__(
        self,
        graph_path: str = None,
        n_iter: int = 5000,
        nn: int = 3,
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
        dataset_path = os.getcwd() + "/output.csv"
        viskit_offline_path = os.getcwd() + "/../cmake-build-release/viskit_offline/viskit_offline"
        output_path = os.getcwd() + "/../build/visualization.txt"

        X.to_csv(dataset_path, index=False, header=False)

        if self.graph_path is None:
            print("Generating kNN graph...")
            generator = FaissGenerator(csv_file=dataset_path, cosine_metric=False)
            generator.run(nn=self.nn)
            self.graph_path = os.getcwd() + "/graphs/output.bin"
            generator.save_to_binary_file(output_file_path=self.graph_path)

        args = (
            viskit_offline_path,
            dataset_path,
            self.graph_path,
            output_path,
            str(self.n_iter),
            str(self.nn),
            str(self.rn),
            str(self.distanceEqualToOne),
            str(self.l1_steps),
            self.optimizer,
        )

        output = subprocess.check_output(args)
        print(output)

        X, Y, labels = np.loadtxt(
            output_path,
            delimiter=",",
            unpack=True,
        )

        # os.remove(output)

        return np.column_stack((X, Y))
