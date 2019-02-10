
import matplotlib.image as img
import numpy as np
import matplotlib.pyplot as plt
import json
import os

n_fleurs = 10

def Pretraitement(image_path):
    # This take time, so we use caching
    if not os.path.isfile("dataset.json"):
        #print("Creating dataset.json")
        #js = open("dataset.json", "x")
        dataset = dict()
    else:
        js = open("dataset.json", "r")
        dataset = json.load(js)
        js.close()
    if image_path in dataset:
        return np.array(dataset[image_path])
    else:
        image = img.imread(image_path)
        image2 = np.asarray(image)
        couleur_norma = lambda pixel3: (1/(max(1, pixel3[0]+pixel3[1]+pixel3[2])))*pixel3
        image_norma = np.zeros(image2.shape)
        moyenne = [0,0,0]
        for i in range(len(image2)):
            for j in range(len(image2[i])):
                image_norma[i][j] = couleur_norma(image[i][j])
                moyenne += image_norma[i][j]
        moyenne = moyenne/(image2.shape[0]*image.shape[1])
        dataset[image_path] = moyenne.tolist()
        js = open("dataset.json", "w")
        json.dump(dataset,js)
        js.close()
        return moyenne


if __name__ == "__main__":
    path = "Fleurs/"
    cm = {}
    for file_name in ["ch", "oe", "pe"]:
        cm[file_name] = []
        for i in range(n_fleurs):
            name = path + file_name + str(i+1) + ".png"
            cm[file_name].append(Pretraitement(name))
    fig, ax = plt.subplots()
    ax.scatter(np.array(cm["ch"])[:, 0], np.array(cm["ch"])[:, 1], color="blue")
    ax.scatter(np.array(cm["oe"])[:, 0], np.array(cm["oe"])[:, 1], color="red")
    ax.scatter(np.array(cm["pe"])[:, 0], np.array(cm["pe"])[:, 1], color="yellow")
    plt.show()

    exit(0)
    # Affichage des images de fleurs Chrysanthemes
    for i in range(n_fleurs):
        path = "./Fleurs/"
        file_name = "ch"
        name = path + file_name + str(i+1) + ".png"
        print(name)
        image = img.imread(name)

        image2 = np.asarray(image)
        plt.figure(1)
        plt.subplot(3, 4, i+1)
        print(image2.shape)
        plt.imshow(image2)

    plt.show()

    # Affichage des images de fleurs oeillets
    for i in range(n_fleurs):
        path = "./Fleurs/"
        file_name = "oe"
        name = path + file_name + str(i+1) + ".png"
        print(name)
        image = img.imread(name)

        image2 = np.asarray(image)
        plt.figure(2)
        plt.subplot(3, 4, i+1)
        print(image2.shape)
        plt.imshow(image2)

    plt.show()

    # Affichage des images de fleurs pensees
    for i in range(n_fleurs):
        path = "./Fleurs/"
        file_name = "pe"
        name = path + file_name + str(i+1) + ".png"
        print(name)
        image = img.imread(name)

        image2 = np.asarray(image)
        plt.figure(3)
        plt.subplot(3, 4, i+1)
        print(image2.shape)
        plt.imshow(image2)

    plt.show()