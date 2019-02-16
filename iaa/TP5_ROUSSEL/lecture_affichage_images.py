# -*- coding: utf-8 -*-
"""
Created on 08/02/19

@author: Thomas Pellegrini
"""

im='picasso.jpg'

from scipy.misc import imread
import matplotlib.pyplot as plt

data = imread(im)
print(data.shape) 

plt.imshow(data)
plt.axis('off')
plt.show()
