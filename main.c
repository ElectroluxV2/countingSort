#include <stdio.h>
#include <stdlib.h>

const long MAXIMUM_RAW_INPUT_LENGTH_NUMBER = 10;

long getInputArrayLength();
long* getInputArray(unsigned long length);
void printArray(const long* array, long length);
void swap(long* first, long* second);

long* countOccurrences(const long* array, const long length) {
    long* occurrences = calloc(10, sizeof(long));

    for (long i = 0; i < length; i++) {
        *(occurrences + *(array + i)) += 1;
    }

    return occurrences;
}

void countingSort(long** array, const long length, long* occurrences) {

    long* indices = occurrences;
    // Sum occurrences to create 1 based indices
    for (long i = 1; i < 10; i++) {
        *(indices + i) += *(indices + i -1);
    }

    // Transform to 0 based indices
    for (long i = 0; i < 10; i++) {
        *(indices + i) -= 1;
    }

    long* output = malloc(length * sizeof(long));
    for (long i = length - 1; i >= 0; i--) {
        *(output + (*(occurrences + *(*array + i)))--) = *(*array + i);
    }

    free(*array);
    *array = output;
}

int main() {
    long inputArrayLength = getInputArrayLength();
    long* inputArray = getInputArray(inputArrayLength);

    printArray(inputArray, inputArrayLength);

    long* occurrences = countOccurrences(inputArray, inputArrayLength);
    printArray(occurrences, 10);

    countingSort(&inputArray, inputArrayLength, occurrences);
    printArray(inputArray, inputArrayLength);

    free(occurrences);
    free(inputArray);

    return 0;
}

long getInputArrayLength() {
    long length = 0;

    while (length <= 0) {
        char* buffer = malloc(sizeof(char) * MAXIMUM_RAW_INPUT_LENGTH_NUMBER);
        scanf("%s", buffer);
        length = strtol(buffer, NULL, 10);
        free(buffer);
    }

    return length;
}

long* getInputArray(const unsigned long length) {
    long *array = malloc(sizeof(long) * length);

    for (long i = 0; i < length; i++) {
        char* buffer = malloc(sizeof(char) * MAXIMUM_RAW_INPUT_LENGTH_NUMBER);
        scanf("%s",  buffer);
        *(array + i) = strtol(buffer, NULL, 10);
        free(buffer);
    }

    return array;
}

void printArray(const long* array, const long length) {
    printf("Array (%ld) [", length);
    for (long i = 0; i < length; i++) {
        printf("%ld%s", *(array + i), i + 1 == length ? "" : ", ");
    }
    printf("]\n");
}

void swap(long* first, long* second) {
    const long tmp = *first;
    *first = *second;
    *second = tmp;
}