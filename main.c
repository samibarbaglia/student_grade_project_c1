// TO DO: avg grade calculating, file printing, formatting
// error/security/user-friendliness (aka no letters in int, no numbers in char)
// fucking ville

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHARACTERS 40
#define MAX_SUBJECTS 30


struct Student {
    char name[MAX_CHARACTERS];
    char subjects[MAX_SUBJECTS][MAX_CHARACTERS];
    int scores[MAX_SUBJECTS];
    int num_subjects;
    int grade[MAX_SUBJECTS];
    struct Student *next;
};

// have to use *student bc othervice can't modify struct, pointers can
void grade_calculator(struct Student *student, int i) {
    if (student->scores[i] < 50) {
        student->grade[i] = 0;
    } else if (student->scores[i] < 60) {
        student->grade[i] = 1;
    } else if (student->scores[i] < 70) {
        student->grade[i] = 2;
    } else if (student->scores[i] < 80) {
        student->grade[i] = 3;
    } else if (student->scores[i] < 90) {
        student->grade[i] = 4;
    } else {
        student->grade[i] = 5;
    }
}

// no need to make into pointer, will directly save and no modify
void subject_print(struct Student *student) {
    for (int i = 0; i < student->num_subjects; i++) {
        printf("%s %d%% %d\n", student->subjects[i], student->scores[i], student->grade[i]);
    }
}

void print_all(struct Student *student, int avg) {
    printf("------------------------------------------\n"
           "Student: %s\n", student->name);
    printf("------------------------------------------\n"
           "Subject Score Grade\n");
    printf("------------------------------------------\n");
    subject_print(student);
    printf("\n");
    printf("Average Grade: %d\n", (avg / student->num_subjects)); /* AVG BIG NUMBER GRADE, NOT THIS!!*/
    printf("------------------------------------------\n");
}

//NOT ALL IS CLEARED YET
void clear_list(struct Student *head) {
    while (head != NULL) {
        struct Student *temp = head;
        head = (head)->next;

        free(temp->name);

        for (int i = 0; i < temp->num_subjects; i++) {
            free(temp->subjects[i]);
        }
        free(temp->scores);
        temp->num_subjects = 0;
        free(temp);

    }
}



int main() {
    struct Student student; // declare/initialize struct instance
    int avg = 0;
    struct Student *head = NULL;

    printf("Welcome to the Student Grade Calculator!\n"
           "Enter your name: \n");
    fgets(student.name, sizeof(student.name), stdin);
    student.name[strcspn(student.name, "\n")] = '\0';

    printf("How many subjects do you want to calculate grades for? \n");
    scanf("%d", &student.num_subjects);
    while (getchar() != '\n');

//NEEDS TO GIVE ERROR MESSAGE FOR INCORRECR INPUT ETC
    for (int i = 0; i < student.num_subjects; i++) {
        printf("\n");
        printf("Enter subject %d name: \n", i+1);
        fgets(student.subjects[i], sizeof(student.subjects[i]), stdin);
        student.subjects[i][strcspn(student.subjects[i], "\n")] = '\0';

        printf("Enter your percentage for %s (0-100): \n", student.subjects[i]);
        scanf("%d", &student.scores[i]);
        while (getchar() != '\n');
        grade_calculator(&student, i);
        avg = (avg + student.scores[i]);
    }

    print_all(&student, avg);
    clear_list(head);

}