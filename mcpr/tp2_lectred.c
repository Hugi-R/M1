/* UPS/IRIT
   Lecteurs-redacteurs partageant un fichier dans lequel
   les premiers lisent (a plusieurs) et les seconds ecrivent
   (en exclusion mutuelle)
*/
/* Complete par Hugo Roussel */

#include <stdio.h>
#include <string.h> /* strerror */
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>

#define NB_MAX_LECTEURS   10
#define NB_MAX_REDACTEURS 10
#define NB_LECTURES        5
#define NB_ECRITURES       1

/* variables moniteur */
pthread_cond_t lecture = PTHREAD_COND_INITIALIZER;
pthread_cond_t ecriture = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
bool redaction = false;
int nbLecture = 0;
int videEcriture = 0;

int fd;

/*---------------------------------------------------------------------*/
void thdErreur(int codeErr, char *msgErr, void *codeArret) {
/*---------------------------------------------------------------------*/
  fprintf(stderr, "%s: %d soit %s \n", msgErr, codeErr, strerror(codeErr));
  pthread_exit(codeArret);
}

void lock (pthread_mutex_t *mutex) {
  int e;
  if((e = pthread_mutex_lock(mutex)) != 0){
    printf("ERROR : pthread_mutex_lock returned %d, aborting.", e);
    exit(e);
  }
}

void unlock (pthread_mutex_t *mutex) {
  int e;
  if((e = pthread_mutex_unlock(mutex)) != 0){
    printf("ERROR : pthread_mutex_unlock returned %d, aborting.", e);
    exit(e);
  }
}

/*---------------------------------------------------------------------*/
void debutLecture(int monNum) {
/*---------------------------------------------------------------------*/
  lock(&mutex);
  while(redaction || videEcriture != 0)
    pthread_cond_wait(&lecture, &mutex);
  nbLecture += 1;
  if(videEcriture == 0) pthread_cond_signal(&lecture);
  unlock(&mutex);
}

/*---------------------------------------------------------------------*/
void finLecture(int monNum) {
/*---------------------------------------------------------------------*/
  lock(&mutex);
  nbLecture -= 1;
  if(nbLecture == 0) pthread_cond_signal(&ecriture);
  unlock(&mutex);
}

/*---------------------------------------------------------------------*/
void debutEcriture(int monNum) {
  lock(&mutex);
  while(nbLecture > 0 || redaction){
    videEcriture += 1;
    pthread_cond_wait(&ecriture, &mutex);
    videEcriture -= 1;
  }
  redaction = true;
  unlock(&mutex);
}

void finEcriture(int monNum) {
/*---------------------------------------------------------------------*/
  lock(&mutex);
  redaction = false;
  if(videEcriture != 0){
    pthread_cond_signal(&ecriture);
  } else {
    pthread_cond_signal(&lecture);
  }
  unlock(&mutex);
}

/*---------------------------------------------------------------------*/
void *threadLecteur(void *arg) {
/*---------------------------------------------------------------------*/
  int nbLus, i;
  int *monNum = (int *)arg;
  char unCar;

  for (i = 0; i < NB_LECTURES; i++) {
    // Demander a pouvoir acceder en lecture au fichier partage
    debutLecture(*monNum);

    /* NOTE : la représentation du fichier est commune aux threads.
      Ils partagent donc le meme curseur, la sortie des lecteurs est
      donc tres dure a prevoir.
      Si le partage du curseur n'est pas souhaite, il faut que chaque lecteur
      ouvre son propre fichier.
    */
    if (lseek(fd, 0, SEEK_SET) < 0)
      thdErreur(errno, "Lseek debut fichier", monNum);

    printf("Lecteur %d: Lecture de :\n", *monNum);
    do {
      if ((nbLus = read(fd, &unCar, sizeof(char))) < 0)
        thdErreur(errno, "Read fichier lecture", monNum);
      if (nbLus > 0)
        printf("%c", unCar);
    } while (nbLus > 0);
    printf("\n");

    // Signaler la fin de l'acces en lecture au fichier partage
    finLecture(*monNum);
    }
  printf ("Lecteur %d, j'ai fini mon execution \n", *monNum);
}

