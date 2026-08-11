#include <string.h>
#include "types.h"

void initializePlayers(GameplayState *game){

    /*Player 0 - Aggressive Inverstor*/
    game->players[0].playerId = 0;
    strcpy(game->players[0].name, "Aggressive Investor");
    game->players[0].strategy = AGGRESSIVE;
    game->players[0].cash = STARTING_CASH;
    game->players[0].position = 0;
    game->players[0].isbankrupt = 0;
    game->players[0].inJail = 0;
    game->players[0].jailTurns = 0;
    game->players[0].loanActive = 0;
    game->players[0].loanAmount = 0;
    game->players[0].loanRoundsRemaining = 0;
    game->players[0].loanInterestRate = 0;

    /* Player 1 - Conservative Banker */
    game->players[1].playerId = 1;
    strcpy(game->players[1].name, "Conservative Banker");
    game->players[1].strategy = CONSERVATIVE;
    game->players[1].cash = STARTING_CASH;
    game->players[1].position = 0;
    game->players[1].isbankrupt = 0;
    game->players[1].inJail = 0;
    game->players[1].jailTurns = 0;
    game->players[1].loanActive = 0;
    game->players[1].loanAmount = 0;
    game->players[1].loanRoundsRemaining = 0;
    game->players[1].loanInterestRate = 0;

    /* Player 2 - Risk Taker */
    game->players[2].playerId = 2;
    strcpy(game->players[2].name, "Risk Taker");
    game->players[2].strategy = RISK_TAKER;
    game->players[2].cash = STARTING_CASH;
    game->players[2].position = 0;
    game->players[2].isbankrupt = 0;
    game->players[2].inJail = 0;
    game->players[2].jailTurns = 0;
    game->players[2].loanActive = 0;
    game->players[2].loanAmount = 0;
    game->players[2].loanRoundsRemaining = 0;
    game->players[2].loanInterestRate = 0;

    /* Player 3 - Opportunistic Trader */
    game->players[3].playerId = 3;
    strcpy(game->players[3].name, "Opportunistic Trader");
    game->players[3].strategy = OPPORTUNISTIC;
    game->players[3].cash = STARTING_CASH;
    game->players[3].position = 0;
    game->players[3].isbankrupt = 0;
    game->players[3].inJail = 0;
    game->players[3].jailTurns = 0;
    game->players[3].loanActive = 0;
    game->players[3].loanAmount = 0;
    game->players[3].loanRoundsRemaining = 0;
    game->players[3].loanInterestRate = 0;
}

int shouldBuyProperty(GameplayState *game, int playerId, int propertyId){

    int cash;
    int price;
    int remainingCash;
    int futureRent;

    cash = game->players[playerId].cash;
    price = game->properties[propertyId].purchasePrice;
    futureRent = game->properties[propertyId].baseRent;
    remainingCash = cash - price;

    if (cash < price){
        return 0;
    }

    switch (game->players[playerId].strategy){
    case AGGRESSIVE:
        if (remainingCash >= futureRent){ /*need money to pay atleast one future rent*/
            return 1;
        }

        return 0;

    case CONSERVATIVE:
        if (remainingCash >= cash / 2){ /*need 50 % of current cash after buying stuff*/
            return 1;
        }

        return 0;

    case RISK_TAKER:
        return 1; /* buy every possible thing*/

    case OPPORTUNISTIC:
        if (remainingCash >= price){
            return 1;
        }

        return 0;
    }

    return 0;
}

int shouldBuyRailway(GameplayState *game, int playerId, int railwayId){

    int cash;
    int price;
    int remainingCash;

    cash = game->players[playerId].cash;
    price = game->railways[railwayId].purchasePrice;
    remainingCash = cash - price;

    if (cash < price){
        return 0;
    }

    switch (game->players[playerId].strategy){
    case AGGRESSIVE:
        if (remainingCash > 0){
            return 1;
        }

        return 0;

    case CONSERVATIVE:
        if (remainingCash >= cash / 2){
            return 1;
        }

        return 0;

    case RISK_TAKER:
        return 1;

    case OPPORTUNISTIC:
        if (remainingCash >= price){
            return 1;
        }

        return 0;
    }

    return 0;
}

