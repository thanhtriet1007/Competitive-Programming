#include <stdio.h>
#include <stdlib.h>
#define maxn 100009

int n, k;
int a[maxn];

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];  
    int i = low - 1;       

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        
        int pi = partition(arr, low, high);

 
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
int main() {
    scanf("%d%d", &n, &k); 
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    quickSort(a, 1, n);

    int ans = 0;
    k = n / k;
    for (int i = 1; i <= n - k + 1; i += k) {
        ans += a[i + k - 1] - a[i];
    }
    printf("%d", ans);
    return 0; 
}