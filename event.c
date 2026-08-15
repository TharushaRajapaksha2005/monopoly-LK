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
        return; 
    }

    propertyId = developedProperties[rand() % developedCount];
    disaster = rand() % 5;
    owner = game->properties[propertyId].owner;
    
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
    printf("\n===== DISASTER =====\n");
    printf("%d occurred.\n", disaster);
    printf("Affected Property :\n");
    printf("%s.\n", game->properties[propertyId].name);  
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
            printf("Insurance Claim Approved.\n");
            printf("Compensation Paid :\n");
            printf("LKR %d.\n", compensation);
        }
        else{
            printf("Property is not covered by insurance.\n");
        }
        repairProperty(game, propertyId);          
}

void applyInflation(GameplayState *game){
    int inflationRates[6] = {-3, 0, 2, 5, 8, 12};
    int inflationRate;
    int i;

    inflationRate = inflationRates[rand() % 6];
    printf("\nEconomic Update\n");
    printf("Inflation rate: %d%%\n", inflationRate);

     for (i = 0; i < MAX_PROPERTIES; i++){
        game->properties[i].normalPurchasePrice = game->properties[i].normalPurchasePrice * (100 + inflationRate) / 100;
        game->properties[i].normalHouseCost = game->properties[i].normalHouseCost * (100 + inflationRate) / 100;
        game->properties[i].normalHotelCost = game->properties[i].normalHotelCost * (100 + inflationRate) / 100;        
        game->properties[i].normalBaseRent = game->properties[i].normalBaseRent * (100 + inflationRate) / 100;
       // copy inflated normal values to property values market effect aplie to this values 
        game->properties[i].purchasePrice = game->properties[i].normalPurchasePrice;
        game->properties[i].houseCost = game->properties[i].normalHouseCost;
        game->properties[i].hotelCost = game->properties[i].normalHotelCost;
        game->properties[i].baseRent = game->properties[i].normalBaseRent;
    }
    game->insurancePremiumFactor = game->insurancePremiumFactor * (100 + inflationRate) / 100;
    game->repairCost = game->repairCost * (100 + inflationRate) / 100;
    game->loanInterestRate = game->loanInterestRate * (100 + inflationRate) / 100;

   // printf("Insurance Premium Factor: %d%%\n", game->insurancePremiumFactor);
   // printf("New repair cost: LKR %d\n", game->repairCost);
   // printf("Current loan interest rate: %d%%\n", game->loanInterestRate);
}

void applyPropertyMarket(GameplayState *game){
    int i;
    int boom;
    int decline;

    do{
        boom = rand() % 8;
    }while (game->currentRound - game->lastMarketAffectedRound[boom] < 30);
    do{
        decline = rand() % 8;
    }while (decline == boom || game->currentRound - game->lastMarketAffectedRound[decline] < 30);
    
   // printf("Selected boom: %d\n", boom);
   // printf("Selected decline: %d\n", decline);

    game->boomGroup = (PropertyGroup)boom;
    game->declineGroup = (PropertyGroup)decline;
    game->boomRoundsRemaining = 10;
    game->declineRoundsRemaining = 10;

    game->lastMarketAffectedRound[boom] = game->currentRound;
    game->lastMarketAffectedRound[decline] = game->currentRound;

    printf("\n=== PROPERTY MARKET UPDATE ===\n");
    printf("Market Boom : %d\n", boom);
    printf("Market Decline : %d\n", decline);
    printf("Boom Duration : 10 Rounds\n");
    printf("Decline Duration : 10 Rounds\n");

    for (i = 0; i < MAX_PROPERTIES; i++){
        // market boom
        if(game->properties[i].group == game->boomGroup){
            game->properties[i].purchasePrice = game->properties[i].normalPurchasePrice * 115 / 100;            
            game->properties[i].mortgageValue = game->properties[i].normalMortgageValue * 115 / 100;
            game->properties[i].baseRent = game->properties[i].normalBaseRent * 125 / 100;
            game->properties[i].houseCost = game->properties[i].normalHouseCost * 110 / 100;
            game->properties[i].hotelCost = game->properties[i].normalHotelCost * 110 / 100;
            game->properties[i].currentMarketValue = game->properties[i].normalMarketValue * 120 / 100;
        }
        // market decline
        if(game->properties[i].group == game->declineGroup){            
            game->properties[i].currentMarketValue = game->properties[i].normalMarketValue * 85 / 100;
            game->properties[i].baseRent = game->properties[i].normalBaseRent * 80 / 100;
            game->properties[i].mortgageValue = game->properties[i].normalMortgageValue * 90 / 100;
        }
    }
}

