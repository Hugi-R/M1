# ROUSSEL Hugo

import solver

sommet_to_var = lambda s, k: (s-1)*k + 1
var_to_sommet = lambda v, k: int((v-1)/k + 1)

def var_to_sc(v, k):
    s = var_to_sommet(v, k)
    c = v - ((s-1)*k)
    return s,c

def pretty_sol(sol, k):
    psol = []
    for s in sol:
        if s > 0:
            psol.append(var_to_sc(s, k))
    return psol

def une_couleur_par_sommet(sommet:int, k:int):
    base_varname = sommet_to_var(sommet, k)
    clauses = []
    c = []
    for i in range(k):
        c.append(base_varname+i)
    clauses.append(c)
    for i in range(k):
        for j in range(k):
            if i != j:
                clauses.append([-(base_varname+i), -(base_varname+j)])

    return clauses

def pas_de_couleur_adjacente(s1:int, s2:int, k:int):
    v1 = sommet_to_var(s1, k)
    v2 = sommet_to_var(s2, k)
    clauses = []
    for i in range(k):
        clauses.append([-(v1+i), -(v2+i)])
    return clauses

def graph_to_sat(graph:list, k:int):
    clauses = []
    var = set()
    for (i,j) in graph:
        if not i in var:
            var.add(i)
            clauses.extend(une_couleur_par_sommet(i, k))
        if not j in var:
            var.add(j)
            clauses.extend(une_couleur_par_sommet(j, k))
        clauses.extend(pas_de_couleur_adjacente(i, j, k))
    return var,clauses



if __name__ == "__main__":
    test = lambda a, b: "OK" if a == b else "KO"
    ok = True
    for i in range(30):
        ok = ok and var_to_sommet(sommet_to_var(i, 10), 10) == i
    print(test(ok, True))

    clauses = une_couleur_par_sommet(1, 3)
    print(test(solver.check_consistency([(1,1,0), (2,-1,0), (3,-1,0)], clauses), True)) #True
    print(test(solver.check_consistency([(1,1,0), (2,1,0), (3,-1,0)], clauses), False)) #False
    print(test(solver.check_consistency([(1,1,0), (2,1,0), (3,1,0)], clauses), False)) #False
    print(test(solver.check_consistency([(1,-1,0), (2,-1,0), (3,-1,0)], clauses), False)) #False

    clauses = pas_de_couleur_adjacente(1, 2, 2)
    print(test(solver.check_consistency([(1,1,0), (2,-1,0), (3,-1,0), (4,1,0)], clauses), True)) #True
    print(test(solver.check_consistency([(1,1,0), (2,-1,0), (3,1,0), (4,-1,0)], clauses), False)) #False

    var,clauses = graph_to_sat([(1,2), (2,3), (3,1)], 3)
    print(test(solver.apply_sol([(1,1,0), (2,-1,0), (3,-1,0), (4,-1,0), (5,1,0), (6,-1,0), (7,-1,0), (8,-1,0), (9,1,0)], clauses), [])) #True
    print(test(solver.check_consistency([(1,1,0), (2,1,0), (3,-1,0), (4,-1,0), (5,1,0), (6,-1,0), (7,-1,0), (8,-1,0), (9,1,0)], clauses), False)) #False
    print(test(solver.check_consistency([(1,1,0), (2,-1,0), (3,-1,0), (4,1,0), (5,-1,0), (6,-1,0), (7,-1,0), (8,-1,0), (9,1,0)], clauses), False)) #False


