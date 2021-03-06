#include <string.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t signalLock; 

void * factorial(int numero)
{
  int result; 

  if(numero == 0 || numero == 1)
  { 
    result = 1; 
  }
  else
  {   
    int i;
    int array[numero];
    array[0]=1;
    array[1]=1;
  
    for(i = 2; i <= numero; i++)
    {  
      array[i] = array[i-1] * i;
    }      
    result = array[numero]; 
  }  

  pthread_mutex_lock(&signalLock);
  printf("%d! = %d \n", numero, result);
  pthread_mutex_unlock(&signalLock);		
  
  pthread_exit(0);
}
  
int main(int argc, char **argv)
{
    pthread_t id[argc-1];
    int i,j;
    void * ret;
    int num;
    
    for(i = 0; i < argc; i++)
    {
        sscanf (argv[i+1], "%i", &num);
        pthread_create(&id[i],NULL,factorial,(void *) num);
        pthread_join(id[i],&ret);  
    }

   /* for(i=0; i<argc; i++)
    {    
        pthread_join(id[i],&ret);   
    }*/
    return 0;
}
