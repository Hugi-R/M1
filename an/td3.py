import math
import numpy as np

def map_fenetre(fct, X, taille_f, ):
    y = []
    recouvrement = math.floor(taille_f/2)
    for i in range(0,len(X)-taille_f+1, recouvrement):
        y.append(fct(X[i:i+taille_f], taille_f))
    return y

def spectrogram (X, taille_f):
    return np.abs(map_fenetre(np.fft.fft, X, taille_f))[:,0:math.ceil(taille_f/2)]

E = lambda t, f : sum(list(map(lambda x : x*x, t)))/f
X = np.array([1,2,3,4,5,6,7,8,9,10])
print(spectrogram(X, 5))