#include <stdio.h>
#include <stdlib.h>
#include "types.h"

int rollDice(){

    int dice1 = rand() % 6 + 1;
    int dice2 = rand() % 6 + 1;

    return dice1 + dice2;
}

/* sort only part of the arrays from high to low*/

void sortTurnOrder(int turnOrder[], int diceValue[], int start, int end){

    int i, j, temp;

    for (i = start; i < end; i++){
        for (j = i + 1; j <= end; j++){
            if (diceValue[j] > diceValue[i]){
                temp = diceValue[i]; // swap dice valuse
                diceValue[i] = diceValue[j];
                diceValue[j] = temp;

                temp = turnOrder[i]; // swap the player index
                turnOrder[i] = turnOrder[j];
                turnOrder[j] = temp;
            }
        }
    }
}

void resolveTiedGroup(GameplayState *game, int start, int end){

    int rerollValuses[MAX_PLAYERS];
    int i;
    int groupStart;
    int groupEnd;

    printf("\nTied Players reroll:\n");

    for (i = start; i <= end; i++){
        rerollValuses[i] = rollDice();
        printf("%s rolled %d\n", game->players[game->turnOrder[i]].name, rerollValuses[i]);
    }

    sortTurnOrder(game->turnOrder, rerollValuses, start, end);

    groupStart = start;

    while (groupStart <= end){
        groupEnd = groupStart;

        while (groupEnd < end && rerollValuses[groupEnd] == rerollValuses[groupEnd + 1]){
            groupEnd++;
        }
        if (groupEnd > groupStart){
            resolveTiedGroup(game, groupStart, groupEnd);
        }
        groupStart = groupEnd + 1;
    }
};

void determineTurnOrder(GameplayState *game){

    int diceValues[MAX_PLAYERS];
    int i;
    int groupStart;
    int groupEnd;

    printf("\n=============================================\n");
    printf("Determining the First Player\n");
    printf("=============================================\n");

    /* All four players roll first */
    for (i = 0; i < MAX_PLAYERS; i++){
        game->turnOrder[i] = i;
        diceValues[i] = rollDice();

        printf("%s rolled %d\n", game->players[i].name, diceValues[i]);
    }

    /* Sort players from highest roll to lowest roll */
    sortTurnOrder(game->turnOrder, diceValues, 0, MAX_PLAYERS - 1);

    /* Find tied groups */
    groupStart = 0;

    while (groupStart < MAX_PLAYERS){
        groupEnd = groupStart;

        while (groupEnd < MAX_PLAYERS - 1 && diceValues[groupEnd] == diceValues[groupEnd + 1]){
            groupEnd++;
        }

        if (groupEnd > groupStart){
            printf("\nTie between:\n");

            for (i = groupStart; i <= groupEnd; i++){
                printf("%s\n", game->players[game->turnOrder[i]].name);
            }

            resolveTiedGroup(game, groupStart, groupEnd);
        }

        groupStart = groupEnd + 1;
    }

    printf("\n%s will begin the game.\n", game->players[game->turnOrder[0]].name);
    printf("\nTurn order:\n");
    for (i = 0; i < MAX_PLAYERS; i++){
        printf("%s\n", game->players[game->turnOrder[i]].name);
    }
    printf("=============================================\n\n");
}
void playTurn(GameplayState *game, int playerId){

    int diceValue;

    printf("\n-----------------------------------\n");
    printf("%s's turn\n", game->players[playerId].name);
    printf("---------------------------------------------\n");

    if(game->players[playerId].isbankrupt == 1){
        return;
    }
    performMaintenance(game, playerId);

    if(game->players[playerId].inJail == 1){
        handleJailTurn(game, playerId);
        return;
    }

    diceValue = rollDice();

    printf("%s rolled %d.\n", game->players[playerId].name, diceValue);

    movePlayer(game, playerId, diceValue);
    resolveLanding(game, playerId, diceValue);
}

