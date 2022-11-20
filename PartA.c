#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

struct student_marks
{
    int pos;
    char student_index[12]; // EG/XXXX/XXXX
    float assgnmt01_marks; // 15%
    float assgnmt02_marks; // 15%
    float project_marks; // 20%
    float finalExam_marks; // 50%
};

void update_student();
void delete_student();

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

    else if (key == 'R')
    {
        delete_student();
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
            for (int i = 0; i < 2; i++)
            {
                struct student_marks student;
                student.pos = i + 1;

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
                int write_ret = fprintf(fp,"%s\t%.2f\t%.2f\t%.2f\t%.2f\n",student.student_index, student.assgnmt01_marks, student.assgnmt02_marks, student.project_marks, student.finalExam_marks);

                if(write_ret < 0)
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
    FILE* fp1 = fopen("marks.txt", "r+");
    FILE* fp2 = fopen("temp.txt", "a+"); // Used for updating
    struct student_marks student1;
    struct student_marks student2;

    char buffer[46]; // Buffer to store read data
    char student_index[13]; // Buffer to store student index
    char index_buffer[13];


    printf("\nEnter the Student's Index to be updated: ");
    scanf("%s",student_index);

    if (fp1 == 0)
    {
        // Error handling for file opening or creating
        perror("Marks.txt");
        printf("Marks.txt could not be opened for editing. Error number is %d\n",errno);
        exit(0);
    }

    if (fp2 == 0)
    {
        // Error handling for file opening or creating
        perror("Temp.txt");
        printf("Temp.txt could not be opened for editing. Error number is %d\n",errno);
        exit(0);
    }

    int match_bytes_read = fscanf(fp1,"%s",index_buffer);
    if (match_bytes_read == -1)
    {
        // Error handling
        perror("Marks.txt");
        printf("Marks.txt could not be scanned for editing. Error number is %d\n",errno);
        exit(0);
    }
    int compare = strcmp(student_index,index_buffer);
    if (compare == 0)
    {
        printf("\n MATCH FOUND\n");
    }
    else
    {
        printf("\n MATCH NOT FOUND\n");
    }


    fseek(fp1,0,SEEK_SET); // Jump to initial point of file before reading

    while (EOF != fscanf(fp1,"%s",buffer))
    {
        // char *ret = strstr(buffer,student_index);
        // if (ret == NULL)
        // {
        //     printf("\n MATCH NOT FOUND\n");
        // }
        // else
        // {
        //     printf("\n MATCH FOUND. %s\n",ret);
        // }
        
        int bytes_written = fprintf(fp2,"%s\t",buffer);
        if (bytes_written == -1)
        {
            perror("temp.txt");
            printf("\ntemp.txt cannot be written. Error no. is %d",errno);
            exit(0);
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

    int write_ret_update = fprintf(fp2,"%s\t%.2f\t%.2f\t%.2f\t%.2f\n",student_index, student2.assgnmt01_marks, student2.assgnmt02_marks, student2.project_marks, student2.finalExam_marks);    
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

void delete_student()
{
    FILE* fp1 = fopen("marks.txt", "r+");
    FILE* fp2 = fopen("temp.txt", "a+"); // Used for updating
    struct student_marks student1;
    struct student_marks student2;

    char buffer[46]; // Buffer to store read data
    char student_index[13]; // Buffer to store student index
    char index_buffer[13];


    printf("\nEnter the Student's Index to be deleted: ");
    scanf("%s",student_index);

    if (fp1 == 0)
    {
        // Error handling for file opening or creating
        perror("Marks.txt");
        printf("Marks.txt could not be opened for editing. Error number is %d\n",errno);
        exit(0);
    }

    if (fp2 == 0)
    {
        // Error handling for file opening or creating
        perror("Temp.txt");
        printf("Temp.txt could not be opened for editing. Error number is %d\n",errno);
        exit(0);
    }

    int match_bytes_read = fscanf(fp1,"%s",index_buffer);
    if (match_bytes_read == -1)
    {
        // Error handling
        perror("Marks.txt");
        printf("Marks.txt could not be scanned for editing. Error number is %d\n",errno);
        exit(0);
    }
    int compare = strcmp(student_index,index_buffer);
    if (compare == 0)
    {
        printf("\n MATCH FOUND\n");
    }
    else
    {
        printf("\n MATCH NOT FOUND\n");
    }


    fseek(fp1,30,SEEK_CUR); // Continue writing after match

    while (EOF != fscanf(fp1,"%s",buffer))
    {
        int bytes_written = fprintf(fp2,"%s\t",buffer);
        if (bytes_written == -1)
        {
            perror("temp.txt");
            printf("\ntemp.txt cannot be written. Error no. is %d",errno);
            exit(0);
        }
    }

    fclose(fp1);
    fclose(fp2);
    remove("marks.txt");
    rename("temp.txt","marks.txt");
}