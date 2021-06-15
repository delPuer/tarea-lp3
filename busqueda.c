#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define MAX 20
int array[MAX];
int key;
int flag = 0; //flag to indicate that item is found in the array or not
int current_thread = 0;
void* ThreadSearch(void* args) { //This is linear search function. It will be running using all threads
    if(flag == 1)
        pthread_exit(0);
    int num = current_thread++;
    for (int i = num * (MAX / 4); i < ((num + 1) * (MAX / 4)); i++){
        if (array[i] == key){
            flag = 1; //set flag if key is found
        }
    }
}
int main(int argc, char **argv) {
    flag = 0;
    sscanf (argv[1], "%i", &key);
    printf("%d\n",key);
    int size;
    sscanf (argv[2], "%i", &size);
    pthread_t thread[size];
    
    for(int i=0;i<MAX;i++){
        array[i]=rand()%10;
        printf("%d\n",array[i]);
    }
    
    for (int i = 0; i < size; i++) { //create multiple threads
        pthread_create(&thread[i], NULL, ThreadSearch, (void*)NULL);
    }
    for (int i = 0; i < size; i++) {
        pthread_join(thread[i], NULL); //wait untill all of the threads are completed
    }
    
    
    if (flag == 1)
        printf("Elemento encontrado\n");
    else
        printf("Elemento NO encontrado\n");
}