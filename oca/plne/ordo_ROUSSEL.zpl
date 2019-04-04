# ROUSSEL Hugo

param fichier := "jobshop.in";  # le fichier d'entree
param dureeMax := 12;           # la duree d'execution (wall clock time) maximale autorisee
param coutMax := 999;           # le cout maximal autorise

set Machine := { read fichier as "<2s>" match "^s .*" } ;                   # l'ensemble des machines
param Cout[Machine] := read fichier as "<2s> 3n" match "^s .*" ;            # le cout horaire d'une machine
set Tache := { read fichier as "<2s>" match "^e .*" } ;                     # l'ensemble des taches
param Duree[Tache*Machine] := read fichier as "<2s, 3s> 4n" match "^e .*" ; # la duree d'une tache sur une machine

var x[Tache*Machine] binary;# la tache i est-elle execute sur la machine j ?
var D;                      # Duree max pour une machine
var C;                      # Cout total

# On peut utiliser D et/ou C à minimiser
# exemple avec jobshop.in : "D + 0.8 * C" donnera D = 8 et C = 236 
minimize Z : D;
subto uneTache : forall<i> in Tache : sum<j> in Machine : x[i,j] == 1;                      # chaque tache doit etre execute
subto wallClockTime : forall<j> in Machine : sum<i> in Tache : x[i,j] * Duree[i,j] <= D;    # le temps de travail d'une machine ne doit pas depasser D
subto cout : sum<i> in Tache : sum<j> in Machine : x[i,j]*Duree[i,j]*Cout[j] == C;          # calcul du cout d'execution total

# Contraintes optionnelles : commenter si non utilisee.
subto tmax : D <= dureeMax;     # limite sur la duree
subto cmax : C <= coutMax;      # limite sur le cout

