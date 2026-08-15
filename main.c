#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"


int main(void)
{
    GameplayState game;
    int i;

    /*
        Seed random number generator.
        Do this only once.
    */
    srand(2026);


    /*
        Initialize board and players.
    */
    initializeGameBoard(&game);
    initializePlayers(&game);


    /*
        Game starts at round 0.
    */
    game.currentRound = 0;


    /*
        Financial / economic starting values.
    */
    game.repairCost = 1000;

    game.insurancePremiumFactor = 100;

    game.loanInterestRate = 10;


    /*
        Tax rates.
    */
    game.incomeTaxRate = 15;

    game.communityFundRate = 10;


    /*
        Dynamic property market.
    */
    game.boomGroup = NO_GROUP;
    game.declineGroup = NO_GROUP;

    game.boomRoundsRemaining = 0;
    game.declineRoundsRemaining = 0;


    /*
        Government regulation.

        There is no regulation before
        the first regulation is selected.
    */
    game.currentGovRegulation = NO_REGULATION;


    /*
        Allow every property group to be
        selected when the first market
        event occurs.
    */
    for (i = 0; i < 8; i++)
    {
        game.lastMarketAffectedRound[i] = -30;
    }


    /*
        Initially nobody has completed
        a lap for the first game round.
    */
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        game.players[i].completedLap = 0;
    }


    /*
        Roll dice and determine the
        starting player order.
    */
    determineTurnOrder(&game);


    printf("\n");
    printf("====================================\n");
    printf("        MONOPOLY-LK STARTED\n");
    printf("====================================\n");


    /*
        Run the simulation.

        The game stops when:

        1. Only one solvent player remains

        OR

        2. 500 GAME ROUNDS are completed.
    */
    while (game.currentRound < 500 &&
           countSolventPlayers(&game) > 1)
    {
        playTurnCycle(&game);
    }


    /*
        Show final winner and player status.
    */
    printGameResult(&game);


    return 0;
}