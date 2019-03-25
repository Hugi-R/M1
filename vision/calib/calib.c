#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "limace.h"
#include "salade.h"
#include "erreurs.h"

/* Codes de retour */
#define OK 0
#define HELP 1
#define ERR_NB_PARAM 2
#define ERR_MAT_3D 3
#define ERR_MAT_3D_TYPE 4
#define ERR_MAT_2D 5
#define ERR_MAT_2D_TYPE 6
#define ERR_MAT_OUT 7


void Syntaxe(void)
{
  Usage("MatricePoints3D MatricePoints2D MatriceProjectionPerspective\n"
        "-h\n");
}

void Description(void)
{
  Mesg("ROLE\n");
  Mesg("\tCalibrage 3D d'une camera\n");
  Mesg("ARGUMENTS\n");
  Mesg("\tMatricePoints3D : Matrice nx3 (format Matrix) des coordonnees des points de la mire\n");
  Mesg("\tMatricePoints2D : Matrice nx2 (format Matrix) des coordonnees des projections dans l'image des points de la mire\n");
  Mesg("\tMatriceProjectionPerspective : nom du fichier destination qui va contenir la matrice 3x4 (format Matrix) de projection perspective\n");
  Mesg("OPTION\n");
  Mesg("\t-h : affichage de l'aide\n");
  Mesg("DIAGNOSTIC (codes de retour)\n");
  Mesg("\t0 : operation realisee sans probleme\n");
  Mesg("\t1 : aide demandee\n");
  Mesg("\t2 : mauvais nombre de parametres\n");
  Mesg("\t3 : probleme d'ouverture du fichier des coordonnees 3D\n");
  Mesg("\t4 : type de matrice 3D incorrect (Double attendu)\n");
  Mesg("\t5 : probleme d'ouverture du fichier des coordonnees 2D\n");
  Mesg("\t6 : type de matrice 2D incorrect (Double attendu)\n");
  Mesg("\t7 : probleme lors du calcul de la matrice de projection perspective\n");
}

int main(int argc, char *argv[])
{
  /* Declaration de la fonction qui sera definie apres la fonction main */
  Matrix Calibrage(Matrix MatP3, Matrix Matp2);
  /* Declaration des variables de la fonction main */
  Matrix MatP3=NULL,Matp2=NULL,MatProjPers=NULL;
  
  /* Initialisation du mecanisme d'affichage des messages */
  InitMesg(argv);
  /* Verification du nombre de parametres */
	if (argc!=2 && argc!=4)
	{
	  Syntaxe();
	  return ERR_NB_PARAM;
	}
	if (argc==2)
	{
	  if (!strcmp(argv[1],"-h"))
	  {
	    Syntaxe();
	    Description();
	    return HELP;
	  }
	  else /* un seul parametre different de -h */
	  {
	    Syntaxe();
	    return ERR_NB_PARAM;
	  }
	}
	/* Lecture de la matrice des points 3D */
	MatP3=MatReadAsc(argv[1]);
	if (MatP3==NULL)
	{
		Erreur("Probleme lors de la lecture de la matrice des coordonnees 3D");
		return ERR_MAT_3D;
	}
	/* Verification du type de la matrice */
	if (MatType(MatP3)!=Double)
	{
		Erreur("La matrice des coordonnees 3D doit etre Double");
		MatFree(&MatP3);
		return ERR_MAT_3D_TYPE;
	}
	/* Lecture de la matrice des points 2D */
	Matp2=MatReadAsc(argv[2]);
	if (Matp2==NULL)
	{
		Erreur("Probleme lors de la lecture de la matrice des coordonnees 2D");
		MatFree(&MatP3);
		return ERR_MAT_2D;
	}
	/* Verification du type de la matrice */
	if (MatType(Matp2)!=Double)
	{
		Erreur("La matrice des coordonnees 2D doit etre Double");
		MatFree(&MatP3);
		MatFree(&Matp2);
		return ERR_MAT_2D_TYPE;
	}

	/* Estimation de ma matrice de projection perspective */
	MatProjPers=Calibrage(MatP3,Matp2);
	if (MatProjPers==NULL)
	{
		Erreur("Probleme lors de l'estimation de la matrice de projection perspective");
		MatFree(&MatP3);
		MatFree(&Matp2);
		return ERR_MAT_OUT;
	}
	/* Ecriture de la matrice resultat */
	MatWriteAsc(MatProjPers,argv[3]);
	/* Liberation des matrices */
	MatFree(&MatP3);
    MatFree(&Matp2);
    MatFree(&MatProjPers);
    
	return OK;
}

