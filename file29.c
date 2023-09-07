#include<stdio.h>
#include<sched.h>
#include<unistd.h>
int main()
{       int pid = getpid();
	int sched_policy =  sched_getscheduler(pid);
	printf("Scheduling Policy: %d ", sched_policy);
	switch(sched_policy){
		case SCHED_FIFO:
			printf("FIFO\n");
			break;
		case SCHED_RR:
			printf("RR\n");
			break;
		case SCHED_OTHER:
			printf("Other\n");
			break;
		default:
			printf("Unknown\n");
	}

	// Modifying the scheduling policy.
	
	//int p =  sched_get_priority_min(SCHED_FIFO);
	
	const struct sched_param sp = {.sched_priority = 99};
	int ret = sched_setscheduler(pid, SCHED_RR, &sp);
	if(ret == -1){
		perror("shed_scheduler");
		return 1;
	}
	printf("Sched_Policy after modification: ");
	int policy = sched_getscheduler(pid);
	switch(policy){
                case SCHED_FIFO:
                        printf("FIFO\n");
                        break;
                case SCHED_RR:
                        printf("RR\n");
                        break;
                case SCHED_OTHER:
                        printf("Other\n");
                        break;
                default:
                        printf("Unknown\n");
        }

        return 0;
}
