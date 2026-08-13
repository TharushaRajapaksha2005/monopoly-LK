#include <stdio.h>
#include "types.h"

int main(void)
{
    GameplayState game;

    initializeGameBoard(&game);
    initializePlayers(&game);

    printf("=== BANKRUPTCY AFTER FORECLOSURE TEST ===\n\n");


    /* ===================================== */
    /* TEST 1 - PLAYER STILL HAS AN ASSET    */
    /* ===================================== */

    printf("TEST 1: PLAYER STILL HAS AN ASSET\n");

    game.players[0].isbankrupt = 0;

    game.players[0].loanActive = 1;
    game.players[0].loanAmount = 5000;
    game.players[0].loanRoundsRemaining = 0;
    game.players[0].loanInterestRate = 8;

    /*
        Pettah is pledged.
    */
    game.properties[0].owner = 0;
    game.properties[0].loanLocked = 1;

    /*
        Maradana is NOT pledged.
        Player should keep it.
    */
    game.properties[1].owner = 0;
    game.properties[1].loanLocked = 0;

    printf("Before default:\n");
    printf("Bankrupt: %d\n", game.players[0].isbankrupt);
    printf("Has assets: %d\n\n",
           hasAssets(&game, 0));

    handleLoanDefault(&game, 0);

    printf("\nAfter default:\n");
    printf("Pettah owner: %d\n",
           game.properties[0].owner);

    printf("Maradana owner: %d\n",
           game.properties[1].owner);

    printf("Has assets: %d\n",
           hasAssets(&game, 0));

    printf("Bankrupt: %d\n\n",
           game.players[0].isbankrupt);


    /* ===================================== */
    /* TEST 2 - PLAYER LOSES ALL ASSETS      */
    /* ===================================== */

    printf("=====================================\n");
    printf("TEST 2: PLAYER LOSES ALL ASSETS\n");
    printf("=====================================\n");

    /*
        Use Player 1 for a clean second test.
    */
    game.players[1].isbankrupt = 0;

    game.players[1].loanActive = 1;
    game.players[1].loanAmount = 4000;
    game.players[1].loanRoundsRemaining = 0;
    game.players[1].loanInterestRate = 8;

    /*
        Give Player 1 only two assets,
        and both are pledged.
    */
    game.properties[2].owner = 1;
    game.properties[2].loanLocked = 1;

    game.railways[1].owner = 1;
    game.railways[1].loanLocked = 1;

    printf("Before default:\n");
    printf("Bankrupt: %d\n",
           game.players[1].isbankrupt);

    printf("Has assets: %d\n\n",
           hasAssets(&game, 1));

    handleLoanDefault(&game, 1);

    printf("\nAfter default:\n");

    printf("%s owner: %d\n",
           game.properties[2].name,
           game.properties[2].owner);

    printf("%s owner: %d\n",
           game.railways[1].name,
           game.railways[1].owner);

    printf("Has assets: %d\n",
           hasAssets(&game, 1));

    printf("Bankrupt: %d\n",
           game.players[1].isbankrupt);

    return 0;
}