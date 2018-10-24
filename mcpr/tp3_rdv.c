#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h> //strerror
#include <pthread.h>


#define N_MAX 20

/* variables partagees */
int nbThread = 0;

/* variables moniteur */
pthread_cond_t attendre = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int nbEnAttente = 0;

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

void sync(){
    lock(&mutex);
    nbEnAttente += 1;
    if(nbEnAttente < nbThread){
        pthread_cond_wait(&attendre, &mutex);
    }
    nbEnAttente -= 1;
    pthread_cond_signal(&attendre);
    unlock(&mutex);
}

void *actionsThread(void *arg){
    printf("%lu : Je fais un certain traitement.\n", pthread_self());
    sleep(1);
    printf("%lu : J’arrive au point de rendez-vous.\n", pthread_self());
    sync();
    printf("%lu : Tout le monde est arrivé, je continue.\n", pthread_self());
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t idThd[N_MAX];

    if(argc != 2){
        printf("Usage : %s <Nb_thread>", argv[0]);
        exit(1);
    }

    nbThread = atoi(argv[1]);
    if(nbThread > N_MAX)
        nbThread = N_MAX;

    /* lancer les threads */
    int etat;
    for(int i = 0; i < nbThread; ++i){
        if ((etat = pthread_create(&idThd[i], NULL, actionsThread, NULL)) != 0)
            thdErreur(etat, "Creation threads", NULL);
    }

    /* attente thread */
    for(int i = 0; i < nbThread; ++i){
        if ((etat = pthread_join(idThd[i], NULL)) != 0)
            thdErreur(etat, "Join threads", NULL);
    }

    printf ("\nFin de l'execution du main \n");
    return 0;
}
