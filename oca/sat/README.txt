# By ROUSSEL Hugo, hugo.roussel@univ-tlse3.fr

Require Python 3 (tested with 3.7.1)

'main.py -h' to display the help.

Basic usage :
'main.py myProblem.cnf' will solve the SAT problem in 'myProblem.cnf' and display its solution in the terminal.
'main.py myProblem.cnf -o:mySolution.sol' will solve the SAT problem in 'myProblem.cnf', display some info in the terminal, and write the solution in 'mySolution.sol'.
'main.py myProblem.col 3 -o:mySolution.sol' does the same, but with a k-coloring problem and k = 3.

Unit tests :
'solver.py' and 'coloration.py' contain some basic unit test in their main.