import numpy as np
import pandas as pd

from viskit.ivhd import IVHD
from sklearn.manifold import TSNE


dataset_file = 'mnist_7k.csv'
X = pd.read_csv(dataset_file, delimiter=",", header=None, index_col=False)
X_embedded = IVHD(n_components=2).fit_transform(X)
