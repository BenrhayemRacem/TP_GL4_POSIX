#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<unistd.h>

pthread_mutex_t segmentAB, segmentBC, segmentCD, segmentEB, segmentFA;
void *departDeA(void *arg) {
    int i = *(int *) (arg);
    pthread_mutex_lock(&segmentAB);
    printf("segment AB occupe par le train  %d\n", i);
    usleep(1000000);
    printf("Train %d quitte le segment AB\n", i);
    pthread_mutex_unlock(&segmentAB);
    pthread_mutex_lock(&segmentBC);
    printf("segment BC occupe par le train  %d\n", i);
    usleep(1000000);
    printf("Train %d quitte le segment BC\n", i);
    pthread_mutex_unlock(&segmentBC);
    pthread_mutex_lock(&segmentCD);
    printf("segment CD occupe par le train  %d\n", i);
    usleep(1000000);
    printf("Train %d quitte le segment CD\n", i);
    pthread_mutex_unlock(&segmentCD);
}

void *departDeF(void *arg) {
    int i = *(int *) (arg);
    pthread_mutex_lock(&segmentFA);
    printf("segment FA occupe par le train %d\n", i);
    usleep(1000000);
    printf("Train %d quitte le segment FA\n", i);
    pthread_mutex_unlock(&segmentFA);
    departDeA(arg);
}

void *departDeE(void *arg) {
    int i = *(int *) (arg);
    pthread_mutex_lock(&segmentEB);
    printf("segment EB occupe par le train  %d\n", i);
    usleep(1000000);
    printf("Train %d quitte le segment EB\n", i);
    pthread_mutex_unlock(&segmentEB);
    pthread_mutex_lock(&segmentBC);
    printf("segment BC occupe par le train  %d\n", i);
    usleep(1000000);
    printf("Train %d quitte le segment BC\n", i);
    pthread_mutex_unlock(&segmentBC);
    pthread_mutex_lock(&segmentCD);
    printf("segment CD occupe par le train  %d\n", i);
    usleep(1000000);
    printf("Train %d quitte le segment CD\n", i);
    pthread_mutex_unlock(&segmentCD);
}

int main() {
    pthread_t train[5];
    pthread_mutex_init(&segmentAB, NULL);
    pthread_mutex_init(&segmentBC, NULL);
    pthread_mutex_init(&segmentCD, NULL);
    pthread_mutex_init(&segmentEB, NULL);
    pthread_mutex_init(&segmentFA, NULL);
    for(int i=0;i<5;i++){
        int * id =  (int*) malloc(sizeof(int));
        *id = i+1;
        if(i%3==0)
            pthread_create(&train[i], NULL, departDeA, id);

        else if(i%3==1)
            pthread_create(&train[i], NULL, departDeF,id);
        else
            pthread_create(&train[i], NULL, departDeE, id);
    }
    for(int i=0;i<5;i++){
        pthread_join(train[i],NULL);
    }
}
