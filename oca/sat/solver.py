import types
import itertools
import numpy as np
import utils

sign = lambda x: -1 if x < 0 else 1

def pass_one(solution:list, literal):
    for v in solution:
        if v[0]*v[1] == literal:
            return True
        elif v[0]*v[1] == -literal:
            return False
    return literal

def apply_sol(solution:list, clauses:list):
    cs2 = []
    for c in clauses:
        c2 = []
        valid = False
        for l in c:
            po = pass_one(solution, l)
            if type(po) == bool :
                if po :
                    valid = True
                    break
            else:
                c2.append(po)
        if not valid :
            cs2.append(c2 if c2 != [] else False)
    return cs2
    

def sol_invalid_literal(solution:list, literal):
    for v in solution:
        if v[0]*v[1] == literal:
            return False
        elif v[0]*v[1] == -literal:
            return True
    return False

def sol_dont_make_clause_false(solution:list, clause:list):
    sil = lambda literal: sol_invalid_literal(solution, literal)
    return not all(map(sil, clause))

# still here for testing
def old_check_consistency(solution:list, clauses:list):
    if not solution : # if empty, solution valid
        return True 
    else:
        tmp = lambda clause: sol_dont_make_clause_false(solution, clause)
        return all(map(tmp, clauses))

def check_consistency(solution:list, clauses:list):
    if not solution : # if empty, solution valid
        return True 
    else:
        return all(apply_sol(solution, clauses))



def select(current_clauses:list):
    unit = list(filter(lambda x: len(x) == 1 if type(x) == list else False, current_clauses))
    if unit :
        return (sign(unit[0][0])*unit[0][0], sign(unit[0][0]), None)

    fast_var = np.unique(list(itertools.chain.from_iterable(current_clauses)))

    t = lambda x: not -x in fast_var
    pure = list(filter(t, fast_var))
    if pure :
        return (sign(pure[0])*pure[0], sign(pure[0]), None)

    return (sign(fast_var[0])*fast_var[0], 1, -1)

def backtrack(var:list, clauses:list):
    nb_var = len(var)
    finished = False
    sol = []
    prev_clauses = clauses
    m = 0
    while not finished:
        current_clauses = apply_sol(sol, prev_clauses)
        if all(current_clauses): #check consistency
            prev_clauses = current_clauses
            if current_clauses == [] :
                finished = True
            else:
                sol.append(select(current_clauses))
        else :
            prev_clauses = clauses
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
    test = lambda given, expected: "OK "+str(given) if given == expected else "KO : got "+str(given)+" expected "+str(expected)
    clauses = [[1, -2, -3, 4], [-1, -3, 4], [3, 4], [-4]]
    var = {1, 2, 3, 4}
    sol = backtrack(var,clauses)
    print(test(old_check_consistency(sol, clauses) and (apply_sol(sol, clauses) == []), True))
    
    clauses = [[1, -2, -3, 4], [-1, -3, 4], [3, 4], [-4], [1,2]]
    print(test( pretty_sol(backtrack(var,clauses)) , [] )) #[]

    print(test(check_consistency([(1,1,-1)], [[-1]]) , False)) #False
    print(test(check_consistency([(1,1,-1)], [[-1, 2]]) , True)) #True

    print(test(apply_sol([(1,1,0)], clauses), [[-3, 4], [3, 4], [-4]] ))
    print(test(apply_sol([(4,1,0)], clauses), [False, [1, 2]]))

    var,clauses = utils.read_file("prob/uf20-01.cnf")
    sol = backtrack(var,clauses)
    print(test(old_check_consistency(sol, clauses) and (apply_sol(sol, clauses) == []), True))

    var,clauses = utils.read_file("prob/uf50-01.cnf")
    sol = backtrack(var,clauses)
    print(test(old_check_consistency(sol, clauses) and (apply_sol(sol, clauses) == []), True))
    