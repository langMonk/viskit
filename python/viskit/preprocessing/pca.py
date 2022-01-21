import configparser
import os

import pandas as pd
from sklearn.decomposition import PCA


def set_dataframe_columns(dataframe: pd.DataFrame) -> None:
    columns = []
    for i in range(0, dataframe.shape[1] - 1):
        columns.append("col{}".format(i))
    columns.append("label")
    dataframe.columns = columns


def read_dataset(filepath: str) -> [pd.DataFrame]:
    data = pd.read_csv(filepath, skiprows=0, header=None)
    set_dataframe_columns(data)

    return data


def preprocess_dataset_with_pca(output_file_name: str, input_path: str):
    """PCA on dense arrays"""
    df = read_dataset(input_path)

    labels = df['label']
    dataset = df.drop(labels=['label'], axis=1)

    n_components = 100
    pca = PCA(n_components=n_components)
    dataset = pca.fit_transform(dataset)
    dataset = pd.DataFrame(dataset)

    dataset['label'] = labels

    print("Explained variance ratio vector:")
    print("- Vector: {0}".format(pca.explained_variance_ratio_))
    print("- Sum: {0}".format(sum(pca.explained_variance_ratio_)))

    dataset.to_csv(output_file_name+"_pca_{0}.csv".format(n_components), header=False, index=False)


if __name__ == "__main__":
    config = configparser.ConfigParser()
    script_path = os.path.dirname(__file__)
    config.read(script_path + "/config.ini")
    preprocess_dataset_with_pca(output_file_name="mnist", input_path=config["Paths"]["InputPath"])
