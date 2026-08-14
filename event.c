#include <stdio.h>
#include <stdlib.h>
#include "types.h"

void triggerDisaster(GameplayState *game){
    int developedProperties[MAX_PROPERTIES];
    int developedCount = 0;
    int i;
    int propertyId;
    int disaster;
    int repairCost = 1000; // placeholder for now 
    int compensation = 0;
    int owner;

    for (i = 0; i < MAX_PROPERTIES; i++){
        if(game->properties[i].owner != NO_OWNER && (game->properties[i].houses > 0 || game->properties[i].hotel == 1)){
            developedProperties[developedCount] = i;
            developedCount++;
        }
    }
    if(developedCount == 0){
        printf("No developed property available for disaster.\n");
        return; 
    }

    propertyId = developedProperties[rand() % developedCount];
    disaster = rand() % 5;
    owner = game->properties[propertyId].owner;

    printf("\n===== DISASTER =====\n");
    
    switch (disaster){
        case FIRE:
            printf("Fire affected %s.\n", game->properties[propertyId].name);
            break;

        case FLOOD:
            printf("Flood affected %s.\n", game->properties[propertyId].name);
            break;

        case RIOT:
            printf("Riot affected %s.\n", game->properties[propertyId].name);
            break;

        case BUILDING_COLLAPSE:
            printf("Building Collapse affected %s.\n", game->properties[propertyId].name);
            break;

        case ELECTRICAL_FAILURE:
            printf("Electrical Failure affected %s.\n", game->properties[propertyId].name);
            break;
    }  
    game->properties[propertyId].damaged = 1;

     switch (game->properties[propertyId].insuranceType){
        case BASIC_INSURANCE:
            /* Basic covers only Fire and Flood, 80% */
            if(disaster == FIRE || disaster == FLOOD){
                compensation = repairCost * 80 / 100;
            }
            break;

        case COMPREHENSIVE_INSURANCE:
            /* Covers all listed disasters, 100% */
            if(disaster == FIRE || disaster == FLOOD || disaster == RIOT){
                compensation = repairCost;
            }
            break;

        case BUSINESS_INTERRUPTION_INSURANCE:
            /*
                For now: if property has a hotel,
                pay full repair cost.
                Lost rent part can be added later.
            */
            if(game->properties[propertyId].hotel == 1){
                compensation = repairCost;
            }
            break;

        case NO_INSURANCE:
            compensation = 0;
            break;
        }

        if(compensation > 0){
            game->players[owner].cash += compensation;
            printf("Insurance compensation: LKR %d\n", compensation);
            printf("%s remains damaged until repaired.\n", game->properties[propertyId].name);
        }
        else{
            printf("%s has no applicable insurance coverage.\n", game->properties[propertyId].name);
        }
        reparProperty(game, propertyId);          
}
