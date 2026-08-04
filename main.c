#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"

int main(void)
{
    GameplayState game;

    srand(time(NULL));

    initializeGameBoard(&game);
    initializePlayers(&game);

    printf("=== TEST 5: PLAY TURN WHILE JAILED ===\n");

    game.players[0].position = 10;
    game.players[0].inJail = 1;
    game.players[0].jailTurns = 0;

    playTurn(&game, 0);

    return 0;
}