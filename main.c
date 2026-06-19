#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game_logic.h"
#include "display.h"
#include "utils.h"

int main() {
    int level;
    printf("=== MEMORY CARD GAME ===\n");
    printf("Select level:\n");
    printf("1. 6x6\n2. 8x8\n3. 10x10\n");
    printf("Enter choice: ");
    scanf("%d", &level);

    int size = (level == 1) ? 6 : (level == 2) ? 8 : 10;

    srand(time(NULL));
    startGame(size);

    return 0;
}
