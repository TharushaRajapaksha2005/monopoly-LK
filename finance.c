#include <stdio.h>
#include "types.h"

/* buy property pay rent */

void buyProperty(GameplayState *game, int playerId, int propertyId){
    int price;
    price = game->properties[propertyId].purchasePrice;

    if(game->properties[propertyId].owner != NO_OWNER){
       // printf("This property already has an owner \n");
        return;
    }
    if(game->players[playerId].cash < price){
       // printf("%s does not have enough cash to buy %s \n", game->players[playerId].name, game->properties[propertyId].name);
        return;
    }

    game->players[playerId].cash -= price;
    game->properties[propertyId].owner = playerId;

    printf("%s purchased %s for LKR %d \n", game->players[playerId].name, game->properties[propertyId].name, price);
    printf("Remaining Balance : LKR %d.\n", game->players[playerId].cash);
}
void payPropertyRent(GameplayState *game, int playerId, int propertyId){
    int ownerId;
    int rent;
    int condition;

    condition = getPropertyBuildingCondition(game, propertyId);
    ownerId = game->properties[propertyId].owner;
    rent = game->properties[propertyId].baseRent;

    // no rent for NO OWNER property
    if(ownerId == NO_OWNER){
        return;
    }
    // doesnt pay rent for own property
    if(ownerId == playerId){
        return;
    }
    // no rent fo mortgaged property
    if(game->properties[propertyId].mortgaged == 1){
        printf("%s is mortgaged. No rent collected.\n", game->properties[propertyId].name);
        return;
    }
    // no rent if property is damaged
    if(game->properties[propertyId].damaged == 1){
        printf("%s is damaged. No rent collected.\n", game->properties[propertyId].name);
        return; 
    }
    /* rent calcutaions*/
    if(game->properties[propertyId].hotel == 1){
        rent = rent * 10;
    }
    else if(game->properties[propertyId].houses == 4){
        rent = rent * 7;
    }
    else if(game->properties[propertyId].houses == 3){
        rent = rent * 5;
    }
    else if(game->properties[propertyId].houses == 2){
        rent = rent * 3;
    }
    else if(game->properties[propertyId].houses == 1){
        rent = rent * 2;
    }
    /* change rent according to the condition*/
    if(condition >= 90){
        /* 100% rent.Nothing needs to change.*/
    }
    else if(condition >= 75){
        rent = rent * 90 / 100;
    }
    else if(condition >= 50){
        rent = rent * 75 / 100;
    }
    else if(condition >= 25){
        rent = rent * 50 / 100;
    }
    else
    {
       // printf("%s is closed because of poor building condition.\n", game->properties[propertyId].name);
        return;
    }

    // structural damges 
    if (game->properties[propertyId].structuralDamage == 1){
        rent = rent * 75 / 100;
    }
    

    /* temp basic payment bankrupcy and debt will add later*/
    if(game->players[playerId].cash < rent){
       // printf("%s does not have enough cash to pay the rent.\n", game->players[playerId].name);

        return;
    }
    game->players[playerId].cash -= rent;
    game->players[ownerId].cash += rent;

    printf("%s landed on %s.\n", game->players[playerId].name, game->properties[propertyId].name);
    printf("Rent Paid : LKR %d.\n", rent);
    printf("Owner : %s.\n", game->players[ownerId].name);
}

/* buy railway pay rent count */

void buyRailway(GameplayState *game, int playerId, int railwayId){
    int price;
    price = game->railways[railwayId].purchasePrice;

    if(game->railways[railwayId].owner != NO_OWNER){
       // printf("This railway already has an owner \n");
        return;
    }
    if(game->players[playerId].cash < price){
      //  printf("%s does not have enough cash to buy %s.\n", game->players[playerId].name, game->railways[railwayId].name);
        return;
    }

    game->players[playerId].cash -= price;
    game->railways[railwayId].owner = playerId;

    printf("%s purchased %s for LKR %d.\n", game->players[playerId].name, game->railways[railwayId].name, price);
    printf("Remaining Balance : LKR %d.\n", game->players[playerId].cash);
}
int countOwnedRailways(GameplayState *game, int playerId){
    int i;
    int count;

    count = 0;

    for (i = 0; i < MAX_RAILWAY; i++){
        if(game->railways[i].owner == playerId){
            count++;
        }
    }
    return count;
}
void payRailwayRent(GameplayState *game, int playerId, int railwayId){
    int ownerId;
    int railwayCount;
    int rent;

    ownerId = game->railways[railwayId].owner;

    if(ownerId == NO_OWNER){
        return;
    }
    if(ownerId == playerId){
        return;
    }
    /* Mortgaged railway cant collect rent*/
    if(game->railways[railwayId].mortgaged == 1){
        printf("%s is mortgaged no rent is paid \n", game->railways[railwayId].name);
        return;
    }

    railwayCount = countOwnedRailways(game, ownerId);
    if(railwayCount == 1){
        rent = 250;
    }
    else if(railwayCount == 2){
        rent = 500;
    }
    else if(railwayCount == 3){
        rent = 1000;
    }
    else{
        rent = 2000;
    }

    if (game->currentGovRegulation == RAILWAY_MODERNIZATION){
        rent = rent * 125 / 100;
    }
    if(game->players[playerId].cash < rent){
        //printf("%s does not have enough cash to pay railway rent.\n", game->players[playerId].name);
        return;
    }

    game->players[playerId].cash -= rent;
    game->players[ownerId].cash += rent;

    printf("%s landed on %s.\n", game->players[playerId].name, game->railways[railwayId].name);
    printf("Railway Rent Paid : LKR %d.\n", rent);
    printf("Owner : %s.\n", game->players[ownerId].name);
}

