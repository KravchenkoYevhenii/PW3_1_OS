#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    size_t size;
} LinkedList;

void initLinkedList(LinkedList* list) {
    list->head = NULL;
    list->size = 0;
}

void addElementAtEnd(LinkedList* list, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
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

    list->size++;
}

void addElementAtIndex(LinkedList* list, int data, size_t index) {
    if (index > list->size) {
        fprintf(stderr, "Index out of bounds.\n");
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;

    if (index == 0) {
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node* current = list->head;
        for (size_t i = 1; i < index; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    list->size++;
}

void removeElementAtIndex(LinkedList* list, size_t index) {
    if (index >= list->size) {
        fprintf(stderr, "Index out of bounds.\n");
        return;
    }

    Node* temp;
    if (index == 0) {
        temp = list->head;
        list->head = list->head->next;
    } else {
        Node* current = list->head;
        for (size_t i = 1; i < index; ++i) {
            current = current->next;
        }
        temp = current->next;
        current->next = temp->next;
    }

    free(temp);
    list->size--;
}

int getElementAtIndex(LinkedList* list, size_t index) {
    if (index >= list->size) {
        fprintf(stderr, "Index out of bounds.\n");
        exit(EXIT_FAILURE);
    }

    Node* current = list->head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}
void setElementAtIndex(LinkedList* list, int data, size_t index) {
    if (index >= list->size) {
        fprintf(stderr, "Index out of bounds.\n");
        return;
    }

    Node* current = list->head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    current->data = data;
}

size_t getSize(LinkedList* list) {
    return list->size;
}

int main() {
    LinkedList list;
    initLinkedList(&list);

    int select;
    int val;
    int index;
    while(1) {
        printf("\n");
        printf("1. add;\n");
        printf("2. insert;\n");
        printf("3. set;\n");
        printf("4. remove;\n");
        printf("5. get;\n");
        printf("6. print;\n");
        printf("7. size;\n");
        printf("0. exit;\n");
        scanf("%d", &select);
        switch (select) {
            case 1 : {
                printf("Enter value: ");
                scanf("%d", &val);
                addElementAtEnd(&list, val);
                continue;
            }
            case 2: {
                printf("Enter value: ");
                scanf("%d", &val);
                printf("Enter index: ");
                scanf("%d", &index);
                addElementAtIndex(&list, val, index);
                continue;
            }
            case 3: {
                printf("Enter value: ");
                scanf("%d", &val);
                printf("Enter index: ");
                scanf("%d", &index);
                setElementAtIndex(&list, val, index);
                continue;
            }
            case 4: {
                printf("Enter index: ");
                scanf("%d", &index);
                removeElementAtIndex(&list, index);
                continue;
            }
            case 5: {
                printf("Enter index: ");
                scanf("%d", &index);
                printf("%d ", getElementAtIndex(&list, index));
                continue;
            }
            case 6: {
                for (size_t i = 0; i < getSize(&list); ++i) {
                    printf("%d ", getElementAtIndex(&list, i));
                }
                continue;
            }
            case 7: {
                printf("Size: %zu", getSize(&list));
                continue;
            }
            case 0: {
                Node *current = list.head;
                while (current != NULL) {
                    Node *temp = current;
                    current = current->next;
                    free(temp);
                }
                return 0;
            }
        }
    }
}
