import time

import utils
import solver

if __name__ == "__main__":
    var,clauses = utils.read_file("prob/uuf125-01.cnf")
    #print(clauses)
    start = time.perf_counter()
    print(solver.pretty_sol(solver.backtrack(var, clauses)))
    print(time.perf_counter()-start)

