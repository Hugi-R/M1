import argparse

import numpy as np

from perceptron import Perceptron
from utils import load_dataset
from tqdm import tqdm


def main():
    # chargement des données
    # le fichier .csv contient 3 groupes de points 2D
    # la première colonne du fichier correspond à x1, la deuxième à x2 
    # et la troisième correspond au groupe auquel est associé le point
    filepath = "./data/2Dpoints.csv"
    data, labels = load_dataset(filepath)

    # On garde le groupe de points 1 et 2
    data = data[(labels==1) | (labels==2)]
    labels = labels[(labels==1) | (labels==2)]
    labels = np.where(labels == 1, 1, -1)

    # On garde le groupe de points 1 et 3
    #data = data[(labels==0) | (labels==2)]
    #labels = labels[(labels==0) | (labels==2)]
    #labels = np.where(labels == 0, 1, -1)

    # Instanciation de la classe perceptron
    p = Perceptron(2, learning_rate=1, lr_decay=True,
                   early_stopping=True, display=True)

    # Apprentissage
    p.fit(data, labels)

    # Score
    score = p.score(data, labels)
    print("precision : {:.2f}".format(score))

    input("Press any key to exit...")


def test_n(n:int):
    filepath = "./data/2Dpoints.csv"
    data, labels = load_dataset(filepath)

    # On garde le groupe de points 1 et 2
    data = data[(labels==0) | (labels==1)]
    labels = labels[(labels==0) | (labels==1)]
    labels = np.where(labels == 0, 1, -1)

    p = Perceptron(2, learning_rate=1, lr_decay=True,
                   early_stopping=True, display=False)

    # points étendus
    data_ext = np.array(list(map(lambda x: np.append(x,1), data)))

    mean_score = 0
    imperfects = []
    for i in tqdm(range(n)):
        new_weights = np.random.normal(0, 1, size=p.in_features+1)
        p.weights = new_weights 
        p.fit(data, labels, data_ext)
        score = p.score(data, labels)
        if score != 1.0 :
            imperfects.append(new_weights)
        mean_score += score
    mean_score /= n
    print("mean score : ", mean_score)
    print("Imperfects : ", imperfects)



if __name__ == "__main__":
    main()
    #test_n(100)
