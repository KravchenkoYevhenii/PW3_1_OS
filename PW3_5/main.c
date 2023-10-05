#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct Point {
    int position;
    int value;
    bool merged;
};

int findMinMassPoint(struct Point *points, int n) {
    int minMass = -1;
    int minMassIndex = -1;

    for (int i = 0; i < n; i++) {
        if (!points[i].merged && (minMass == -1 || points[i].value < minMass)) {
            minMass = points[i].value;
            minMassIndex = i;
        }
    }

    return minMassIndex;
}

int findNearestNeighbor(struct Point *points, int n, int index) {
    int nearestIndex = -1;
    int minDistance = -1;

    for (int i = 0; i < n; i++) {
        if (!points[i].merged && i != index) {
            int distance = abs(points[i].position - points[index].position);
            if (nearestIndex == -1 || distance < minDistance) {
                nearestIndex = i;
                minDistance = distance;
            }
        }
    }

    return nearestIndex;
}

void mergePoints(struct Point *points, int index1, int index2) {
    points[index2].value += points[index1].value;
    points[index1].value = 0;
    points[index1].merged = true;
}

int main() {
    srand(time(NULL));

    int n;
    printf("Enter number of points: ");
    scanf("%d", &n);

    struct Point *points = malloc(n * sizeof(struct Point));

    for (int i = 0; i < n; i++) {
        points[i].value = rand() % 50;
        points[i].position = i + 1;
        points[i].merged = false;
    }

    printf("Created points:\n");
    for (int i = 0; i < n; i++) {
        printf("Point %d: value: %d\n", points[i].position, points[i].value);
    }

    int remainingPoints = n;
    while (remainingPoints > 1) {
        int minMassIndex = findMinMassPoint(points, n);

        if (minMassIndex == -1) {
            break;
        }

        int nearestIndex = findNearestNeighbor(points, n, minMassIndex);

        mergePoints(points, minMassIndex, nearestIndex);

        printf("\nPoints %d and %d merged. Count of points: %d\n",
               points[minMassIndex].position, points[nearestIndex].position, remainingPoints - 1);

        for (int i = 0; i < n; i++) {
            if (!points[i].merged) {
                printf("Point %d: value: %d\n", points[i].position, points[i].value);
            }
        }

        remainingPoints--;
    }

    for (int i = 0; i < n; i++) {
        if (!points[i].merged) {
            printf("\nPoint remained %d with value: %d\n", points[i].position, points[i].value);
            break;
        }
    }

    free(points);

    return 0;
}