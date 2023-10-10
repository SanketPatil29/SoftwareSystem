/*
Name: Sanket S. Patil (MT2023051).

Program to receive messages to message queue.
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<unistd.h>
#include<string.h>

struct msg{
    long int m_type;
    char message[100];
}msq;

int main(){
    key_t key;
    int msgq_id;
   
    // Key is generated
    key = ftok("./file26.c", 'a');

    // Message ID
    msgq_id = msgget(key, 0666);
    int ret = msgrcv(msgq_id, &msq, sizeof(msq), 1, 0);
    
    if (ret == -1){
        perror("RET");
        exit(-1);
    }
    // msg with flag 0
    printf("Message: %s\n", msq.message);

    int ret2 = msgrcv(msgq_id, &msq, sizeof(msq), 2, IPC_NOWAIT);
    if (ret2 != -1){
        printf("Message received with IPC_NOWAIT flag: %s\n", msq.message);
    }
    return 0;
}

