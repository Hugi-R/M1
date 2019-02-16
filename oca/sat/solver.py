

import utils

def check_consistency(solution:list, clauses:list):
    if not solution : # if empty, solution valid
        return True 
    for c in clauses:
        valid = [True]*
        for v in solution:
            if v[0]*v[1] in c:
                valid.append(True)
                break # The clause is valid thanks to v
            elif -(v[0]*v[1]) in c:
                print(c, v, valid)
                valid.append(False)
            else:
                valid.append(True) # We suppose var not set will validate the clause
        if valid.count(True) == 0:
            return False
    return True

def select(solution:list, clauses:list, var:list):
    for v in var:
        if not v in list(map(lambda x: x[0], solution)):
            return (v, 1, -1)

def backtrack(var:list, clauses:list):
    nb_var = len(var)
    finished = False
    sol = []
    while not finished:
        if check_consistency(sol, clauses):
            if len(sol) == nb_var :
                finished = True
            else:
                sol.append(select(sol, clauses, var))
        else :
            v = sol.pop()
            while (len(sol) > 0) and (v[2] is None):
                v = sol.pop()
            if not v[2] is None:
                sol.append((v[0],v[2],None))
            else:
                return []
    return sol




if __name__ == "__main__":
    #var,clauses = utils.read_file("prob/uf20-01.cnf")
    var = {1, 2, 3}
    clauses = [[1, -2, 3], [2], [-3]]
    sol = [(1, 1, -1), (2, 1, -1), (3, 1, -1)]

    print(check_consistency(sol, clauses))
    #print(select(sol, clauses, var))
    print(backtrack(var,clauses))