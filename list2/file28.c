/*
Name: Sanket S. Patil (MT2023051).

Program to change the existing message queue permission.
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/msg.h>
#include<unistd.h>

int main(){
    int msq_id;
    key_t key;
    struct msqid_ds msq_ds;
    key = ftok("./file26.c", 'a');

    // Message queue ID
    msq_id = msgget(key, IPC_CREAT | 0666);
    if(msq_id == -1){
        perror("MSGGET");
        exit(1);
    }

    // initialization of msqid_ds
    msgctl(msq_id, IPC_CREAT, &msq_ds);

    //Modifying permissions
    msq_ds.msg_perm.mode = 0644;

    //Setting updated permissions
    msgctl(msq_id, IPC_CREAT, &msq_ds);

    printf("Message queue permissions are updated!\n");
    return 0;
}