/* buy utility pay rent count*/

void buyUtility(GameplayState *game, int playerId, int utilityId){
    int price;
    price = game->utilities[utilityId].purchasePrice;

    if(game->utilities[utilityId].owner != NO_OWNER){
       // printf("This utility already has an owner.\n");
        return;
    }
    if(game->players[playerId].cash < price){
       // printf("%s does not have enough cash to buy %s.\n", game->players[playerId].name, game->utilities[utilityId].name);
        return;
    }

    game->players[playerId].cash -= price;
    game->utilities[utilityId].owner = playerId;

    printf("%s purchased %s for LKR %d.\n", game->players[playerId].name, game->utilities[utilityId].name, price);
    printf("Remaining Balance : LKR %d.\n", game->players[playerId].cash);
}
int countOwnedUtilities(GameplayState *game, int playerId){
    int i;
    int count;

    count = 0;

    for (i = 0; i < MAX_UTILITY; i++){
        if(game->utilities[i].owner == playerId){
            count++;
        }
    }
    return count;
}
void payUtilityRent(GameplayState *game, int playerId, int utilityId, int diceValue){
    int ownerId;
    int utilityCount;
    int rent;

    ownerId = game->utilities[utilityId].owner;

    if(ownerId == NO_OWNER){
        return;
    }
    if(ownerId == playerId){
        return;
    }
    // cant collect rent because mortgaged
    if(game->utilities[utilityId].mortgaged == 1){
        printf("%s is mortgaged. No rent is paid.\n", game->utilities[utilityId].name);
        return;
    }

    utilityCount = countOwnedUtilities(game, ownerId);
    if(utilityCount == 1){
        rent = diceValue * 4;
    }
    else{
        rent = diceValue * 10;
    }

    if (game->currentGovRegulation == ELECTRICITY_TARIFF_REVISION){
        rent = rent * 120 / 100;
    }
    if(game->players[playerId].cash < rent){
       // printf("%s does not have enough cash to pay utility rent \n", game->players[playerId].name);
        return;
    }

    game->players[playerId].cash -= rent;
    game->players[ownerId].cash += rent;

    printf("%s landed on %s.\n", game->players[playerId].name, game->utilities[utilityId].name);
    printf("Utility Rent Paid : LKR %d.\n", rent);
    printf("Owner : %s.\n", game->players[ownerId].name);  
}

int payJailBail(GameplayState *game, int playerId){
    int bailAmount = 300;

    if(game->players[playerId].cash < bailAmount){
        printf("%s does not have enough cash to pay bail.\n", game->players[playerId].name);
        return 0;
    }

    game->players[playerId].cash -= bailAmount;
    game->players[playerId].inJail = 0;
    game->players[playerId].jailTurns = 0;

    printf("%s paid LKR %d bail and left Jail.\n", game->players[playerId].name, bailAmount);
    printf("%s now has LKR %d.\n", game->players[playerId].name, game->players[playerId].cash);

    return 1; /* return 1 = bail was paid return 0 = baild wasnt paid*/
}

int calculateTotalPropertyValue(GameplayState *game, int playerId){
    int i;
    int total = 0;

    for (i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].owner == playerId){
            total += game->properties[i].currentMarketValue;
        }
    }
    return total;
}

void payCommunityDevelopmentFund(GameplayState *game, int playerId){
    int propertyAssetValue;
    int tax;

    propertyAssetValue = calculateTotalPropertyValue(game, playerId);
    tax = (int)(propertyAssetValue * game->communityFundRate);

    printf("%s landed on Community Development Fund.\n", game->players[playerId].name);

    if(tax == 0){
        return;
    }
    if(game->players[playerId].cash < tax){
        printf("%s cannot pay the Community Development Fund tax of LKR %d.\n", game->players[playerId].name, tax);
        // Debt recovert will add later
        return;
    }

    game->players[playerId].cash -= tax;

    printf("Payment Made : LKR %d.\n", tax);
    printf("Remaining Balance : LKR %d.\n", game->players[playerId].cash);
}

int calculateIncomeTax(GameplayState *game, int playerId){
    int taxableAmount;
    int taxRate;
    int tax;

    taxableAmount = game->players[playerId].cash;
    taxRate = game->incomeTaxRate;
    if(game->currentGovRegulation == INCREASE_PROPERTY_TAX){
        taxRate = taxRate * 150 / 100;
    }
    tax = taxableAmount * taxRate/100;
    return tax;
}
void payIncomeTax(GameplayState *game, int playerId){
    int tax;
    tax = calculateIncomeTax(game, playerId);

    printf("\n=== INCOME TAX ===\n");
    printf("%s landed on Income Tax.\n", game->players[playerId].name);
    printf("Tax Due: LKR %d\n", tax);
    
    if(game->players[playerId].cash >= tax){
        game->players[playerId].cash -= tax;
        printf("Income Tax Paid : LKR %d.\n", tax);
        printf("Remaining Balance: LKR %d\n", game->players[playerId].cash);
        return;
    }
    printf("%s cannot afford Income Tax of LKR %d.\n", game->players[playerId].name, tax);
    // handle Debt
}

