import numpy as np
import sys

from viskit.scoring.local_score import LocalMetric


if __name__ == "__main__":
    local_metrics = LocalMetric()

    X = np.loadtxt(sys.argv[1], delimiter=",")
    labels = np.loadtxt(sys.argv[2], delimiter=",")

    for i in range(3, len(sys.argv), 2):
        Y = np.loadtxt(sys.argv[i], delimiter=",")

        local_metrics.calculate_knn_gain_and_dr_quality(
            X_lds=Y,
            X_hds=X,
            labels=labels,
            method_name=sys.argv[i+1],
        )

    local_metrics.visualize("./metrics_data/")

# python metric_calculator.py /Users/bartoszminch/Documents/Repositories/dataset_viskit/datasets/mnist_7k_data.csv
# /Users/bartoszminch/Documents/Repositories/dataset_viskit/datasets/mnist_7k_labels.csv
# ./metrics_data/output_ivhd_binary_distances.csv ivhd_binary_distances
# ./metrics_data/output_ivhd_regular_distances.csv ivhd_regular_distances
