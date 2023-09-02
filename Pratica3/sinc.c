#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int current_thread = 1;

void * th1(){
	while(1){
		pthread_mutex_lock(&mutex);
        while (current_thread != 1) {
            pthread_cond_wait(&cond, &mutex);
        }
		printf("1\n");
		fflush(stdout);
		current_thread = 2;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

void * th2(){
	while(1){
		pthread_mutex_lock(&mutex);
        while (current_thread != 2) {
            pthread_cond_wait(&cond, &mutex);
        }
		printf("2\n");
		fflush(stdout);
		current_thread = 3;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		sleep(2);
	}
}

void * th3(){
	while(1){
		pthread_mutex_lock(&mutex);
        while (current_thread != 3) {
            pthread_cond_wait(&cond, &mutex);
        }
		printf("3\n");
		fflush(stdout);
		current_thread = 1;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
		sleep(3);
	}
}


int main(int argc, char **argv){
	pthread_t thread1, thread2, thread3;
	

	if(pthread_create(&thread1, NULL, th1, NULL)) {
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}
	

	if(pthread_create(&thread2, NULL, th2, NULL)) {
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}
	
	if(pthread_create(&thread3, NULL, th3, NULL)) {
		fprintf(stderr, "Error creating thread\n");
		return 1;
	}
	

	if(pthread_join(thread1, NULL)) {
		fprintf(stderr, "Error joining thread\n");
		return 1;
	}

	return 0;
}