void auctionProperty(GameplayState *game, int propertyId){
    int active[MAX_PLAYERS];
    int activeCount;
    int highestBidder;
    int currentBid;
    int nextBid;
    int openingBid;
    int i;

    highestBidder = NO_OWNER;
    openingBid = game->properties[propertyId].currentMarketValue / 2;
    // during market decline openingbid decrease 
    if(game->properties[propertyId].group == game->declineGroup && game->declineRoundsRemaining > 0){
        openingBid = openingBid * 75/100;
    }
    currentBid = openingBid - 250;
    /* subtract 250 because shouldBidProperty()
        calculates the next bid as currentBid + 250.

        So the first possible bid becomes openingBid. */

    activeCount = 0;

    printf("\n=== AUCTION STARTED ===\n");
    printf("Property: \n");
    printf("%s\n", game->properties[propertyId].name);
    printf("Opening Bid: \n");
    printf("LKR %d.\n", openingBid);

    for (i = 0; i < MAX_PLAYERS; i++){
        if(game->players[i].isbankrupt == 0){
            active[i] = 1;
            activeCount++;
        }
        else{
            active[i] = 0;
        }
    }
    // auction starts from here
    while (activeCount > 0){
        for (i = 0; i < MAX_PLAYERS; i++){
            if (active[i] == 0){
                continue;
            }

            if (i == highestBidder){
                continue;
            }

            nextBid = currentBid + 250;

            if (shouldBidProperty(game, i, propertyId, currentBid) == 1){
                currentBid = nextBid;
                highestBidder = i;

                printf("%s bids LKR %d \n", game->players[i].name, currentBid);
            }
            else{
                active[i] = 0;
                activeCount--;

                printf("%s withdraws \n", game->players[i].name);
            }
        }

        if (highestBidder != NO_OWNER){
            activeCount = 0;

            for (i = 0; i < MAX_PLAYERS; i++){
                if (active[i] == 1){
                    activeCount++;
                }
            }
            if (activeCount == 1){
                break;
            }
        }
        else{
            /* nobody made even the opening bid*/
            if (activeCount == 0){
                break;
            }
        }
    }
    /* no one wanted the property*/
    if (highestBidder == NO_OWNER){
        printf("\nNobody purchased %s \n", game->properties[propertyId].name);
        printf("Property remain owned by the Bank \n");

        return;
    }

    game->players[highestBidder].cash -= currentBid;
    game->properties[propertyId].owner = highestBidder;

    printf("\n %s wins the auction \n", game->players[highestBidder].name);
}
void auctionRailway(GameplayState *game, int railwayId){
    int active[MAX_PLAYERS];
    int activeCount;
    int highestBidder;
    int currentBid;
    int nextBid;
    int openingBid;
    int i;

    openingBid = game->railways[railwayId].currentMarketValue / 2;
    highestBidder = NO_OWNER;
    currentBid = openingBid - 250;
    activeCount = 0;

    printf("\n=== AUCTION STARTED ===\n");
    printf("Railway: \n");
    printf("%s\n", game->railways[railwayId].name);
    printf("Opening Bid: LKR \n");
    printf("LKR %d.\n", openingBid);

    for (i = 0; i < MAX_PLAYERS; i++){
        if(game->players[i].isbankrupt == 0){
            active[i] = 1;
            activeCount++;
        }
        else{
            active[i] = 0;
        }
    }

    while (activeCount > 0){
        for (i = 0; i < MAX_PLAYERS; i++){
            if(active[i] == 0){
                continue;
            }

            nextBid = currentBid + 250;

            if(shouldBidRailway(game, i, railwayId, currentBid) == 1){
                currentBid = nextBid;
                highestBidder = i;
                printf("%s bids LKR %d\n", game->players[i].name, currentBid);
            }
            else{
                active[i] = 0;
                activeCount--;

                printf("%s withdraws \n", game->players[i].name);
            }
        }
        if (highestBidder != NO_OWNER){
            activeCount = 0;

            for (i = 0; i < MAX_PLAYERS; i++){
                if(active[i] == 1){
                    activeCount++;
                }
            }
            if(activeCount == 1){
                break;
            }
        }
        else if (activeCount == 0){
            break;
        }
    }
    if(highestBidder == NO_GROUP){
        printf("\nNobidy purchased %s \n", game->railways[railwayId].name);
        return;
    }

    game->players[highestBidder].cash -= currentBid;
    game->railways[railwayId].owner = highestBidder;

    printf("%s wins the auction.\n", game->players[highestBidder].name);
}
void auctionUtility(GameplayState *game, int utilityId){
    int active[MAX_PLAYERS];
    int activeCount;
    int highestBidder;
    int currentBid;
    int nextBid;
    int openingBid;
    int i;

    openingBid = game->utilities[utilityId].currentMarketValue / 2;

    highestBidder = NO_OWNER;
    currentBid = openingBid - 250;
    activeCount = 0;

    printf("\n=== AUCTION STARTED ===\n");
    printf("Utility: \n");
    printf("%s\n", game->utilities[utilityId].name);
    printf("Opening Bid :\n");
    printf("LKR %d\n", openingBid);

    for (i = 0; i < MAX_PLAYERS; i++){
        if(game->players[i].isbankrupt == 0){
            active[i] = 1;
            activeCount++;
        }
        else{
            active[i] = 0;
        }
    }

    while (activeCount > 0){
        for (i = 0; i < MAX_PLAYERS; i++){
            if(active[i] == 0){
                continue;
            }
            if(i == highestBidder){
                continue;
            }

            nextBid = currentBid + 250;

            if(shouldBidUtility(game, i, utilityId, currentBid) == 1){
                currentBid = nextBid;
                highestBidder = i;
                printf("%s bids LKR %d\n", game->players[i].name, currentBid);
            }
            else{
                active[i] = 0;
                activeCount--;
                printf("%s withdraws \n", game->players[i].name);
            }
        }

        if(highestBidder != NO_OWNER){
            activeCount = 0;

            for (i = 0; i < MAX_PLAYERS; i++){
                if(active[i] == 1){
                    activeCount++;
                }
            }
            if(activeCount == 1){
                break;
            }
        }
        else if(activeCount == 0){
            break;
        }
    }

    if(highestBidder == NO_OWNER){
        printf("\nNobody purchased %s.\n", game->utilities[utilityId].name);
        return;
    }

    game->players[highestBidder].cash -= currentBid;
    game->utilities[utilityId].owner = highestBidder;

    printf("\n%s wins the auction\n", game->players[highestBidder].name);
}

