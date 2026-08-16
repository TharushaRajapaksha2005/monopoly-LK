#include <stdio.h>
#include <string.h>
#include "types.h"

void initializePlayers(GameplayState *game){
    game->players[0].playerId = 0;
    strcpy(game->players[0].name, "Aggressive Investor");
    game->players[0].strategy = AGGRESSIVE;
    game->players[0].cash = STARTING_CASH;
    game->players[0].position = 0;
    game->players[0].completedLap = 0;
    game->players[0].isbankrupt = 0;
    game->players[0].inJail = 0;
    game->players[0].jailTurns = 0;
    game->players[0].loanActive = 0;
    game->players[0].loanAmount = 0;
    game->players[0].loanRoundsRemaining = 0;
    game->players[0].loanInterestRate = 0;

    game->players[1].playerId = 1;
    strcpy(game->players[1].name, "Conservative Banker");
    game->players[1].strategy = CONSERVATIVE;
    game->players[1].cash = STARTING_CASH;
    game->players[1].position = 0;
    game->players[1].completedLap = 0;
    game->players[1].isbankrupt = 0;
    game->players[1].inJail = 0;
    game->players[1].jailTurns = 0;
    game->players[1].loanActive = 0;
    game->players[1].loanAmount = 0;
    game->players[1].loanRoundsRemaining = 0;
    game->players[1].loanInterestRate = 0;

    game->players[2].playerId = 2;
    strcpy(game->players[2].name, "Risk Taker");
    game->players[2].strategy = RISK_TAKER;
    game->players[2].cash = STARTING_CASH;
    game->players[2].position = 0;
    game->players[2].completedLap = 0;
    game->players[2].isbankrupt = 0;
    game->players[2].inJail = 0;
    game->players[2].jailTurns = 0;
    game->players[2].loanActive = 0;
    game->players[2].loanAmount = 0;
    game->players[2].loanRoundsRemaining = 0;
    game->players[2].loanInterestRate = 0;

    game->players[3].playerId = 3;
    strcpy(game->players[3].name, "Opportunistic Trader");
    game->players[3].strategy = OPPORTUNISTIC;
    game->players[3].cash = STARTING_CASH;
    game->players[3].position = 0;
    game->players[3].completedLap = 0;
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

    cash = game->players[playerId].cash;
    price = game->properties[propertyId].purchasePrice;
    remainingCash = cash - price;

    if(cash < price){
        return 0;
    }

    switch (game->players[playerId].strategy){
    case AGGRESSIVE:
        if (remainingCash > 0){
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

    if(cash < price){
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

    if(cash < price){
        return 0;
    }

    switch (game->players[playerId].strategy){
    case AGGRESSIVE:
        if(remainingCash > 0){
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

    if (game->players[playerId].isbankrupt == 1){
        return 0;
    }
    if (game->players[playerId].cash < nextBid){
        return 0;
    }

    switch (game->players[playerId].strategy){
    case AGGRESSIVE:
        maximumBid = (int)(marketValue * 1.20f); // bids up to 120% of market value

        if(nextBid <= maximumBid){
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

    if(game->players[playerId].isbankrupt == 1){
        return 0;
    }

    if(game->players[playerId].cash < nextBid){
        return 0;
    }

    switch (game->players[playerId].strategy){
    case AGGRESSIVE:
        maximumBid = (int)(marketValue * 1.20f);

        if(nextBid <= maximumBid){
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
        if(nextBid < marketValue){
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

    if(game->players[playerId].isbankrupt == 1){
        return 0;
    }

    if(game->players[playerId].cash < nextBid){
        return 0;
    }

    switch (game->players[playerId].strategy){
    case AGGRESSIVE:
        maximumBid = (int)(marketValue * 1.20f);

        if(nextBid <= maximumBid){
            return 1;
        }
        return 0;

    case CONSERVATIVE:
        if(nextBid < marketValue){
            return 1;
        }
        return 0;

    case RISK_TAKER:
        return 1;

    case OPPORTUNISTIC:
        if(nextBid < marketValue){
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
        if(game->properties[i].group == group){
            totalInGroup++;
            if(game->properties[i].owner == playerId){
                ownedByPlayer++;
            }
        }
    }
    if(totalInGroup > 0 && ownedByPlayer == totalInGroup){
        return 1;
    }
    return 0;
}
int canBuildHouse(GameplayState *game, int playerId, int propertyId){

    PropertyGroup group;
    int minimumHouses = 4;
    int i;

    group = game->properties[propertyId].group;

    if(game->properties[propertyId].owner != playerId){
        return 0;
    }
    if(game->properties[propertyId].mortgaged == 1){
        return 0;
    }
    if(game->properties[propertyId].hotel == 1){
        return 0;
    }
    if(hasMonopoly(game, playerId, group) == 0){
        return 0;
    }
    if(game->properties[propertyId].houses >= 4){
        return 0;
    }

    for (i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].group == group){
            if(game->properties[i].houses < minimumHouses){
                minimumHouses = game->properties[i].houses;
            }
        }
    }
    if(game->properties[propertyId].houses != minimumHouses){
        return 0;
    }
    return 1;
}
int canBuildHotel(GameplayState *game, int playerId, int propertyId){

    PropertyGroup group;
    int i;
    group = game->properties[propertyId].group;

    if(game->properties[propertyId].owner != playerId){
        return 0;
    }
    if(game->properties[propertyId].mortgaged == 1){
        return 0;
    }
    if(game->properties[propertyId].hotel == 1){
        return 0;
    }
    if(hasMonopoly(game, playerId, group) == 0){
        return 0;
    }

    for (i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].group == group){
            if(game->properties[i].houses < 4 && game->properties[i].hotel == 0){
                return 0;
            }
        }
    }

    if(game->players[playerId].cash < game->properties[propertyId].hotelCost){
        return 0;
    }
    return 1;
}
int shouldBuildHouse(GameplayState *game, int playerId, int propertyId){
    int cost;
    cost = game->properties[propertyId].houseCost;
    if(game->currentGovRegulation == HOUSING_SUBSIDY){
        cost = cost * 70 / 100;
    }
    if(canBuildHouse(game, playerId, propertyId) == 0){
        return 0;
    }
    if(game->players[playerId].cash < cost){
        return 0;
    }

    switch (game->players[playerId].strategy){
    case AGGRESSIVE:
        return 1; // aggressive investor build house asap

    case CONSERVATIVE:
    if(game->players[playerId].cash - cost >= game->players[playerId].cash / 2){
        return 1;
    }
        return 0; // add later

    case RISK_TAKER:
        return 1; // build house asap

    case OPPORTUNISTIC:
    if(game->currentGovRegulation == HOUSING_SUBSIDY){
        return 1;
    }
        return 0;
    }
    return 0;
}
int shouldBuildHotel(GameplayState *game, int playerId, int propertyId){
    int cost;
    cost = game->properties[propertyId].hotelCost;

    if(canBuildHotel(game, playerId, propertyId) == 0){
        return 0;
    }
    if(game->players[playerId].cash < cost){
        return 0;
    }

    switch (game->players[playerId].strategy){
    case AGGRESSIVE:
        return 1;

    case CONSERVATIVE:
    if(game->players[playerId].loanActive == 1){
        return 0;
    }
    if(game->players[playerId].cash - cost >= game->players[playerId].cash / 2){
        return 1;
    }
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
            if(game->properties[i].group == group){
                if(shouldBuildHouse(game, playerId, i) == 1){
                    if(buildHouse(game, playerId, i) == 1){
                        changed = 1;
                    }
                    
                }
            }
        }
        /* build hotels if can*/
        for (i = 0; i < MAX_PROPERTIES; i++){
            if(game->properties[i].group == group){
                if(shouldBuildHotel(game, playerId, i) == 1){
                    if(buildHotel(game, playerId, i) == 1){
                        changed = 1;
                    }
                }
            }
        }
    } while (changed == 1);
}

void makeDevelopmentDecision(GameplayState *game, int playerId){
    int i;
    PropertyGroup group;

    if(game->players[playerId].isbankrupt == 1){
        return;
    }
    for (i = BROWN; i < DARK_BLUE; i++){
        group = (PropertyGroup)i;
        if(hasMonopoly(game, playerId, group) == 1){
            developMonopoly(game, playerId, group);
        }
    }
}
void makeLoanDecision(GameplayState *game, int playerId){
    int maxLoan;
    maxLoan = calculateMaxLoan(game, playerId);

    if(game->players[playerId].loanActive == 1){
        return;
    }
    switch(game->players[playerId].strategy){
        case RISK_TAKER:
        takeLoan(game, playerId, maxLoan);
            break;
        case AGGRESSIVE:
        if(game->players[playerId].cash < 5000){
                takeLoan(game, playerId, maxLoan);
            }
            break;
        case CONSERVATIVE:
            if(game->players[playerId].cash < 500){
                takeLoan(game, playerId, maxLoan);
            }
            break;
        case OPPORTUNISTIC:
            if(game->players[playerId].cash < 3000 && game->players[playerId].loanInterestRate < 10){
                takeLoan(game, playerId, maxLoan);
            }
            break;
    }
}
void makeInsuranceDecision(GameplayState *game, int playerId){
    int i;

    for (i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].owner != playerId){
            continue;
        }
        if(game->properties[i].insuranceType != NO_INSURANCE){
            continue;
        }
        /* Only insure developed properties.*/
        if(game->properties[i].houses == 0 && game->properties[i].hotel == 0){
            continue;
        }
        switch (game->players[playerId].strategy){
            case AGGRESSIVE:
            if(game->properties[i].hotel == 1){
                    buyInsurance(game, playerId, i, COMPREHENSIVE_INSURANCE);
                }
                else{
                    buyInsurance(game, playerId, i, BASIC_INSURANCE);
                }
                return;

            case CONSERVATIVE:
            buyInsurance(game, playerId, i, COMPREHENSIVE_INSURANCE);
                return;

            case RISK_TAKER:
            return;

            case OPPORTUNISTIC:
            return;
        }
    }
    printf("%s decided not to purchase insurance.\n", game->players[playerId].name);
}

void handleBankLanding(GameplayState *game, int playerId){
    int maxLoan;
    maxLoan = calculateMaxLoan(game, playerId);

    printf("%s landed on Bank of Ceylon\n", game->players[playerId].name);

    if(game->players[playerId].loanActive == 0){
        if(maxLoan <= 0){
            printf("No eligible collateral available for a loan\n");
            return;
        }

        switch(game->players[playerId].strategy){
            case AGGRESSIVE:
            if(hasDevelopmentOppertunity(game, playerId) == 1){
                takeLoan(game, playerId, maxLoan);
            }
            else{
                printf("%s decided not to obtain a loan.\n", game->players[playerId].name);
            }
            break;

            case CONSERVATIVE:
            printf("%s decided not to obtain a loan.\n", game->players[playerId].name);
            break;

            case RISK_TAKER:
            takeLoan(game, playerId, maxLoan);
            break;

            case OPPORTUNISTIC:
            printf("%s decided not to obtain a loan.\n", game->players[playerId].name);
            //add later
            break;
        }
        return;       
    }
    else if(game->players[playerId].loanActive == 1){
        switch(game->players[playerId].strategy){
            case AGGRESSIVE:
            if(game->players[playerId].cash > game->players[playerId].loanAmount * 2){
                repayLoan(game, playerId, game->players[playerId].loanAmount);
            }
            else{
                printf("%s keeps the loan active\n", game->players[playerId].name);
            }
            break;

            case CONSERVATIVE:
            if(game->players[playerId].cash >= game->players[playerId].loanAmount){
                repayLoan(game, playerId, game->players[playerId].loanAmount);
            }
            else{
                printf("%s keeps the loan active\n", game->players[playerId].name);
            }
            break;

            case RISK_TAKER:
            maxLoan = calculateMaxLoan(game, playerId);
            if(maxLoan > 0){
                increaseLoan(game, playerId, maxLoan);
            }
            else{
                printf("%s has no additional collateral available\n", game->players[playerId].name);
            }
            break;

            case OPPORTUNISTIC:
            // add later
            printf("%s made no bank transaction.\n", game->players[playerId].name);
            break;
        }
    }
        
}

int countOwnedInGroup(GameplayState *game, int playerId, PropertyGroup group){
    int i;
    int count = 0;

    for (i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].group == group &&
            game->properties[i].owner == playerId){
            count++;
        }
    }
    return count;
}
int countTotalInGroup(GameplayState *game, PropertyGroup group){
    int i;
    int count = 0;

    for (i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].group == group){
            count++;
        }
    }
    return count;
}
void attemptPropertyTrade(GameplayState *game, int playerId){
    int i;
    int totalInGroup;
    int ownedInGroup;
    int sellerId;
    int offer;
    PropertyGroup group;

    for (group = BROWN; group <= DARK_BLUE; group++){
        totalInGroup = countTotalInGroup(game, group);
        ownedInGroup = countOwnedInGroup(game, playerId, group);

        if(ownedInGroup != totalInGroup - 1){
            continue;
        }
        for (i = 0; i < MAX_PROPERTIES; i++){
            if(game->properties[i].group != group){
                continue;
            }
            if(game->properties[i].owner == playerId){
                continue;
            }
            if(game->properties[i].owner == NO_OWNER){
                continue;
            }
            if(game->properties[i].loanLocked == 1){
                continue;
            }
            sellerId = game->properties[i].owner;
            offer = game->properties[i].currentMarketValue * 120 / 100; // I add this rule 

            if(game->players[playerId].cash < offer){
                continue;
            }
            if (offer > game->properties[i].currentMarketValue){
                game->players[playerId].cash -= offer;
                game->players[sellerId].cash += offer;
                game->properties[i].owner = playerId;

                printf("\n=== PROPERTY TRADE ===\n");
                printf("%s purchased %s from %s for LKR %d.\n", game->players[playerId].name, game->properties[i].name, game->players[sellerId].name, offer);
                printf("%s completed a monopoly!\n", game->players[playerId].name);

                return;
            }
        }
    }
}

