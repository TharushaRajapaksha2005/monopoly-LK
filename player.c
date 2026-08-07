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
    game->players[0].inJail = 0;
    game->players[0].jailTurns = 0;

    /* Player 1 - Conservative Banker */
    game->players[1].playerId = 1;
    strcpy(game->players[1].name, "Conservative Banker");
    game->players[1].strategy = CONSERVATIVE;
    game->players[1].cash = STARTING_CASH;
    game->players[1].position = 0;
    game->players[1].isbankrupt = 0;
    game->players[1].inJail = 0;
    game->players[1].jailTurns = 0;

    /* Player 2 - Risk Taker */
    game->players[2].playerId = 2;
    strcpy(game->players[2].name, "Risk Taker");
    game->players[2].strategy = RISK_TAKER;
    game->players[2].cash = STARTING_CASH;
    game->players[2].position = 0;
    game->players[2].isbankrupt = 0;
    game->players[2].inJail = 0;
    game->players[2].jailTurns = 0;

    /* Player 3 - Opportunistic Trader */
    game->players[3].playerId = 3;
    strcpy(game->players[3].name, "Opportunistic Trader");
    game->players[3].strategy = OPPORTUNISTIC;
    game->players[3].cash = STARTING_CASH;
    game->players[3].position = 0;
    game->players[3].isbankrupt = 0;
    game->players[3].inJail = 0;
    game->players[3].jailTurns = 0;
}

int shouldBuyProperty(GameplayState *game, int playerId, int propertyId)
{
    int cash;
    int price;
    int remainingCash;
    int futureRent;

    cash = game->players[playerId].cash;
    price = game->properties[propertyId].purchasePrice;
    futureRent = game->properties[propertyId].baseRent;

    remainingCash = cash - price;

    if (cash < price)
    {
        return 0;
    }

    switch (game->players[playerId].strategy)
    {
    case 0:                              // aggressive
        if (remainingCash >= futureRent) /*need money to pay atleast one future rent*/
        {
            return 1;
        }

        return 0;

    case 1:                            // conservative
        if (remainingCash >= cash / 2) /*need 50 % of current cash after buying stuff*/
        {
            return 1;
        }

        return 0;

    case 2:       // risk taker
        return 1; /* buy every possible thing*/

    case 3: // opertunistic:
        if (remainingCash >= price)
        {
            return 1;
        }

        return 0;
    }

    return 0;
}

int shouldBuyRailway(GameplayState *game, int playerId, int railwayId)
{
    int cash;
    int price;
    int remainingCash;

    cash = game->players[playerId].cash;
    price = game->railways[railwayId].purchasePrice;

    remainingCash = cash - price;

    if (cash < price)
    {
        return 0;
    }

    switch (game->players[playerId].strategy)
    {
    case 0: // aggressive
        if (remainingCash > 0)
        {
            return 1;
        }

        return 0;

    case 1: // conservative
        if (remainingCash >= cash / 2)
        {
            return 1;
        }

        return 0;

    case 2: // resk taker
        return 1;

    case 3: // opertunistic
        if (remainingCash >= price)
        {
            return 1;
        }

        return 0;
    }

    return 0;
}

int shouldBuyUtility(GameplayState *game, int playerId, int utilityId)
{
    int cash;
    int price;
    int remainingCash;

    cash = game->players[playerId].cash;
    price = game->utilities[utilityId].purchasePrice;

    remainingCash = cash - price;

    if (cash < price)
    {
        return 0;
    }

    switch (game->players[playerId].strategy)
    {
    case 0: // aggresive
        if (remainingCash > 0)
        {
            return 1;
        }

        return 0;

    case 1: // conservative
        if (remainingCash >= cash / 2)
        {
            return 1;
        }

        return 0;

    case 2: // risk taker
        return 1;

    case 3: // opertunistic
        if (remainingCash >= price)
        {
            return 1;
        }

        return 0;
    }

    return 0;
}

int shouldBidProperty(GameplayState *game, int playerId, int propertyId, int currentBid)
{
    int nextBid;
    int marketValue;
    int maximumBid;

    nextBid = currentBid + 250;

    marketValue = game->properties[propertyId].currentMarketValue;

    /* if bankrupt cant particiapate for bid*/
    if (game->players[playerId].isbankrupt == 1)
    {
        return 0;
    }

    /*check have cash for bid*/
    if (game->players[playerId].cash < nextBid)
    {
        return 0;
    }

    switch (game->players[playerId].strategy)
    {
    case 0:                                      // aggressive
        maximumBid = (int)(marketValue * 1.20f); // bids up to 120% of market value

        if (nextBid <= maximumBid)
        {
            return 1;
        }

        return 0;

    case 1:                        // conservative
        if (nextBid < marketValue) // only bids below market value
        {
            return 1;
        }

        return 0;

    case 2: // risk taker
        return 1;

    case 3: // opertunistic
        /*
                   Opportunistic Trader prefers
                   discounted auction purchases.

                   For now, treat a bid below market
                   value as a discounted purchase.
               */
        if (nextBid < marketValue)
        {
            return 1;
        }

        return 0;
    }

    return 0;
}