/*---------------------------------------------------------------------*/
void *threadRedacteur(void *arg) {
/*---------------------------------------------------------------------*/
  int i, nbEcrits;
  int *monNum = (int *)arg;
  char monCar = *monNum+65;

  for (i = 0; i < NB_ECRITURES; i++) {
    // Demander a pouvoir acceder en ecriture au fichier partage
    debutEcriture(*monNum);

    if (lseek(fd, 0, SEEK_END) < 0)
      thdErreur(errno, "Lseek fin fichier", monNum);

    if ((nbEcrits = write(fd, &monCar, 1)) < 0)
      thdErreur(errno, "Write fichier", monNum);
    printf("Redacteur %d: Ecriture de %c \n", *monNum, monCar);

    // Signaler la fin de l'acces en ecriture au fichier partage
    finEcriture(*monNum);
    }
  printf ("Redacteur %d, j'ai fini mon execution \n", *monNum);
}

/*---------------------------------------------------------------------*/
int main(int argc, char*argv[]) {
/*---------------------------------------------------------------------*/
  pthread_t lesLecteurs[NB_MAX_LECTEURS];
  pthread_t lesRedacteurs[NB_MAX_REDACTEURS];
  int       rangLecteurs[NB_MAX_LECTEURS];
  int       rangRedacteurs[NB_MAX_REDACTEURS];
  int nbLecteurs, nbRedacteurs, nbThds;
  int i, etat;

  if (argc != 3) {
    printf("Usage: %s <Nb lecteurs <= %d> <Nb redacteurs <= %d> \n",
            argv[0], NB_MAX_LECTEURS, NB_MAX_REDACTEURS);
    exit(1);
  }

  nbLecteurs = atoi(argv[1]);
  if (nbLecteurs > NB_MAX_LECTEURS)
    nbLecteurs = NB_MAX_LECTEURS;

  nbRedacteurs = atoi(argv[2]);
  if (nbRedacteurs > NB_MAX_REDACTEURS)
    nbRedacteurs = NB_MAX_REDACTEURS;

  nbThds = nbLecteurs + nbRedacteurs;

  /* Creation du fichier partage */
  if ((fd = open("LectRed_shared", O_RDWR|O_CREAT, 0666)) < 0) {
    printf("Erreur ouverture fichier %s\n", strerror(errno));
    exit(1);
  }

  /*  A completer pour assurer la synchronisation souhaitee */

  /* Lancement des threads lecteurs et redacteurs */
  for (i = 0; i < nbLecteurs; i++) {
    rangLecteurs[i] = i;
    if ((etat = pthread_create(&lesLecteurs[i], NULL,
                               threadLecteur, &rangLecteurs[i])) != 0)
      thdErreur(etat, "Creation lecteurs", NULL);
  }

  for (i = 0; i < nbRedacteurs; i++) {
    rangRedacteurs[i] = i;
    if ((etat = pthread_create(&lesRedacteurs[i], NULL,
                               threadRedacteur, &rangRedacteurs[i])) != 0)
      thdErreur(etat, "Creation redacteurs", NULL);
  }

  /* Attente de la fin des threads */
  for (i = 0; i < nbLecteurs; i++)
    if ((etat = pthread_join(lesLecteurs[i], NULL)) != 0)
      thdErreur(etat, "Join lecteurs", NULL);

  for (i = 0; i < nbRedacteurs; i++)
    if ((etat = pthread_join(lesRedacteurs[i], NULL)) != 0)
      thdErreur(etat, "Join lecteurs", NULL);

  /*  A completer pour assurer la synchronisation souhaitee */

  /* Fermeture du fichier partage */
  close(fd);

  printf ("\nFin de l'execution du main \n");
}
