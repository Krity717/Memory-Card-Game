#include "game.h"
#include "utils.h"
#include <stdlib.h>
#include <time.h>

int main(void) {
    srand((unsigned int)time(NULL));
    clear_screen();
    show_menu();
    return 0;
}
