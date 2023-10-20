#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHARACTERS_NAME 100 // max. length of student names
#define MAX_CHARACTERS_COURSE 40 // max. length of course names
#define MAX_SUBJECTS 30 // max. amount of courses


typedef struct Student {
    char name[MAX_CHARACTERS_NAME];
    char courses[MAX_SUBJECTS][MAX_CHARACTERS_COURSE];
    int scores[MAX_SUBJECTS];
    int num_of_courses;
    int grades[MAX_SUBJECTS];
    struct Student *next; // for emptying allocated memory + possibility for multiple students?
} Student;


// calculate individual grades for the percentage scores
void grade_calculator(Student *student, int i) {
    if (student->scores[i] < 50) {
        student->grades[i] = 0;
    } else if (student->scores[i] < 60) {
        student->grades[i] = 1;
    } else if (student->scores[i] < 70) {
        student->grades[i] = 2;
    } else if (student->scores[i] < 80) {
        student->grades[i] = 3;
    } else if (student->scores[i] < 90) {
        student->grades[i] = 4;
    } else {
        student->grades[i] = 5;
    }
}


double calculate_final_avg(Student student) {
    double final_grade = 0;
    for (int i = 0; i < student.num_of_courses; i++) {
        final_grade += student.grades[i];
    }
    return (final_grade / student.num_of_courses);
}


// print course names, scores, and that course's grade from arrays together
void subject_print(Student student) {
    printf("%-40s %8s %8s\n", "Subject", "Score", "Grade");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < student.num_of_courses; i++) {
        printf("%-40s %8d%% %8d\n", student.courses[i], student.scores[i], student.grades[i]);
    }
}


// prints terminal output
void print_all(Student student) {
    printf("------------------------------------------------------------\n");
    printf("Student: %s\n", student.name);
    printf("------------------------------------------------------------\n");
    subject_print(student);
    printf("\n");
    printf("Average Grade: %.2f\n", (calculate_final_avg(student)));
    printf("------------------------------------------------------------\n");
    printf("\n");
}


void print_all_file(Student student) {
    FILE *student_file = fopen("student_info2.txt", "w");

    if (student_file == NULL) {
        perror("UNABLE TO CREATE FILE\n");
        return;
    }

    fprintf(student_file, "------------------------------------------------------------\n");
    fprintf(student_file, "Student: %s\n", student.name);
    fprintf(student_file, "------------------------------------------------------------\n");
    fprintf(student_file, "%-40s %8s %8s\n", "Subject", "Score", "Grade");
    fprintf(student_file,"------------------------------------------------------------\n");
    for (int i = 0; i < student.num_of_courses; i++) {
        fprintf(student_file, "%-40s %8d%% %8d\n", student.courses[i], student.scores[i], student.grades[i]);
    }
    fprintf(student_file, "\n");
    fprintf(student_file, "Average Grade: %.2f\n", (calculate_final_avg(student)));
    fprintf(student_file, "------------------------------------------------------------\n");

    fclose(student_file);
}


// empty allocated memory to prevent memory leak
void clear_list(Student *head) {
    while (head != NULL) {
        Student *temp = head;
        head = head->next;

        for (int i = 0; i < temp->num_of_courses; i++) {
            free(temp->courses[i]);
        }

        free(temp->name);
        free(temp->scores);
        free(temp);
    }
}


// MAIN PROGRAM STARTS HERE
int main() {
    Student student;
    Student *head = NULL;
    int valid_input = 0;

    printf("Welcome to the Student Grade Calculator!\n");

    // double prints below "how many subjects""invalid input" if longer than 100 char
    printf("Please enter your name: \n");
    fgets(student.name, MAX_CHARACTERS_NAME, stdin);
    student.name[strcspn(student.name, "\n")] = '\0';

    // WORKS (modify variable valid input)
    while (!valid_input) {
        printf("\n");
        printf("How many subjects do you want to calculate grades for? \n");
        if (scanf("%d", &student.num_of_courses) != 1) {
            printf("Invalid, please enter in numbers\n");
            while (getchar() != '\n');
        } else {
            while (getchar() != '\n');
            valid_input = 1;
        }
    }

// will not know what to do if prefecntage more than 100
    for (int i = 0; i < student.num_of_courses; i++) {

        // WORKS WITH TOO MANY CHAR, double enter with less
        printf("Enter subject %d name: \n", i + 1);
        fgets(student.courses[i], MAX_CHARACTERS_COURSE, stdin);
        size_t len = strlen(student.courses[i]);

        if (len > 0 && student.courses[i][len - 1] == '\n') {
            student.courses[i][len - 1] = '\0';
        } else {
            while (getchar() != '\n');
        }

        valid_input = 0;
        int score;

        while (!valid_input) {
            printf("Enter your percentage for %s (0-100): \n", student.courses[i]);

            if (scanf("%d", &score) != 1) {
                printf("Invalid input. Please enter number between 0 and 100\n");
                while (getchar() != '\n');
            } else if (score < 0 || score > 100) {
                printf("INVALID. Enter between 100 and 0\n");
            } else {
                student.scores[i] = score;
                valid_input = 1;
            }
        }

        while (getchar() != '\n');
        grade_calculator(&student, i);
    }

    print_all_file(student);
    print_all(student);
    clear_list(head);

    printf("NOTE: Information above is also copied to a newly created file student_info.txt\n");

    return 0;
}