#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 17

typedef struct {
    int num;
    char letter;
} Key;

typedef struct {
    char info[64];
} Data;

int compare_keys(Key a, Key b) {
    if (a.num < b.num) return -1;
    if (a.num > b.num) return 1;
    if (a.letter < b.letter) return -1;
    if (a.letter > b.letter) return 1;
    return 0;
}

void swap_elements(Key *k1, Data *d1, Key *k2, Data *d2) {
    Key tmp_k = *k1;
    Data tmp_d = *d1;
    *k1 = *k2;
    *d1 = *d2;
    *k2 = tmp_k;
    *d2 = tmp_d;
}

void selection_sort(Key keys[], Data data[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (compare_keys(keys[j], keys[min_idx]) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap_elements(&keys[i], &data[i], &keys[min_idx], &data[min_idx]);
        }
    }
}

int binary_search(Key keys[], int n, Key target) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = compare_keys(keys[mid], target);
        if (cmp == 0) return mid;
        if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void print_table(Key keys[], Data data[], int n, const char *title) {
    printf("\n--- %s ---\n", title);
    printf("%-5s | %-8s | %s\n", "Index", "Key", "Data");
    for (int i = 0; i < n; i++) {
        printf("%-5d | %-3d%-2c | %s\n", i, keys[i].num, keys[i].letter, data[i].info);
    }
}

void generate_data(Key keys[], Data data[], int n, int case_type) {
    for (int i = 0; i < n; i++) {
        if (case_type == 1) {
            keys[i].num = i * 2;
            keys[i].letter = 'A' + (i % 26);
        } else if (case_type == 2) {
            keys[i].num = (n - 1 - i) * 2;
            keys[i].letter = 'Z' - (i % 26);
        } else {
            keys[i].num = rand() % 100;
            keys[i].letter = 'A' + rand() % 26;
        }
        sprintf(data[i].info, "Element_%d", i);
    }
}

int main(void) {
    srand((unsigned int)time(NULL));

    Key keys[TABLE_SIZE];
    Data data[TABLE_SIZE];

    for (int t = 0; t < 3; t++) {
        generate_data(keys, data, TABLE_SIZE, t + 1);
        print_table(keys, data, TABLE_SIZE, "Original Table");

        selection_sort(keys, data, TABLE_SIZE);
        print_table(keys, data, TABLE_SIZE, "After Sorting");
    }

    int search_num;
    char search_letter;

    while (1) {
        printf("\nEnter key (num letter): ");
        if (scanf("%d", &search_num) != 1) break;
        if (search_num < 0) break;
        scanf(" %c", &search_letter);

        Key target = {search_num, search_letter};
        int idx = binary_search(keys, TABLE_SIZE, target);

        if (idx >= 0) {
            printf("Found: [%d%c] -> %s (index %d)\n", keys[idx].num, keys[idx].letter, data[idx].info, idx);
        } else {
            printf("Not found: [%d%c]\n", target.num, target.letter);
        }
    }

    return 0;
}