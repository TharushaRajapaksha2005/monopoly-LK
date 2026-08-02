#include <string.h>
#include "types.h"

void initializePlayers(GameplayState *game)
{
    /*Player 0 - Aggressive Inverstor*/
    game->players[0].playerId = 0;
    strcpy(game->players[0].name, "Aggressive Investor");
    game->players[0].strategy = AGGRESSIVE;
    game->players[0].cash = STARTING_CASH;
    game->players[0].position = 0;
    game->players[0].isbankrupt = 0;
    game->players[0].isJailed = 0;
    game->players[0].jailTurns = 0;

    /* Player 1 - Conservative Banker */
    game->players[1].playerId = 1;
    strcpy(game->players[1].name, "Conservative Banker");
    game->players[1].strategy = CONSERVATIVE;
    game->players[1].cash = STARTING_CASH;
    game->players[1].position = 0;
    game->players[1].isbankrupt = 0;
    game->players[1].isJailed = 0;
    game->players[1].jailTurns = 0;

    /* Player 2 - Risk Taker */
    game->players[2].playerId = 2;
    strcpy(game->players[2].name, "Risk Taker");
    game->players[2].strategy = RISK_TAKER;
    game->players[2].cash = STARTING_CASH;
    game->players[2].position = 0;
    game->players[2].isbankrupt = 0;
    game->players[2].isJailed = 0;
    game->players[2].jailTurns = 0;

    /* Player 3 - Opportunistic Trader */
    game->players[3].playerId = 3;
    strcpy(game->players[3].name, "Opportunistic Trader");
    game->players[3].strategy = OPPORTUNISTIC;
    game->players[3].cash = STARTING_CASH;
    game->players[3].position = 0;
    game->players[3].isbankrupt = 0;
    game->players[3].isJailed = 0;
    game->players[3].jailTurns = 0;
}