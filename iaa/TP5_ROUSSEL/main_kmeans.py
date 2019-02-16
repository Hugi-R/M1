# author: Benjamin Chamand, Thomas Pelligrini

from kmeans import KMeans
import matplotlib.pyplot as plt
from scipy.misc import imread
import numpy as np

def load_dataset(path):
     im = imread(path)
     im = np.array(im, dtype="float32")/255
     shape = im.shape
     im = im.reshape((shape[0]*shape[1],shape[2]))
     return im, shape

def recolor(X, shape, y):
    n_class = len(np.unique(y))
    mean_color = [0]*(n_class)
    for i in range(n_class):
        cluster = [X[j] for j in range(len(X)) if y[j] == i]
        mean_color[i] = sum(cluster)/len(cluster)
    #print(mean_color)
    img = list(map(lambda x : mean_color[x], y))
    img = np.reshape(img, shape)
    #print(img)
    plt.imshow(img)
    plt.axis('off')
    plt.show()
    

def main():
    #filepath = "./data/self_test.csv"
    filepath = "picasso.jpg"

    # chargement des données
    data, shape= load_dataset(filepath)

    # initialisation de l'objet KMeans
    kmeans = KMeans(n_clusters=3,
                    max_iter=10,
                    early_stopping=True,
                    tol=1e-6,
                    display=False)

    # calcule les clusters
    kmeans.fit(data)

    prediction = kmeans.predict(data)
    print(prediction)
    recolor(data, shape, prediction)

    input("Press any key to exit...")


if __name__ == "__main__":
    main()
