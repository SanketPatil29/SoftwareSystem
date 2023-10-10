#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>

struct msgbuff{
    long mtype;
    char msg_txt[200];
};

int main(){

    struct msgbuff msg;
    int msgid;
    key_t key;
    
    // Key is generated for the file "file20.c"
    if((key = ftok("file24.c", 'b')) == -1){
        perror("KEY");
        exit(1);
    }

    // Message id is generated 
    if((msgid == msgget(key, 0644| IPC_CREAT)) == -1){
        perror("MSG_ID");
        exit(1);
    }
    printf("Key: %d\n", key);
    printf("Message ID: %d\n", msgid);

    return 0;
}
