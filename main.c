#include <stdio.h>
#include "types.h"

int main(void)
{
    GameplayState game;
    int result;

    initializeGameBoard(&game);
    initializePlayers(&game);

    printf("=== MORTGAGE TESTS ===\n\n");

    /* ============================= */
    /* TEST 1 - PROPERTY MORTGAGE    */
    /* ============================= */

    printf("TEST 1: PROPERTY MORTGAGE\n");

    game.players[0].cash = 10000;

    game.properties[0].owner = 0;
    game.properties[0].mortgaged = 0;
    game.properties[0].houses = 0;
    game.properties[0].hotel = 0;

    printf("Cash before: LKR %d\n",
           game.players[0].cash);

    printf("Mortgage value: LKR %d\n",
           game.properties[0].mortgageValue);

    result = mortgageProperty(&game, 0, 0);

    printf("Result: %d\n", result);

    printf("Cash after: LKR %d\n",
           game.players[0].cash);

    printf("Mortgage status: %d\n\n",
           game.properties[0].mortgaged);

    /* ============================= */
    /* TEST 2 - SAME PROPERTY AGAIN  */
    /* ============================= */

    printf("TEST 2: MORTGAGE SAME PROPERTY AGAIN\n");

    result = mortgageProperty(&game, 0, 0);

    printf("Result: %d\n", result);

    printf("Cash: LKR %d\n",
           game.players[0].cash);

    printf("Mortgage status: %d\n\n",
           game.properties[0].mortgaged);

    /* ============================= */
    /* TEST 3 - DEVELOPED PROPERTY   */
    /* ============================= */

    printf("TEST 3: DEVELOPED PROPERTY\n");

    game.properties[1].owner = 0;
    game.properties[1].mortgaged = 0;
    game.properties[1].houses = 2;
    game.properties[1].hotel = 0;

    result = mortgageProperty(&game, 0, 1);

    printf("Result: %d\n", result);

    printf("Mortgage status: %d\n\n",
           game.properties[1].mortgaged);

    /* ============================= */
    /* TEST 4 - RAILWAY MORTGAGE     */
    /* ============================= */

    printf("TEST 4: RAILWAY MORTGAGE\n");

    game.players[0].cash = 10000;

    game.railways[0].owner = 0;
    game.railways[0].mortgaged = 0;

    printf("Cash before: LKR %d\n",
           game.players[0].cash);

    printf("Mortgage value: LKR %d\n",
           game.railways[0].mortgageValue);

    result = mortgageRailway(&game, 0, 0);

    printf("Result: %d\n", result);

    printf("Cash after: LKR %d\n",
           game.players[0].cash);

    printf("Mortgage status: %d\n\n",
           game.railways[0].mortgaged);

    /* ============================= */
    /* TEST 5 - UTILITY MORTGAGE     */
    /* ============================= */

    printf("TEST 5: UTILITY MORTGAGE\n");

    game.players[0].cash = 10000;

    game.utilities[0].owner = 0;
    game.utilities[0].mortgaged = 0;

    printf("Cash before: LKR %d\n",
           game.players[0].cash);

    printf("Mortgage value: LKR %d\n",
           game.utilities[0].mortgageValue);

    result = mortgageUtility(&game, 0, 0);

    printf("Result: %d\n", result);

    printf("Cash after: LKR %d\n",
           game.players[0].cash);

    printf("Mortgage status: %d\n\n",
           game.utilities[0].mortgaged);

    /* ============================= */
    /* TEST 6 - NOT THE OWNER        */
    /* ============================= */

    printf("TEST 6: TRY TO MORTGAGE SOMEONE ELSE'S ASSET\n");

    game.properties[2].owner = 1;
    game.properties[2].mortgaged = 0;

    result = mortgageProperty(&game, 0, 2);

    printf("Result: %d\n",
           result);

    printf("Mortgage status: %d\n",
           game.properties[2].mortgaged);

    return 0;
}