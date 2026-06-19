#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "display.h"
#include "utils.h"

void startGame(int size) {
    char board[10][10], shown[10][10];
    char patterns[100][10];
    int totalPairs = (size * size) / 2;

    loadPatterns(patterns, totalPairs);
    initializeBoard(board, patterns, size);
    initializeShown(shown, size);

    int attempts = 0, matches = 0;
    time_t start, end;
    time(&start);

    while (matches < totalPairs) {
        clearScreen();
        displayBoard(shown, size);

        int r1, c1, r2, c2;
        printf("\nEnter first card (row col) or 0 0 to quit: ");
        scanf("%d %d", &r1, &c1);
        if (r1 == 0 && c1 == 0) break;

        printf("Enter second card (row col): ");
        scanf("%d %d", &r2, &c2);

        flipCards(board, shown, r1, c1, r2, c2);
        attempts++;

        if (board[r1][c1] == board[r2][c2]) matches++;
        else pauseAndHide(shown, r1, c1, r2, c2);
    }

    time(&end);
    double totalTime = difftime(end, start);
    int minutes = totalTime / 60;
    int seconds = (int)totalTime % 60;
    double score = 1000.0 / (attempts + minutes + 1);

    clearScreen();
    if (matches == totalPairs)
        printf("🎉 You cleared the board!\n");
    else
        printf("👋 You quit early.\n");

    printf("Attempts: %d\nTime: %d min %d sec\nScore: %.2f\n", attempts, minutes, seconds, score);
}
