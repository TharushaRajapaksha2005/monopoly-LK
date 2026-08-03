#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"

int main(void)
{
    GameplayState game;
    int i;
    int playerId;

    srand(time(NULL));

    initializeGameBoard(&game);
    initializePlayers(&game);

    printf("Player positions: %d %d %d %d\n",
           game.players[0].position,
           game.players[1].position,
           game.players[2].position,
           game.players[3].position);

    determineTurnOrder(&game);

    printf("\n========== ROUND 1 ==========\n");

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        playerId = game.turnOrder[i];
        playTurn(&game, playerId);
    }

    return 0;
}