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

    game.incomeTaxRate = 0.15f;
    game.communityFundRate = 0.10f;

    printf("=== START TEST ===\n");
    game.players[0].position = 0;
    resolveLanding(&game, 0, 7);

    printf("\n=== JAIL VISITING TEST ===\n");
    game.players[0].position = 10;
    game.players[0].inJail = 0;
    resolveLanding(&game, 0, 7);

    printf("\n=== FREE PARKING TEST ===\n");
    game.players[0].position = 20;
    resolveLanding(&game, 0, 7);

    printf("\n=== TAX PLACEHOLDER TEST ===\n");
    game.players[0].position = 4;
    resolveLanding(&game, 0, 7);

    return 0;
}