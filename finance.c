#include <stdio.h>
#include "types.h"

/* buy property pay rent */

void buyProperty(GameplayState *game, int playerId, int propertyId){
    int price;

    price = game->properties[propertyId].purchasePrice;

    if(game->properties[propertyId].owner != NO_OWNER){
        printf("This property already has an owner \n");
        return;
    }

    if(game->players[playerId].cash < price){
        printf("%s does not have enough cash to buy %s \n", game->players[playerId].name, game->properties[propertyId].name);
        return;
    }

    game->players[playerId].cash -= price;
    game->properties[propertyId].owner = playerId;

    printf("%s purchased %s for LKR %d \n", game->players[playerId].name, game->properties[propertyId].name, price);
    printf("%s now has LKR %d.\n", game->players[playerId].name, game->players[playerId].cash);
}

void payPropertyRent(GameplayState *game, int playerId, int propertyId){
    int ownerId;
    int rent;

    ownerId = game->properties[propertyId].owner;
    rent = game->properties[propertyId].baseRent;

    // no rent for NO OWNER property
    if(ownerId == NO_OWNER){
        printf("This property has no owner.\n");
        return;
    }
    // doesnt pay rent for own property
    if(ownerId == playerId){
        printf("%s owns this property No rent is paid \n", game->players[playerId].name);
        return;
    }
    // no rent fo mortgaged property
    if(game->properties[propertyId].mortgaged == 1){
        printf("%s is mortgaged no rent is collected \n", game->properties[propertyId].name);
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

    /* temp basic payment bankrupcy and debt will add later*/
    if(game->players[playerId].cash < rent){
        printf("%s does not have enough cash to pay the rent.\n", game->players[playerId].name);

        return;
    }
    game->players[playerId].cash -= rent;
    game->players[ownerId].cash += rent;

    printf("%s paid LKR %d rent to %s.\n", game->players[playerId].name, rent, game->players[ownerId].name);
    printf("%s now has LKR %d.\n", game->players[playerId].name, game->players[playerId].cash);
    printf("%s now has LKR %d.\n", game->players[ownerId].name, game->players[ownerId].cash);
}

/* buy railway pay rent count */

void buyRailway(GameplayState *game, int playerId, int railwayId){
    int price;

    price = game->railways[railwayId].purchasePrice;

    if(game->railways[railwayId].owner != NO_OWNER){
        printf("This railway already has an owner \n");
        return;
    }

    if(game->players[playerId].cash < price){
        printf("%s does not have enough cash to buy %s.\n", game->players[playerId].name, game->railways[railwayId].name);
        return;
    }

    game->players[playerId].cash -= price;
    game->railways[railwayId].owner = playerId;

    printf("%s purchased %s for LKR %d.\n", game->players[playerId].name, game->railways[railwayId].name, price);
    printf("%s now has LKR %d.\n", game->players[playerId].name, game->players[playerId].cash);
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
        printf("%s owns this railway No rent is paid \n", game->players[playerId].name);
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

    if(game->players[playerId].cash < rent){
        printf("%s does not have enough cash to pay railway rent.\n", game->players[playerId].name);

        return;
    }

    game->players[playerId].cash -= rent;
    game->players[ownerId].cash += rent;

    printf("%s paid LKR %d railway rent to %s.\n", game->players[playerId].name, rent, game->players[ownerId].name);
}

/* buy utility pay rent count*/

void buyUtility(GameplayState *game, int playerId, int utilityId){
    int price;

    price = game->utilities[utilityId].purchasePrice;

    if(game->utilities[utilityId].owner != NO_OWNER){
        printf("This utility already has an owner.\n");
        return;
    }

    if(game->players[playerId].cash < price){
        printf("%s does not have enough cash to buy %s.\n", game->players[playerId].name, game->utilities[utilityId].name);

        return;
    }

    game->players[playerId].cash -= price;
    game->utilities[utilityId].owner = playerId;

    printf("%s purchased %s for LKR %d.\n", game->players[playerId].name, game->utilities[utilityId].name, price);

    printf("%s now has LKR %d.\n", game->players[playerId].name, game->players[playerId].cash);
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
        printf("%s owns this utility. No rent is paid.\n", game->players[playerId].name);
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
    if(game->players[playerId].cash < rent){
        printf("%s does not have enough cash to pay utility rent \n", game->players[playerId].name);
        return;
    }

    game->players[playerId].cash -= rent;
    game->players[ownerId].cash += rent;

    printf("%s paid LKR %d utility rent to %s.\n", game->players[playerId].name, rent, game->players[ownerId].name);
    printf("Dice total: %d\n", diceValue);
    printf("Utilities owned by owner: %d\n", utilityCount);
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

int calculatePropertyAssetValue(GameplayState *game, int playerId){
    int i;
    int totalValue = 0;

    for (i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].owner == playerId){
            totalValue += game->properties[i].currentMarketValue;
        }
    }

    return totalValue;
}

