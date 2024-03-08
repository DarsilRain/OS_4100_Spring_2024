/******************************************************************************
*    Authors: Haley Burnell, Angus Brennan, Addison Goforth
*    Date: 7 March 2024
*    Purpose: Learn about producers and consumers by modifying some example
*           code.
*           1) Producer inserts a string and prints to output
*           2) consumer reverses the string and prints to output
*
*  Note Compile and run with> gcc burnell_homework_2.c -o prodcons && ./prodcons
******************************************************************************/

//https://sites.cc.gatech.edu/classes/AY2010/cs4210_fall/code/ProducerConsumer.c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

/* Size of shared buffer */
#define BUF_SIZE 10

char buffer[BUF_SIZE];							/* shared buffer */
char add=0;										/* place to add next element */
char rem=0;										/* place to remove next element */
int num=0;										/* number elements in buffer */
pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;	/* mutex lock for buffer */
pthread_cond_t c_cons=PTHREAD_COND_INITIALIZER; /* consumer waits on this cond var */
pthread_cond_t c_prod=PTHREAD_COND_INITIALIZER; /* producer waits on this cond var */

void *producer(void *param);
void *consumer(void *param);

int main (int argc, char *argv[])
{
	pthread_t tid1, tid2;		/* thread identifiers */
	int i;

	/* create the threads; may be any number, in general */
	if (pthread_create(&tid1,NULL,producer,NULL) != 0) {
		fprintf (stderr, "Unable to create producer thread\n");
		exit(1);
	}
	if (pthread_create(&tid2,NULL,consumer,NULL) != 0) {
		fprintf (stderr, "Unable to create consumer thread\n");
		exit(1);
	}
	/* wait for created thread to exit */
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	printf ("Parent quiting\n");

    return 0;
}


/* Produce value(s) */
void *producer(void *param)
{
	int i;
	for (i=0; i<=2; i++) {
		/* Insert into buffer */
		pthread_mutex_lock (&m);
		if(num > BUF_SIZE){exit(1);}	/* overflow */
		while(num == BUF_SIZE)			/* block if buffer is full */
			pthread_cond_wait (&c_prod, &m);
		/* if executing here, buffer not full so add element */
        char my_string[] = "hello\0";
        //load the whole of my_string into the buffer
        for(i=0;i<sizeof(my_string);i++){
            buffer[add] = my_string[i];
            add = (add+1) % BUF_SIZE;
            num++;
        }
		pthread_mutex_unlock (&m);
		pthread_cond_signal (&c_cons);
		printf ("producer: inserted %s\n", my_string);  fflush (stdout);
        sleep(2);
	}
	printf ("producer quiting\n");  fflush (stdout);
}

/* Consume value(s); Note the consumer never terminates */
void *consumer(void *param)
{
	char in[BUF_SIZE];
	while (1) {
		pthread_mutex_lock (&m);
		if (num < 0) exit(1);   /* underflow */
		while (num == 0)		/* block if buffer empty */
			pthread_cond_wait (&c_cons, &m);
		/* if executing here, buffer not empty so remove element */
        //read the whole string from the buffer
        char next_char = 'a';
        int i = 0;
        while(next_char != 0){
            next_char = buffer[rem];
            in[i] = next_char;
            rem = (rem+1) % BUF_SIZE;
            num--;
            i++;
        }
		pthread_mutex_unlock (&m);
		pthread_cond_signal (&c_prod);
		printf ("Consume value %s\n", in);  
        //fflush(stdout);

        //now that the string was read, reverse it and print it
        char reversed[BUF_SIZE];
        int j = 0;
        for(int k=BUF_SIZE; k>=0; k--){
            if(in[k] == '\n' || in[k]=='\0'){
                continue; //skip nonletter characters
            }
            reversed[j] = in[k];
            j++;
        }
        printf("Reversed value %s\n",reversed);

	}
}
