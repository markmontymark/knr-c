#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
int basic_main( int argc, char ** argv);
int mutex_main( int argc, char ** argv);
void * basic_function( void * ptr );
void * mutex_function();

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
int counter = 0;
 
int main(int argc, char ** argv)
{
	basic_main(argc,argv);
	mutex_main(argc,argv);
}

int mutex_main( int argc, char ** argv)
{
   int rc1, rc2;
   pthread_t thread1, thread2;
 
   /* Create independent threads each of which will execute functionC */
 
   if( (rc1=pthread_create( &thread1, NULL, &mutex_function, NULL)) )
   {
      printf("Thread creation failed: %d\n", rc1);
   }
 
   if( (rc2=pthread_create( &thread2, NULL, &mutex_function, NULL)) )
   {
      printf("Thread creation failed: %d\n", rc2);
   }
 
   /* Wait till threads are complete before main continues. Unless we  */
   /* wait we run the risk of executing an exit which will terminate   */
   /* the process and all threads before the threads have completed.   */
 
   pthread_join( thread1, NULL);
   pthread_join( thread2, NULL);
 
   return 0;
}
 
void * mutex_function()
{
   pthread_mutex_lock( &mutex1 );
   counter++;
   printf("Counter value: %d\n",counter);
   pthread_mutex_unlock( &mutex1 );
}


 
int basic_main(int argc, char ** argv)
{
     pthread_t thread1, thread2;
     char *message1 = "Thread 1";
     char *message2 = "Thread 2";
     int  iret1, iret2;
 
    /* Create independent threads each of which will execute function */
 
     iret1 = pthread_create( &thread1, NULL, basic_function, (void*) message1);
     iret2 = pthread_create( &thread2, NULL, basic_function, (void*) message2);
 
     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */
 
     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL);
 
     printf("Thread 1 returns: %d\n",iret1);
     printf("Thread 2 returns: %d\n",iret2);
     return 0;
}
 
void * basic_function( void * ptr )
{
     char * message = (char *) ptr;
     printf("%s \n", message);
}
