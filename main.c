// CREATE A STRUCT WITH NAME, SUBJECT NAMES (ARRAY), SCORE(ARRAY), AVG GRADE
// subject names + score need to be connected at least by being in the correct order
// all should be pointers?

// should printer function and file printer function be same or separate?

// void info_input(int subject_amount) {}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHARACTERS 40


// struct here

// printer function here

// file function here

int main() {
    char student_name[MAX_CHARACTERS];
    int subject_amount;
    char subject_name[MAX_CHARACTERS];
    int student_score = 0;

    printf("Welcome to the Student Grade Calculator!\n"
           "Please enter your name: \n");
    fgets(student_name, MAX_CHARACTERS, stdin);
    student_name[strcspn(student_name, "\n")] = '\0';

    printf("How many subjects do you want to calculate grades for? \n");
    scanf("%d", &subject_amount);
    while (getchar() != '\n');

    for (int i = 1; i <= subject_amount; i++) {
        printf("\n");
        printf("Enter subject %d name: \n", i); //needs to be pointer array for display
        fgets(subject_name, MAX_CHARACTERS, stdin);
        subject_name[strcspn(subject_name, "\n")] = '\0';

        printf("Enter your percentage score for %s (0-100): \n", subject_name); //same as above
        scanf("%d", &student_score);
        while (getchar() != '\n');
    }


}