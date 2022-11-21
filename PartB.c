#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>

#define LINE_SIZE 50
#define LENGTH 100

typedef struct 
{
    char student_index[20]; //EG/XXXX/XXXX
    float assgnmt01_marks; //15%
    float assgnmt02_marks; //15%
    float project_marks; //20%
    float finalExam_marks; //50%

}student_marks;

int main()
{
	pid_t pid, pid1, pid2, pid3;
    student_marks *shmp;

    float sum = 0;
    float avg = 0;
    float min;
    float max;

    FILE* fp = fopen("marks.txt", "r+");
    if (fp == 0)
    {
        // Error handling for file opening or creating
        perror("Marks.txt");
        printf("Marks.txt could not be opened for reading. Error number is %d\n",errno);
        exit(0);
    }

    // Create file token
    key_t ky = ftok("marks.txt",89);
    if (ky == -1){
        perror("ftok error: ");
        printf("Error No: %d\n",errno);
        exit(1);
    }

    int SMID = shmget(ky,sizeof(student_marks*)*LENGTH,IPC_CREAT|0666);

    if (SMID == -1)
    {
        perror("shmget error: ");
        printf("Error No: %d\n",errno);
        exit(1);
    }

    shmp = (student_marks *)shmat(SMID,NULL,SHM_R|SHM_W); // Attach to shared memory

    //////////////////////////////////////////////////////////////////////////////////
	pid = fork();
    if (pid == -1)
    {
        // Handle fork errors
        perror("Fork error.PID");
        printf("Error no. %d \n",errno);
        exit(0);
    
    }
	else if (pid == 0) // C1
    {
        if (shmp == (void *)-1)
        {
            perror("shmat error: ");
            printf("Error No: %d\n",errno);
            exit(1);
        }

        for (int i = 0; i < LENGTH; i++)
        {
            student_marks *n= (student_marks*)malloc(sizeof(student_marks));             
            fscanf(fp,"%s\t%f\t%f\t%f\t%f", n->student_index, &n->assgnmt01_marks, &n->assgnmt02_marks, &n->project_marks,&n->finalExam_marks);
            shmp[i].assgnmt02_marks = n->assgnmt02_marks;
        }
        
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
		else if (pid1 == 0) // C2
        {
            pid3 = fork();
            if (pid3 == -1)
            {
                // Handle fork errors
                perror("Fork error. PID3");
                printf("Error no. %d \n",errno);
                exit(0);
            
            }

			else if (pid3 == 0) // CC1
            {
                int i = 0;
                min = shmp[0].assgnmt02_marks;
				while (i < LENGTH)
                {
                    if (shmp[i].assgnmt02_marks < min)
                    {
                        min = shmp[i].assgnmt02_marks;
                    }
                    i++;
                }
                printf("Minimum: %f\n",min);
			}

			else 
            {
                int i = 0;
                max = shmp[0].assgnmt02_marks;
				while (i < LENGTH)
                {
                    if (shmp[i].assgnmt02_marks > max)
                    {
                        max = shmp[i].assgnmt02_marks;
                    }
                    i++;
                }
                printf("Maximum: %f\n",max);
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

			else if (pid2 == 0) // C3
            {
                int i = 0;
                while (i < LENGTH)
                {
                    sum += shmp[i].assgnmt02_marks;
                    i++;
                }
                // printf("Sum = %f\n",sum);
                avg = sum/100;
                printf("Average = %f\n",avg);
                
			}

			else 
            {
				pid_t wpidRet = waitpid(pid,NULL,0);
                if (wpidRet == -1)
                {
                    perror("waitpid error: ");
                    printf("Error No: %d\n",errno);
                    exit(0);
                }
                int i = 0;
                int count = 0;
                while (i < LENGTH)
                {
                    if (shmp[i].assgnmt02_marks < 1.50)
                    {
                        count++;
                    }
                    i++;
                }

                printf("No of students above 10%% is %d\n",count);
                if(shmdt(shmp) == -1) // Detach from shaerd memory
                {
                    perror("shmdt error: ");
                    printf("Error No: %d\n",errno);
                    exit(1);
                }
			}
		}
	}

    int shmCtl = shmctl(SMID,IPC_RMID,NULL); // Destroy shared memory
    if (shmCtl == -1){
        perror("shmctl error: ");
        printf("Error No: %d\n",errno);
        exit(0);
    }

    fclose(fp);

	return 0;
}