/* Dot product A.B
 */
Matrix MatDot(Matrix MA, Matrix MB){
	assert(MatNbCol(MA) == MatNbRow(MB));
	size_t r = MatNbRow(MA);
	size_t c = MatNbCol(MB);
	size_t n = MatNbRow(MB);
	Matrix Mres = MatAlloc(Double, r, c);
	double **res = MatGetDouble(Mres);
	double **A = MatGetDouble(MA);
	double **B = MatGetDouble(MB);
	for(size_t i = 0; i < r; ++i){
		for(size_t j = 0; j < c; ++j){
			double sum = 0;
			for(size_t p = 0; p < n; ++p){
				sum += A[i][p]*B[p][j];
			}
			res[i][j] = sum;
		}
	}
	return Mres;
}

/* Calibrage 3D : estimation au sens des moindres carres totaux de la matrice
 * de projection perspective a partir de correspondances 3D <--> 2D
 */
Matrix Calibrage(Matrix MatP3, Matrix Matp2)
{
		assert(MatNbRow(MatP3) == MatNbRow(Matp2));
    double **P3,**p2;
    
		size_t n = MatNbRow(MatP3);

    P3=MatGetDouble(MatP3);
    p2=MatGetDouble(Matp2);
    
		Matrix MatA = MatAlloc(Double, n*2, 12);
		double **A = MatGetDouble(MatA);
		for(size_t i = 0; i < n; i+=2){
			A[i][0] = P3[i][0];
			A[i][1] = P3[i][1];
			A[i][2] = P3[i][2];
			A[i][3] = 1;
			A[i][4] = 0;
			A[i][5] = 0;
			A[i][6] = 0;
			A[i][7] = 0;
			A[i][8] = -p2[i][0]*P3[i][0];
			A[i][9] = -p2[i][0]*P3[i][1];
			A[i][10] = -p2[i][0]*P3[i][2];
			A[i][11] = -p2[i][0];

			A[i+1][0] = 0;
			A[i+1][1] = 0;
			A[i+1][2] = 0;
			A[i+1][3] = 0;
			A[i+1][4] = P3[i][0];
			A[i+1][5] = P3[i][1];
			A[i+1][6] = P3[i][2];
			A[i+1][7] = 1;
			A[i+1][8] = -p2[i][0]*P3[i][0];
			A[i+1][9] = -p2[i][0]*P3[i][1];
			A[i+1][10] = -p2[i][0]*P3[i][2];
			A[i+1][11] = -p2[i][0];
		}

		Matrix MatAT = MatAlloc(Double, 12, n*2);
		double **AT = MatGetDouble(MatAT);
		for(size_t i = 0; i < 12; ++i){
			for(size_t j = 0; j < 2*n; ++j){
				AT[i][j] = A[j][i];
			}
		}

		Matrix pVal;
		Matrix pVec;
		Matrix dot = MatDot(MatAT, MatA);
		if(SymEig(dot, &pVal, &pVec) != 0){
			
		}

		double **val = MatGetDouble(pVal);
		size_t m = MatNbRow(pVal);
		size_t min = 0;
		for (size_t i = 0; i < m; ++i){
			if(val[i][0] < val[min][0]){
				min = i;
			}
		}

		printf("min : %lf\n", val[min][0]);
		MatWriteAsc(pVal, "");
		


    MatFree(&dot);
		MatFree(&pVal);
		MatFree(&pVec);
	  MatFree(&MatA);
		MatFree(&MatAT);
    return NULL;
}