void buildHouse(GameplayState *game, int playerId, int propertyId){
    int cost;
    int newHouse;
    cost = game->properties[propertyId].houseCost;
    newHouse = game->properties[propertyId].houses;

    if(game->currentGovRegulation == HOUSING_SUBSIDY){
        cost = cost * 70/100;
    }
    if(canBuildHouse(game, playerId, propertyId) == 0){
        return;
    }

    game->players[playerId].cash -= cost;
    game->properties[propertyId].houseCondition[newHouse] = 100;
    game->properties[propertyId].houses++;

    printf("%s constructed one house on %s.\n", game->players[playerId].name, game->properties[propertyId].name);
    printf("Construction Cost : LKR %d.\n", cost);
}
void buildHotel(GameplayState *game, int playerId, int propertyId){
    int cost;
    int i;
    cost = game->properties[propertyId].hotelCost;

    if(canBuildHotel(game, playerId, propertyId) == 0){
        return;
    }

    game->players[playerId].cash -= cost;
    for (i = 0; i < 4; i++){
    game->properties[propertyId].houseCondition[i] = 0;
    }
    game->properties[propertyId].houses = 0;
    game->properties[propertyId].hotel = 1;
    game->properties[propertyId].hotelCondition = 100;

    printf("%s upgraded %s to a Hotel.\n", game->players[playerId].name, game->properties[propertyId].name);
    printf("Construction Cost : LKR %d.\n", cost);
}

int mortgageProperty(GameplayState *game, int playerId, int propertyId){

    if(game->properties[propertyId].owner != playerId){
        return 0;
    }
    if(game->properties[propertyId].mortgaged == 1){
        return 0;
    }
    if(game->properties[propertyId].houses > 0 || game->properties[propertyId].hotel == 1){
        return 0;
    }

    game->properties[propertyId].mortgaged = 1;
    game->players[playerId].cash += game->properties[propertyId].mortgageValue;

    printf("%s mortgaged %s \n", game->players[playerId].name, game->properties[propertyId].name);
    printf("Mortgage Value : LKR %d\n", game->properties[propertyId].mortgageValue);
    printf("Current Balance : LKR %d\n", game->players[playerId].cash);

    return 1;
}
int mortgageRailway(GameplayState *game, int playerId, int railwayId){

    if(game->railways[railwayId].owner != playerId){
        return 0;
    }
    if(game->railways[railwayId].mortgaged == 1){
        return 0;
    }

    game->railways[railwayId].mortgaged = 1;
    game->players[playerId].cash += game->railways[railwayId].mortgageValue;

    printf("%s mortgaged %s.\n", game->players[playerId].name, game->railways[railwayId].name);
    printf("Mortgage Value : LKR %d\n", game->railways[railwayId].mortgageValue);
    printf("Current Balance : LKR %d\n", game->players[playerId].cash);

    return 1;
}
int mortgageUtility(GameplayState *game, int playerId, int utilityId){

    if(game->utilities[utilityId].owner != playerId){
        return 0;
    }
    if(game->utilities[utilityId].mortgaged == 1){
        return 0;
    }

    game->utilities[utilityId].mortgaged = 1;
    game->players[playerId].cash += game->utilities[utilityId].mortgageValue;

    printf("%s mortgaged %s.\n", game->players[playerId].name, game->utilities[utilityId].name);
    printf("Mortgage Value : LKR %d\n", game->utilities[utilityId].mortgageValue);
    printf("Current Balance : LKR %d\n", game->players[playerId].cash);

    return 1;
}

