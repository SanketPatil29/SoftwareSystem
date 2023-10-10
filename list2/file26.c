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
    char* message;
}msq;

int main(){
    key_t key;
    int msgq_id;
   
    // Key is generated
    key = ftok("./file26.c", 'a');
    // Message ID
    msgq_id = msgget(key, IPC_CREAT | 0744);
    msq.message = "File26's message!\n";
    int size = strlen(msq.message);
    msgsnd(msgq_id, &msq, size+1, 0);
    return 0;
}