int raiseMoney(GameplayState *game, int playerId, int amount){
    int i;

    if(game->players[playerId].cash >= amount){
        return 1;
    }
    // mortgage property
    for(i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].owner == playerId && game->properties[i].mortgaged == 0 &&
             game->properties[i].loanLocked == 0 && game->properties[i].houses == 0  &&
              game->properties[i].hotel == 0){
                 mortgageProperty(game, playerId, i);
                 if(game->players[playerId].cash >= amount){
                    return 1;
                 }
           }
    }
    for(i = 0; i < MAX_RAILWAY; i++){
        if(game->railways[i].owner == playerId && game->railways[i].mortgaged == 0 && game->railways[i].loanLocked == 0){
           mortgageRailway(game, playerId, i);
           if(game->players[playerId].cash >= amount){
                return 1;
            }
        }
    }
    for(i = 0; i < MAX_UTILITY; i++){
        if(game->utilities[i].owner == playerId && game->utilities[i].mortgaged == 0 && game->utilities[i].loanLocked == 0){
            mortgageUtility(game, playerId, i);
            if(game->players[playerId].cash >= amount){
                return 1;
            }
        }
    }
    return 0;
}

int hasDevelopmentOppertunity(GameplayState *game, int playerId){
    int i;

    for(i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].owner == playerId){
             if(hasMonopoly(game, playerId, game->properties[i].group) == 1){
                if(game->properties[i].houses < 4 || game->properties[i].hotel == 0){
                    return 1;
                }
             }
        }
    }
    return 0;
}