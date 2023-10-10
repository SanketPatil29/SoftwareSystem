/*
Name: Sanket S. Patil (MT2023051).

Program to print message queue's:
    a. access permission
    b. uid, gid
    c. time of last msg sent & received
    d. size of queue
    e. time of last msg in queue
    f. number of queues
    g. max bytes allowed
    h. pid of msgsnd and msgrcv
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<unistd.h>

int main(){
    key_t key;
    int msgq_id;
    struct msqid_ds msq_stat;
    // Key is generated
    key = ftok("./file25.c", "a");
    // Message ID
    msgq_id = msgget(key, IPC_CREAT | 0666);

    // msg queue attributes
    msgctl(msgq_id, IPC_CREAT, &msq_stat);

    printf("Access Permissions: %d\n", msq_stat.msg_perm.mode);
    printf("User ID: %d\n", msq_stat.msg_perm.uid);
    printf("GID: %d\n", msq_stat.msg_perm.gid);
    printf("Last time of msg send: %d\n", ctime(&msq_stat.msg_stime));
    printf("Last time of msg received: %d\n", ctime(&msq_stat.msg_rtime));
    printf("Last time changes: %d\n", ctime(&msq_stat.msg_ctime));

    return 0;
}