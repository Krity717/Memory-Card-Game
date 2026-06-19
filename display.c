#include <stdio.h>
#include <stdlib.h>
#include "display.h"

void displayBoard(char shown[][10], int size) {
    printf("\n   ");
    for (int i = 0; i < size; i++) printf("%2d ", i);
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("%2d ", i);
        for (int j = 0; j < size; j++) {
            printf("%2c ", shown[i][j]);
        }
        printf("\n");
    }
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
