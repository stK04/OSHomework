#include <stdio.h>
#include <math.h>
#include <time.h>
#include "ArrayList.c"
#include "LinkedList.c"
#include "Matrix.c"
#include "Point.c"

int enterNumber(char str[]){
    int item = 0;
    while (1){
        printf("Enter your %s: ", str);
        if(scanf("%d", &item) != 1){
            printf("Wrong %s. Try again!\n", str);
            getchar();
        }else{
            break;
        }
    }
    return item;
}

void workWithArrayList(){
    ArrayList list;
    if(initArrayList(&list, 1) != 0){
        printf("Wrong capacity\n");
        return;
    }
    int choice = 0;

    while(1){
        printArrayList(&list);
        printf("|0.exit      |\n");
        printf("|1.add       |\n");
        printf("|2.insert    |\n");
        printf("|3.size      |\n");
        printf("|4.remove    |\n");
        printf("|5.set       |\n");
        printf("|6.get       |\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
            {
                int item = enterNumber("item");
                addArrayList(&list, item);
            }
                break;
            case 2:
            {
                int item = enterNumber("item");
                int index = enterNumber("index");
                if(insertArrayList(&list, index, item) != 0){
                    printf("Wrong index\n");
                    break;
                }else{
                    printf("Item was inserted\n");
                }
            }
                break;
            case 3:
                printf("Size of your list: %d\n", sizeArrayList(&list));
                break;
            case 4:
            {
                int index = enterNumber("index");
                if(removeAtArrayList(&list, index) != 0){
                    printf("Wrong index\n");
                    break;
                }else{
                    printf("Item was deleted\n");
                }
            }
                break;
            case 5:
            {
                int item = enterNumber("item");
                int index = enterNumber("index");
                if(setArrayList(&list, index, item) != 0){
                    printf("Wrong index\n");
                    break;
                }else{
                    printf("Item was changed\n");
                }
            }
                break;
            case 6:
            {
                int index = enterNumber("index");
                printf("Element by index [%d] = %d\n", index, getArrayList(&list, index));
            }
                break;
            case 0:
                clearArrayList(&list);
                return;
            default:
                printf("Unknown command, try again\n");
                getchar();
                break;
        }
    }
}

void workWithLinkedList(){
    LinkedList list;
    initLinkedList(&list);
    int choice = 0;

    while(1){
        printLinkedList(&list);
        printf("|0.exit      |\n");
        printf("|1.add       |\n");
        printf("|2.insert    |\n");
        printf("|3.size      |\n");
        printf("|4.remove    |\n");
        printf("|5.set       |\n");
        printf("|6.get       |\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
            {
                int item = enterNumber("item");
                addLinkedList(&list, item);
            }
                break;
            case 2:
            {
                int item = enterNumber("item");
                int index = enterNumber("index");
                if(insertLinkedList(&list, index, item) != 0){
                    printf("Wrong index\n");
                    break;
                }else{
                    printf("Item was inserted\n");
                }
            }
                break;
            case 3:
                printf("Size of your list: %d\n", sizeLinkedList(&list));
                break;
            case 4:
            {
                int index = enterNumber("index");
                if(removeAtLinkedList(&list, index) != 0){
                    printf("Wrong index\n");
                    break;
                }else{
                    printf("Item was deleted\n");
                }
            }
                break;
            case 5:
            {
                int item = enterNumber("item");
                int index = enterNumber("index");
                if(setLinkedList(&list, index, item) != 0){
                    printf("Wrong index\n");
                    break;
                }else{
                    printf("Item was changed\n");
                }
            }
                break;
            case 6:
            {
                int index = enterNumber("index");
                printf("Element by index [%d] = %d\n", index, getLinkedList(&list, index));
            }
                break;
            case 0:
                clearLinkedList(&list);
                return;
            default:
                printf("Unknown command, try again\n");
                getchar();
                break;
        }
    }
}

