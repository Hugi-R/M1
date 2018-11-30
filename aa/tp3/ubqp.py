import numpy as np
import copy

def rand_x(n):
    return np.random.randint(0,2,n)

def f(q,x):
    sum = 0
    for i in range(len(x)) :
        for j in range(len(x)) :
            sum += q[i][j]*x[i]*x[j]
    return sum

def file_len(datafile):
    for i, l in enumerate(datafile):
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

def best_neighbour(x,q):
    tmp_x = copy.copy(x)
    tmp_x[0] = (tmp_x[0]+1)%2
    best_x = tmp_x
    best_value = f(q,tmp_x)
    for i in range(1,len(x)):
        tmp_x = copy.copy(x)
        tmp_x[i] = (tmp_x[i]+1)%2
        v = f(q, tmp_x)
        if( v > best_value):
            best_value = v
            best_x = tmp_x
    return best_x

def speepest_hill_climbing(q,n,max_step,nb_restart):
    x = rand_x(n)
    nb_step = 0
    stop = False
    while(nb_step < max_step and not stop):
        x2 = best_neighbour(x,q)
        if(f(q,x2) > f(q,x)):
            x = copy.copy(x2)
        else:
            stop = True
        nb_step += 1
    return x


q,n,p = read_q_n_p("partition6.txt")
x = rand_x(n)
print(x,f(q,x))
x2 = speepest_hill_climbing(q,n,10)
print(x2,f(q,x2))
#print(f(q,x))
