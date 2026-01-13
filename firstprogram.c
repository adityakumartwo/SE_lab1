#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void heapify(int arr[], int n, int i) {
    int largest = i;        
    int left = 2 * i + 1;   
    int right = 2 * i + 2; 

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);

        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
    
}

int main() {

    FILE *fin, *fout;
    int n, i;

    fin = fopen("heapInput.txt", "r");
    if (fin == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    fscanf(fin, "%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        fscanf(fin, "%d", &arr[i]);

    fclose(fin);

    heapSort(arr, n);

    fout = fopen("heapOutput.txt", "w");
    if (fout == NULL) {
        printf("Error opening output file!\n");
        free(arr);
        return 1;
    }

    printArray(arr, n);
    fprintf(fout, "\n");

    fclose(fout);
    // free(arr);

    printf("Sorting complete. Check output.txt\n");
    return 0;



//     int arr[] = {12, 11, 13, 5, 6, 7};
//     int n = sizeof(arr) / sizeof(arr[0]);

//     printf("Unsorted array: ");
//     printArray(arr, n);

//     heapSort(arr, n);

//     printf("Sorted array:   ");
//     printArray(arr, n);

//     return 0;
}