int shouldBuyUtility(GameplayState *game, int playerId, int utilityId){

    int cash;
    int price;
    int remainingCash;

    cash = game->players[playerId].cash;
    price = game->utilities[utilityId].purchasePrice;
    remainingCash = cash - price;

    if (cash < price){
        return 0;
    }

    switch (game->players[playerId].strategy){
    case AGGRESSIVE:
        if (remainingCash > 0){
            return 1;
        }

        return 0;

    case CONSERVATIVE:
        if (remainingCash >= cash / 2){
            return 1;
        }

        return 0;

    case RISK_TAKER:
        return 1;

    case OPPORTUNISTIC:
        if (remainingCash >= price){
            return 1;
        }

        return 0;
    }

    return 0;
}

int shouldBidProperty(GameplayState *game, int playerId, int propertyId, int currentBid){

    int nextBid;
    int marketValue;
    int maximumBid;

    nextBid = currentBid + 250;
    marketValue = game->properties[propertyId].currentMarketValue;

    /* if bankrupt cant particiapate for bid*/
    if (game->players[playerId].isbankrupt == 1){
        return 0;
    }

    /*check have cash for bid*/
    if (game->players[playerId].cash < nextBid){
        return 0;
    }

    switch (game->players[playerId].strategy){
    case AGGRESSIVE:
        maximumBid = (int)(marketValue * 1.20f); // bids up to 120% of market value

        if (nextBid <= maximumBid){
            return 1;
        }

        return 0;

    case CONSERVATIVE:
        if (nextBid < marketValue){ // only bids below market value
            return 1;
        }

        return 0;

    case RISK_TAKER:
        return 1;

    case OPPORTUNISTIC:
        /*
                   Opportunistic Trader prefers
                   discounted auction purchases.

                   For now, treat a bid below market
                   value as a discounted purchase.
               */
        if (nextBid < marketValue){
            return 1;
        }

        return 0;
    }

    return 0;
}

int shouldBidRailway(GameplayState *game, int playerId, int railwayId, int currentBid){

    int nextBid;
    int marketValue;
    int maximumBid;

    nextBid = currentBid + 250;
    marketValue = game->railways[railwayId].currentMarketValue;

    if (game->players[playerId].isbankrupt == 1){
        return 0;
    }

    if (game->players[playerId].cash < nextBid){
        return 0;
    }

    switch (game->players[playerId].strategy){
    case AGGRESSIVE:
        maximumBid = (int)(marketValue * 1.20f);

        if (nextBid <= maximumBid){
            return 1;
        }

        return 0;

    case CONSERVATIVE:
        if (nextBid < marketValue){
            return 1;
        }

        return 0;

    case RISK_TAKER:
        return 1;

    case OPPORTUNISTIC:
        if (nextBid < marketValue){
            return 1;
        }

        return 0;
    }

    return 0;
}

int shouldBidUtility(GameplayState *game, int playerId, int utilityId, int currentBid){

    int nextBid;
    int marketValue;
    int maximumBid;

    nextBid = currentBid + 250;
    marketValue = game->utilities[utilityId].currentMarketValue;

    if (game->players[playerId].isbankrupt == 1){
        return 0;
    }

    if (game->players[playerId].cash < nextBid){
        return 0;
    }

    switch (game->players[playerId].strategy){
    case AGGRESSIVE:
        maximumBid = (int)(marketValue * 1.20f);

        if (nextBid <= maximumBid){
            return 1;
        }

        return 0;

    case CONSERVATIVE:
        if (nextBid < marketValue){
            return 1;
        }

        return 0;

    case RISK_TAKER:
        return 1;

    case OPPORTUNISTIC:
        if (nextBid < marketValue){
            return 1;
        }

        return 0;
    }

    return 0;
}

