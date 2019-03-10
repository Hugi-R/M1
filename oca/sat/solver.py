# ROUSSEL Hugo

import time
import types
import itertools
#import pymp
import utils

sign = lambda x: -1 if x < 0 else 1

def pass_one(pretty_solutions:list, literal):
    if literal in pretty_solutions :
        return True
    elif -literal in pretty_solutions:
        return False
    return literal

# still here for testing
def pass_one_v0(pretty_solutions:list, literal):
    for s in pretty_solutions:
        if s == literal:
            return True
        elif s == -literal:
            return False
    return literal

def pass_two(clause:list):
    c = []
    for l in clause:
        if type(l) == bool :
            if l :
                return []
        else:
            c.append(l)
    if c == []:
        return False
    return c

"""
# A parrallel apply_sol using pymp, not effective
def apply_sol_pymp(solution:list, clauses:list):
    sol = pretty_sol(solution)

    cs2 = pymp.shared.list([None]*len(clauses))
    #print(cs2)
    with pymp.Parallel(8) as p:
        for i in p.range(len(clauses)):
            cs2[i] = list(map(lambda l: pass_one(sol, l), clauses[i]))

    #print(cs2)
    cs3 = []
    for c in cs2:
        c2 = pass_two(c)
        if c2 != []:
            cs3.append(c2)
        if c2 == False:
            break # bad solution, no need to finish
    return cs3
"""

# still here for testing
def apply_sol_v0(solution:list, clauses:list):
    sol = pretty_sol(solution)
    tmp = lambda c: map(lambda l: pass_one(sol, l), c)
    cs2 = map(tmp, clauses)
    cs3 = []
    for c in cs2:
        c2 = pass_two(c)
        if c2 != []:
            cs3.append(c2)
        if c2 == False:
            break # bad solution, no need to finish
    return cs3

def apply_sol_v1(solution:list, clauses:list):
    sol = pretty_sol(solution)
    cs2 = []
    for c in clauses:
        c2 = []
        valid = False
        for l in c:
            po = pass_one(sol, l)
            if type(po) == bool :
                if po :
                    valid = True
                    break
            else:
                c2.append(po)
        if not valid :
            cs2.append(c2 if c2 != [] else False)
            if c2 == []:
                break # bad solution, no need to finish
    return cs2

apply_sol = apply_sol_v1

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

# still here for testing
def check_consistency(solution:list, clauses:list):
    if not solution : # if empty, solution valid
        return True 
    else:
        return all(apply_sol(solution, clauses))



def select(current_clauses:list):
    """
    unit = list(filter(lambda x: len(x) == 1 if type(x) == list else False, current_clauses))
    if unit :
        return (sign(unit[0][0])*unit[0][0], sign(unit[0][0]), None)
    """
    flat_clauses = list(itertools.chain.from_iterable(current_clauses))
    fast_var = set(flat_clauses)
    """
    t = lambda x: not -x in fast_var
    pure = list(filter(t, fast_var))
    if pure :
        return (sign(pure[0])*pure[0], sign(pure[0]), None)
    
    count = dict.fromkeys(fast_var, 0)
    maxi = flat_clauses[0]
    for v in flat_clauses:
        count[v] += 1
        if count[v] > count[maxi]:
            maxi = v
    return (sign(v)*v, sign(v), -sign(v))
    """
    v = next(iter(fast_var))
    return (sign(v)*v, sign(v), -sign(v))
    

def backtrack(var:list, clauses:list, log=False):
    finished = False
    sol = []
    prev_clauses = [clauses]
    m = 0
    bt_cpt = 0
    while not finished:
        if log :
            if len(sol) > m:
                m = len(sol)
                print("Max solution length : ",m)
        current_clauses = apply_sol(sol, prev_clauses[-1])
        prev_clauses.append(current_clauses)
        if all(current_clauses): #check consistency
            if current_clauses == [] :
                finished = True
            else:
                sol.append(select(current_clauses))
        else :
            bt_cpt += 1
            prev_clauses.pop()
            v = sol.pop()
            while (len(sol) > 0) and (v[2] is None):
                prev_clauses.pop()
                v = sol.pop()
            if not v[2] is None:
                sol.append((v[0],v[2],None))
            else:
                return []
            if log :
                print("Bactrack n° %d. New solution length : %d"%(bt_cpt, len(sol)))
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
    print(test(apply_sol([(4,1,0)], clauses), [False]))

    var,clauses = utils.read_file("prob/uf20-01.cnf")
    start = time.perf_counter()
    sol = backtrack(var,clauses)
    print(test(old_check_consistency(sol, clauses) and (apply_sol(sol, clauses) == []), True), " t=",time.perf_counter()-start) #best : 0.012; 0.041; 0.019; 0.011; 0.008; 0.0036

    var,clauses = utils.read_file("prob/uf50-01.cnf")
    start = time.perf_counter()
    sol = backtrack(var,clauses)
    print(test(old_check_consistency(sol, clauses) and (apply_sol(sol, clauses) == []), True), " t=",time.perf_counter()-start) #best : 20.40; 0.544; 0.211; 0.11; 0.074; 0.179
    