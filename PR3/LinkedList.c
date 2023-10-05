#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
} LinkedList;

void initLinkedList(LinkedList* list) {
    list->head = NULL;
}

void addLinkedList(LinkedList* list, int item) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

int removeAtLinkedList(LinkedList* list, int index) {
    if(index < 0) return 1;

    if (index == 0) {
        if (list->head != NULL) {
            Node* temp = list->head;
            list->head = list->head->next;
            free(temp);
        }
    } else {
        Node* current = list->head;
        int currentIndex = 0;
        while (current != NULL && currentIndex < index - 1) {
            current = current->next;
            currentIndex++;
        }
        if (current == NULL || current->next == NULL) return 1;
        Node* temp = current->next;
        current->next = current->next->next;
        free(temp);
    }
    return 0;
}

int insertLinkedList(LinkedList* list, int index, int item) {
    if(index < 0) return 1;

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;
    newNode->next = NULL;

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node* current = list->head;
        int currentIndex = 0;
        while (current != NULL && currentIndex < index - 1) {
            current = current->next;
            currentIndex++;
        }
        if (current == NULL) return 1;

        newNode->next = current->next;
        current->next = newNode;
    }

    return 0;
}

int sizeLinkedList(const LinkedList* list) {
    int count = 0;
    Node* current = list->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int setLinkedList(LinkedList* list, int index, int item) {
    if(index < 0) return 1;

    Node* current = list->head;
    int currentIndex = 0;
    while (current != NULL && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }
    if (current == NULL) return 1;
    current->data = item;

    return 0;
}

int getLinkedList(const LinkedList* list, int index) {
    if(index < 0) return 1;

    Node* current = list->head;
    int currentIndex = 0;
    while (current != NULL && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }
    if (current == NULL) return -1;
    return current->data;
}

void printLinkedList(const LinkedList* list) {
    Node* current = list->head;
    printf("Your LinkedList: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void clearLinkedList(LinkedList* list) {
    while (list->head != NULL) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
    }
}