void handleJailTurn(GameplayState *game, int playerId){

    int dice1;
    int dice2;
    int diceValue;

    printf("\n%s is currently is jail\n", game->players[playerId].name);

    dice1 = rand() % 6 + 1;
    dice2 = rand() % 6 + 1;
    diceValue = dice1 + dice2;

    printf("%s rolled %d and %d \n", game->players[playerId].name, dice1, dice2);

    /* player can leave jail if dice 1 = dice 2 */

    if (dice1 == dice2){
        printf("%s rolled doubles and left Jail.\n", game->players[playerId].name);

        game->players[playerId].inJail = 0;
        game->players[playerId].jailTurns = 0;

        movePlayer(game, playerId, diceValue);
        resolveLanding(game, playerId, diceValue);

        return;
    }
    /* player failed to roll doubles*/
    game->players[playerId].jailTurns++;

    printf("%s did not roll doubles.\n", game->players[playerId].name);

    printf("Turns spent in Jail: %d\n", game->players[playerId].jailTurns);

    /* after three turns release player*/
    if (game->players[playerId].jailTurns >= 3)
    {
        game->players[playerId].inJail = 0;
        game->players[playerId].jailTurns = 0;

        printf("%s completed three turns in Jail and has been released.\n", game->players[playerId].name);
    }
    else
    {
        printf("%s remains in Jail.\n", game->players[playerId].name);
    }
}

int isGameRoundComplete(GameplayState *game){
    int i;

    for (i = 0; i < MAX_PLAYERS; i++){
        if(game->players[i].isbankrupt == 0){
            if(game->players[i].completedLap == 0){
            return 0;
            }
        }
    }
    return 1;
}

void completeGameRound(GameplayState *game){
    int i;

    game->currentRound++;

    printf("\n=================================\n");
    printf("GAME ROUND %d COMPLETED\n", game->currentRound);
    printf("=================================\n");

    for (i = 0; i < MAX_PLAYERS; i++){
        if(game->players[i].isbankrupt == 0){
            updateLoanAfterRound(game, i);
        }
    }
    /* insurance duration*/
    updateInsuranceAfterRound(game);
    updatePropertyAge(game);
    updateBuildingCondition(game);
    updateBuildingCondition(game);
    updateMaintenanceNeglect(game);
    updatePropertyMarket(game);

    if(game->currentRound % 10 == 0){
        triggerDisaster(game);
        applyInflation(game);
        applyPropertyMarket(game);
    }
    if(game->currentRound % 20 == 0){
        triggerGovRegulation(game);
    }

    for (i = 0; i < MAX_PLAYERS; i++){
        if(game->players[i].isbankrupt == 0){
            game->players[i].completedLap = 0;
        }
    }
    printRoundSummary(game);
    printMarketConditions(game);
}

void playTurnCycle(GameplayState *game){

    int i;
    int playerId;

    for (i = 0; i < MAX_PLAYERS; i++){
        playerId = game->turnOrder[i];

        if(game->players[playerId].isbankrupt == 0){
            playTurn(game, playerId);
             if(isGameRoundComplete(game)){
                completeGameRound(game);
            }
        }    
    }
}

void updatePropertyAge(GameplayState *game){
    int i;

    for (i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].owner != NO_OWNER){
            game->properties[i].age++;
            if(game->properties[i].age > 50 && game->properties[i].age % 5 == 0 && game->properties[i].depreciationPercent < 30){
                game->properties[i].depreciationPercent++;
                game->properties[i].currentMarketValue = game->properties[i].currentMarketValue * 99/100;
                printf("Property\n");
                printf("%s\n", game->properties[i].name);
                printf("has depreciated by %d%%.\n", game->properties[i].depreciationPercent);
                printf("Current value\n");
                printf("LKR %d.\n", game->properties[i].currentMarketValue);
            }
        }
    }
}

void updateBuildingCondition(GameplayState *game){
    int i,j;

    for (i = 0; i < MAX_PROPERTIES; i++){
        for (j = 0; j < game->properties[i].houses; j++){
            if(game->properties[i].houseCondition[j] > 0){
                game->properties[i].houseCondition[j] -= 2;
                if (game->properties[i].houseCondition[j] < 0){
                    game->properties[i].houseCondition[j] = 0;
                }
            }
        }
        if(game->properties[i].hotel == 1){
            if (game->properties[i].hotelCondition > 0){
                game->properties[i].hotelCondition -= 2;
                if (game->properties[i].hotelCondition < 0){
                    game->properties[i].hotelCondition = 0;
                }
            }
        }
    }
}

int getPropertyBuildingCondition(GameplayState *game, int propertyId){
    int i;
    int lowestCondition = 100;

    if(game->properties[propertyId].hotel == 1){
        return game->properties[propertyId].hotelCondition;
    }
    if(game->properties[propertyId].houses > 0){
        for (i = 0; i < game->properties[propertyId].houses; i++){
            if(game->properties[propertyId].houseCondition[i] < lowestCondition){
                lowestCondition = game->properties[propertyId].houseCondition[i];
            }
        }
        return lowestCondition;
    }
    return 100;
}

