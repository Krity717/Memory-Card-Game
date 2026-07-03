# Memory Concentration Card Game

## Setup & Compile Instructions

### Linux
- Ensure GCC is installed.
- Run:

-->// for me
make
./memory_game


## How to Play & Controls

- Select a level (1-5) and number of players (1-3).
- On your turn, enter the row and column of two cards to reveal.
- If they match, you get a point and the cards stay revealed.
- If they don't match, they are hidden again.
- The game ends when all pairs are matched.
- The player with the most points wins.
- The best completion time per level is saved.
- Press -1 -1 at any time to exit.

## Fair Play (Anti-Cheating) Explanation

- Non-matching cards are flipped back before the turn is passed.
- After each turn, the screen is cleared only after the next player presses ENTER.
- This ensures no player can see the previous player's revealed cards.

## Record File Format

- The file `data/record.txt` stores the best completion time for each level in the format:

-->//
Level 1: 12.34
Level 2: 23.45


## Option to Disable Color

- This project uses ANSI colors for terminal output.
- If your terminal does not support color, simply ignore the color codes or remove them from the code.

## Notes

- The game is modular and cross-platform.
- The Makefile is provided for Linux; Windows users can compile manually.