void payCommunityDevelopmentFund(GameplayState *game, int playerId){
    int propertyAssetValue;
    int taxAmount;

    propertyAssetValue = calculatePropertyAssetValue(game, playerId);
    taxAmount = (int)(propertyAssetValue * game->communityFundRate);

    printf("%s has property assets worth LKR %d \n", game->players[playerId].name, propertyAssetValue);

    printf("Community Development Fund rate: %.0f%%\n", game->communityFundRate * 100);

    if(taxAmount == 0){
        printf("%s owns no properties, so no tax is paid.\n", game->players[playerId].name);
        return;
    }

    if(game->players[playerId].cash < taxAmount){
        printf("%s cannot pay the Community Development Fund tax of LKR %d.\n", game->players[playerId].name, taxAmount);

        // Debt recovert will add later
        return;
    }

    game->players[playerId].cash -= taxAmount;

    printf("%s paid LKR %d to the Community Development Fund.\n", game->players[playerId].name, taxAmount);
    printf("%s now has LKR %d.\n", game->players[playerId].name, game->players[playerId].cash);
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
    currentBid = openingBid - 250;

    /* subtract 250 because shouldBidProperty()
        calculates the next bid as currentBid + 250.

        So the first possible bid becomes openingBid. */

    activeCount = 0;

    printf("\n=== AUCTION STARTED ===\n");
    printf("Property: %s\n", game->properties[propertyId].name);
    printf("Market Value: LKR %d\n", game->properties[propertyId].currentMarketValue);
    printf("Opening Bid: LKR %d\n\n", openingBid);

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

                printf("%s withdraws from the auction \n", game->players[i].name);
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
    printf("Winner Bid: LKR %d\n", currentBid);
    printf("Remaining Cash: LKR %d\n", game->players[highestBidder].cash);

    printf("=======================\n");
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
    currentBid = currentBid - 250;
    activeCount = 0;

    printf("\n=== RAILWAY AUCTION STARTED ===\n");
    printf("Railway: %s\n", game->railways[railwayId].currentMarketValue);
    printf("Market Value: LKR %d\n", game->railways[railwayId].currentMarketValue);
    printf("Opening Bid: LKR %d\n\n", openingBid);

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

                printf("%s withdraws from the auction\n", game->players[i].name);
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
    if(highestBidder == NO_CLOUR){
        printf("\nNobidy purchased %s \n", game->railways[railwayId].name);
        return;
    }

    game->players[highestBidder].cash -= currentBid;
    game->railways[railwayId].owner = highestBidder;

    printf("\n%s wins the railway auction \n", game->players[highestBidder].name);
    printf("Winning Bid: LKR %d \n", currentBid);
    printf("Remaining Cahs: LKR %d\n", game->players[highestBidder].cash);

    printf("==============================\n");
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

    printf("\n=== UTILITY AUCTION STARTED ===\n");
    printf("Utility: %s\n", game->utilities[utilityId].name);

    printf("Market Value: LKR %d\n", game->utilities[utilityId].currentMarketValue);

    printf("Opening Bid: LKR %d\n\n", openingBid);

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

                printf("%s withdraws from the auction\n", game->players[i].name);
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

    printf("\n%s wins the utility auction\n", game->players[highestBidder].name);
    printf("Winning Bid: LKR %d\n", currentBid);
    printf("Remaining Cash: LKR %d\n", game->players[highestBidder].cash);

    printf("==============================\n");
}

