param fichier := "jobshop.in";
param dureeMax := 12;

set Machine := { read fichier as "<2s>" match "^s .*" } ;
param Cout[Machine] := read fichier as "<2s> 3n" match "^s .*" ;
set Tache := { read fichier as "<2s>" match "^e .*" } ;
param Duree[Tache*Machine] := read fichier as "<2s, 3s> 4n" match "^e .*" ;
var x[Tache*Machine] binary;

minimize cout : sum<i> in Tache : sum<j> in Machine : x[i,j]*Duree[i,j]*Cout[j];
subto uneTache : forall<i> in Tache : sum<j> in Machine : x[i,j] == 1;
subto tmax : forall<j> in Machine : sum<i> in Tache : x[i,j] * Duree[i,j] <= dureeMax; 

