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

    printf("=== TEST 6: SECOND UTILITY ===\n\n");

    game.players[0].position = 28;

    handleUtilityLanding(&game, 0, 7);

    printf("\nUtility 1 owner ID: %d\n",
           game.utilities[1].owner);

    return 0;
}