#include <stdio.h>
#include "types.h"

int main(void)
{
    GameplayState game;

    initializeGameBoard(&game);
    initializePlayers(&game);

    printf("Player 1: %s\n", game.players[0].name);
    printf("Cash: LKR %d\n", game.players[0].cash);
    printf("Position: %d\n", game.players[0].position);

    printf("\nPlayer 2: %s\n", game.players[1].name);
    printf("Cash: LKR %d\n", game.players[1].cash);

    printf("\nPlayer 3: %s\n", game.players[2].name);
    printf("Cash: LKR %d\n", game.players[2].cash);

    printf("\nPlayer 4: %s\n", game.players[3].name);
    printf("Cash: LKR %d\n", game.players[3].cash);

    return 0;
}