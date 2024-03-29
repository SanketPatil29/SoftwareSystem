/*
Name: Sanket S. Patil (MT2023051).

Program to send messages to message queue.
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
    msgq_id = msgget(key, 0666 | IPC_CREAT);
    msq.m_type = 1;

    printf("Enter Message: ");
    scanf(" %[^\n]", msq.message);

    
    msgsnd(msgq_id, &msq, sizeof(msq), 0);

    return 0;
}

