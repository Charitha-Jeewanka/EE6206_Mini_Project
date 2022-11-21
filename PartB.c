#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define LINE_SIZE 50

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
	int pid, pid1, pid2, pid3;
    FILE* fp = fopen("marks.txt", "r+");
    if (fp == 0)
    {
        // Error handling for file opening or creating
        perror("Marks.txt");
        printf("Marks.txt could not be opened for reading. Error number is %d\n",errno);
        exit(0);
    }
    ////////////////////////////////////////////////////////////////////////////
    char line[LINE_SIZE];

    while(!feof(fp)) 
    {
        student_marks *n= (student_marks*)malloc(sizeof(student_marks));             
        fscanf(fp,"%s\t%f\t%f\t%f\t%f", n->student_index, &n->assgnmt01_marks, &n->assgnmt02_marks, &n->project_marks,&n->finalExam_marks);
        printf("%f\n",n->assgnmt02_marks); 
    }   

    ///////////////////////////////////////////////////////////////////////////

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

    fclose(fp);

	return 0;
}
