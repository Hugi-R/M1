

import utils

def get_vars(clause:list):
    return list(map(abs, clause))

def get_sol_vars(sol:list):
    return list(map(lambda x: x[0], sol))

def clause_in_sol(sol:list, clause:list):
    sol_vars = get_sol_vars(sol)
    return all(map(lambda x: x in sol_vars, get_vars(clause)))

def check_consistency(solution:list, clauses:list):
    if not solution : # if empty, solution valid
        return True 
    valid = [True]*len(clauses)
    for i in range(len(clauses)):
        if clause_in_sol(solution, clauses[i]):
            for v in solution:
                if v[0]*v[1] in clauses[i]:
                    valid[i] = True
                    break # The clause is valid thanks to v
                elif -(v[0]*v[1]) in clauses[i]:
                    valid[i] = False
        else:
            valid[i] = True
        #print(i, valid)
    if valid.count(False) == 0:
        return True
    return False

def select(solution:list, clauses:list, var:list):
    for v in var:
        if not v in list(map(lambda x: x[0], solution)):
            return (v, 1, -1)

def backtrack(var:list, clauses:list):
    nb_var = len(var)
    finished = False
    sol = []
    m = 0
    while not finished:
        if len(sol) > m:
            m = len(sol)
        print(len(sol), " ", m)
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


def pretty_sol(sol:list):
    return list(map((lambda x: x[0]*x[1]), sol))

if __name__ == "__main__":
    #var,clauses = utils.read_file("prob/uf20-01.cnf")
    #var = {1, 2, 3}
    #clauses = [[1, -2, 3], [2], [-3]]
    #sol = [(1, 1, -1), (2, 1, -1), (3, 1, -1)]
    clauses = [[1, -2, -3, 4], [-1, -3, 4], [3, 4], [-4]]
    var = {1, 2, 3, 4}
    sol = [(1, 1, -1), (2, -1, -1), (3, 1, -1), (4, -1, None)]
    #print(check_consistency(sol, clauses))
    #print(select(sol, clauses, var))
    print(pretty_sol(backtrack(var,clauses))) #[(1, -1, None), (2, -1, None), (3, 1, -1), (4, -1, None)]

    clauses = [[1, -2, -3, 4], [-1, -3, 4], [3, 4], [-4], [1,2]]
    print(pretty_sol(backtrack(var,clauses))) #[]

    #print(check_consistency([(1,1,-1)], [[-1]])) #False
    #print(check_consistency([(1,1,-1)], [[-1, 2]])) #True