for fic in $(ls | grep '.wav')
do
	echo $fic
    sox "$fic" temp.dat && ( grep -v ";" temp.dat | awk '{ print $2 }' > "../enregistrement_perso_csv/$fic.csv") && rm temp.dat
done