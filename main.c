#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"

int main(void)
{
    GameplayState game;

    initializeGameBoard(&game);
    initializePlayers(&game);

    srand(time(NULL));

    printf("=== DISASTER TEST ===\n\n");

    /*
        Give Player 0 some money.
    */
    game.players[0].cash = 10000;

    /*
        Make Pettah a developed property.
    */
    game.properties[0].owner = 0;
    game.properties[0].houses = 2;
    game.properties[0].hotel = 0;
    game.properties[0].damaged = 0;

    /*
        Give it Basic Insurance.
    */
    game.properties[0].insuranceType = BASIC_INSURANCE;
    game.properties[0].insuranceRoundsRemaining = 20;


    /*
        Make Maradana another developed property.
    */
    game.properties[1].owner = 0;
    game.properties[1].houses = 0;
    game.properties[1].hotel = 1;
    game.properties[1].damaged = 0;

    /*
        Give it Comprehensive Insurance.
    */
    game.properties[1].insuranceType = COMPREHENSIVE_INSURANCE;
    game.properties[1].insuranceRoundsRemaining = 20;


    printf("BEFORE DISASTER\n");
    printf("-----------------------------\n");

    printf("%s\n", game.properties[0].name);
    printf("Damaged: %d\n", game.properties[0].damaged);
    printf("Insurance Type: %d\n\n",
           game.properties[0].insuranceType);

    printf("%s\n", game.properties[1].name);
    printf("Damaged: %d\n", game.properties[1].damaged);
    printf("Insurance Type: %d\n\n",
           game.properties[1].insuranceType);

    printf("Player Cash: LKR %d\n\n",
           game.players[0].cash);


    /*
        Trigger one disaster.
    */
    triggerDisaster(&game);


    printf("\nAFTER DISASTER\n");
    printf("-----------------------------\n");

    printf("%s\n", game.properties[0].name);
    printf("Damaged: %d\n\n",
           game.properties[0].damaged);

    printf("%s\n", game.properties[1].name);
    printf("Damaged: %d\n\n",
           game.properties[1].damaged);

    printf("Player Cash: LKR %d\n",
           game.players[0].cash);

    return 0;
}