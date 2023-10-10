/*
Name: Sanket S. Patil (MT2023051).

Program to remove the message queue.
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/msg.h>

int main(){
    key_t key;
    int msgId;

    key = ftok("./file24.c", 'a');
    if(key == -1){
        perror("ftok");
        exit(1);
    }

    //Remove message queue.
    msgctl(0, IPC_RMID, NULL);
    printf("Msg queue is removed!\n");
    return 0;
}