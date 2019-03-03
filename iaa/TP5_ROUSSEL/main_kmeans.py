# author: Benjamin Chamand, Thomas Pelligrini

from kmeans import KMeans
import matplotlib.pyplot as plt
from scipy.misc import imread, imsave
import numpy as np

def load_dataset(path):
     im = imread(path)
     im = np.array(im, dtype="float32")/255
     shape = im.shape
     im = im.reshape((shape[0]*shape[1],shape[2]))
     return im, shape

def recolor(shape, y, colors):
    img = list(map(lambda x : colors[x], y))
    img = np.reshape(img, shape)
    return img
    
def mse3(X, Y):
    return sum((X-Y)**2)/len(X)

def mse(X, Y):
    return sum(mse3(X, Y))/3

def main():
    #filepath = "./data/self_test.csv"
    filepath = "onion.jpg"

    # chargement des données
    data, shape= load_dataset(filepath)

    # initialisation de l'objet KMeans
    k = 3
    #for k in range(2, 7, 2):
    kmeans = KMeans(n_clusters=k,
                    max_iter=10,
                    early_stopping=True,
                    tol=1e-6,
                    display=False)

    # calcule les clusters
    kmeans.fit(data)

    prediction = kmeans.predict(data)
    #print(prediction)
    name = "%s_k%d.png" % (filepath, k)
    colors =  kmeans.cluster_centers #[[1,0,0],[0,1,0],[0,0,1]]
    rimg = recolor(shape, prediction, colors)
    print("MSE : ", mse(data, np.reshape(rimg, data.shape)))
    imsave(name, rimg)

    input("Press any key to exit...")


if __name__ == "__main__":
    main()
    #a,_ = load_dataset("iles.jpg")
    #b,_ = load_dataset("iles.jpg_k8.png")
    #print(mse(a,b))
