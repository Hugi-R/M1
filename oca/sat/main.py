
import utils
import solver

if __name__ == "__main__":
    var,clauses = utils.read_file("prob/uf50-01.cnf")
    #print(clauses)
    print(solver.pretty_sol(solver.backtrack(var, clauses)))

