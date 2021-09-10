import numpy as np
import pandas as pd

from sklearn.manifold import TSNE

X = pd.read_csv(dataset_file, delimiter=",", header=None, index_col=False)

X_embedded = TSNE(n_components=2).fit_transform(X)