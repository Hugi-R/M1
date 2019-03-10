# By ROUSSEL Hugo, hugo.roussel@univ-tlse3.fr

Require Python 3 (tested with 3.7.1)

'main.py -h' to display the help.
main.py file [k] [-t:(cnf|col)] [-s|-v] [-o:[file]]
Solve a SAT problem. By default display a human readable solution. Use -s if you want the same output as an output file.
file : path to the problem to solve.
 k   : only relevant if k-coloring problem. Number of color.
-t   : optionnal, force the type of the file.
-s   : optionnal, silent. Only print the solution.
-v   : optionnal, verbose. Print progress update, usefull for large problem (>100 variables).
-o   : optionnal, print the formated solution to a file. Does not impact terminal display. If no argument are given, use the same filename as the input, with a .sol extension.

Basic usage :
'main.py myProblem.cnf' will solve the SAT problem in 'myProblem.cnf' and display its solution in the terminal.
'main.py myProblem.col 3' does the same, but with a k-coloring problem and k = 3.
'main.py myProblem.cnf -o:' will solve the SAT problem in 'myProblem.cnf', display the solution and ome info in the terminal, and write the solution in 'myProblem.sol'.
'main.py myProblem.cnf -o:mySolution.sol' will solve the SAT problem in 'myProblem.cnf', display some info in the terminal, and write the solution in 'mySolution.sol'.
'main.py myProblem.col 3 -o:mySolution.sol' does the same, but with a k-coloring problem and k = 3.

Unit tests :
'solver.py' and 'coloration.py' contain some basic unit test in their main.