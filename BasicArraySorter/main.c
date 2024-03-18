#include <stdio.h>

int isSorted(int arr[], int len)
{
    if (len == 1 || len == 0) {
        return 1;
    }

    if (arr[len-1] < arr[len-2])
    {
        return 0;
    }

    return isSorted(arr, len-1);
}

int main()
{
    int arr[] = {5, 9, 2, 8, 0, 1, 7, 4, 6, 3};
    int arrLen = sizeof(arr) / sizeof(arr[0]);
    int temp;

    printf("Unsorted: ");
    for (size_t i = 0; i < arrLen; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");

    // Sort the array
    while (!isSorted(arr, arrLen)) {
        for (size_t i = 0; i < arrLen; i++) {
            if (arr[i] > arr[i+1] && arrLen > i+1) {
                temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
            }
        }
        printf("          ");
        for (size_t i = 0; i < arrLen; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    printf("\n  Sorted: ");
    for (size_t i = 0; i < arrLen; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
