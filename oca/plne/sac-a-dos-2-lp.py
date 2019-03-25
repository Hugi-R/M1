#!/usr/bin/python3
# coding: utf-8
# Début de programme python pour transformer une instance du sac à dos en LP
# 	le fichier peut contenir des lignes de commentaires commençant par #
# 	la première ligne non commentée doit contenir la capacité
# 	les autres lignes doivent décrire les objets, 1 par ligne, d'abord une id puis le poids puis la valeur

import sys

path = sys.argv[1]

fichier_entree = open(path,'r')
fichier_sortie = open(path[:-3]+"lp",'w')

objectif = "" ; objectif_sep = "" ; deja_capacite = False
variables_binaires = ""
contraintes = ""
for ligne in fichier_entree:
	toks=ligne.split()
	if len(toks) >0 and toks[0] != '#':
		if not deja_capacite:
			capacite = toks[0]
			deja_capacite = True
		else: 
			v = "x" + toks[0]
			variables_binaires += v + " "
			objectif = objectif + objectif_sep + toks[2] + " " + v
			contraintes += objectif_sep + toks[1] + " " + v
			objectif_sep = " + "

fichier_sortie.write("Maximize\n")
fichier_sortie.write(objectif+"\n")
fichier_sortie.write("Subject To\n")
fichier_sortie.write(contraintes+" <= "+capacite+"\n")
fichier_sortie.write("Binary\n")
fichier_sortie.write(variables_binaires+"\n")
fichier_sortie.write("End\n")

fichier_entree.close()
fichier_sortie.close()

