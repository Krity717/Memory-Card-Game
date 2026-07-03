#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

void update_record(int level, double time) {
    char filename[] = "data/record.txt";
    FILE *file = fopen(filename, "r+");
    if (!file) {
        file = fopen(filename, "w");
        if (!file) return;
    }

    char line[100];
    int found = 0;
    long pos = 0;
    while (fgets(line, sizeof(line), file)) {
        int l;
        double best;
        if (sscanf(line, "Level %d: %.2f", &l, &best) == 2 && l == level) {
            if (time < best || best == 0.0) {
                fseek(file, pos, SEEK_SET);
                fprintf(file, "Level %d: %.2f\n", level, time);
                found = 1;
            }
            break;
        }
        pos = ftell(file);
    }

    if (!found) {
        fseek(file, 0, SEEK_END);
        fprintf(file, "Level %d: %.2f\n", level, time);
    }

    fclose(file);
}
