#include <stdio.h>
#include <stdlib.h>

struct Student {
    char name[20];
    char surname[20];
    int age;
};

int main() {
    int numStudents = 0;

    while (1){
        printf("How many students are in your group?\n");
        if(scanf("%d", &numStudents) != 1){
            printf("Invalid number of students. Try again!\n");
            getchar();
        }else if (numStudents <= 0) {
            printf("Invalid number of students. Try again!\n");
        }else{
            break;
        }
    }

    struct Student *students = (struct Student *)malloc(numStudents * sizeof(struct Student));

    if (students == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < numStudents; i++) {
        printf("\nEnter name: ");
        scanf("%s", students[i].name);

        printf("Enter surname: ");
        scanf("%s", students[i].surname);

        int studentAge = 0;
        while (1){
            printf("Enter age: ");
            if(scanf("%d", &studentAge) != 1){
                printf("Age is incorrect. Try again!\n");
                getchar();
            }else if (studentAge <= 0) {
                printf("Age is incorrect. Try again!\n");
            }else{
                students[i].age = studentAge;
                break;
            }
        }
    }

    printf("\nList of Students:\n");
    printf("Student|                Name|             Surname|Age|\n");
    for (int i = 0; i < numStudents; i++) {
        printf("%7d|", i + 1);
        printf("%20s|", students[i].name);
        printf("%20s|", students[i].surname);
        printf("%3d|\n", students[i].age);
    }

    free(students);

    return 0;
}
