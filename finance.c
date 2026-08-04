#include <stdio.h>
#include "types.h"

/* buy property pay rent */

void buyProperty(GameplayState *game, int playerId, int propertyId)
{
    int price;

    price = game->properties[propertyId].purchasePrice;

    if (game->properties[propertyId].owner != NO_OWNER)
    {
        printf("This property already has an owner \n");
        return;
    }

    if (game->players[playerId].cash < price)
    {
        printf("%s does not have enough cash to buy %s \n", game->players[playerId].name, game->properties[propertyId].name);

        return;
    }

    game->players[playerId].cash -= price;

    game->properties[propertyId].owner = playerId;

    printf("%s purchased %s for LKR %d \n", game->players[playerId].name, game->properties[propertyId].name, price);

    printf("%s now has LKR %d.\n",
           game->players[playerId].name, game->players[playerId].cash);
}

void payPropertyRent(GameplayState *game, int playerId, int propertyId)
{
    int ownerId;
    int rent;

    ownerId = game->properties[propertyId].owner;
    rent = game->properties[propertyId].baseRent;

    // doesnt pay rent for own property

    if (ownerId == playerId)
    {
        printf("%s owns this property No rent is paid \n", game->players[playerId].name);
        return;
    }

    // no rent fo mortgaged property
    if (game->properties[propertyId].mortgaged == 1)
    {
        printf("%s is mortgaged no rent is collected \n", game->properties[propertyId].name);
        return;
    }
    // no rent for NO OWNER property
    if (ownerId == NO_OWNER)
    {
        printf("This property has no owner.\n");
        return;
    }

    /* temp basic payment bankrupcy and debt will add later*/

    if (game->players[playerId].cash < rent)
    {
        printf("%s does not have enough cash to pay the rent.\n",
               game->players[playerId].name);

        return;
    }
    game->players[playerId].cash -= rent;
    game->players[ownerId].cash += rent;

    printf("%s paid LKR %d rent to %s.\n",
           game->players[playerId].name,
           rent,
           game->players[ownerId].name);

    printf("%s now has LKR %d.\n",
           game->players[playerId].name,
           game->players[playerId].cash);

    printf("%s now has LKR %d.\n",
           game->players[ownerId].name,
           game->players[ownerId].cash);
}

/* buy railway pay rent count */

void buyRailway(GameplayState *game, int playerId, int railwayId)
{
    int price;

    price = game->railways[railwayId].purchasePrice;

    if (game->railways[railwayId].owner != NO_OWNER)
    {
        printf("This railway already has an owner \n");
        return;
    }

    if (game->players[playerId].cash < price)
    {
        printf("%s does not have enough cash to buy %s.\n", game->players[playerId].name, game->railways[railwayId].name);

        return;
    }

    game->players[playerId].cash -= price;
    game->railways[railwayId].owner = playerId;

    printf("%s purchased %s for LKR %d.\n", game->players[playerId].name, game->railways[railwayId].name, price);

    printf("%s now has LKR %d.\n", game->players[playerId].name, game->players[playerId].cash);
}

int countOwnedRailways(GameplayState *game, int playerId)
{
    int i;
    int count;

    count = 0;

    for (i = 0; i < MAX_RAILWAY; i++)
    {
        if (game->railways[i].owner == playerId)
        {
            count++;
        }
    }
    return count;
}

