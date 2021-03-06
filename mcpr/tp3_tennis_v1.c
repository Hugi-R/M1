/* Hugo Roussel */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h> //strerror
#include <pthread.h>


#define NB_JOUEUR_MAX 20

/* variables partagees */
int nbJoueur = 0;

/* variables moniteur */
pthread_cond_t joueurs = PTHREAD_COND_INITIALIZER;
pthread_cond_t match = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int nbJsurTerrain = 0;

/*---------------------------------------------------------------------*/
void thdErreur(int codeErr, char *msgErr, void *codeArret) {
  fprintf(stderr, "%s: %d soit %s \n", msgErr, codeErr, strerror(codeErr));
  pthread_exit(codeArret);
}

void lock (pthread_mutex_t *mutex) {
  int e;
  if((e = pthread_mutex_lock(mutex)) != 0){
    fprintf(stderr, "ERROR : pthread_mutex_lock returned %d, aborting.", e);
    exit(e);
  }
}

void unlock (pthread_mutex_t *mutex) {
  int e;
  if((e = pthread_mutex_unlock(mutex)) != 0){
    fprintf(stderr, "ERROR : pthread_mutex_unlock returned %d, aborting.", e);
    exit(e);
  }
}
/*---------------------------------------------------------------------*/

void demanderTerrain(){
    lock(&mutex);
    if(nbJsurTerrain == 2)
        pthread_cond_wait(&joueurs, &mutex);

    nbJsurTerrain += 1;
    if(nbJsurTerrain == 1){
        pthread_cond_signal(&joueurs);
        pthread_cond_wait(&match, &mutex);
    }
    pthread_cond_signal(&match);
    unlock(&mutex);
}

void libererTerrain(){
    lock(&mutex);
    nbJsurTerrain -= 1;
    if(nbJsurTerrain == 0)
        pthread_cond_signal(&joueurs);
    unlock(&mutex);
}

void *thdJoueur(void *arg){
    printf("%lu : Je suis un joueur qui demande un terrain.\n", pthread_self());
    demanderTerrain();
    printf("%lu : Je joue.\n", pthread_self());
    sleep(1);
    printf("%lu : J'ai fini de jouer.\n", pthread_self());
    libererTerrain();
    //printf("%lu : J'ai libérer le terrain'.\n", pthread_self());
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t idThd[2][NB_JOUEUR_MAX];

    if(argc != 2){
        printf("Usage : %s <Nb_equipes_joueurs>\n", argv[0]);
        exit(1);
    }

    nbJoueur = atoi(argv[1])*2; // *2 pour etre sur d'avoir un nbr pair de joueur
    if(nbJoueur > NB_JOUEUR_MAX)
        nbJoueur = NB_JOUEUR_MAX;

    /* lancer les joueurs */
    int etat;
    for(int i = 0; i < nbJoueur; ++i){
        if ((etat = pthread_create(&idThd[0][i], NULL, thdJoueur, NULL)) != 0)
            thdErreur(etat, "Creation threads", NULL);
    }

    /* attente thread */
    for(int i = 0; i < nbJoueur; ++i){
        if ((etat = pthread_join(idThd[0][i], NULL)) != 0)
            thdErreur(etat, "Join threads", NULL);
    }

    printf ("\nFin de l'execution du main \n");
    return 0;
}
