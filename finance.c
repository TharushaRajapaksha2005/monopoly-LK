#include <stdio.h>
#include "types.h"

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

    game->players[playerId].cash = game->players[playerId].cash - price;

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
}