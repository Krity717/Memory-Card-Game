#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

void loadPatterns(char patterns[][10], int totalPairs) {
    FILE *f = fopen("patterns.txt", "r");
    int i = 0;
    while (f && fscanf(f, "%s", patterns[i]) != EOF && i < totalPairs) i++;
    fclose(f);
}

void initializeBoard(char board[][10], char patterns[][10], int size) {
    // duplicate each pattern twice, shuffle, and assign to board
}

void initializeShown(char shown[][10], int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            shown[i][j] = '*';
}

void flipCards(char board[][10], char shown[][10], int r1, int c1, int r2, int c2) {
    shown[r1][c1] = board[r1][c1];
    shown[r2][c2] = board[r2][c2];
}

void pauseAndHide(char shown[][10], int r1, int c1, int r2, int c2) {
    printf("\nNot a match! Try again...\n");
    sleep(2);
    shown[r1][c1] = '*';
    shown[r2][c2] = '*';
}