void buildHouse(GameplayState *game, int playerId, int propertyId){
    int cost;
    cost = game->properties[propertyId].houseCost;

    if(canBuildHouse(game, playerId, propertyId) == 0){
        printf("%s cannot build a house on %s \n", game->players[playerId].name, game->properties[propertyId].name);
        return;
    }

    game->players[playerId].cash -= cost;
    game->properties[propertyId].houses++;

    printf("%s build one house on %s \n", game->players[playerId].name, game->properties[propertyId].name);
    printf("Build cost: LKR %d\n", cost);
    printf("Houses on property: %d \n", game->properties[propertyId].houses);
    printf("Remaining cash: LKR %d \n", game->players[playerId].cash);
}

void buildHotel(GameplayState *game, int playerId, int propertyId){
    int cost;
    cost = game->properties[propertyId].hotelCost;

    if(canBuildHotel(game, playerId, propertyId) == 0){
        printf("%s cannot build a hotel on %s \n", game->players[playerId].name, game->properties[propertyId].name);
        return;
    }

    game->players[playerId].cash -= cost;
    game->properties[propertyId].houses = 0;
    game->properties[propertyId].hotel = 1;

    printf("%s build a hotel on %s \n", game->players[playerId].name, game->properties[propertyId].name);
    printf("Hotel cost: LKR %d\n", cost);
    printf("Remaining cash: LKR %d \n", game->players[playerId].cash);
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
    printf("Received: LKR %d\n", game->properties[propertyId].mortgageValue);
    printf("Cash: LKR %d\n", game->players[playerId].cash);

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
    printf("Received: LKR %d\n", game->railways[railwayId].mortgageValue);
    printf("Cash: LKR %d\n", game->players[playerId].cash);

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
    printf("Received: LKR %d\n", game->utilities[utilityId].mortgageValue);
    printf("Cash: LKR %d\n", game->players[playerId].cash);

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

    printf("%s loan collateral unlocked.\n", game->players[playerId].name);
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
    maxLoan = calculateMaxLoan(game, playerId);

    // player can only have one active loan
    if(game->players[playerId].loanActive == 1){
        printf("%s already has as active loan\n", game->players[playerId].name);
        return 0;
    }
    if(amount <= 0){
        return 0;
    }
    // cant requset more than max loan amount
    if(amount > maxLoan){
        printf("Loan request rejected\n");
        return 0;
    }
    // 
    if(lockLoanCollateral(game, playerId, amount)  == 0){
        printf("Could not lock enough collateral\n");
        return 0;
    }

    game->players[playerId].loanActive = 1;
    game->players[playerId].loanAmount = amount;
    game->players[playerId].loanRoundsRemaining = 20;

    // store interest rate when the loan is created
    game->players[playerId].loanInterestRate = game->loanInterestRate;
    // player get loan amount
    game->players[playerId].cash += amount; 

    printf("%s obtained a loan of LKR %d.\n", game->players[playerId].name, amount);
    printf("Loan duration: 20 rounds\n");
    printf("Current cash: LKR %d\n", game->players[playerId].cash);

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

    printf("%s loan updated\n", game->players[playerId].name);
    printf("Interest added: LKR %d\n", interest);
    printf("Outstanding loan: LKR %d\n", game->players[playerId].loanAmount);
    printf("Rounds remaining: %d\n", game->players[playerId].loanRoundsRemaining);

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
    printf("Remaining loan: LKR %d\n", game->players[playerId].loanAmount);
    printf("Reaining cash: LKR %d\n", game->players[playerId].cash);

    // if loan completely paid
    if(game->players[playerId].loanAmount == 0){
        game->players[playerId].loanActive = 0;
        game->players[playerId].loanRoundsRemaining = 0;
        game->players[playerId].loanInterestRate = 0;

        unlockLoanCollateral(game, playerId);

        printf("Loan fully repiad\n");
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
    
    printf("%s has defaulted on the loan\n", game->players[playerId].name);

    // foreclose pledged properties, railways and utilities
    for (i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].owner == playerId && game->properties[i].loanLocked ==1){
            printf("%s transferred to the banl\n", game->properties[i].name);

            game->properties[i].owner = NO_OWNER;
            game->properties[i].houses = 0;
            game->properties[i].hotel = 0;
            game->properties[i].loanLocked = 0;
            game->properties[i].InsuranceType = NO_INSURANCE;
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

    printf("Outstanding loan cleared\n");

    if(hasAssets(game, playerId) == 0){
        game->players[playerId].isbankrupt = 1;
        printf("%s has been declared bankrupt\n", game->players[playerId].name);
    }
    else{
        printf("%s still has assets and continue the game\n", game->players[playerId].name);
    }
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