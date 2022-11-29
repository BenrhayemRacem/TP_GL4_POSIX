#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t semaphore_counter;
pthread_mutex_t sectionCritique_camion;
#define camions	5
#define voitures	5
#define vehicules  (camions+voitures)
void wait()
{
        struct timespec tempsAttente;
        tempsAttente.tv_sec=1;
        tempsAttente.tv_nsec=0;
        nanosleep(&tempsAttente,NULL);
}
void* voiture(void* arg)
{
	wait();
	goIn(5);
	printf(" Voiture N°%d : go into bridge \n",*((int*)arg)-camions);
	wait();
	printf(" Voiture N° %d : go out of the bridge \n",*((int*)arg)-camions);
	goOut(5);
	pthread_exit(NULL);
}
void* camion(void* arg)
{
	wait();
	goIn(15);
	printf(" Camion N° %d : go into bridge \n",*((int*)arg));
	wait();
	printf(" Camion N° %d : go out of the bridge \n",*((int*)arg));
	goOut(15);
	pthread_exit(NULL);
}
void goIn(int tonnes) 
{
	if (tonnes==15)
		{
		pthread_mutex_lock(&sectionCritique_camion);
		while(tonnes>0)
			{
			sem_wait(&semaphore_counter);
			tonnes=tonnes-5;
			};
		pthread_mutex_unlock(&sectionCritique_camion);
		}
	else  sem_wait(&semaphore_counter);
}
void goOut(int tonnes)
{
	while(tonnes>0)
		{
		sem_post(&semaphore_counter);
		tonnes=tonnes-5;
		};
}


int main(int argc, char* argv[])
{
	int i;
	pthread_t id;

	sem_init(&semaphore_counter,0,3);

	for(i=0; i<vehicules;i++){

		int* j=(int*)malloc(sizeof(int));
		*j=i;
		if (i<camions)
		pthread_create(&id,NULL,camion,j);
		else	
		pthread_create(&id,NULL,voiture,j);
	}
	pthread_exit(NULL);
};
