import numpy as np

from bayes import GaussianBayes
from utils import load_dataset, plot_scatter_hist


def main():
    train_data, train_labels = load_dataset("./data/train.csv")
    test_data, test_labels = load_dataset("./data/test.csv")

    train_data_3d, train_labels_3d = load_dataset("./data/3d_train.csv")
    test_data_3d, test_labels_3d = load_dataset("./data/3d_test.csv")

    train = train_data_3d,train_labels_3d
    test = test_data_3d,test_labels_3d

    # affichage
    #plot_scatter_hist(train_data, train_labels)
    #print(train_labels)

    # Instanciation de la classe GaussianB
    classes = np.unique(train[1])
    n_classes = len(classes)
    priors = np.zeros(n_classes)
    for c in range(n_classes):
        priors[c] = len([train[0][i] for i in range(len(train[0])) if train[1][i] == classes[c]])
    priors /= len(train[0])
    print("Priors : ", priors)
    g = GaussianBayes(priors=priors, diag=True)

    # Apprentissage
    g.fit(train[0], train[1])
    #print(g.predict(train_data))

    # Score
    #score = g.score(train_data, train_labels)
    score = g.score(test[0], test[1])
    print("precision : {:.2f}".format(score))

    input("Press any key to exit...")


if __name__ == "__main__":
    main()
