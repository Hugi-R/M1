import numpy as np
import copy
import math
from math import inf

def rand_x(n):
    return np.random.randint(0,2,n)

def f(q,x):
    sum = 0
    for i in range(len(x)) :
        for j in range(len(x)) :
            sum += q[i][j]*x[i]*x[j]
    return sum

def file_len(datafile):
    for i, _ in enumerate(datafile):
        pass
    return i + 1

def read_q_n_p(path):
    with open(path) as datafile :
        assert file_len(datafile) > 2, "Bad file ! Make sure you have at least 3 lines in your file."
        datafile.seek(0)
        n = int(datafile.readline())
        p = int(datafile.readline())
        q = []
        i = -1
        j = 0
        for line in datafile :
            if(j == 0):
                q.append([])
                i += 1
            q[i].append(int(line))
            j = (j+1)%n
    return q,n,p

def best_neighbour(x,q,p):
    best_x = []
    best_value = inf
    for i in range(len(x)):
        tmp_x = copy.copy(x)
        tmp_x[i] = (tmp_x[i]+1)%2
        if sum(tmp_x) <= p:
            v = f(q, tmp_x)
            if( v < best_value):
                best_value = v
                best_x = tmp_x
    return best_x

def speepest_hill_climbing(q,n,max_step,nb_restart,p=inf):
    best_x = np.zeros(n, dtype=int)
    for _ in range(nb_restart):
        x = rand_x(n)
        while sum(x) > p:
            x = rand_x(n)
        nb_step = 0
        stop = False
        while(nb_step < max_step and not stop):
            x2 = best_neighbour(x,q,p)
            if len(x2) != 0:
                if(f(q,x2) < f(q,x)):
                    x = copy.copy(x2)
                else:
                    stop = True
                nb_step += 1
            else:
                stop = True
        if(f(q,x) < f(q,best_x)):
            best_x = copy.copy(x)
    return best_x

def best_neighbour_not_taboo(x,q,taboo):
    best_x = []
    best_value = inf
    for i in range(len(x)):
        tmp_x = copy.copy(x)
        tmp_x[i] = (tmp_x[i]+1)%2
        if set(np.unique(tmp_x)) not in set(np.unique(taboo)):
            v = f(q, tmp_x)
            if( v < best_value):
                best_value = v
                best_x = tmp_x
    return best_x

def taboo(q,n,taboo_size,max_step):
    taboo = []
    x = rand_x(n)
    best_x = copy.copy(x)
    step = 0
    stop = False
    while(step < max_step and not stop):
        tmp_x = best_neighbour_not_taboo(x,q,taboo)
        if len(tmp_x) == 0:
            stop = True
        else:
            if len(taboo) == taboo_size:
                taboo.pop(0)
            taboo.append(x)
            if f(q,tmp_x) < f(q,best_x):
                best_x = copy.copy(tmp_x)
            x = copy.copy(tmp_x)
            step += 1
    return best_x

def tsp_rand_x(n):
    x = np.arange(1,n+1)
    return np.random.shuffle(x)

def tsp_read(path):
    stringToCity = lambda s : tuple(map(int, s.split()))
    with open(path) as datafile:
        n = int(datafile.readline())
        cities = []
        for l in datafile:
            cities.append(stringToCity(l))
        return cities,n

def tsp_trip_length(x):
    coord = lambda c : (c[1],c[2])
    dist = lambda a,b : math.sqrt((a[0]+b[0])**2 + (a[1]+b[1])**2)
    trip = dist((0,0),coord(x[0]))
    for i in range(len(x)-1):
        trip += dist(coord(x[i]), coord(x[i+1]))
    trip += dist(coord(x[len(x)-1]), (0,0))
    return trip

def tsp_best_neighbour(x):
    best_x = []
    best_value = inf
    for i in range(len(x)):
        for j in range(i+1,len(x)):
            tmp_x = copy.copy(x)
            tmp_x[i], tmp_x[j] = tmp_x[j], tmp_x[i]
            v = tsp_trip_length(tmp_x)
            if v < best_value:
                best_x = copy.copy(tmp_x)
                best_value = v
    return best_x

def tsp_speepest_hill_climbing(cities,max_step,nb_restart):
    best_x = []
    best_value = inf
    for _ in range(nb_restart):
        x = copy.copy(cities)
        np.random.shuffle(x)
        nb_step = 0
        stop = False
        while(nb_step < max_step and not stop):
            tmp_x = tsp_best_neighbour(x)
            if(tsp_trip_length(tmp_x) < tsp_trip_length(x)):
                x = copy.copy(tmp_x)
            else:
                stop = True
            nb_step += 1
        v = tsp_trip_length(x)
        if( v < best_value):
            best_x = copy.copy(x)
            best_value = v
    return best_x

def tsp_best_neighbour_not_taboo(x,taboo):
    best_x = []
    best_value = inf
    for i in range(len(x)):
        for j in range(i+1,len(x)):
            tmp_x = copy.copy(x)
            tmp_x[i], tmp_x[j] = tmp_x[j], tmp_x[i]
            if set(np.unique(tmp_x)) not in set(np.unique(taboo)):
                v = tsp_trip_length(tmp_x)
                if v < best_value:
                    best_x = copy.copy(tmp_x)
                    best_value = v
    return best_x

def tsp_taboo(cities,taboo_size,max_step):
    taboo = []
    x = np.random.shuffle(cities)
    best_x = []
    best_value = inf
    step = 0
    stop = False
    while(step < max_step and not stop):
        tmp_x = tsp_best_neighbour_not_taboo(x,taboo)
        if len(tmp_x) == 0:
            stop = True
        else:
            if len(taboo) == taboo_size:
                taboo.pop(0)
            taboo.append(x)
            v = tsp_trip_length(tmp_x)
            if v < best_value:
                best_x = copy.copy(tmp_x)
                best_value = v
            x = copy.copy(tmp_x)
            step += 1
    return best_x

'''
q,n,p = read_q_n_p("partition6.txt")
x = np.ones(n, dtype=int)
print(x,f(q,x))
x2 = speepest_hill_climbing(q,n,2*n,10)
print(x2,f(q,x2))
x2 = speepest_hill_climbing(q,n,2*n,10,p)
print(x2,f(q,x2))
x3 = taboo(q,n,n,2*n)
print(x3,f(q,x3))
x3 = taboo(q,n,5,2*n)
print(x3,f(q,x3))
x3 = taboo(q,n,1,2*n)
print(x3,f(q,x3))
'''
cities,n = tsp_read("tsp101.txt")
print(cities, n)
print(tsp_trip_length(cities))
#x = tsp_speepest_hill_climbing(cities,n,5)
#print(x, tsp_trip_length(x))
x2 = tsp_taboo(cities,n,2*n)
print(x2, tsp_trip_length(x2))