void workWithMatrix(){
    Matrix mat1 = initMatrix(3, 3);
    Matrix mat2 = initMatrix(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            setElement(&mat1, i, j, i * 3 + j + 1);
            setElement(&mat2, i, j, i * 3 + j);
        }
    }

    printf("Matrix 1:\n");
    printMatrix(mat1);
    printf("\nMatrix 2:\n");
    printMatrix(mat2);

    saveMatrixToFile(mat1, "PR3/matrix1.txt");
    saveMatrixToFile(mat2, "PR3/matrix2.txt");

    Matrix loadedMat1 = loadMatrixFromFile("PR3/matrix1.txt");
    Matrix loadedMat2 = loadMatrixFromFile("PR3/matrix2.txt");

    printf("\nLoaded Matrix 1:\n");
    printMatrix(loadedMat1);
    printf("\nLoaded Matrix 2:\n");
    printMatrix(loadedMat2);

    Matrix sum = addMatrices(mat1, mat2);
    printf("\nSum of matrices:\n");
    printMatrix(sum);

    Matrix difference = subtractMatrices(mat1, mat2);
    printf("\nDifference of matrices:\n");
    printMatrix(difference);

    Matrix scaledMat1 = multiplyMatrixByScalar(mat1, 2);
    printf("\nMatrix 1 multiplied by 2:\n");
    printMatrix(scaledMat1);

    Matrix product = multiplyMatrices(mat1, mat2);
    printf("\nProduct of matrices:\n");
    printMatrix(product);

    mat1 = resizeMatrix(mat1, 4, 4);
    mat2 = resizeMatrix(mat2, 4, 4);
    printf("\nResized matrices:\n");
    printMatrix(mat1);
    printf("\n");
    printMatrix(mat2);

    freeMatrix(mat1);
    freeMatrix(mat2);
    freeMatrix(loadedMat1);
    freeMatrix(loadedMat2);
    freeMatrix(sum);
    freeMatrix(difference);
    freeMatrix(scaledMat1);
    freeMatrix(product);

    return;
}

void workWithArray(){

    int choice = 0;
    int size = enterNumber("size");
    if(size <= 0) {
        printf("Wrong size\n");
        return;
    }
    double arr[size];
    int negativeFound = 0;
    double sumAfterNegative = 0.0;
    double sum = 0.0;
    int countGreaterThanAvg = 0;

    printf("\n|0.exit        |\n");
    printf("|1.enter arr   |\n");
    printf("|2.generate arr|\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            for(int i = 0; i < size; i++){
                int item = enterNumber("item");
                sum += item;
                arr[i] = item;
                if (item < 0) {
                    negativeFound = 1;
                }
                if (negativeFound) {
                    sumAfterNegative += fabs(arr[i]);
                }
            }
            break;
        case 2:
            printf("Array: ");
            for(int i = 0; i < size; i++){
                int item = rand() % 9 - 1;
                arr[i] = item;
                sum += item;
                if (negativeFound) {
                    sumAfterNegative += fabs(arr[i]);
                }
                if (item < 0) {
                    negativeFound = 1;
                }
                printf("%d ", item);
            }
            printf("\n");
            break;
        case 0:
            return;
        default:
            printf("Unknown command, try again\n");
            getchar();
            break;
    }

    double avg = sum / size;
    for (int i = 0; i < size; i++) {
        if (arr[i] > avg) {
            countGreaterThanAvg++;
        }
    }

    printf("the average value: %lf\n", avg);
    printf("The number of elements that are greater than the average value: %d\n", countGreaterThanAvg);
    printf("The sum of the modules of the elements that are located after the first negative element: %.2lf\n", sumAfterNegative);

}

void workWithPoints(){
    struct point points[] = {{1, 2, 10}, {3, 4, 5}, {5, 6, 2}, {7, 8, 3}, {9, 10, 4}};
    int n = sizeof(points) / sizeof(points[0]);

    struct point *final_point = evaporate_points(points, n);

    printf("Left point: (%f, %f, %f)\n", final_point->x, final_point->y, final_point->mass);
}

void main(){
    srand(time(NULL));
    int choice = 0;

    while(1){
        printf("|1.ArrayList |\n");
        printf("|2.LinkedList|\n");
        printf("|3.Matrix    |\n");
        printf("|4.Array     |\n");
        printf("|5.Points    |\n");
        printf("|=>");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                workWithArrayList();
                break;
            case 2:
                workWithLinkedList();
                break;
            case 3:
                workWithMatrix();
                break;
            case 4:
                workWithArray();
                break;
            case 5:
                workWithPoints();
                break;
            default:
                printf("Unknown command, try again\n");
                getchar();
                break;
        }
    }

}