int calculateCollateralValue(GameplayState *game, int playerId){

    int i;
    int totalValue = 0;

    // properties
    for (i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].owner == playerId && game->properties[i].mortgaged == 0){
            totalValue += game->properties[i].mortgageValue;
        }
    }

    // railways
    for (i = 0; i < MAX_RAILWAY; i++){
        if(game->railways[i].owner == playerId && game->railways[i].mortgaged == 0){
            totalValue += game->railways[i].mortgageValue;
        }
    }

    // utilities
    for (i = 0; i < MAX_UTILITY; i++){
        if(game->utilities[i].owner == playerId && game->utilities[i].mortgaged == 0){
            totalValue += game->utilities[i].mortgageValue;
        }
    }

    return totalValue;
}

int lockLoanCollateral(GameplayState *game, int playerId, int loanAmount){
    int i;
    int requiredCollateral;
    int lockedValue = 0;

    requiredCollateral = loanAmount * 100/75;

    for (i = 0; i < MAX_PROPERTIES; i++){
        if(lockedValue >= requiredCollateral){
            break;
        }
        if(game->properties[i].owner == playerId && game->properties[i].mortgaged == 0 && game->properties[i].loanLocked == 0 ){
            game->properties[i].loanLocked = 1;
            lockedValue = game->properties[i].mortgageValue;
        }
    }
    for (i = 0; i < MAX_RAILWAY; i++){
        if(lockedValue >= requiredCollateral){
            break;
        }

        if(game->railways[i].owner == playerId && game->railways[i].mortgaged == 0 && game->railways[i].loanLocked == 0){
            game->railways[i].loanLocked = 1;
            lockedValue += game->railways[i].mortgageValue;
        }
    }
    for (i = 0; i < MAX_UTILITY; i++){
        if(lockedValue >= requiredCollateral){
            break;
        }

        if(game->utilities[i].owner == playerId && game->utilities[i].mortgaged == 0 && game->utilities[i].loanLocked == 0){
            game->utilities[i].loanLocked = 1;
            lockedValue += game->utilities[i].mortgageValue;
        }
    }
    if(lockedValue >= requiredCollateral)
    {
        return 1;
    }
    return 0;
}
void unlockLoanCollateral(GameplayState *game, int playerId){
    int i;

    for (i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].owner == playerId && game->properties[i].loanLocked == 1){
            game->properties[i].loanLocked = 0;
        }
    }
    for (i = 0; i < MAX_RAILWAY; i++){
        if(game->railways[i].owner == playerId && game->railways[i].loanLocked == 1){
            game->railways[i].loanLocked = 0;
        }
    }
    for (i = 0; i < MAX_UTILITY; i++){
        if(game->utilities[i].owner == playerId && game->utilities[i].loanLocked == 1){
            game->utilities[i].loanLocked = 0;
        }
    }
    //printf("%s loan collateral unlocked.\n", game->players[playerId].name);
}

int calculateMaxLoan(GameplayState *game, int playerId){
    int collateralValue;
    int maxLoan;

    collateralValue = calculateCollateralValue(game, playerId);
    maxLoan = collateralValue * 75/100;

    return maxLoan;
}

int takeLoan(GameplayState *game, int playerId, int amount){
    //amount means the loan amount that player want to get 
    int maxLoan;
    int interestRate;
    maxLoan = calculateMaxLoan(game, playerId);
    interestRate = game->loanInterestRate;

    if (game->currentGovRegulation == REDUCE_LOAN_INTEREST){
        interestRate -= 2;
        if (interestRate < 0){
               interestRate = 0;
        }
    }
    // player can only have one active loan
    if(game->players[playerId].loanActive == 1){
        return 0;
    }
    if(amount <= 0){
        return 0;
    }
    // cant requset more than max loan amount
    if(amount > maxLoan){
        return 0;
    }
    // 
    if(lockLoanCollateral(game, playerId, amount)  == 0){
        return 0;
    }

    game->players[playerId].loanActive = 1;
    game->players[playerId].loanAmount = amount;
    game->players[playerId].loanRoundsRemaining = 20;

    // store interest rate when the loan is created
    game->players[playerId].loanInterestRate = interestRate;
    // player get loan amount
    game->players[playerId].cash += amount; 

    printf("%s obtained a secured loan\n", game->players[playerId].name);
    printf("Loan Amount : LKR %d.\n", amount);
    printf("Interest Rate : %d%%\n", game->players[playerId].loanInterestRate);
    printf("Duration: %d\n",game->players[playerId].loanRoundsRemaining);

    return 1;
}

void updateLoanAfterRound(GameplayState *game, int playerId){
    
    int interest;
    interest = game->players[playerId].loanAmount * game->players[playerId].loanInterestRate / 100;

    if(game->players[playerId].loanActive == 0){
        return;
    }

    game->players[playerId].loanAmount += interest;
    game->players[playerId].loanRoundsRemaining--;

   /* printf("%s loan updated\n", game->players[playerId].name);
    printf("Interest added: LKR %d\n", interest);
    printf("Outstanding loan: LKR %d\n", game->players[playerId].loanAmount);
    printf("Rounds remaining: %d\n", game->players[playerId].loanRoundsRemaining);
*/
    if (game->players[playerId].loanRoundsRemaining == 0){
        handleLoanDefault(game, playerId);
    }
}

