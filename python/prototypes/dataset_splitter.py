import sys

import pandas as pd


def set_dataframe_columns(dataframe: pd.DataFrame) -> None:
    # set up dataset columns id
    columns = []
    for i in range(0, dataframe.shape[1] - 1):
        columns.append("col{}".format(i))
    columns.append("label")
    dataframe.columns = columns


if __name__ == '__main__':
    try:
        if len(sys.argv) < 4:
            raise AttributeError

        input_dataset_file_path = sys.argv[1]
        output_dataset_file_path = sys.argv[2]
        output_labels_file_path = sys.argv[3]
        X = pd.read_csv(input_dataset_file_path, delimiter=",", header=None, index_col=False)
        set_dataframe_columns(X)

        labels = X["label"]
        X = X.drop(labels=["label"], axis=1)

        X.to_csv(output_dataset_file_path, index=False, header=False)
        labels.to_csv(output_labels_file_path, index=False, header=False)

    except AttributeError:
        print("Pass 3 arguments to script. File path of input dataset, and file paths for output dataset and labels "
              "files.")

# Example usage:
# python dataset_splitter.py
# "../datasets/mnist.csv"
# "../datasets/mnist_data.csv"
# "../datasets/mnist_labels.csv"
