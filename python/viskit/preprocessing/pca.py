import configparser
import os
import sys
import numpy as np
import matplotlib.pyplot as plt

import pandas as pd
from sklearn.decomposition import PCA


def set_dataframe_columns(dataframe: pd.DataFrame, with_labels: bool = True) -> None:
    columns = []

    columns_range = dataframe.shape[1] - 1
    if not with_labels:
        columns_range = dataframe.shape[1]

    for i in range(0, columns_range):
        columns.append("col{}".format(i))
    if with_labels:
        columns.append("label")
    dataframe.columns = columns


def read_dataset(filepath: str, with_labels: bool = True) -> [pd.DataFrame]:
    data = pd.read_csv(filepath, skiprows=0, header=None)
    set_dataframe_columns(data, with_labels)

    return data


def preprocess_dataset_with_pca(dataset_file_name: str, input_path: str):
    """PCA on dense arrays"""
    df = read_dataset(input_path)

    n_components = 100
    pca = PCA(n_components=n_components)
    dataset = pca.fit_transform(df)
    dataset = pd.DataFrame(dataset)

    print("Explained variance ratio vector:")
    print("- Vector: {0}".format(pca.explained_variance_ratio_))
    print("- Sum: {0}".format(sum(pca.explained_variance_ratio_)))

    dataset.to_csv(
        dataset_file_name + "_pca_{0}.csv".format(n_components),
        header=False,
        index=False,
    )


if __name__ == "__main__":
    preprocess_dataset_with_pca(
        dataset_file_name="emnist-letters-data", input_path='/Users/bartoszminch/Documents/Repositories/dataset_viskit/datasets/emnist-letters-data.csv'
    )

    # df = read_dataset('/Users/bartoszminch/Documents/Repositories/dataset_viskit/datasets/emnist-letters-data.csv', False)
    # # df = df.drop(labels=["label"], axis=1)
    #
    # pca_cancer = PCA(n_components=783)
    #
    # pca_cancer.fit(df)
    #
    # variance = pca_cancer.explained_variance_ratio_
    # variance = np.cumsum(variance * 100)
    #
    # fig = plt.figure(figsize=(8, 8))
    # ax = fig.add_subplot(1, 1, 1)
    #
    # ax.set_xlim(0, 783 + 1)
    # ax.set_ylim(0, 100 + 1)
    #
    # dim = np.arange(1, 783 + 1, 1)
    # x = list(range(1, 783 + 1))
    # ax.step(x, variance, where='post')
    # ax.set_xticks(np.arange(0, 784, 50))
    # ax.grid()
    #
    # plt.title('Cumulative Explained Variance as a Function of the Number of Components')
    # plt.ylabel('Cumulative Explained variance')
    # plt.xlabel('Principal components')
    #
    # plt.axhline(y=95, color='k', linestyle='--', label='95% Explained Variance')
    # plt.axhline(y=90, color='c', linestyle='--', label='90% Explained Variance')
    # plt.axhline(y=85, color='r', linestyle='--', label='85% Explained Variance')
    #
    # plt.legend(loc='best')
    #
    # plt.show()