int repayLoan(GameplayState *game, int playerId, int amount){
    if(game->players[playerId].loanActive == 0){
        printf("This player has no active loan\n");
        return 0;
    }
    if(amount <= 0){
        return 0;
    }
    if(game->players[playerId].cash < amount){
        printf("This player does not have enough cash\n");
        return 0;
    }
    // if player tires to pay more than the loan
    if(amount > game->players[playerId].loanAmount){
        amount = game->players[playerId].loanAmount;
    }

    game->players[playerId].cash -= amount;
    game->players[playerId].loanAmount -= amount;

    printf("%s repaid LKR %d\n", game->players[playerId].name, amount);
    printf("Outstanding Balance :\n");
    printf("LKR %d\n", game->players[playerId].loanAmount);

    // if loan completely paid
    if(game->players[playerId].loanAmount == 0){
        game->players[playerId].loanActive = 0;
        game->players[playerId].loanRoundsRemaining = 0;
        game->players[playerId].loanInterestRate = 0;

        unlockLoanCollateral(game, playerId);

        printf("%s fully repaid the loan\n", game->players[playerId].name);
    }
    return 1;
}

/* int extendLoan(GameplayState *game, int playerId, int extraRounds){
    
    if(game->players[playerId].loanActive == 0){
        return 0;
    }
    if(extraRounds <= 0){
        return 0;
    }

    game->players[playerId].loanRoundsRemaining += extraRounds;

    printf("%s extended the loan period by %d rounds.\n", game->players[playerId].name, extraRounds);
    printf("New rounds remaining: %d\n", game->players[playerId].loanRoundsRemaining);

    return 1;
} */

int increaseLoan(GameplayState *game, int playerId, int extraAmount){
    
    int maxLoan;
    int newLoanAmount;

    maxLoan = calculateMaxLoan(game, playerId);
    newLoanAmount = game->players[playerId].loanAmount + extraAmount;

    if(game->players[playerId].loanActive == 0){
        return 0;
    }
    if (extraAmount <= 0){
        return 0;
    }
    if(newLoanAmount > maxLoan){
        printf("Loan increase rejected.\n");
        printf("Maximum allowed: LKR %d\n", maxLoan);
        return 0;
    }

    game->players[playerId].loanAmount += extraAmount;
    game->players[playerId].cash += extraAmount;

    printf("%s increased the loan by LKR %d.\n", game->players[playerId].name, extraAmount);
    printf("New loan amount: LKR %d\n", game->players[playerId].loanAmount);
    printf("Current cash: LKR %d\n", game->players[playerId].cash);

    return 1;

}

void handleLoanDefault(GameplayState *game, int playerId){
    int i;

    if(game->players[playerId].loanActive == 0){
        return;
    }
    if(game->players[playerId].loanRoundsRemaining > 0){
        return;
    }
    
    printf("%s has defaulted\n", game->players[playerId].name);

    // foreclose pledged properties, railways and utilities
    for (i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].owner == playerId && game->properties[i].loanLocked ==1){
            printf("%s transferred to the banl\n", game->properties[i].name);

            game->properties[i].owner = NO_OWNER;
            game->properties[i].houses = 0;
            game->properties[i].hotel = 0;
            game->properties[i].loanLocked = 0;
            game->properties[i].insuranceType = NO_INSURANCE;
        }
    }
     for (i = 0; i < MAX_RAILWAY; i++){
        if(game->railways[i].owner == playerId && game->railways[i].loanLocked == 1){
            printf("%s transferred to the Bank.\n", game->railways[i].name);

            game->railways[i].owner = NO_OWNER;
            game->railways[i].loanLocked = 0;

        }
    }
     for (i = 0; i < MAX_UTILITY; i++){
        if(game->utilities[i].owner == playerId && game->utilities[i].loanLocked == 1){
            printf("%s transferred to the Bank.\n", game->utilities[i].name);

            game->utilities[i].owner = NO_OWNER;
            game->utilities[i].loanLocked = 0;
        }
    }

    game->players[playerId].loanActive = 0;
    game->players[playerId].loanAmount = 0;
    game->players[playerId].loanRoundsRemaining = 0;
    game->players[playerId].loanInterestRate = 0;

    printf("Collateral has been foreclosed.\n");
    printf("Outstanding loan cleared\n");

    if(hasAssets(game, playerId) == 0){
        declareBankrupt(game, playerId);   
    }
    else{
       // printf("%s still has assets and continue the game\n", game->players[playerId].name);
    }
}

