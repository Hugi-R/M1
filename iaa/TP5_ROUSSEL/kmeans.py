# author: Benjamin Chamand, Thomas Pelligrini

import shutil

import numpy as np

import math
import random


class KMeans(object):
    def __init__(self, n_clusters:int, max_iter:int, early_stopping:bool=False,
                 tol:float=1e-4, display:bool=False) -> None:
        self.n_clusters = n_clusters            # Nombre de clusters
        self.max_iter = max_iter                # Nombre d'itération
        self.early_stopping = early_stopping    # arrête l'apprentissage si
        self.tol = tol                          # seuil de tolérance entre 2 itérations
        self.display = display                  # affichage des données

        self.cluster_centers = None             # Coordonnées des centres de regroupement
                                                # (centre de gravité des classes)

    def _compute_distance(self, vec1:np.ndarray, vec2:np.ndarray) -> float:
        """Retourne la distance quadratique entre vec1 et vec2 (squared euclidian distance)
        """
        assert len(vec1) == len(vec2), "Vectors must be same dimension"
        return sum((vec1-vec2)**2)
        #return sum(abs(vec1-vec2))
        #return max(abs(vec1-vec2))


    def _compute_inertia(self, X:np.ndarray, y:np.ndarray) -> float:
        """Retourne la Sum of Squared Errors entre les points et le centre de leur
        cluster associe
        """
        inertia = 0
        for i in range(len(X)):
            center = self.cluster_centers[y[i]]
            inertia += self._compute_distance(X[i], center)
        return inertia


    def _update_centers(self, X:np.ndarray, y:np.ndarray) -> None:
        """Recalcule les coordonnées des centres des clusters
        """
        for i in range(self.n_clusters):
            cluster = [X[j] for j in range(len(X)) if y[j] == i]
            if(len(cluster) == 0):
                 print(self.n_clusters, "\n",X,"\n", y,"\n", i, "\n",self.cluster_centers)
            #print("Cluster : ", cluster)
            #print("Sum cluster : ",sum(cluster))
            self.cluster_centers[i] = sum(cluster)/len(cluster)

    def predict(self, X:np.ndarray) -> np.ndarray:
        """attribue un indice de cluster à chaque point de data

        X = données
        y = cluster associé à chaque donnée
        """
        # nombre d'échantillons
        n_data = X.shape[0]
        y = np.zeros(n_data, dtype=int)
        for i in range(n_data):
            y[i] = np.argmax(list(map(lambda c : -self._compute_distance(X[i], self.cluster_centers[c]), range(self.n_clusters))))
            #for c in range(0, self.n_clusters):
            #    if self._compute_distance(X[i], self.cluster_centers[c]) <= self._compute_distance(X[i], self.cluster_centers[y[i]]) :
                    #print(self._compute_distance(X[i], self.cluster_centers[c]) ," <= ", self._compute_distance(X[i], self.cluster_centers[y[i]]))
            #        y[i] = c
        return y

    def fit(self, X:np.ndarray) -> None:
        """Apprentissage des centroides
        """
        # Récupère le nombre de données
        n_data = X.shape[0]

        # Sauvegarde tous les calculs de la somme des distances euclidiennes pour l'affichage
        if self.display:
            shutil.rmtree('./img_training', ignore_errors=True)
            metric = []

        # 2 cas à traiter :
        #   - soit le nombre de clusters est supérieur ou égale au nombre de données
        #   - soit le nombre de clusters est inférieur au nombre de données
        if self.n_clusters >= n_data:
            # Initialisation des centroides : chacune des données est le centre d'un clusteur
            self.cluster_centers = np.zeros(self.n_clusters, X.shape[1])
            self.cluster_centers[:n_data] = X
        else:
            # Initialisation des centroides
            uniq = np.unique(X, axis=0)
            self.cluster_centers = []
            for i in range(self.n_clusters):
                j = random.randint(0, len(uniq))
                self.cluster_centers.append(uniq[j])
                uniq = np.delete(uniq, j, axis=0)
            #while True:
            #    self.cluster_centers = np.array([uniq[i] for i in np.random.randint(0, len(uniq), self.n_clusters, int)])
            #    if len(self.cluster_centers) != len(np.unique(self.cluster_centers, 0)):
            #        break #No do-while loop in python :'(

            # initialisation d'un paramètre permettant de stopper les itérations lors de la convergence
            stabilise = False

            # Exécution de l'algorithme sur plusieurs itérations
            for i in range(self.max_iter):
                # détermine le numéro du cluster pour chacune de nos données
                #print(self.cluster_centers)
                y = self.predict(X)

                # calcule de la somme des distances initialiser le paramètres
                # de la somme des distances
                if i == 0:
                    current_distance = self._compute_inertia(X, y)

                # mise à jour des centroides
                #print("\nUpdate centers")
                #print(self.cluster_centers)
                #print(y)
                self._update_centers(X, y)

                # mise à jour de la somme des distances
                old_distance = current_distance
                current_distance = self._compute_inertia(X, y)

                # stoppe l'algorithme si la somme des distances quadratiques entre
                # 2 itérations est inférieur au seuil de tolérance
                if self.early_stopping:
                    stabilise = abs(old_distance - current_distance) < self.tol
                    if stabilise:
                        break

    def score(self, X:np.ndarray, y:np.ndarray) -> float:
        """Calcule le score de pureté
        """
        n_data = X.shape[0]

        y_pred = self.predict(X)

        score = 0
        for i in range(self.n_clusters):
            _, counts = np.unique(y[y_pred == i], return_counts=True)
            score += counts.max()

        score /= n_data

        return score

if __name__ == "__main__":
    km = KMeans(2, 0)
    X = np.array([[-0.5,-0.5],[1,1],[3,3]])
    y = np.array([0,0,1])
    km.cluster_centers = np.array([[0.5,0.5], [2,2]])
    print(km._compute_distance(np.array([0,0]), np.array([0.5,0.5])))
    print(km._compute_inertia(X,y))
    print(km.predict(X))
    print("Cluster centers beffore update : ",km.cluster_centers)
    km._update_centers(X,y)
    print("Cluster centers after update : ",km.cluster_centers)
