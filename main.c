#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"

int main(void)
{
    GameplayState game;
    int i;
    int result;

    srand(time(NULL));

    initializeGameBoard(&game);
    initializePlayers(&game);

    /*
        Nuwara Eliya
        propertyId = 20
        market value = 10000
    */

    printf("=== AUCTION DECISION TEST ===\n\n");

    printf("Current bid: LKR 10000\n");
    printf("Next bid: LKR 9250\n\n");

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        game.players[i].cash = 30000;

        result =
            shouldBidProperty(&game,
                              i,
                              20,
                              10000);

        printf("%s\n", game.players[i].name);

        if (result == 1)
        {
            printf("Decision: BID LKR 9250\n");
        }
        else
        {
            printf("Decision: WITHDRAW\n");
        }

        printf("\n");
    }

    return 0;
}