int hasMonopoly(GameplayState *game, int playerId, PropertyGroup group){

    int i;
    int totalInGroup = 0;
    int ownedByPlayer = 0;

    for (i = 0; i < MAX_PROPERTIES; i++){
        if (game->properties[i].group == group){
            totalInGroup++;

            if (game->properties[i].owner == playerId){
                ownedByPlayer++;
            }
        }
    }
    if (totalInGroup > 0 && ownedByPlayer == totalInGroup){
        return 1;
    }
    return 0;
}

int canBuildHouse(GameplayState *game, int playerId, int propertyId){

    PropertyGroup group;
    int minimumHouses;
    int i;

    group = game->properties[propertyId].group;

    /* check whether play owns the property or not */
    if (game->properties[propertyId].owner != playerId){
        return 0;
    }
    if (game->properties[propertyId].mortgaged == 1){
        return 0;
    }
    if (game->properties[propertyId].hotel == 1){
        return 0;
    }
    if (hasMonopoly(game, playerId, group) == 0){
        return 0;
    }
    if (game->properties[propertyId].houses >= 4){
        return 0;
    }
    if (game->players[playerId].cash < game->properties[propertyId].houseCost){
        return 0;
    }

    minimumHouses = 4;

    for (i = 0; i < MAX_PROPERTIES; i++){
        if (game->properties[i].group == group){
            if (game->properties[i].houses < minimumHouses){
                minimumHouses = game->properties[i].houses;
            }
        }
    }

    if (game->properties[propertyId].houses != minimumHouses)
    {
        return 0;
    }
    return 1;
}

int canBuildHotel(GameplayState *game, int playerId, int propertyId){

    PropertyGroup group;
    int i;

    group = game->properties[propertyId].group;

    if (game->properties[propertyId].owner != playerId){
        return 0;
    }
    if (game->properties[propertyId].mortgaged == 1){
        return 0;
    }
    if (game->properties[propertyId].hotel == 1){
        return 0;
    }
    if (hasMonopoly(game, playerId, group) == 0){
        return 0;
    }

    for (i = 0; i < MAX_PROPERTIES; i++){
        if (game->properties[i].group == group){
            if (game->properties[i].houses < 4 && game->properties[i].hotel == 0){
                return 0;
            }
        }
    }

    if (game->players[playerId].cash < game->properties[propertyId].hotelCost)
    {
        return 0;
    }
    return 1;
}

int shouldBuildHouse(GameplayState *game, int plaeyerId, int propertyId){

    if (canBuildHouse(game, plaeyerId, propertyId) == 0){
        return 0;
    }

    switch (game->players[plaeyerId].strategy){
    case AGGRESSIVE:
        return 1; // aggressive investor build house asap

    case CONSERVATIVE:
        return 0; // add later

    case RISK_TAKER:
        return 1; // build house asap

    case OPPORTUNISTIC:
        return 0; // add later
    }
    return 0;
}

int shouldBuildHotel(GameplayState *game, int playerId, int propertId){

    if (canBuildHotel(game, playerId, propertId) == 0){
        return 0;
    }

    switch (game->players[playerId].strategy){
    case AGGRESSIVE:
        return 1;

    case CONSERVATIVE:
        // add later
        return 0;

    case RISK_TAKER:
        return 1;

    case OPPORTUNISTIC:
        // add later
        return 0;
    }
    return 0;
}

void developMonopoly(GameplayState *game, int playerId, PropertyGroup group){

    int i;
    int changed;

    do{
        changed = 0;

        /* 1st build houses */

        for (i = 0; i < MAX_PROPERTIES; i++){
            if (game->properties[i].group == group){
                if (shouldBuildHouse(game, playerId, i) == 1){
                    buildHouse(game, playerId, i);
                    changed = 1;
                }
            }
        }

        /* build hotels if can*/
        for (i = 0; i < MAX_PROPERTIES; i++){
            if (game->properties[i].group == group){
                if (shouldBuildHotel(game, playerId, i) == 1){
                    buildHotel(game, playerId, i);
                    changed = 1;
                }
            }
        }
    } while (changed == 1);
}