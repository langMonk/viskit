import subprocess

import numpy as np
import pandas as pd


class IVHD:
    def __init__(self, n_components: int = 2, n_iter: int = 2000, nn: int = 2, rn: int = 1, l1_steps: int = 0):
        self.n_components = n_components
        self.n_iter = n_iter
        self.nn = nn
        self.rn = rn
        self.l1_steps = l1_steps

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

        X.to_csv('output.csv', index=False, header=False)

        # args = (
        #     "./viskit_offline",
        #     "./temp.csv",
        #     "./",
        #     str(self.n_iter),
        #     str(self.nn),
        #     str(self.rn),
        #     str(self.l1_steps),
        # )
        #
        # output = subprocess.check_output(args)
        # print(output)
        #
        # x, y, labels = np.loadtxt(
        #     "./visualization.txt",
        #     delimiter=",",
        #     unpack=True,
        # )
        #
        # embedding = []
        #
        # return embedding
