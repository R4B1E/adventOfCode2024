#include "../../common.h"

#define MAX_LINES 1000

typedef struct {
    long* first;
    long* second;
}List ;

void swap(long *a, long *b) {
    long tmp = *a;
    *a = *b;
    *b = tmp;
}

void merge(long* list, int begin, int mid, int end) {
    int n1 = mid - begin + 1;
    int n2 = end - mid;

    long* left = malloc(n1 * sizeof(long));
    long* right = malloc(n2 * sizeof(long));

    for (int i = 0; i < n1; i++) left[i] = list[begin + i];
    for (int j = 0; j < n2; j++) right[j] = list[mid + 1 + j];

    int i = 0, j = 0, k = begin;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) list[k++] = left[i++];
        else list[k++] = right[j++];
    }

    while (i < n1) list[k++] = left[i++];
    while (j < n2) list[k++] = right[j++];


    free(left);
    free(right);
}

void sort_help(long* list, int begin, int end) {
    if (begin < end) {
        int mid = begin + (end - begin) / 2;
        sort_help(list, begin, mid);
        sort_help(list, mid + 1, end);
        merge(list, begin, mid, end);
    }
}

void sort(long* list, int size) {
    sort_help(list, 0, size - 1);
}


List readFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    long *firstList = (long*)malloc(MAX_LINES * sizeof(long));
    long *secondList = (long*)malloc(MAX_LINES * sizeof(long));
    int index = 0;
    size_t line_size;
    char* line = NULL;
    while (getline(&line, &line_size, file) > 0) {
        const char * token = strtok(line, " ");
        firstList[index] = strtol(token, NULL, 10);
        token = strtok(NULL, "\n");
        secondList[index++] = strtol(token, NULL, 10);
        free(line);
        line = NULL;
    }
    free(line);
    fclose(file);
    const List list = {firstList, secondList};
    return list;
}

int main(const int ac, const char **av)
{
    (void) ac;
    const List list = readFile(av[1]);
    sort(list.first, MAX_LINES);
    sort(list.second, MAX_LINES);
    long Sum = 0;
    for (int i = 0; i < MAX_LINES; i++) {
        Sum += labs(list.first[i] - list.second[i]);
    }
    printf("%li\n", Sum);
    free (list.first);
    free (list.second);
}