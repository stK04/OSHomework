#include <stdlib.h>

typedef struct {
    int* data;
    int size;
    int capacity;
} ArrayList;

int initArrayList(ArrayList* list, int capacity) {

    if(capacity <= 0) return 1;

    list->data = (int*)malloc(capacity * sizeof(int));
    list->size = 0;
    list->capacity = capacity;

    return 0;
}

void addArrayList(ArrayList* list, int item) {
    if (list->size < list->capacity) {
        list->data[list->size] = item;
        list->size++;
    } else {
        list->capacity *= 2;
        list->data = (int*)realloc(list->data, list->capacity * sizeof(int));
        list->data[list->size] = item;
        list->size++;
    }
}

int removeAtArrayList(ArrayList* list, int index) {
    if (index >= 0 && index < list->size) {
        for (int i = index; i < list->size - 1; i++) {
            list->data[i] = list->data[i + 1];
        }
        list->size--;
        return 0;
    }
    return 1;
}

int insertArrayList(ArrayList* list, int index, int item) {
    if (index >= 0 && index <= list->size) {
        if (list->size >= list->capacity) {
            list->capacity *= 2;
            list->data = (int*)realloc(list->data, list->capacity * sizeof(int));
        }

        for (int i = list->size; i > index; i--) {
            list->data[i] = list->data[i - 1];
        }

        list->data[index] = item;
        list->size++;
        return 0;
    }
     return 1;
}

int sizeArrayList(ArrayList* list) {
    return list->size;
}

int setArrayList(ArrayList* list, int index, int item) {
    if (index >= 0 && index < list->size) {
        list->data[index] = item;
        return 0;
    }
    return 1;
}

int getArrayList(ArrayList* list, int index) {
    if (index >= 0 && index < list->size) {
        return list->data[index];
    }
    return -1;
}

void clearArrayList(ArrayList* list) {
    free(list->data);
    list->size = 0;
    list->capacity = 0;
}

void printArrayList(const ArrayList * list) {
    printf("\nYour ArrayList: ");
    for (int i = 0; i < list->size; i++) {
        printf("%d ", list->data[i]);
    }
    printf("\n");
}
