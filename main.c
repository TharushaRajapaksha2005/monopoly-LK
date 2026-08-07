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

    printf("=== RAILWAY BID TEST ===\n\n");

    /*
        Test railway 0.

        Set currentBid close to its market value
        so we can see different strategy decisions.
    */

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        game.players[i].cash = 30000;
    }

    printf("Railway market value: LKR %d\n",
           game.railways[0].currentMarketValue);

    printf("Current bid: LKR %d\n\n",
           game.railways[0].currentMarketValue);

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        result = shouldBidRailway(
            &game,
            i,
            0,
            game.railways[0].currentMarketValue - 1000);

        printf("%s: ",
               game.players[i].name);

        if (result == 1)
        {
            printf("BID\n");
        }
        else
        {
            printf("WITHDRAW\n");
        }
    }

    printf("\n==============================\n");
    printf("=== UTILITY BID TEST ===\n\n");

    printf("Utility market value: LKR %d\n",
           game.utilities[0].currentMarketValue);

    printf("Current bid: LKR %d\n\n",
           game.utilities[0].currentMarketValue);

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        result = shouldBidUtility(
            &game,
            i,
            0,
            game.utilities[0].currentMarketValue - 1000);

        printf("%s: ",
               game.players[i].name);

        if (result == 1)
        {
            printf("BID\n");
        }
        else
        {
            printf("WITHDRAW\n");
        }
    }

    return 0;
}