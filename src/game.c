#include "game.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PLAYERS 3
#define MAX_LEVELS 5
#define MAX_CARDS 64

// Emoji symbols for cards
const char* emojis[] = {
    "\U0001F34E", // 🍎
    "\U0001F347", // 🍇
    "\U0001F34D", // 🍍
    "\U0001F319", // 🌙
    "\U0001F308", // 🌈
    "\U0001F327", // 🌧️
    "\U0001F525", // 🔥
    "\U0001F342", // 🍂
    "\U000023F0", // ⏰
    "\U000026BD", // ⚽
    "\U0001F48E", // 💎
    "\U0001F511", // 🔑
    "\U0001F4D8", // 📘
    "\U0001F436", // 🐶
    "\U0001F430", // 🐰
    "\U0001F98A", // 🦊
    "\U0001F422", // 🐢
    "\U0001F418", // 🐘
    "\U0001F334", // 🌴
    "\U0001F384", // 🎄
    "\U0001F33E", // 🌾
    "\U0001F33F", // 🌿
    "\U0001F33A"  // 🌺
};

typedef struct {
    int value;
    int revealed;
    int matched;
} Card;

typedef struct {
    char name[20];
    int score;
    double best_time;
} Player;

typedef struct {
    int size;
    Card board[MAX_CARDS];
    int pairs;
    int revealed_count;
    int matched_count;
    int turn;
    Player players[MAX_PLAYERS];
    int num_players;
    int current_player;
    double start_time;
    double total_time;
} GameState;

GameState state;

void init_game(int level, int num_players) {
    int board_size = (level + 1) * 2;
    int total_cards = board_size * board_size;
    state.size = board_size;
    state.pairs = total_cards / 2;
    state.revealed_count = 0;
    state.matched_count = 0;
    state.turn = 0;
    state.num_players = num_players;
    state.current_player = 0;
    state.total_time = 0.0;

    for (int i = 0; i < total_cards; i++) {
        state.board[i].value = i / 2;
        state.board[i].revealed = 0;
        state.board[i].matched = 0;
    }

    for (int i = 0; i < total_cards; i++) {
        int j = rand() % total_cards;
        Card temp = state.board[i];
        state.board[i] = state.board[j];
        state.board[j] = temp;
    }

    for (int i = 0; i < num_players; i++) {
        printf("Enter name for Player %d: ", i + 1);
        scanf("%19s", state.players[i].name);
        state.players[i].score = 0;
        state.players[i].best_time = 0.0;
    }
}

void print_board() {
    int size = state.size;
    printf("\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int idx = i * size + j;
            if (state.board[idx].matched) {
                printf("  *  ");
            } else if (state.board[idx].revealed) {
                printf(" %s ", emojis[state.board[idx].value]);
            } else {
                printf("  ?  ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int get_card_index(int row, int col) {
    if (row < 0 || row >= state.size || col < 0 || col >= state.size) return -1;
    return row * state.size + col;
}

void reveal_card(int row, int col) {
    int idx = get_card_index(row, col);
    if (idx != -1 && !state.board[idx].matched && !state.board[idx].revealed) {
        state.board[idx].revealed = 1;
        state.revealed_count++;
    }
}

void hide_card(int row, int col) {
    int idx = get_card_index(row, col);
    if (idx != -1 && !state.board[idx].matched) {
        state.board[idx].revealed = 0;
    }
}

int check_match(int row1, int col1, int row2, int col2) {
    int idx1 = get_card_index(row1, col1);
    int idx2 = get_card_index(row2, col2);
    if (idx1 == -1 || idx2 == -1) return 0;
    if (state.board[idx1].value == state.board[idx2].value) {
        state.board[idx1].matched = 1;
        state.board[idx2].matched = 1;
        state.matched_count++;
        state.players[state.current_player].score++;
        return 1;
    }
    return 0;
}

void next_player() {
    state.current_player = (state.current_player + 1) % state.num_players;
    state.turn++;
}

void play_game() {
    int level, num_players;
    printf("Select level (1-5): ");
    scanf("%d", &level);
    level = (level < 1) ? 1 : (level > 5) ? 5 : level;
    printf("Number of players (1-3): ");
    scanf("%d", &num_players);
    num_players = (num_players < 1) ? 1 : (num_players > 3) ? 3 : num_players;

    init_game(level, num_players);
    state.start_time = get_time();

    while (state.matched_count < state.pairs) {
        clear_screen();
        printf("Level: %d | Players: %d\n", level, num_players);
        printf("Player %s's turn\n", state.players[state.current_player].name);
        print_board();

        int row1, col1, row2, col2;
        printf("Enter first card (row col): ");
        if (scanf("%d %d", &row1, &col1) != 2) break;
        if (row1 == -1 || col1 == -1) break;

        reveal_card(row1, col1);
        print_board();

        printf("Enter second card (row col): ");
        if (scanf("%d %d", &row2, &col2) != 2) break;
        if (row2 == -1 || col2 == -1) break;

        reveal_card(row2, col2);
        print_board();

        if (check_match(row1, col1, row2, col2)) {
            printf("Match found!\n");
        } else {
            printf("No match. Cards will be hidden.\n");
            hide_card(row1, col1);
            hide_card(row2, col2);
        }

        printf("Press ENTER to pass turn...");
        getchar();
        getchar();
        next_player();
    }

    double elapsed = get_time() - state.start_time;
    state.total_time = elapsed;
    printf("Game over! Total time: %.2f seconds\n", elapsed);
    for (int i = 0; i < num_players; i++) {
        printf("%s: %d points\n", state.players[i].name, state.players[i].score);
    }

    update_record(level, elapsed);
}

void show_records() {
    FILE *file = fopen("data/record.txt", "r");
    if (!file) {
        printf("No records found.\n");
        return;
    }
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

void show_instructions() {
    printf("How to Play:\n");
    printf("1. Select a level (1-5) and number of players (1-3).\n");
    printf("2. On your turn, enter the row and column of two cards to reveal.\n");
    printf("3. If they match, you get a point and the cards stay revealed.\n");
    printf("4. If they don't match, they are hidden again.\n");
    printf("5. The game ends when all pairs are matched.\n");
    printf("6. The player with the most points wins.\n");
    printf("7. The best completion time per level is saved.\n");
    printf("8. Press -1 -1 at any time to exit.\n");
}

void show_menu() {
    int choice;
    do {
        printf("\n--- Memory Concentration Card Game ---\n");
        printf("1. Start Game\n");
        printf("2. View Best Records\n");
        printf("3. How to Play\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                play_game();
                break;
            case 2:
                show_records();
                break;
            case 3:
                show_instructions();
                break;
            case 4:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 4);
}