void payRailwayRent(GameplayState *game, int playerId, int railwayId)
{
    int ownerId;
    int railwayCount;
    int rent;

    ownerId = game->railways[railwayId].owner;

    if (ownerId == NO_OWNER)
    {
        return;
    }

    if (ownerId == playerId)
    {
        printf("%s owns this railway No rent is paid \n", game->players[playerId].name);

        return;
    }

    /* Mortgaged railway cant collect rent*/
    if (game->railways[railwayId].mortgaged == 1)
    {
        printf("%s is mortgaged no rent is paid \n", game->railways[railwayId].name);

        return;
    }

    railwayCount = countOwnedRailways(game, ownerId);

    if (railwayCount == 1)
    {
        rent = 250;
    }
    else if (railwayCount == 2)
    {
        rent = 500;
    }
    else if (railwayCount == 3)
    {
        rent = 1000;
    }
    else
    {
        rent = 2000;
    }

    if (game->players[playerId].cash < rent)
    {
        printf("%s does not have enough cash to pay railway rent.\n",
               game->players[playerId].name);

        return;
    }

    game->players[playerId].cash -= rent;
    game->players[ownerId].cash += rent;

    printf("%s paid LKR %d railway rent to %s.\n", game->players[playerId].name, rent, game->players[ownerId].name);
}

/* buy utility pay rent count*/

void buyUtility(GameplayState *game, int playerId, int utilityId)
{
    int price;

    price = game->utilities[utilityId].purchasePrice;

    if (game->utilities[utilityId].owner != NO_OWNER)
    {
        printf("This utility already has an owner.\n");
        return;
    }

    if (game->players[playerId].cash < price)
    {
        printf("%s does not have enough cash to buy %s.\n", game->players[playerId].name, game->utilities[utilityId].name);

        return;
    }

    game->players[playerId].cash -= price;
    game->utilities[utilityId].owner = playerId;

    printf("%s purchased %s for LKR %d.\n", game->players[playerId].name, game->utilities[utilityId].name, price);

    printf("%s now has LKR %d.\n", game->players[playerId].name, game->players[playerId].cash);
}

int countOwnedUtilities(GameplayState *game, int playerId)
{
    int i;
    int count;

    count = 0;

    for (i = 0; i < MAX_UTILITY; i++)
    {
        if (game->utilities[i].owner == playerId)
        {
            count++;
        }
    }
    return count;
}

void payUtilityRent(GameplayState *game, int playerId, int utilityId, int diceValue)
{
    int ownerId;
    int utilityCount;
    int rent;

    ownerId = game->utilities[utilityId].owner;

    if (ownerId == NO_OWNER)
    {
        return;
    }

    if (ownerId == playerId)
    {
        printf("%s owns this utility. No rent is paid.\n", game->players[playerId].name);

        return;
    }
    // cant collect rent because mortgaged

    if (game->utilities[utilityId].mortgaged == 1)
    {
        printf("%s is mortgaged. No rent is paid.\n", game->utilities[utilityId].name);

        return;
    }

    utilityCount = countOwnedUtilities(game, ownerId);

    if (utilityCount == 1)
    {
        rent = diceValue * 4;
    }

    else
    {
        rent = diceValue * 10;
    }

    if (game->players[playerId].cash < rent)
    {
        printf("%s does not have enough cash to pay utility rent \n", game->players[playerId].name);

        return;
    }

    game->players[playerId].cash -= rent;
    game->players[ownerId].cash += rent;

    printf("%s paid LKR %d utility rent to %s.\n", game->players[playerId].name, rent, game->players[ownerId].name);

    printf("Dice total: %d\n", diceValue);
    printf("Utilities owned by owner: %d\n", utilityCount);
}

int payJailBail(GameplayState *game, int playerId)
{
    int bailAmount = 300;

    if (game->players[playerId].cash < bailAmount)
    {
        printf("%s does not have enough cash to pay bail.\n",
               game->players[playerId].name);

        return 0;
    }

    game->players[playerId].cash -= bailAmount;
    game->players[playerId].inJail = 0;
    game->players[playerId].jailTurns = 0;

    printf("%s paid LKR %d bail and left Jail.\n",
           game->players[playerId].name,
           bailAmount);

    printf("%s now has LKR %d.\n",
           game->players[playerId].name,
           game->players[playerId].cash);

    return 1; /* return 1 = bail was paid return 0 = baild wasnt paid*/
}