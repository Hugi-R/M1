import numpy as np

from bayes import GaussianBayes
from utils import load_dataset, plot_scatter_hist
from matplotlib import cm
import matplotlib.pyplot as plt
#from mpl_toolkits.mplot3d import Axes3D
from matplotlib.colors import ListedColormap

import Donnees

def plot_surface(data,label,fun):
    fig = plt.figure()
    ax = fig.add_subplot(111)
    x = np.arange(0.15, 0.45, 0.005)
    y = np.arange(0.05, 0.35, 0.005)
    X, Y = np.meshgrid(x, y)
    zs = np.array([fun(np.array([[x,y]])) for x,y in zip(np.ravel(X), np.ravel(Y))])
    Z = zs.reshape(X.shape)

    #cmap = cm.get_cmap('viridis', 3)
    #color = cmap(np.linspace(0, 1, 3))
    color = np.array([[1,0,0,1],[0,1,0,1],[0,0,1,1]])
    cmap = ListedColormap(color)
    p = ax.pcolormesh(X,Y,Z, alpha=0.2, cmap=cmap)
    #fig.colorbar(p)
    for i in np.unique(label):
        c = np.array([data[j] for j in range(len(data)) if label[j] == i])
        ax.scatter(c[:,0], c[:,1], color=color[i])
    #ax.plot(X, Y, Z)

    #ax.set_xlabel('X Label')
    #ax.set_ylabel('Y Label')
    #ax.set_zlabel('Z Label')

    plt.show()

def build_dataset():
    X = []
    y = []
    path = "Fleurs/"
    f_type = ["ch", "oe", "pe"]
    for i in range(len(f_type)):
        for j in range(10):
            name = path + f_type[i] + str(j+1) + ".png"
            flower = Donnees.Pretraitement(name)
            X.append([flower[0], flower[1]])
            y.append(i)
    return X,y

def build_dataset_centre():
    X = []
    y = []
    path = "Fleurs/"
    f_type = ["ch", "oe", "pe"]
    for i in range(len(f_type)):
        for j in range(10):
            name = path + f_type[i] + str(j+1) + ".png"
            flower = Donnees.Pretraitement_centre(name)
            X.append([flower[1][1], flower[1][2]])
            y.append(i)
    return X,y

def main():
    X,y = build_dataset_centre()
    X = np.array(X)
    y = np.array(y)

    # affichage
    #plot_scatter_hist(train_data, train_labels)
    #print(train_labels)

    # Instanciation de la classe GaussianB
    #classes = np.unique(y)
    #n_classes = len(classes)
    #priors = np.zeros(n_classes)
    #for c in range(n_classes):
    #    priors[c] = len([X[i] for i in range(len(X)) if y[i] == classes[c]])
    #priors /= len(X)
    priors = [0.3, 0.42, 0.18]
    print("Priors : ", priors)
    g = GaussianBayes(priors=priors, diag=False)

    # Apprentissage
    g.fit(X, y)
    plot_surface(X,y,g.predict)
    print("Prédiction : ",g.predict(X))

    # Score
    #score = g.score(train_data, train_labels)
    score = g.score(X, y)
    print("precision : {:.2f}".format(score))

    input("Press any key to exit...")


if __name__ == "__main__":
    main()
