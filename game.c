#include <stdio.h>
#include <stdlib.h>
#include "types.h"

int rollDice()
{
    int die1 = rand() % 6 + 1;
    int die2 = rand() % 6 + 1;

    return die1 + die2;
}

/* sort only part of the arrays from high to low*/

void sortTurnOrder(int turnOrder[],
                   int diceValue[],
                   int start,
                   int end)
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

        printf("%s rolled %d\n",
               game->players[game->turnOrder[i]].name,
               rerollValuses[i]);
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

        printf("%s rolled %d\n",
               game->players[i].name,
               diceValues[i]);
    }

    /* Sort players from highest roll to lowest roll */
    sortTurnOrder(game->turnOrder,
                  diceValues,
                  0,
                  MAX_PLAYERS - 1);

    /* Find tied groups */
    groupStart = 0;

    while (groupStart < MAX_PLAYERS)
    {
        groupEnd = groupStart;

        while (groupEnd < MAX_PLAYERS - 1 &&
               diceValues[groupEnd] ==
                   diceValues[groupEnd + 1])
        {
            groupEnd++;
        }

        if (groupEnd > groupStart)
        {
            printf("\nTie between:\n");

            for (i = groupStart; i <= groupEnd; i++)
            {
                printf("%s\n",
                       game->players[game->turnOrder[i]].name);
            }

            resolveTiedGroup(game,
                             groupStart,
                             groupEnd);
        }

        groupStart = groupEnd + 1;
    }

    printf("\nFinal turn order:\n");

    for (i = 0; i < MAX_PLAYERS; i++)
    {
        printf("%d. %s\n",
               i + 1,
               game->players[game->turnOrder[i]].name);
    }
}

void playTurn(GameplayState *game, int playerId)
{
    int diceValue;

    printf("\n-----------------------------------\n");
    printf("%s's turn\n", game->players[playerId].name);

    diceValue = rollDice();

    printf("%s rolled %d.\n",
           game->players[playerId].name,
           diceValue);

    movePlayer(game, playerId, diceValue);

    resolveLanding(game, playerId, diceValue);
}