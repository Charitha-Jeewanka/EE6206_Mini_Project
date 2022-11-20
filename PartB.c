#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main()
{
	int pid, pid1, pid2, pid3;

	pid = fork();
    if (pid == -1)
    {
        // Handle fork errors
        perror("Fork error.PID");
        printf("Error no. %d \n",errno);
        exit(0);
    
    }
	else if (pid == 0) 
    {
		sleep(3);
		printf("C1 --> pid = %d and ppid = %d\n",getpid(), getppid());
	}

	else 
    {
		pid1 = fork();
        if (pid1 == -1)
        {
            // Handle fork errors
            perror("Fork error. PID1");
            printf("Error no. %d \n",errno);
            exit(0);
        
        }
		else if (pid1 == 0) 
        {

			sleep(2);
			printf("C2--> pid = %d and ppid = %d\n",getpid(), getppid());
            pid3 = fork();
            if (pid3 == -1)
            {
                // Handle fork errors
                perror("Fork error. PID3");
                printf("Error no. %d \n",errno);
                exit(0);
            
            }

			else if (pid3 == 0) 
            {
				printf("CC1 --> pid = %d and ppid = %d\n",getpid(), getppid());
			}

			else 
            {
				sleep(3);
				printf("CC1P--> pid = %d\n", getpid());
			}
		}
		else 
        {
			pid2 = fork();
            if (pid2 == -1)
            {
                // Handle fork errors
                perror("Fork error. PID2");
                printf("Error no. %d \n",errno);
                exit(0);
            
            }

			else if (pid2 == 0) 
            {
				printf("C3 --> pid = %d and ppid = %d\n",getpid(), getppid());
			}

			else 
            {
				sleep(3);
				printf("P--> pid = %d\n", getpid());
			}
		}
	}

	return 0;
}
