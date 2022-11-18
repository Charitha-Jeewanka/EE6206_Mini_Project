#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

struct student_marks
{
    char student_index[12]; // EG/XXXX/XXXX
    float assgnmt01_marks; // 15%
    float assgnmt02_marks; // 15%
    float project_marks; // 20%
    float finalExam_marks; // 50%
};

void update_student();

int main()
{
    char key;
    printf("For updating details of a student Enter key 'U'");
    printf("\nFor Removing details of a student Enter key 'R'");
    printf("\nFor entering the data of student marks press any key");

    printf("\n************************************************************\n");
    printf("\nPress required key to continue: ");
    scanf("%c",&key);


    if (key == 'U')
    {
        update_student();
    }

    else
    {
        FILE* fp = fopen("marks.txt", "w+"); 

        if (fp == NULL)
        {
            // Error handling for file opening or creating
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


                // Taking Inputs from the user and handling possible errors by defining goto statements
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
                    printf("\nProject marks cannot exceed 20\n");
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

                // Writing to file marks.txt
                fprintf(fp,"\n===============================================================================\n");
                int write_ret1 = fprintf(fp,"\n Marks for the student with Index number %s\n",student.student_index);
                fprintf(fp,"===============================================================================\n");
                int write_ret2 = fprintf(fp,"\nAssignment 01: %f\n Assignment 02: %f\n Project: %f\n Final Exam: %f\n", student.assgnmt01_marks, student.assgnmt02_marks, student.project_marks, student.finalExam_marks);
                
                if((write_ret1 < 0) || (write_ret2 < 0))
                {
                    // Error handling in writing
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
    }

    
    
    
    return 0;
}

void update_student()
{
    FILE* fp1 = fopen("marks.txt", "w+");
    FILE* fp2 = fopen("temp.txt", "a+"); // Used for updating
    char student_index[12];
    struct student_marks student1;
    struct student_marks student2;

    printf("\nEnter the Student's Index to be updated: ");
    scanf("%s",student_index);

    while (fread(&student1,sizeof(struct student_marks),1,fp1))
    {
        if (student1.student_index != student_index)
        {
            // Hnadle errors
            fwrite(&student1,sizeof(struct student_marks),1,fp2);
            // strcpy(student2.student_index,student_index);
        }
    }
    Assignment1_update:
    printf("Assignment 01: ");
    scanf("%f",&student2.assgnmt01_marks);
    if (student2.assgnmt01_marks > 15)
    {
        printf("\nAssignment marks cannot exceed 15\n");
        goto Assignment1_update;
    }
    

    Assignment2_update:
    printf("\nAssignment 02: ");
    scanf("%f",&student2.assgnmt02_marks);
    if (student2.assgnmt02_marks > 15)
    {
        printf("\nAssignment marks cannot exceed 15\n");
        goto Assignment2_update;
    }
    

    Project_update:
    printf("\nProject: ");
    scanf("%f",&student2.project_marks);
    if (student2.project_marks > 20)
    {
        printf("\nProject marks cannot exceed 20\n");
        goto Project_update;
    }

    Final_update:
    printf("\nFinal Exam: ");
    scanf("%f",&student2.finalExam_marks);
    if (student2.finalExam_marks > 50)
    {
        printf("\nFinal Exam marks cannot exceed 50\n");
        goto Final_update;
    }

    fprintf(fp2,"\n Marks for the student with Index number %s\n",student_index);
    fprintf(fp2,"===============================================================================\n");
    int write_ret_update = fprintf(fp2,"\nAssignment 01: %f\n Assignment 02: %f\n Project: %f\n Final Exam: %f\n", student2.assgnmt01_marks, student2.assgnmt02_marks, student2.project_marks, student2.finalExam_marks);
    // int write_ret_update = fwrite(&student2,sizeof(struct student_marks),1,fp2);     
    if(write_ret_update < 0)
    {
        // Error handling in writing
        perror("fwrite: ");
        printf("Updating file error. Error no. %d \n",errno);
        exit(0);
    }
    else
    {
        printf("\nSuccessfully updated to file.");
    }

    fclose(fp1);
    fclose(fp2);
    remove("marks.txt");
    rename("temp.txt","marks.txt");
}