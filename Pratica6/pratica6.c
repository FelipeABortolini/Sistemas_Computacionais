#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

#define TRAVESSA 10
int porcoes = TRAVESSA;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
sem_t scoz, scan;

void seserve(){
    pthread_mutex_lock(&m);
    int result_try_wait_can = sem_trywait(&scan);

	// while (porcoes == 0) {
	// 	pthread_cond_wait(&cond, &m);
	// }

	porcoes -= 1;

    if(result_try_wait_can == -1 && porcoes == 0){
        // Chamar cozinheiro
        sem_post(&scoz);
		pthread_cond_wait(&cond, &m);
		pthread_mutex_unlock(&m);
    } else {
    	pthread_mutex_unlock(&m);
	}
}

void encheTravessa(){
    int result_try_wait_coz = sem_trywait(&scoz);

    while(result_try_wait_coz == -1){
        result_try_wait_coz = sem_trywait(&scoz);
    }

    porcoes = TRAVESSA;
    for(int i = 0; i < TRAVESSA; i++){
        sem_post(&scan);
		porcoes += 1;
    }
	pthread_cond_signal(&cond);
}

void *canibal(void *p){
	int id = (int) p;
	
	while(1){
		seserve();
		printf("Canibal %d servido.\n", id);
		fflush(stdout);
		sleep(1);
	}
}

void *cozinheiro(void *p){
	while(1){
		encheTravessa();
		printf("Cozinheiro serviu mesa.\n");
	}
}

int main(int argc, char **argv){
	pthread_t td, cz;
	long int i, nc;

	if(argc < 2){
		printf("%s <número canibais>\n", argv[0]);
		return 0;
	}

	nc = atoi(argv[1]);

    sem_init(&scoz, 0, 0);
    sem_init(&scan, 0, TRAVESSA);

	pthread_create(&cz, NULL, cozinheiro, NULL);

	for(i=0; i<nc; i++){
		pthread_create(&td, NULL, canibal, (void*)i);
		pthread_detach(td); // Resultado da thread não será guardado, pois não iremos utilizar pthread_join para acessar esse resultado.
	}

	getchar();

	return 0;
}