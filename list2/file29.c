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

    //Generated Key 
    key = ftok("./file24.c", 'b');
    if(key == -1){
        perror("ftok");
        exit(1);
    }
    // msgQ-id of file24
    msgId = msgget(key, 0644);
    if(msgId == -1){
        perror("msgID");
        exit(1);
    }

    //Remove message queue.
    if(msgctl(msgId, IPC_RMID, NULL) == -1){
        perror("MSG_Control");
        exit(1);
    }
    printf("Msg queue %d is removed!\n", msgId);
    return 0;
}