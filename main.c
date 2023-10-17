#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHARACTERS 40

int main() {
    char student_name[MAX_CHARACTERS];
    int subject_amount;
    char subject_name[MAX_CHARACTERS];
    int student_score;

    printf("Welcome to the Student Grade Calculator!\n"
           "Please enter your name: \n");
    fgets(student_name, MAX_CHARACTERS, stdin);
    student_name[strcspn(student_name, "\n")] = '\0';

    printf("How many subjects do you want to calculate grades for? [Input as numbers] \n");
    scanf("%d", &subject_amount);

    for (int i = 1; i < subject_amount; i++) {
        printf("Enter subject %d name: \n", i);
        fgets(subject_name, MAX_CHARACTERS, stdin);
        subject_name[strcspn(subject_name, "\n")] = '\0';

        printf("Enter percentage score for %s (0-100): \n", subject_name);
        scanf("%d", &student_score);
    }


}