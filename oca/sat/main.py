# ROUSSEL Hugo

import time
import sys, getopt

import utils
import solver
import coloration

help_str = """
%s file [k] [-t:(cnf|col)] [-s|-v] [-o:[file]]
Solve a SAT problem. By default display a human readable solution. Use -s if you want the same output as an output file.
file : path to the problem to solve.
 k   : only relevant if k-coloring problem. Number of color.
-t   : optionnal, force the type of the file.
-s   : optionnal, silent. Only print the solution.
-v   : optionnal, verbose. Print progress update, usefull for large problem (>100 variables).
-o   : optionnal, print the formated solution to a file. Does not impact terminal display. If no argument are given, use the same filename as the input, with a .sol extension.
"""

if __name__ == "__main__":
    verbose_level = 1
    output_file = None
    opts, argv = getopt.gnu_getopt(sys.argv, "hvst:o:", [])

    t = ""
    for opt,arg in opts:
        if opt == "-h":
            if len(argv) == 1:
                print(help_str%argv[0])
                exit(0)
            else:
                if verbose_level > 0 :
                    print("WARNING : -h ignored.")
        elif opt == "-s":
            verbose_level = 0
        elif opt == "-v":
            verbose_level = 2
        elif opt == "-t":
            if arg[1:] in ["cnf", "col"]:
                t = arg[1:]
            else:
                print("Bad type provided for -t. Options are 'cnf' or 'col'.")
                exit(0)
        elif opt == "-o":
            if arg != ":" :
                output_file = open(arg[1:], "w")
            else:
                name = argv[1][:-3]+"sol"
                output_file = open(name, "w")

        else:
            print("Unknow option '%s'."%opt)
            exit(0)

    if len(argv) == 1:
        print("No file provided. Use -h to print help.")
        exit(0)
    path = argv[1]

    if t == "":
        t = path[-3:]
        if not t in ["cnf", "col"]:
            print("Unknow type '%s. Maybe use -t ?."%t)
            exit(0)

    col = False
    if t == "cnf":
        if verbose_level > 0 :
            print("Loading sat file '%s' ..."%path)
        var,clauses = utils.read_file(path)
        if verbose_level > 0 :
            print("Done.")
    elif t == "col":
        if len(argv) < 3:
            print("No k provided.")
            exit(0)
        col = True
        k = int(argv[2])
        if verbose_level > 0 :
            print("Loading coloration file '%s' ..."%path)
        graph = utils.read_graph(path)
        var,clauses = coloration.graph_to_sat(graph, k)
        if verbose_level > 0 :
            print("Done.")
    else:
        print("Unknow file '%s'."%path)
        exit(0)

    if verbose_level > 0 :
        print("Solving ...")
        start = time.perf_counter()
    sol = solver.backtrack(var, clauses, (verbose_level==2))
    if verbose_level > 0 :
        print("Done in %f s."%(time.perf_counter()-start))
        print("--- Printing solution (if [] then there's none) ---")

    if verbose_level > 0:
        psol = solver.pretty_sol(sol)
        if col :
            print(coloration.pretty_sol(psol, k))
        else:
            print(psol)

    if verbose_level == 0 or output_file :
        if col :
            for s in coloration.pretty_sol(solver.pretty_sol(sol), k):
                r = "%d %d\n"%s
                if output_file:
                    output_file.write(r)
                if verbose_level == 0:
                    print(r[:-1])
        else:
            for s in sol:
                r = "%d %d\n"%s[:2]
                if output_file:
                    output_file.write(r)
                if verbose_level == 0:
                    print(r[:-1])

    if verbose_level > 0 :
        print("--- End ---")


