#include <stdio.h>
#include <stdlib.h>
#include "types.h"

int rollDice()
{
    int dice1 = rand() % 6 + 1;
    int dice2 = rand() % 6 + 1;

    return dice1 + dice2;
}

/* sort only part of the arrays from high to low*/

void sortTurnOrder(int turnOrder[], int diceValue[], int start, int end)
{
    int i, j, temp;

    for (i = start; i < end; i++)
    {
        for (j = i + 1; j <= end; j++)
        {
            if (diceValue[j] > diceValue[i])
            {
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

void resolveTiedGroup(GameplayState *game, int start, int end)
{
    int rerollValuses[MAX_PLAYERS];
    int i;
    int groupStart;
    int groupEnd;

    printf("\nTied Players reroll:\n");

    for (i = start; i <= end; i++)
    {
        rerollValuses[i] = rollDice();

        printf("%s rolled %d\n", game->players[game->turnOrder[i]].name, rerollValuses[i]);
    }

    sortTurnOrder(game->turnOrder, rerollValuses, start, end);

    groupStart = start;

    while (groupStart <= end)
    {
        groupEnd = groupStart;

        while (groupEnd < end && rerollValuses[groupEnd] == rerollValuses[groupEnd + 1])
        {
            groupEnd++;
        }
        if (groupEnd > groupStart)
        {
            resolveTiedGroup(game, groupStart, groupEnd);
        }
        groupStart = groupEnd + 1;
    }
}

void determineTurnOrder(GameplayState *game)
{
    int diceValues[MAX_PLAYERS];
    int i;
    int groupStart;
    int groupEnd;

    printf("Determining turn order:\n\n");

    /* All four players roll first */
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        game->turnOrder[i] = i;
        diceValues[i] = rollDice();

        printf("%s rolled %d\n", game->players[i].name, diceValues[i]);
    }

    /* Sort players from highest roll to lowest roll */
    sortTurnOrder(game->turnOrder, diceValues, 0, MAX_PLAYERS - 1);

    /* Find tied groups */
    groupStart = 0;

    while (groupStart < MAX_PLAYERS)
    {
        groupEnd = groupStart;

        while (groupEnd < MAX_PLAYERS - 1 && diceValues[groupEnd] == diceValues[groupEnd + 1])
        {
            groupEnd++;
        }

        if (groupEnd > groupStart)
        {
            printf("\nTie between:\n");

            for (i = groupStart; i <= groupEnd; i++)
            {
                printf("%s\n", game->players[game->turnOrder[i]].name);
            }

            resolveTiedGroup(game, groupStart, groupEnd);
        }

        groupStart = groupEnd + 1;
    }

    printf("\nFinal turn order:\n");

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        printf("%d. %s\n", i + 1, game->players[game->turnOrder[i]].name);
    }
}

void playTurn(GameplayState *game, int playerId)
{
    int diceValue;

    printf("\n-----------------------------------\n");
    printf("%s's turn\n", game->players[playerId].name);

    if (game->players[playerId].inJail == 1)
    {
        handleJailTurn(game, playerId);
        return;
    }

    diceValue = rollDice();

    printf("%s rolled %d.\n", game->players[playerId].name, diceValue);

    movePlayer(game, playerId, diceValue);

    resolveLanding(game, playerId, diceValue);
}

void handleJailTurn(GameplayState *game, int playerId)
{
    int dice1;
    int dice2;
    int diceValue;

    printf("\n%s is currently is jail\n", game->players[playerId].name);

    dice1 = rand() % 6 + 1;
    dice2 = rand() % 6 + 1;
    diceValue = dice1 + dice2;

    printf("%s rolled %d and %d \n", game->players[playerId].name, dice1, dice2);

    /* player can leave jail if dice 1 = dice 2 */

    if (dice1 == dice2)
    {
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

void playRound(GameplayState *game)
{
    int i;
    int playerId;

    printf("\n===================================\n");
    printf("ROUND %d\n", game->currentRound);
    printf("===================================\n");
}
