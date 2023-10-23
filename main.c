#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CHARACTERS_NAME 100 // max. length of student names
#define MAX_CHARACTERS_COURSE 40 // max. length of course names
#define MAX_SUBJECTS 30 // max. amount of courses

// struct for student information
typedef struct Student {
    char name[MAX_CHARACTERS_NAME];
    char courses[MAX_SUBJECTS][MAX_CHARACTERS_COURSE];
    double scores[MAX_SUBJECTS];
    int num_of_courses;
    double grades[MAX_SUBJECTS];
    struct Student *next; // for emptying allocated memory + possibility for multiple students?
} Student;

// function declarations
void grade_calculator(Student *student, int i);

double calculate_final_avg(Student student);

void subject_print(Student student);

void print_all(Student student);

void write_into_file(Student student);

void clear_list(Student *head);



// MAIN PROGRAM STARTS HERE
int main() {
    Student student;
    Student *head = NULL;
    int is_input_valid = 0;
    double score = 0;

    printf("Welcome to the Student Grade Calculator!\n");

    // double prints below "how many subjects""invalid input" if longer than 100 char
    printf("Please enter your name: \n");
    fgets(student.name, MAX_CHARACTERS_NAME, stdin);
    size_t lent = strlen(student.name);
    if (lent > 0 && student.name[lent - 1] == '\n') {
        student.name[lent - 1] = '\0';
    } else {
        while (getchar() != '\n');
    }

    // saves number of subjects to struct and checks that user enters numbers and not text
    while (!is_input_valid) {
        printf("\n");
        printf("How many subjects do you want to calculate grades for? \n");
        if (scanf("%d", &student.num_of_courses) != 1) {
            printf("Invalid, please enter in numbers\n");
            while (getchar() != '\n');
        } else {
            while (getchar() != '\n');
            is_input_valid = 1;
        }
    }

    for (int i = 0; i < student.num_of_courses; i++) {

        // saves course names to struct
        printf("Enter subject %d name: \n", i + 1);
        fgets(student.courses[i], MAX_CHARACTERS_COURSE, stdin);
        size_t len = strlen(student.courses[i]);

        // removes extra char in case user goes over limit
        if (len > 0 && student.courses[i][len - 1] == '\n') {
            student.courses[i][len - 1] = '\0';
        } else {
            while (getchar() != '\n');
        }

        // empties checking variable 'is_input_valid'
        is_input_valid = 0;

        while (!is_input_valid) {
            printf("Enter your percentage for %s (0-100): \n", student.courses[i]);
            // checks that user enters a number not text and that the number is 0-100
            if (scanf("%lf", &score) != 1) {
                printf("INVALID INPUT: Please enter a number between 0 and 100.\n");
                while (getchar() != '\n');
            } else if (score < 0 || score > 100) {
                printf("INVALID INPUT: Enter a percentage between 0 and 100.\n");
            } else {
                student.scores[i] = score;
                is_input_valid = 1;
            }
        }

        while (getchar() != '\n');
        grade_calculator(&student, i);
    }

    write_into_file(student);
    print_all(student);
    clear_list(head);
    printf("NOTE: Information above is also copied to a newly created file student_info.txt\n");

    return 0;
}



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

// calculates final average score for student between 0-5
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
        printf("%-40s %8.1f%% %8.0f\n", student.courses[i], student.scores[i], student.grades[i]);
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

// prints student info to file
void write_into_file(Student student) {
    FILE *student_file = fopen("student_info2.txt", "w");

    if (student_file == NULL) {
        fprintf(stderr, "UNABLE TO CREATE FILE\n");
        return;
    }

    fprintf(student_file, "------------------------------------------------------------\n");
    fprintf(student_file, "Student: %s\n", student.name);
    fprintf(student_file, "------------------------------------------------------------\n");
    fprintf(student_file, "%-40s %8s %8s\n", "Subject", "Score", "Grade");
    fprintf(student_file,"------------------------------------------------------------\n");
    for (int i = 0; i < student.num_of_courses; i++) {
        fprintf(student_file, "%-40s %8.1f%% %8.0f\n", student.courses[i], student.scores[i], student.grades[i]);
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