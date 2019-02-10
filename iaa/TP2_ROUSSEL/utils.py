import csv
import os
from typing import Tuple

import matplotlib.pyplot as plt
import numpy as np
from mpl_toolkits.mplot3d import Axes3D


def load_dataset(pathname:str) -> Tuple[np.ndarray, np.ndarray]:
    """Load a dataset in csv format.

    Each line of the csv file represents a data from our dataset and each
    column represents the parameters.
    The last column corresponds to the label associated with our data.

    Parameters
    ----------
    pathname : str
        The path of the csv file.

    Returns
    -------
    data : ndarray
        All data in the database.
    labels : ndarray
        Labels associated with the data.
    """
    # check the file format through its extension
    if pathname[-4:] != '.csv':
        raise OSError("The dataset must be in csv format")
    # open the file in read mode
    with open(pathname, 'r') as csvfile:
        # create the reader object in order to parse the data file
        reader = csv.reader(csvfile, delimiter=',')
        # extract the data and the associated label
        # (he last column of the file corresponds to the label)
        data = []
        labels = []
        for row in reader:
            data.append(row[:-1])
            labels.append(row[-1])
        # converts Python lists into NumPy matrices
        # in the case of the list of labels, generate an int id per class
        data = np.array(data, dtype=np.float)
        lookupTable, labels = np.unique(labels, return_inverse=True)
    # return data with the associated label
    return data, labels


def plot_training(iteration:int, data:np.ndarray, labels:np.ndarray, weights:np.ndarray,
                  metric:list=None, figure:int=1, save_png:bool=False) -> None:
    customPalette = ['#630C3A', '#39C8C6', '#D3500C', '#FFB139', '#04AF00', '#39A7FF',
                     '#7519CC', '#79E7FF', '#1863C15', '#B72EB9', '#EC2328', '#C86D39']
    fig = plt.figure(figure, clear=True)

    # nombre de dimensions
    n_dim = data.shape[1]
    n_subplot = 2 if metric else 1

    ax = fig.add_subplot(1, n_subplot, 1)
    ax.set_title("Iteration {}".format(iteration))
    for y in np.unique(labels):
        x = data[labels == y]
        # add data points
        ax.scatter(x=x[:,0],
                    y=x[:,1],
                    alpha=0.20,
                    color=customPalette[int(y)])
        # add label
        ax.annotate(int(y),
                    x.mean(0),
                    horizontalalignment='center',
                    verticalalignment='center',
                    size=20, weight='bold',
                    color=customPalette[int(y)])
    
    # affiche la droite séparatrice
    if weights[1] != 0:
        l = np.linspace(np.amin(data[:,0]), np.amax(data[:,0]))
        slope = -weights[0]/weights[1]  
        intercept = -weights[2]/weights[1]
        ax.plot(l, (slope*l)+intercept, '--k')

    if metric:
        ax = fig.add_subplot(1, n_subplot, 2)
        ax.set_title("Elements mal classés")
        plt.plot(metric, '-', color=customPalette[-1])
    
    if save_png:
        os.makedirs('./img_training', exist_ok=True)
        plt.savefig("./img_training/im{}.png".format(iteration))
    # met à jour l'affichage
    plt.pause(0.01)
