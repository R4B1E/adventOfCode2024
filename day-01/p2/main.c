#include "../../common.h"

#define MAX_LINES 1000

#define READ_BIT(value, index) (((value) >> (index)) & 1)
#define SET_BIT(value, index) (value |=  (1 << (index)))

long max(const long first, const long second) {
    return first > second ? first : second;
}

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

void sort(long* list, const int size) {
    sort_help(list, 0, size - 1);
}

int findFirstOccurrence(const long *list, const long value, long first, long last) {
    int firstOcc = -1;
    while (first <= last) {
        const long mid = (first + last) / 2;

        if (list[mid] == value) {
            firstOcc = mid;
            last = mid - 1;
        }
        else if (value < list[mid]) {
            last = mid - 1;
        }
        else {
            first = mid + 1;
        }
    }
    return firstOcc;
}

int findLastOccurrence(const long *list, const long value,long first, long last) {
    int lastOcc = -1;
    while (first <= last) {
        const long mid = (first + last) / 2;

        if (list[mid] == value) {
            lastOcc = mid;
            first = mid + 1;
        }
        else if (value < list[mid]) {
            last = mid - 1;
        }
        else {
            first = mid + 1;
        }
    }
    return lastOcc;
}

typedef struct {
    long* first;
    long* second;
    int size;
}List ;

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
    const List list = {firstList, secondList, index};
    return list;
}

int main(const int ac, const char **av) {
    (void)ac;
    const List list = readFile(av[1]);
    long totalSimilarityScore = 0;
    // how about setting MAX_LINES bits and set
    sort(list.first, list.size);
    sort(list.second, list.size);
    // build a hashMap with a capacity that it's the max value between the two lists, not efficient in space, but at least we make the code less complex by avoiding hash collisions ...
    // what happens when trying to get access index x even though it has no value ? it will give us a random value ... how can we solve that ? we can initialize the array with 0's
    // can I have another array that stores unique ID's that are set in the hash map ? with that I won't pass through all hashMap that contains the max value ...
    const long maxValue = max(list.first[list.size - 1], list.second[list.size - 1]);
    const long bitSetSize = maxValue / 8 + 1;
    char bitSet[bitSetSize];
    memset(bitSet, 0, bitSetSize);
    // >> 32 & bitmask
    long hashMap[maxValue + 1];
    for (int i = 0; i < list.size; i++) {
        // perform binary search for first occurrence and last occurrence
        const int firstOccurrence = findFirstOccurrence(list.second, list.first[i],0, list.size - 1);
        if (firstOccurrence != -1) {
            if (!READ_BIT(bitSet[list.first[i] / 8] , list.first[i] % 8)) {
                const int lastOccurrence = findLastOccurrence(list.second, list.first[i],0, list.size - 1);
                const int similarityScore = lastOccurrence - firstOccurrence + 1;
                hashMap[list.first[i]] = similarityScore;
                SET_BIT(bitSet[list.first[i] / 8], list.first[i] % 8);
                totalSimilarityScore += list.first[i] * similarityScore;
            }
            else {
                totalSimilarityScore += list.first[i] * hashMap[list.first[i]];
            }
        }
    }
    printf("%li", totalSimilarityScore);
    free(list.first);
    free(list.second);
    return 0;
}