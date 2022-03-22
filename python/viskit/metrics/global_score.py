import math
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import confusion_matrix
from numpy import linalg as linalg


class GlobalMetric:
    def __init__(self, n_neighbors=2):
        self.model = KNeighborsClassifier(n_neighbors=n_neighbors)
        self.embedding_confusion_matrix = None
        self.original_confusion_matrix = None
        self.original_difference_indexes = None
        self.embedding_difference_indexes = None

    def calculate_embedding_confusion_matrix(self, data, labels):
        (
            self.embedding_confusion_matrix,
            self.embedding_difference_indexes,
        ) = self.__calculate_confusion_matrix(data, labels)

    def calculate_original_confusion_matrix(self, data, labels):
        (
            self.original_confusion_matrix,
            self.original_difference_indexes,
        ) = self.__calculate_confusion_matrix(data, labels)

    def save_embedding_confusion_matrix(self):
        if self.embedding_confusion_matrix is not None:
            self.embedding_confusion_matrix.to_csv(
                "/Users/bartoszminch/Documents/Repositories/viskit/python/results"
                "/embedding_confusion_matrix.csv"
            )

    def save_original_confusion_matrix(self):
        if self.original_confusion_matrix is not None:
            self.original_confusion_matrix.to_csv(
                "/Users/bartoszminch/Documents/Repositories/viskit/python/results"
                "/original_confusion_matrix.csv"
            )

    def calculate_forbenius(self):
        res = math.sqrt(
            abs(self.original_confusion_matrix - self.embedding_confusion_matrix)
        )
        return linalg.norm(res)

    def __calculate_confusion_matrix(self, data, labels):
        dataset_train, dataset_test, labels_train, labels_test = train_test_split(
            data, labels, test_size=0.3
        )
        self.model.fit(dataset_train, labels_train)
        predicted_labels = self.model.predict(dataset_test)
        res = np.flatnonzero(predicted_labels != labels_test)
        return (
            confusion_matrix(labels_test, predicted_labels, labels=labels.unique()),
            res,
        )
