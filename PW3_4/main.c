#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main() {
srand(time(NULL));
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);

    float arr[n];
    float sum = 0;

    for (int i = 0; i < n; ++i) {
        arr[i] = (rand() % (15 - (-15) + 1)) + (-15);
        sum += arr[i];
        printf("%.2f ", arr[i]);
    }
    printf("\n");
    float average = sum / n;
    printf("Average: %.2f\n", average);
    int count = 0;
    float absSum = 0;
    int negativeFound = 0;

    for (int i = 0; i < n; ++i) {
        if (arr[i] > average) {
            count++;
        }

        if (arr[i] < 0) {
            negativeFound = 1;
        }

        if (negativeFound) {
            absSum += fabsf(arr[i]);
        }
    }

    printf("Count arr[i] > average: %d\n", count);
    printf("Sum abs: %.2f\n", absSum);

    return 0;
}