void updatePropertyMarket(GameplayState *game){
    int i;

    if(game->boomRoundsRemaining > 0){
        game->boomRoundsRemaining--;
    }
    if(game->declineRoundsRemaining > 0){
        game->declineRoundsRemaining--;
    }

    if(game->boomRoundsRemaining == 0 && game->boomGroup != NO_GROUP){
        for (i = 0; i < MAX_PROPERTIES; i++){
            if(game->properties[i].group == game->boomGroup){
                game->properties[i].purchasePrice = game->properties[i].normalPurchasePrice;
                game->properties[i].mortgageValue = game->properties[i].normalMortgageValue;
                game->properties[i].baseRent = game->properties[i].normalBaseRent;
                game->properties[i].houseCost = game->properties[i].normalHouseCost;
                game->properties[i].hotelCost = game->properties[i].normalHotelCost;
                game->properties[i].currentMarketValue = game->properties[i].normalMarketValue;
            }
        }
        printf("Market boom has ended.\n");
        game->boomGroup = NO_GROUP;
    }
    if(game->declineRoundsRemaining == 0 && game->declineGroup != NO_GROUP){
        for (i = 0; i < MAX_PROPERTIES; i++){
            if(game->properties[i].group == game->declineGroup){
                game->properties[i].mortgageValue = game->properties[i].normalMortgageValue;
                game->properties[i].baseRent = game->properties[i].normalBaseRent;
                game->properties[i].currentMarketValue = game->properties[i].normalMarketValue;
            }
        }
        printf("Market decline has ended.\n");
        game->declineGroup = NO_GROUP;
    }
    if(game->boomRoundsRemaining == 0 && game->declineRoundsRemaining == 0){
        for (i = 0; i < MAX_PROPERTIES; i++){
            game->properties[i].purchasePrice = game->properties[i].normalPurchasePrice;
            game->properties[i].mortgageValue = game->properties[i].normalMortgageValue;
            game->properties[i].baseRent = game->properties[i].normalBaseRent;
            game->properties[i].houseCost = game->properties[i].normalHouseCost;
            game->properties[i].hotelCost = game->properties[i].normalHotelCost;
            game->properties[i].currentMarketValue = game->properties[i].normalMarketValue;
        }
        game->boomGroup = NO_GROUP;
        game->declineGroup = NO_GROUP;
    }
}

void triggerGovRegulation(GameplayState *game){
    int regulation;

    regulation = 1 + rand() % 8;
    game->currentGovRegulation = (GovernmentRegulation)regulation;

    printf("\n=== GOVERNMENT REGULATION ===\n");
    switch (regulation){
        case INCREASE_PROPERTY_TAX:
            printf("Increase Property Tax Introduced\n");
            printf("Income Tax increased by 50%%.\n");
            break;

        case REDUCE_LOAN_INTEREST:
            printf("Reduce Loan Interest Introduced\n");
            printf("Loan interest rate reduced by 2%%.\n");
            break;

        case HOUSING_SUBSIDY:
            printf("Housing Subsidy Introduced.\n");
            printf("Construction costs reduced by 30%%.\n");
            break;

        case LUXURY_PROPERTY_TAX:
            printf("Luxury Property Tax Introduced\n");
            printf("Hotels are subject to a 25%% maintenance tax.\n");
            break;

        case RAILWAY_MODERNIZATION:
            printf("Railway Modernization Introduced\n");
            printf("Railway rent increased by 25%%.\n");
            break;

        case ELECTRICITY_TARIFF_REVISION:
            printf("Electricity Tariff Revision Introduced\n");
            printf("Utility rent increased by 20%%.\n");
            break;

        case INSURANCE_REGULATION:
            printf("Insurance Regulation Introduced\n");
            printf("Insurance premiums reduced by 15%%.\n");
            break;

        case ANTI_SPECULATION_ACT:
            printf("Anti-Speculation Act Introducedn");
            printf("Players may own at most three undeveloped properties.\n");
            printf("Additional purchases require development within 5 rounds.\n");
            break;
        default:
            break;
    }
    printf("=============================\n");
}
