#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

struct student_marks
{
    char student_index[12]; // EG/XXXX/XXXX
    float assgnmt01_marks; // 15%
    float assgnmt02_marks; // 15%
    float project_marks; // 20%
    float finalExam_marks; // 50%
};


int main()
{
    FILE* fp = fopen("marks.txt", "w+");
    if (fp == NULL)
    {
        perror("Marks.txt");
        printf("Marks.txt could not be opened or created. Error number is %d\n",errno);
        exit(0);
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            struct student_marks student;

            printf("Enter the Registration Number: ");
            scanf("%s",student.student_index);

            printf("\n==================================================\n");
            printf("Enter the Marks for the following Assesment Criteria");
            printf("\n==================================================\n");

            Assignment1:
            printf("Assignment 01: ");
            scanf("%f",&student.assgnmt01_marks);
            if (student.assgnmt01_marks > 15)
            {
                printf("\nAssignment marks cannot exceed 15\n");
                goto Assignment1;
            }
            

            Assignment2:
            printf("\nAssignment 02: ");
            scanf("%f",&student.assgnmt02_marks);
            if (student.assgnmt02_marks > 15)
            {
                printf("\nAssignment marks cannot exceed 15\n");
                goto Assignment2;
            }
            

            Project:
            printf("\nProject: ");
            scanf("%f",&student.project_marks);
            if (student.project_marks > 20)
            {
                printf("\nProject marks cannot exceed 15\n");
                goto Project;
            }

            Final:
            printf("\nFinal Exam: ");
            scanf("%f",&student.finalExam_marks);
            if (student.finalExam_marks > 50)
            {
                printf("\nFinal Exam marks cannot exceed 50\n");
                goto Final;
            }

            fprintf(fp,"\n===============================================================================\n");
            int write_ret1 = fprintf(fp,"\n Marks for the student with Index number %s\n",student.student_index);
            fprintf(fp,"===============================================================================\n");
            int write_ret2 = fprintf(fp,"\nAssignment 01: %f\n Assignment 02: %f\n Project: %f\n Final Exam: %f\n", student.student_index, student.assgnmt01_marks, student.assgnmt02_marks, student.project_marks, student.finalExam_marks);
            if((write_ret1 < 0) || (write_ret2 < 0))
            {
                perror("fprintf: ");
                printf("Writing to file error. Error no. %d \n",errno);
                exit(0);
            }
            else
            {
                printf("Successfully written to file for student %d\n",i);
            }
        }
        
        
        fclose(fp);
    }
    
    
    return 0;
}
