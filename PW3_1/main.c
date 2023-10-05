#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* array;
    size_t size;
    size_t capacity;
} ArrayList;

void initArrayList(ArrayList* list, size_t capacity) {
    list->array = (int*)malloc(capacity * sizeof(int));
    if (list->array == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    list->size = 0;
    list->capacity = capacity;
}

void resizeArrayList(ArrayList* list) {
    list->array = (int*)realloc(list->array, list->capacity * 2 * sizeof(int));
    if (list->array == NULL) {
        fprintf(stderr, "Memory reallocation failed.\n");
        exit(EXIT_FAILURE);
    }
    list->capacity = list->capacity * 2;
}

void addElement(ArrayList* list, int element) {
    if (list->size >= list->capacity) {
        resizeArrayList(list);
    }
    list->array[list->size++] = element;
}

void insertElement(ArrayList* list, int element, size_t index) {
    if (index > list->size) {
        fprintf(stderr, "Index out of bounds.\n");
        return;
    }
    if (list->size >= list->capacity) {
        resizeArrayList(list);
    }
    for (size_t i = list->size; i > index; --i) {
        list->array[i] = list->array[i - 1];
    }
    list->array[index] = element;
    list->size++;
}

void removeElement(ArrayList* list, size_t index) {
    if (index >= list->size) {
        fprintf(stderr, "Index out of bounds.\n");
        return;
    }
    for (size_t i = index; i < list->size - 1; ++i) {
        list->array[i] = list->array[i + 1];
    }
    list->size--;
}

void setElement(ArrayList* list, int element, size_t index) {
    if (index >= list->size) {
        fprintf(stderr, "Index out of bounds.\n");
        return;
    }
    list->array[index] = element;
}

int getElement(ArrayList* list, size_t index) {
    if (index >= list->size) {
        fprintf(stderr, "Index out of bounds.\n");
        exit(EXIT_FAILURE);
    }
    return list->array[index];
}

size_t getSize(ArrayList* list) {
    return list->size;
}

int main() {
    ArrayList list;
    initArrayList(&list, 10);
    int select;
    int val;
    int index;
    while(1){
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
                addElement(&list, val);
                continue;
            }
            case 2: {
                printf("Enter value: ");
                scanf("%d", &val);
                printf("Enter index: ");
                scanf("%d", &index);
                insertElement(&list, val, index);
                continue;
            }
            case 3: {
                printf("Enter value: ");
                scanf("%d", &val);
                printf("Enter index: ");
                scanf("%d", &index);
                setElement(&list, val, index);
                continue;
            }
            case 4: {
                printf("Enter index: ");
                scanf("%d", &index);
                removeElement(&list, index);
                continue;
            }
            case 5: {
                printf("Enter index: ");
                scanf("%d", &index);
                printf("%d ", getElement(&list, index));
                continue;
            }
            case 6: {
                for (size_t i = 0; i < getSize(&list); ++i) {
                    printf("%d ", getElement(&list, i));
                }
                continue;
            }
            case 7: {
                printf("Size: %zu", getSize(&list));
                continue;
            }
            case 0: {
                free(list.array);
                return 0;
            }
        }

    }
}
