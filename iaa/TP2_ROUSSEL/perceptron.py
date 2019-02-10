import csv
import shutil

import matplotlib.pyplot as plt
import numpy as np
import math
import random

from utils import plot_training


class Perceptron(object):
    """ Classe codant le fonctionnement du perceptron
    dans sa version non stochastique
    """
    def __init__(self, in_features:int, learning_rate:float=0.01, lr_decay:bool=False, max_iter:int=200,
                 early_stopping:bool=False, tol:float=1e-6, display:bool=False, is_batch:bool=True) -> None:
        # paramètres générals de la classe
        self.in_features = in_features              # taille d'entrée du perceptron
        self.lr = learning_rate                     # taux d'apprentissage
        self.lr_decay = lr_decay                    # modifie le taux d'apprentissage à chaque itération
                                                    # en le divisant par le nombre d'itération déjà passée
        self.max_iter = max_iter                    # nombre d'epoch
        self.early_stopping = early_stopping        # arrête l'apprentissage si les poids
                                                    # ne s'améliorent pas
        self.tol = tol                              # différence entre avant et après la
                                                    # mise à jour des poids
        self.display = display                      # affichage de l'apprentissage du perceptron
        self.is_batch = is_batch                    # l'apprentissage se fait par batch
        self.x_extended = False                     # si on utilise un 2e vecteur d'entree etendue

        # initialisation quelconques des connexions synaptiques
        # on considèrera le biais comme la multiplication d'une entrée de valeur 1.0 par un poids associé
        # le biais est utilisé comme seuil de décision du perceptron lors de la prédiction
        #self.weights = np.array([0.2, -0.8, 0.5])
        #self.weights = np.array([-0.09712177,  1.46883398,  0.08352999])
        #self.weights = np.array([-12.58894277,  -9.23054977,  47.25674503])
        #self.weights = np.random.rand(in_features+1)
        self.weights = np.random.normal(0, 1, size=in_features+1)

    def predict_point(self, x:np.ndarray) -> np.ndarray:
        """Prédiction pour un point"""
        if self.x_extended:
            return 1 if np.dot(x,self.weights) > 0 else -1
        else:
            return 1 if np.dot(np.append(x,1),self.weights) > 0 else -1

    def predict(self, X:np.ndarray) -> np.ndarray:
        """Prédiction des données d'entrée par le perceptron

        X est de la frome [nb_data, nb_param]
        La valeur renvoyée est un tableau contenant les prédictions des valeurs de X de la forme [nb_data]
        """
        return np.array(list(map(self.predict_point, X)))
    
    def fit(self, X:np.ndarray, y:np.ndarray, Xp:np.ndarray=None) -> np.ndarray:
        """Apprentissage du modèle du perceptron

        X : données d'entrée de la forme [nb_data, nb_param]
        y : label associée à X ayant comme valeur
                 1 pour la classe positive
                -1 pour la classe négative
            y est de la forme [nb_data]
        Xp : optionel, données d'entrée étendue de la forme [nb_data, nb_param+1]
        """
        self.x_extended = not(Xp is None) 
        if not self.x_extended :
            Xp = X

        # vérification des labels
        assert np.all(np.unique(y) == np.array([-1, 1]))

        # Sauvegarde tous les calculs de la somme des distances euclidiennes pour l'affichage
        if self.display:
            shutil.rmtree('./img_training', ignore_errors=True)
            metric = []
        
        # initialisation d'un paramètre permettant de stopper les itérations lors de la convergence
        stabilise = False

        if self.display :
            print("Starting weights : ",self.weights)

        # apprentissage sur les données
        errors = np.zeros(self.max_iter)
        for iteration in range(self.max_iter):
            # variable stockant l'accumulation des coordonnées
            modif_w = np.zeros(len(self.weights))

            # prédiction des points (on peut le faire ici car batch)
            out = self.predict(Xp)

            # choisir l'equation de droite qui donne le moins d'erreur
            # permet de débloquer le perceptron dans certaines situations,
            # utile surtout si lr est petit.
            # sum(abs(y-out)/2) permet de compter le nombre d'erreur plus rappidement que np.sum(y != out)
            if self.display:
                print("mal classé : ", sum(abs(y-out)/2))
            if sum(abs(y-out)/2) > len(y)/2 :
                self.weights = -self.weights
                out = self.predict(Xp)

            old_weights = np.array(self.weights)

            if self.lr_decay:
                #if iteration != 0:
                #    if errors[iteration-1] != errors[iteration]:
                #        lr_modif_n += 1
                #lr = self.lr/lr_modif_n
                #lr = self.lr / (iteration+1)
                lr = self.lr / ((iteration%50)+1)
                #lr = self.lr/math.log10((iteration % 50)+2)
                #lr = self.lr*((errors[iteration]+1)/len(y))
            else:
                lr = self.lr

            if self.display :
                print("lr : ", lr)

            if self.is_batch :
                # batch learning
                for point, label, predicted in zip(Xp, y, out):
                    # accumulation des coordonnées suivant la classe si les données sont mal classées
                    if predicted != label:
                        errors[iteration] += 1
                        if self.x_extended :
                            modif_w += label*point
                        else:
                            modif_w += label*np.append(point, 1)
                self.weights += lr*modif_w
                #if errors[iteration] < len(y)*0.25 :
                #    self.is_batch = False
                #    print("\n----------\nSwitching to online\n----------\n")
            else :
                # online learning
                for point, label in zip(X,y):
                    predicted = self.predict_point(point)
                    if predicted != label:
                        self.weights += lr*label*np.append(point, 1)
                errors[iteration] = sum(abs(y-out)/2)

            # affichage de l'erreur et de la ligne séparatrice
            if self.display:
                plot_training(iteration, X, y, self.weights, list(errors[:iteration+1]))
        
            # stopper l'algorithme lorsque l'algorithme converge
            if self.early_stopping:
                stabilise = abs(sum(old_weights - self.weights)) < self.tol
                if stabilise:
                    # on affiche le dernier hyperplan calculé
                    if self.display :
                        plot_training(iteration, X, y, self.weights, list(errors[:iteration+1]))
                    # on arrete l'apprentissage
                    break
        if self.display :
            print("End weights : ",self.weights)
        
        self.x_extended = False

    def score(self, X:np.ndarray, y:np.ndarray) -> float:
        """Retourne la moyenne de précision sur les données de test et labels
        """
        return np.sum(y == self.predict(X)) / len(X)


if __name__ == "__main__":
    p = Perceptron(2)
    X = np.array([[0.5,0.5],[1,1],[-1,-1]])
    print(p.predict(X))