void declareBankrupt(GameplayState *game, int playerId){
    int i;

    printf("%s has been declared bankrupt.\n", game->players[playerId].name);

    game->players[playerId].isbankrupt = 1;
    for (i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].owner == playerId){
            game->properties[i].houses = 0;
            game->properties[i].hotel = 0;
            game->properties[i].insuranceType = NO_INSURANCE;
            game->properties[i].insuranceRoundsRemaining = 0;
            game->properties[i].owner = NO_OWNER;
            game->properties[i].mortgaged = 0;
            game->properties[i].loanLocked = 0;
        }
    }
    for (i = 0; i < MAX_RAILWAY; i++){
        if(game->railways[i].owner == playerId){
            game->railways[i].owner = NO_OWNER;
            game->railways[i].mortgaged = 0;
            game->railways[i].loanLocked = 0;
        }
    }
    for (i = 0; i < MAX_UTILITY; i++){
        if(game->utilities[i].owner == playerId){
            game->utilities[i].owner = NO_OWNER;
            game->utilities[i].mortgaged = 0;
            game->utilities[i].loanLocked = 0;
        }
    }
    game->players[playerId].loanActive = 0;
    game->players[playerId].loanAmount = 0;
    game->players[playerId].loanRoundsRemaining = 0;
    game->players[playerId].cash = 0;

    printf("Remaining assets transferred to the Bank.\n");
}

int hasAssets(GameplayState *game, int playerId){
    int i;

    for (i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].owner == playerId){
            return 1;
        }
    }
    for (i = 0; i < MAX_RAILWAY; i++){
        if(game->railways[i].owner == playerId){
            return 1;
        }
    }
    for (i = 0; i <MAX_UTILITY; i++){
        if(game->utilities[i].owner == playerId){
            return 1;
        }
    }
    return 0;
}

int buyInsurance(GameplayState *game, int playerId, int propertyId, InsuranceType type){
    int premium = 0;

    if(game->properties[propertyId].owner != playerId){
        return 0;
    }
    if(type ==BASIC_INSURANCE){
        printf("Basic Insurance purchased.\n");
        premium = game->properties[propertyId].currentMarketValue * 5/100;
        if(game->currentGovRegulation == INSURANCE_REGULATION){
            premium = premium * 85 / 100;
        }
    }
    else if(type == COMPREHENSIVE_INSURANCE){
        printf("Comprehensive Insurance purchased.\n");
        premium = game->properties[propertyId].currentMarketValue * 10/100;
        if(game->currentGovRegulation == INSURANCE_REGULATION){
            premium = premium * 85 / 100;
        }
    }
     else if (type == BUSINESS_INTERRUPTION_INSURANCE){
        printf("Business Interruption Insurance purchased.\n");
        /* Business Interruption Insurance only applies to properties with hotels. */
        if(game->properties[propertyId].hotel == 0){
            return 0;
        } 
        premium = game->properties[propertyId].currentMarketValue * 15 / 100;
        if(game->currentGovRegulation == INSURANCE_REGULATION){
            premium = premium * 85 / 100;
        }
    }
    else{
        return 0;
    }
    if(game->players[playerId].cash < premium){
        return 0;
    }

    game->players[playerId].cash -= premium;
    game->properties[propertyId].insuranceType = type;
    game->properties[propertyId].insuranceRoundsRemaining = 20;

    printf("Property : %s\n", game->properties[propertyId].name);
    printf("Premium: LKR %d\n", premium);

    return 1;
}
void updateInsuranceAfterRound(GameplayState *game){
    int i;

    for (i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].insuranceType != NO_INSURANCE){
            game->properties[i].insuranceRoundsRemaining--;
            /* Reminder 3 rounds before expiry. */
            if (game->properties[i].insuranceRoundsRemaining == 3){
                printf("Insurance on %s expires in 3 rounds.\n", game->properties[i].name);
            }
            /* Policy expired. */
            if(game->properties[i].insuranceRoundsRemaining <= 0){
                printf("Insurance on %s has expired.\n", game->properties[i].name);
                game->properties[i].insuranceType = NO_INSURANCE;
                game->properties[i].insuranceRoundsRemaining = 0;
            }
        }
    }
}

