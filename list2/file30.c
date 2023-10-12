/*
Name: Sanket S. Patil (MT2023051).

Shared Memory - create, write, detach, remove
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/shm.h>

int main(){
    char * shared_mem;
    int shmid;
    key_t key = 0051;

    // Creating shared memory.
    shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if(shmid < 0){
        perror("shmget");
        exit(1);
    }
    // Attaching shared memeory segment
    shared_mem = shmat(shmid, 0, 0);
    if (shared_mem == (char*)-1){
        perror("shmat");
        exit(1);
    }

    // Writing data
    printf("Enter the text: ");
    scanf("%[^\n]", shared_mem);

    //2
    //Attaching shared memory seg with O_RDONLY
    char* shm_rdonly = shmat(shmid,  NULL, SHM_RDONLY);
    if(*shm_rdonly == -1){
        perror("shmat-rdonly");
        exit(1);
    }
    //Overwriting data
    strcpy(shm_rdonly, "Data Overwritting!");
    printf("Data: %s", shm_rdonly);

    //3
    //Detaching pointer to shared memory
    shmdt(shared_mem);
    shmdt(shm_rdonly);

    //4
    //Deleting shared memory
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}