int countSolventPlayers(GameplayState *game){
    int i;
    int count = 0;

    for (i = 0; i < MAX_PLAYERS; i++){
        if(game->players[i].isbankrupt == 0){
            count++;
        }
    }
    return count;
}

int calculateNetWorth(GameplayState *game, int playerId){
    int i;
    int netWorth;
    netWorth = game->players[playerId].cash;

    for (i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].owner == playerId){
            netWorth += game->properties[i].currentMarketValue;
            netWorth += game->properties[i].houses * game->properties[i].houseCost;
            if(game->properties[i].hotel == 1){
                netWorth += game->properties[i].hotelCost;
            }
        }
    }
    for (i = 0; i < MAX_RAILWAY; i++){
        if (game->railways[i].owner == playerId){
            netWorth += game->railways[i].currentMarketValue;
        }
    }
    for (i = 0; i < MAX_UTILITY; i++){
        if (game->utilities[i].owner == playerId){
            netWorth += game->utilities[i].currentMarketValue;
        }
    }
    if (game->players[playerId].loanActive == 1){
        netWorth -= game->players[playerId].loanAmount;
    }
    return netWorth;
}

int findWinner(GameplayState *game){
    int i;
    int winner = -1;
    int highestNetWorth = -1;
    int netWorth;

    for (i = 0; i < MAX_PLAYERS; i++){
        if (game->players[i].isbankrupt == 0){
            netWorth = calculateNetWorth(game, i);
            if(winner == -1 || netWorth > highestNetWorth){
                highestNetWorth = netWorth;
                winner = i;
            }    
        }
    }
    return winner;
}
void printRoundSummary(GameplayState *game){
    int i;
    int j;
    int properties;
    int hotels;

    printf("\n");
    printf("=============================================\n");
    printf("Round %d Summary\n", game->currentRound);
    printf("=============================================\n");

    for (i = 0; i < MAX_PLAYERS; i++){
        properties = 0;
        hotels = 0;
        for (j = 0; j < MAX_PROPERTIES; j++){
            if(game->properties[j].owner == i){
                properties++;
                if(game->properties[j].hotel == 1){
                    hotels++;
                }
            }
        }
        printf("%s\n", game->players[i].name);
        if(game->players[i].isbankrupt == 1){
            printf("Status : BANKRUPT\n");
        }
        else{
            printf("Cash : LKR %d\n", game->players[i].cash);
            printf("Net Worth : LKR %d\n", calculateNetWorth(game, i));
            printf("Properties : %d\n", properties);
            printf("Hotels : %d\n", hotels);

            if(game->players[i].loanActive == 1){
                printf("Outstanding Loan : LKR %d\n", game->players[i].loanAmount);
            }
            else{
                printf("Outstanding Loan : None\n");
            }
        }
        printf("---------------------------------------------\n");
    }
    printf("=============================================\n");
}
void printMarketConditions(GameplayState *game)
{
    printf("\n=============================================\n");
    printf("Current Market Conditions\n");
    printf("=============================================\n");

    if (game->boomRoundsRemaining > 0)
    {
        printf("Market Boom Active\n");
        printf("Rounds Remaining : %d\n",
               game->boomRoundsRemaining);
    }
    else
    {
        printf("Market Boom : None\n");
    }

    if (game->declineRoundsRemaining > 0)
    {
        printf("Market Decline Active\n");
        printf("Rounds Remaining : %d\n",
               game->declineRoundsRemaining);
    }
    else
    {
        printf("Market Decline : None\n");
    }

    printf("Current Loan Interest : %d%%\n",
           game->loanInterestRate);

    printf("=============================================\n");
}
void printGameResult(GameplayState *game){
    int winner;
    winner = findWinner(game);

    printf("\n");
    printf("====================================\n");
    printf("            GAME OVER\n");
    printf("====================================\n");

    if(winner == -1){
        printf("No winner.\n");
        return;
    }
    printf("Winner\n");
    printf("%s\n", game->players[winner].name);
    printf("Total Cash\n");
    printf("LKR %d\n", game->players[winner].cash);
    printf("Total Property Value\n");
    printf("LKR %d\n", calculateTotalPropertyValue(game, winner));
    printf("Outstanding Loans\n");

    if(game->players[winner].loanActive == 1){
        printf("LKR %d\n", game->players[winner].loanAmount);
    }
    else{
        printf("None\n");
    }

    printf("Net Worth\n");
    printf("LKR %d\n", calculateNetWorth(game, winner));
    printf("=============================================\n");
}

   



    
        
    

    