int repairProperty(GameplayState *game, int propertyId){
    int owner;
    int repairCost = 1000;
    owner = game->properties[propertyId].owner;

    if(game->properties[propertyId].damaged == 0){
        return 0;
    }
    if(owner == NO_OWNER){
        return 0;
    }
    if(game->players[owner].cash < repairCost){
        return 0;
    }

    game->players[owner].cash -= repairCost;
    game->properties[propertyId].damaged = 0;
    printf("%s renovated %s.\n", game->players[owner].name, game->properties[propertyId].name);
    printf("Renovation Cost : LKR %d.\n", repairCost);
    printf("Property age reset to 0.\n");
    printf("Depreciation restored.\n");

    return 1;
}
void maintainProperty(GameplayState *game, int playerId, int propertyId){
    int i;
    int maintenanceCost;

    if(game->properties[propertyId].owner != playerId){
        return;
    }
    for(i = 0; i < game->properties[propertyId].houses; i++){
        if(game->properties[propertyId].houseCondition[i] < 100){
            maintenanceCost = game->properties[propertyId].houseCost * 5 / 100;
            if (game->properties[propertyId].structuralDamage == 1){
                maintenanceCost = maintenanceCost * 150 / 100;
            }
            if(game->players[playerId].cash >= maintenanceCost){
                game->players[playerId].cash -= maintenanceCost;
                game->properties[propertyId].houseCondition[i] = 100;

                printf("%s maintained House on %s.\n", game->players[playerId].name, game->properties[propertyId].name);
                printf("Maintenance Cost : LKR %d.\n", maintenanceCost);
            }
        }
    }
    if(game->properties[propertyId].hotel == 1 && game->properties[propertyId].hotelCondition < 100){
        maintenanceCost = game->properties[propertyId].hotelCost * 8 / 100;
        if (game->properties[propertyId].structuralDamage == 1){
            maintenanceCost = maintenanceCost * 150 / 100;
        }
        if(game->players[playerId].cash >= maintenanceCost){
            game->players[playerId].cash -= maintenanceCost;
            game->properties[propertyId].hotelCondition = 100;

            printf("%s maintained the hotel on %s for LKR %d.\n", game->players[playerId].name, game->properties[propertyId].name, maintenanceCost);
        }
    }
    int allMaintained = 1;

    for(i = 0; i < game->properties[propertyId].houses; i++){
        if(game->properties[propertyId].houseCondition[i] < 100){
            allMaintained = 0;
        }
    }
    if (game->properties[propertyId].hotel == 1 && game->properties[propertyId].hotelCondition < 100){
            allMaintained = 0;
    }
    if(allMaintained == 1){
            game->properties[propertyId].maintenanceIgnoredRounds = 0;
    }
}
void performMaintenance(GameplayState *game, int playerId){
    int i;

    for(i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].owner == playerId){
            maintainProperty(game, playerId, i);
        }
    }
}
void updateMaintenanceNeglect(GameplayState *game){
    int i,j;
    int needMaintenance;

    for (i = 0; i < MAX_PROPERTIES; i++){
         if (game->properties[i].houses == 0 && game->properties[i].hotel == 0){
            continue;
        }
        needMaintenance = 0;

       for (j = 0; j < game->properties[i].houses; j++){
            if(game->properties[i].houseCondition[j] < 100){
                needMaintenance = 1;
            }
        }
        if(game->properties[i].hotel == 1 && game->properties[i].hotelCondition < 100){
            needMaintenance = 1;
        }

        if(needMaintenance == 1){
            game->properties[i].maintenanceIgnoredRounds++;
        }
        else{
            game->properties[i].maintenanceIgnoredRounds = 0;
        }

        if (game->properties[i].maintenanceIgnoredRounds > 20 && game->properties[i].structuralDamage == 0){
            game->properties[i].structuralDamage = 1;
            game->properties[i].valueBeforeStructuralDamage = game->properties[i].currentMarketValue;
            game->properties[i].currentMarketValue = game->properties[i].currentMarketValue * 85 / 100;

            printf("%s has suffered structural damage due to neglected maintenance.\n", game->properties[i].name);
            printf("Property value reduced to 15%%\n");
            printf("Maximum Rent reduced by 25%%.\n");
        }
    }
}

int repaireStructuralDamage(GameplayState *game, int playerId, int propertyId){
    int i;
    int replacementValue = 0;
    int renovationCost;

    renovationCost = replacementValue * 25 / 100;

    if(game->properties[propertyId].owner != playerId){
        return 0;
    }
    if(game->properties[propertyId].structuralDamage == 0){
        return 0;
    }
// ca;culate replacement values
    if(game->properties[propertyId].hotel == 1){
        replacementValue = game->properties[propertyId].hotelCost;
    }
    else{
        replacementValue = game->properties[propertyId].houses * game->properties[propertyId].houseCost;
    }

    if(game->players[playerId].cash < renovationCost){
        return 0;
    }
// restore values
    game->properties[propertyId].currentMarketValue = game->properties[propertyId].valueBeforeStructuralDamage;
    for (i = 0; i < game->properties[propertyId].houses; i++){
        game->properties[propertyId].houseCondition[i] = 100;
    }
    if(game->properties[propertyId].hotel == 1){
        game->properties[propertyId].hotelCondition = 100;
    }
    game->properties[propertyId].structuralDamage = 0;
    game->properties[propertyId].maintenanceIgnoredRounds = 0;
    game->properties[propertyId].valueBeforeStructuralDamage = 0;

    printf("%s renovated structural damage on %s for \n", game->players[playerId].name, game->properties[propertyId].name);
    printf("Renovation Cost : LKR %d.\n", renovationCost);
    printf("Property condition restored.\n");

    return 1;
}
int repaireProperty(GameplayState *game, int playerId, int propertyId){
    int renovationCost;
    renovationCost = game->properties[propertyId].currentMarketValue * 10 / 100;

    if(game->properties[propertyId].owner != playerId){
        return 0;
    }
    if(game->properties[propertyId].depreciationPercent == 0){
        return 0;
    }
    if(game->players[playerId].cash < renovationCost){
        printf("%s cannot afford to renovate %s.\n", game->players[playerId].name, game->properties[propertyId].name);
        return 0;
    }
    game->players[playerId].cash -= renovationCost;
    //resotre values
     if(game->properties[propertyId].depreciationPercent > 0){
        game->properties[propertyId].currentMarketValue = game->properties[propertyId].currentMarketValue * 100 / (100 - game->properties[propertyId].depreciationPercent);
    }
    game->properties[propertyId].depreciationPercent = 0;
    game->properties[propertyId].age = 0;

    printf("%s renovated property on %s.\n", game->players[playerId].name, game->properties[propertyId].name);
    printf("Renovation Cost : LKR %d.\n", renovationCost);
    printf("Property condition restored.\n");

    return 1;
}
  