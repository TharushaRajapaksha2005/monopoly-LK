#include <stdio.h>
#include <string.h>
#include "types.h"

void initializeProperties(GameplayState *game)
{
       /* Property 0 - Pettah */
       game->properties[0].propertyId = 0;
       strcpy(game->properties[0].name, "Pettah");
       game->properties[0].group = BROWN;
       game->properties[0].purchasePrice = 1500;
       game->properties[0].currentMarketValue = 1500;
       game->properties[0].mortgageValue = 750;
       game->properties[0].baseRent = 100;
       game->properties[0].houseCost = 500;
       game->properties[0].hotelCost = 2000;
       game->properties[0].owner = NO_OWNER;
       game->properties[0].mortgaged = 0;
       game->properties[0].houses = 0;
       game->properties[0].hotel = 0;

       /* Property 1 - Maradana */
       game->properties[1].propertyId = 1;
       strcpy(game->properties[1].name, "Maradana");
       game->properties[1].group = BROWN;
       game->properties[1].purchasePrice = 1800;
       game->properties[1].currentMarketValue = 1800;
       game->properties[1].mortgageValue = 750;
       game->properties[1].baseRent = 120;
       game->properties[1].houseCost = 500;
       game->properties[1].hotelCost = 2000;
       game->properties[1].owner = NO_OWNER;
       game->properties[1].mortgaged = 0;
       game->properties[1].houses = 0;
       game->properties[1].hotel = 0;

       /* Property 2 - Bambalapitiya */
       game->properties[2].propertyId = 2;
       strcpy(game->properties[2].name, "Bambalapitiya");
       game->properties[2].group = LIGHT_BLUE;
       game->properties[2].purchasePrice = 2500;
       game->properties[2].currentMarketValue = 2500;
       game->properties[2].mortgageValue = 1250;
       game->properties[2].baseRent = 180;
       game->properties[2].houseCost = 750;
       game->properties[2].hotelCost = 3000;
       game->properties[2].owner = NO_OWNER;
       game->properties[2].mortgaged = 0;
       game->properties[2].houses = 0;
       game->properties[2].hotel = 0;

       /* Property 3 - Wellawatte */
       game->properties[3].propertyId = 3;
       strcpy(game->properties[3].name, "Wellawatte");
       game->properties[3].group = LIGHT_BLUE;
       game->properties[3].purchasePrice = 2700;
       game->properties[3].currentMarketValue = 2700;
       game->properties[3].mortgageValue = 1250;
       game->properties[3].baseRent = 200;
       game->properties[3].houseCost = 750;
       game->properties[3].hotelCost = 3000;
       game->properties[3].owner = NO_OWNER;
       game->properties[3].mortgaged = 0;
       game->properties[3].houses = 0;
       game->properties[3].hotel = 0;

       /* Property 4 - Mount Lavinia */
       game->properties[4].propertyId = 4;
       strcpy(game->properties[4].name, "Mount Lavinia");
       game->properties[4].group = LIGHT_BLUE;
       game->properties[4].purchasePrice = 3000;
       game->properties[4].currentMarketValue = 3000;
       game->properties[4].mortgageValue = 1250;
       game->properties[4].baseRent = 220;
       game->properties[4].houseCost = 750;
       game->properties[4].hotelCost = 3000;
       game->properties[4].owner = NO_OWNER;
       game->properties[4].mortgaged = 0;
       game->properties[4].houses = 0;
       game->properties[4].hotel = 0;

       /* Property 5 - Nugegoda */
       game->properties[5].propertyId = 5;
       strcpy(game->properties[5].name, "Nugegoda");
       game->properties[5].group = PINK;
       game->properties[5].purchasePrice = 3500;
       game->properties[5].currentMarketValue = 3500;
       game->properties[5].mortgageValue = 1750;
       game->properties[5].baseRent = 260;
       game->properties[5].houseCost = 1000;
       game->properties[5].hotelCost = 4000;
       game->properties[5].owner = NO_OWNER;
       game->properties[5].mortgaged = 0;
       game->properties[5].houses = 0;
       game->properties[5].hotel = 0;

       /* Property 6 - Maharagama */
       game->properties[6].propertyId = 6;
       strcpy(game->properties[6].name, "Maharagama");
       game->properties[6].group = PINK;
       game->properties[6].purchasePrice = 3800;
       game->properties[6].currentMarketValue = 3800;
       game->properties[6].mortgageValue = 1750;
       game->properties[6].baseRent = 280;
       game->properties[6].houseCost = 1000;
       game->properties[6].hotelCost = 4000;
       game->properties[6].owner = NO_OWNER;
       game->properties[6].mortgaged = 0;
       game->properties[6].houses = 0;
       game->properties[6].hotel = 0;

       /* Property 7 - Kottawa */
       game->properties[7].propertyId = 7;
       strcpy(game->properties[7].name, "Kottawa");
       game->properties[7].group = PINK;
       game->properties[7].purchasePrice = 4000;
       game->properties[7].currentMarketValue = 4000;
       game->properties[7].mortgageValue = 1750;
       game->properties[7].baseRent = 300;
       game->properties[7].houseCost = 1000;
       game->properties[7].hotelCost = 4000;
       game->properties[7].owner = NO_OWNER;
       game->properties[7].mortgaged = 0;
       game->properties[7].houses = 0;
       game->properties[7].hotel = 0;

       /* Property 8 - Negombo */
       game->properties[8].propertyId = 8;
       strcpy(game->properties[8].name, "Negombo");
       game->properties[8].group = ORANGE;
       game->properties[8].purchasePrice = 4500;
       game->properties[8].currentMarketValue = 4500;
       game->properties[8].mortgageValue = 2250;
       game->properties[8].baseRent = 350;
       game->properties[8].houseCost = 1250;
       game->properties[8].hotelCost = 5000;
       game->properties[8].owner = NO_OWNER;
       game->properties[8].mortgaged = 0;
       game->properties[8].houses = 0;
       game->properties[8].hotel = 0;

       /* Property 9 - Katunayake */
       game->properties[9].propertyId = 9;
       strcpy(game->properties[9].name, "Katunayake");
       game->properties[9].group = ORANGE;
       game->properties[9].purchasePrice = 4700;
       game->properties[9].currentMarketValue = 4700;
       game->properties[9].mortgageValue = 2250;
       game->properties[9].baseRent = 370;
       game->properties[9].houseCost = 1250;
       game->properties[9].hotelCost = 5000;
       game->properties[9].owner = NO_OWNER;
       game->properties[9].mortgaged = 0;
       game->properties[9].houses = 0;
       game->properties[9].hotel = 0;

       /* Property 10 - Ja-Ela */
       game->properties[10].propertyId = 10;
       strcpy(game->properties[10].name, "Ja-Ela");
       game->properties[10].group = ORANGE;
       game->properties[10].purchasePrice = 5000;
       game->properties[10].currentMarketValue = 5000;
       game->properties[10].mortgageValue = 2250;
       game->properties[10].baseRent = 400;
       game->properties[10].houseCost = 1250;
       game->properties[10].hotelCost = 5000;
       game->properties[10].owner = NO_OWNER;
       game->properties[10].mortgaged = 0;
       game->properties[10].houses = 0;
       game->properties[10].hotel = 0;

       /* Property 11 - Kandy City */
       game->properties[11].propertyId = 11;
       strcpy(game->properties[11].name, "Kandy City");
       game->properties[11].group = RED;
       game->properties[11].purchasePrice = 5500;
       game->properties[11].currentMarketValue = 5500;
       game->properties[11].mortgageValue = 2750;
       game->properties[11].baseRent = 450;
       game->properties[11].houseCost = 1500;
       game->properties[11].hotelCost = 6000;
       game->properties[11].owner = NO_OWNER;
       game->properties[11].mortgaged = 0;
       game->properties[11].houses = 0;
       game->properties[11].hotel = 0;

       /* Property 12 - Peradeniya */
       game->properties[12].propertyId = 12;
       strcpy(game->properties[12].name, "Peradeniya");
       game->properties[12].group = RED;
       game->properties[12].purchasePrice = 5800;
       game->properties[12].currentMarketValue = 5800;
       game->properties[12].mortgageValue = 2750;
       game->properties[12].baseRent = 480;
       game->properties[12].houseCost = 1500;
       game->properties[12].hotelCost = 6000;
       game->properties[12].owner = NO_OWNER;
       game->properties[12].mortgaged = 0;
       game->properties[12].houses = 0;
       game->properties[12].hotel = 0;

       /* Property 13 - Katugastota */
       game->properties[13].propertyId = 13;
       strcpy(game->properties[13].name, "Katugastota");
       game->properties[13].group = RED;
       game->properties[13].purchasePrice = 6000;
       game->properties[13].currentMarketValue = 6000;
       game->properties[13].mortgageValue = 2750;
       game->properties[13].baseRent = 500;
       game->properties[13].houseCost = 1500;
       game->properties[13].hotelCost = 6000;
       game->properties[13].owner = NO_OWNER;
       game->properties[13].mortgaged = 0;
       game->properties[13].houses = 0;
       game->properties[13].hotel = 0;

       /* Property 14 - Galle Fort */
       game->properties[14].propertyId = 14;
       strcpy(game->properties[14].name, "Galle Fort");
       game->properties[14].group = YELLOW;
       game->properties[14].purchasePrice = 6500;
       game->properties[14].currentMarketValue = 6500;
       game->properties[14].mortgageValue = 3250;
       game->properties[14].baseRent = 600;
       game->properties[14].houseCost = 2000;
       game->properties[14].hotelCost = 8000;
       game->properties[14].owner = NO_OWNER;
       game->properties[14].mortgaged = 0;
       game->properties[14].houses = 0;
       game->properties[14].hotel = 0;

       /* Property 15 - Unawatuna */
       game->properties[15].propertyId = 15;
       strcpy(game->properties[15].name, "Unawatuna");
       game->properties[15].group = YELLOW;
       game->properties[15].purchasePrice = 6800;
       game->properties[15].currentMarketValue = 6800;
       game->properties[15].mortgageValue = 3250;
       game->properties[15].baseRent = 620;
       game->properties[15].houseCost = 2000;
       game->properties[15].hotelCost = 8000;
       game->properties[15].owner = NO_OWNER;
       game->properties[15].mortgaged = 0;
       game->properties[15].houses = 0;
       game->properties[15].hotel = 0;

       /* Property 16 - Hikkaduwa */
       game->properties[16].propertyId = 16;
       strcpy(game->properties[16].name, "Hikkaduwa");
       game->properties[16].group = YELLOW;
       game->properties[16].purchasePrice = 7000;
       game->properties[16].currentMarketValue = 7000;
       game->properties[16].mortgageValue = 3250;
       game->properties[16].baseRent = 650;
       game->properties[16].houseCost = 2000;
       game->properties[16].hotelCost = 8000;
       game->properties[16].owner = NO_OWNER;
       game->properties[16].mortgaged = 0;
       game->properties[16].houses = 0;
       game->properties[16].hotel = 0;

       /* Property 17 - Jaffna Town */
       game->properties[17].propertyId = 17;
       strcpy(game->properties[17].name, "Jaffna Town");
       game->properties[17].group = GREEN;
       game->properties[17].purchasePrice = 8000;
       game->properties[17].currentMarketValue = 8000;
       game->properties[17].mortgageValue = 4000;
       game->properties[17].baseRent = 750;
       game->properties[17].houseCost = 2500;
       game->properties[17].hotelCost = 10000;
       game->properties[17].owner = NO_OWNER;
       game->properties[17].mortgaged = 0;
       game->properties[17].houses = 0;
       game->properties[17].hotel = 0;

       /* Property 18 - Nallur */
       game->properties[18].propertyId = 18;
       strcpy(game->properties[18].name, "Nallur");
       game->properties[18].group = GREEN;
       game->properties[18].purchasePrice = 8300;
       game->properties[18].currentMarketValue = 8300;
       game->properties[18].mortgageValue = 4000;
       game->properties[18].baseRent = 780;
       game->properties[18].houseCost = 2500;
       game->properties[18].hotelCost = 10000;
       game->properties[18].owner = NO_OWNER;
       game->properties[18].mortgaged = 0;
       game->properties[18].houses = 0;
       game->properties[18].hotel = 0;

       /* Property 19 - Trincomalee */
       game->properties[19].propertyId = 19;
       strcpy(game->properties[19].name, "Trincomalee");
       game->properties[19].group = GREEN;
       game->properties[19].purchasePrice = 8500;
       game->properties[19].currentMarketValue = 8500;
       game->properties[19].mortgageValue = 4000;
       game->properties[19].baseRent = 800;
       game->properties[19].houseCost = 2500;
       game->properties[19].hotelCost = 10000;
       game->properties[19].owner = NO_OWNER;
       game->properties[19].mortgaged = 0;
       game->properties[19].houses = 0;
       game->properties[19].hotel = 0;

       /* Property 20 - Nuwara Eliya */
       game->properties[20].propertyId = 20;
       strcpy(game->properties[20].name, "Nuwara Eliya");
       game->properties[20].group = DARK_BLUE;
       game->properties[20].purchasePrice = 10000;
       game->properties[20].currentMarketValue = 10000;
       game->properties[20].mortgageValue = 5000;
       game->properties[20].baseRent = 1000;
       game->properties[20].houseCost = 3000;
       game->properties[20].hotelCost = 12000;
       game->properties[20].owner = NO_OWNER;
       game->properties[20].mortgaged = 0;
       game->properties[20].houses = 0;
       game->properties[20].hotel = 0;

       /* Property 21 - Galle Face */
       game->properties[21].propertyId = 21;
       strcpy(game->properties[21].name, "Galle Face");
       game->properties[21].group = DARK_BLUE;
       game->properties[21].purchasePrice = 12000;
       game->properties[21].currentMarketValue = 12000;
       game->properties[21].mortgageValue = 5000;
       game->properties[21].baseRent = 1200;
       game->properties[21].houseCost = 3000;
       game->properties[21].hotelCost = 12000;
       game->properties[21].owner = NO_OWNER;
       game->properties[21].mortgaged = 0;
       game->properties[21].houses = 0;
       game->properties[21].hotel = 0;
}

void initializeRailways(GameplayState *game)
{
       game->railways[0].railwayId = 0;
       strcpy(game->railways[0].name, "Colombo Fort Railway Station");
       game->railways[0].purchasePrice = 1500;
       game->railways[0].currentMarketValue = 1500;
       game->railways[0].mortgageValue = 750;
       game->railways[0].owner = NO_OWNER;
       game->railways[0].mortgaged = 0;

       game->railways[1].railwayId = 1;
       strcpy(game->railways[1].name, "Kandy Railway Station");
       game->railways[1].purchasePrice = 1500;
       game->railways[1].currentMarketValue = 1500;
       game->railways[1].mortgageValue = 750;
       game->railways[1].owner = NO_OWNER;
       game->railways[1].mortgaged = 0;

       game->railways[2].railwayId = 2;
       strcpy(game->railways[2].name, "Galle Railway Station");
       game->railways[2].purchasePrice = 1500;
       game->railways[2].currentMarketValue = 1500;
       game->railways[2].mortgageValue = 750;
       game->railways[2].owner = NO_OWNER;
       game->railways[2].mortgaged = 0;

       game->railways[3].railwayId = 3;
       strcpy(game->railways[3].name, "Jaffna Railway Station");
       game->railways[3].purchasePrice = 1500;
       game->railways[3].currentMarketValue = 1500;
       game->railways[3].mortgageValue = 750;
       game->railways[3].owner = NO_OWNER;
       game->railways[3].mortgaged = 0;
}

void initializeUtilities(GameplayState *game)
{
       game->utilities[0].utilityId = 0;
       strcpy(game->utilities[0].name,
              "Ceylon Electricity Board");
       game->utilities[0].purchasePrice = 1500;
       game->utilities[0].currentMarketValue = 1500;
       game->utilities[0].mortgageValue = 750;
       game->utilities[0].owner = NO_OWNER;
       game->utilities[0].mortgaged = 0;

       game->utilities[1].utilityId = 1;
       strcpy(game->utilities[1].name,
              "National Water Supply and Drainage Board");
       game->utilities[1].purchasePrice = 1500;
       game->utilities[1].currentMarketValue = 1500;
       game->utilities[1].mortgageValue = 750;
       game->utilities[1].owner = NO_OWNER;
       game->utilities[1].mortgaged = 0;
}

void initializeBoard(GameplayState *game)
{
       game->board[0].squareId = 0;
       strcpy(game->board[0].name, "GO");
       game->board[0].type = START;
       game->board[0].propertyId = NO_ASSET;

       game->board[1].squareId = 1;
       strcpy(game->board[1].name, "Pettah");
       game->board[1].type = PROPERTY;
       game->board[1].propertyId = 0;

       game->board[2].squareId = 2;
       strcpy(game->board[2].name, "Community Development Fund");
       game->board[2].type = EVENT;
       game->board[2].propertyId = NO_ASSET;

       game->board[3].squareId = 3;
       strcpy(game->board[3].name, "Maradana");
       game->board[3].type = PROPERTY;
       game->board[3].propertyId = 1;

       game->board[4].squareId = 4;
       strcpy(game->board[4].name, "Income Tax");
       game->board[4].type = TAX;
       game->board[4].propertyId = NO_ASSET;

       game->board[5].squareId = 5;
       strcpy(game->board[5].name, "Colombo Fort Railway Station");
       game->board[5].type = RAILWAY;
       game->board[5].propertyId = 0;

       game->board[6].squareId = 6;
       strcpy(game->board[6].name, "Bambalapitiya");
       game->board[6].type = PROPERTY;
       game->board[6].propertyId = 2;

       game->board[7].squareId = 7;
       strcpy(game->board[7].name, "National Event Card");
       game->board[7].type = EVENT;
       game->board[7].propertyId = NO_ASSET;

       game->board[8].squareId = 8;
       strcpy(game->board[8].name, "Wellawatte");
       game->board[8].type = PROPERTY;
       game->board[8].propertyId = 3;

       game->board[9].squareId = 9;
       strcpy(game->board[9].name, "Mount Lavinia");
       game->board[9].type = PROPERTY;
       game->board[9].propertyId = 4;

       game->board[10].squareId = 10;
       strcpy(game->board[10].name, "Jail / Just Visiting");
       game->board[10].type = JAIL;
       game->board[10].propertyId = NO_ASSET;

       game->board[11].squareId = 11;
       strcpy(game->board[11].name, "Nugegoda");
       game->board[11].type = PROPERTY;
       game->board[11].propertyId = 5;

       game->board[12].squareId = 12;
       strcpy(game->board[12].name, "Ceylon Electricity Board");
       game->board[12].type = UTILITY;
       game->board[12].propertyId = 0;

       game->board[13].squareId = 13;
       strcpy(game->board[13].name, "Maharagama");
       game->board[13].type = PROPERTY;
       game->board[13].propertyId = 6;

       game->board[14].squareId = 14;
       strcpy(game->board[14].name, "Kottawa");
       game->board[14].type = PROPERTY;
       game->board[14].propertyId = 7;

       game->board[15].squareId = 15;
       strcpy(game->board[15].name, "Kandy Railway Station");
       game->board[15].type = RAILWAY;
       game->board[15].propertyId = 1;

       game->board[16].squareId = 16;
       strcpy(game->board[16].name, "Negombo");
       game->board[16].type = PROPERTY;
       game->board[16].propertyId = 8;

       game->board[17].squareId = 17;
       strcpy(game->board[17].name, "Sri Lanka Insurance");
       game->board[17].type = INSURANCE;
       game->board[17].propertyId = NO_ASSET;

       game->board[18].squareId = 18;
       strcpy(game->board[18].name, "Katunayake");
       game->board[18].type = PROPERTY;
       game->board[18].propertyId = 9;

       game->board[19].squareId = 19;
       strcpy(game->board[19].name, "Ja-Ela");
       game->board[19].type = PROPERTY;
       game->board[19].propertyId = 10;

       game->board[20].squareId = 20;
       strcpy(game->board[20].name, "Free Parking");
       game->board[20].type = FREE_PARKING;
       game->board[20].propertyId = NO_ASSET;

       game->board[21].squareId = 21;
       strcpy(game->board[21].name, "Kandy City");
       game->board[21].type = PROPERTY;
       game->board[21].propertyId = 11;

       game->board[22].squareId = 22;
       strcpy(game->board[22].name, "National Event Card");
       game->board[22].type = EVENT;
       game->board[22].propertyId = NO_ASSET;

       game->board[23].squareId = 23;
       strcpy(game->board[23].name, "Peradeniya");
       game->board[23].type = PROPERTY;
       game->board[23].propertyId = 12;

       game->board[24].squareId = 24;
       strcpy(game->board[24].name, "Katugastota");
       game->board[24].type = PROPERTY;
       game->board[24].propertyId = 13;

       game->board[25].squareId = 25;
       strcpy(game->board[25].name, "Galle Railway Station");
       game->board[25].type = RAILWAY;
       game->board[25].propertyId = 2;

       game->board[26].squareId = 26;
       strcpy(game->board[26].name, "Galle Fort");
       game->board[26].type = PROPERTY;
       game->board[26].propertyId = 14;

       game->board[27].squareId = 27;
       strcpy(game->board[27].name, "Unawatuna");
       game->board[27].type = PROPERTY;
       game->board[27].propertyId = 15;

       game->board[28].squareId = 28;
       strcpy(game->board[28].name,
              "National Water Supply and Drainage Board");
       game->board[28].type = UTILITY;
       game->board[28].propertyId = 1;

       game->board[29].squareId = 29;
       strcpy(game->board[29].name, "Hikkaduwa");
       game->board[29].type = PROPERTY;
       game->board[29].propertyId = 16;

       game->board[30].squareId = 30;
       strcpy(game->board[30].name, "Go To Jail");
       game->board[30].type = GO_TO_JAIL;
       game->board[30].propertyId = NO_ASSET;

       game->board[31].squareId = 31;
       strcpy(game->board[31].name, "Jaffna Town");
       game->board[31].type = PROPERTY;
       game->board[31].propertyId = 17;

       game->board[32].squareId = 32;
       strcpy(game->board[32].name, "Nallur");
       game->board[32].type = PROPERTY;
       game->board[32].propertyId = 18;

       game->board[33].squareId = 33;
       strcpy(game->board[33].name, "Ceylinco Insurance");
       game->board[33].type = INSURANCE;
       game->board[33].propertyId = NO_ASSET;

       game->board[34].squareId = 34;
       strcpy(game->board[34].name, "Trincomalee");
       game->board[34].type = PROPERTY;
       game->board[34].propertyId = 19;

       game->board[35].squareId = 35;
       strcpy(game->board[35].name, "Jaffna Railway Station");
       game->board[35].type = RAILWAY;
       game->board[35].propertyId = 3;

       game->board[36].squareId = 36;
       strcpy(game->board[36].name, "National Event Card");
       game->board[36].type = EVENT;
       game->board[36].propertyId = NO_ASSET;

       game->board[37].squareId = 37;
       strcpy(game->board[37].name, "Nuwara Eliya");
       game->board[37].type = PROPERTY;
       game->board[37].propertyId = 20;

       game->board[38].squareId = 38;
       strcpy(game->board[38].name, "Bank of Ceylon");
       game->board[38].type = BANK;
       game->board[38].propertyId = NO_ASSET;

       game->board[39].squareId = 39;
       strcpy(game->board[39].name, "Galle Face");
       game->board[39].type = PROPERTY;
       game->board[39].propertyId = 21;
}

void initializeGameBoard(GameplayState *game)
{
       initializeProperties(game);
       initializeRailways(game);
       initializeUtilities(game);
       initializeBoard(game);
}

void movePlayer(GameplayState *game, int playerId, int diceValue)
{
       int oldPosition;
       int newPosition;

       oldPosition = game->players[playerId].position;
       newPosition = oldPosition + diceValue;

       if (newPosition >= BOARD_SIZE)
       {
              newPosition = newPosition - BOARD_SIZE;

              game->players[playerId].cash = game->players[playerId].cash + 2000;

              printf("%s passed GO and recevid LKR 2000 \n", game->players[playerId].name);
       }

       game->players[playerId].position = newPosition;

       printf("%s moved form square %d to square %d \n", game->players[playerId].name, oldPosition, newPosition);

       printf("%s landed on %s \n", game->players[playerId].name, game->board[newPosition].name);
}

void resolveLanding(GameplayState *game, int playerId, int diceValue)
{
       int position;
       int type;

       position = game->players[playerId].position;
       type = game->board[position].type;

       switch (type)
       {
       case 0:
              printf("Square type: START\n");
              break;

       case 1:
              printf("Square type: PROPERTY\n");
              handlePropertyLanding(game, playerId);
              break;

       case 2:
              printf("Square type: RAILWAY\n");
              handleRailwayLanding(game, playerId);
              break;

       case 3:
              printf("Square type: UTILITY\n");
              handleUtilityLanding(game, playerId, diceValue);
              break;

       case 4:
              printf("Square type: EVENT\n");

              if (position == 2)
              {
                     payCommunityDevelopmentFund(game, playerId);
              }
              else
              {
                     printf("Other event card handling will be added later.\n");
              }
              break;

       case 5:
              printf("Square type: TAX\n");
              printf("Income Tax handling will be completed later.\n");
              break;

       case 6:
              printf("Square type: JAIL\n");
              printf("Just visiting Jail\n");
              break;

       case 7:
              printf("Square type: FREE PARKING\n");
              printf("%s landed on Free Parking. Nothing happens.\n", game->players[playerId].name);
              break;

       case 8:
              printf("Square type: GO TO JAIL\n");
              sendPlayerToJail(game, playerId);
              break;

       case 9:
              printf("Square type: BANK\n");
              break;

       case 10:
              printf("Square type: INSURANCE\n");
              break;

       default:
              printf("Square type: UNKNOWN\n");
              break;
       }
}
// handle property landing
void handlePropertyLanding(GameplayState *game, int playerId)
{
       int position;
       int propertyId;
       int ownerId;

       position = game->players[playerId].position;
       propertyId = game->board[position].propertyId;
       ownerId = game->properties[propertyId].owner;

       printf("Property name: %s\n", game->properties[propertyId].name);

       printf("Purchase price: LKR %d\n", game->properties[propertyId].purchasePrice);

       if (ownerId == NO_OWNER)
       {
              if (shouldBuyProperty(game, playerId, propertyId) == 1)
              {
                     buyProperty(game, playerId, propertyId);
              }
              else
              {
                     printf("%s decided not to buys %s \n", game->players[playerId].name, game->properties[propertyId].name);

                     auctionProperty(game, propertyId);
              }
       }
       else if (ownerId == playerId)
       {
              printf("%s already owns this prorperty \n", game->players[playerId].name);
       }
       else
       {
              printf("This property is owned by %s \n", game->players[ownerId].name);

              payPropertyRent(game, playerId, propertyId);
       }
}

// handle railway landing
void handleRailwayLanding(GameplayState *game, int playerId)
{
       int position;
       int railwayId;
       int ownerId;

       position = game->players[playerId].position;
       railwayId = game->board[position].propertyId;
       ownerId = game->railways[railwayId].owner;

       printf("Railway: %s\n", game->railways[railwayId].name);

       printf("Purchase price: LKR %d\n", game->railways[railwayId].purchasePrice);

       if (ownerId == NO_OWNER)
       {
              if (shouldBuyRailway(game, playerId, railwayId) == 1)
              {
                     buyProperty(game, playerId, railwayId);
              }
              else
              {
                     printf("%s decided not to buy %s \n", game->players[playerId].name, game->railways[railwayId].name);

                     /* auction will add later*/
              }
       }

       else if (ownerId == playerId)
       {
              printf("%s already owns this railway.\n", game->players[playerId].name);
       }
       else
       {
              printf("This railway is owned by %s.\n", game->players[ownerId].name);

              payRailwayRent(game, playerId, railwayId);
       }
}

// handle utitlity landing
void handleUtilityLanding(GameplayState *game, int playerId, int diceValue)
{
       int position;
       int utilityId;
       int ownerId;

       position = game->players[playerId].position;
       utilityId = game->board[position].propertyId;
       ownerId = game->utilities[utilityId].owner;

       printf("Utility: %s\n", game->utilities[utilityId].name);

       printf("Purchase price: LKR %d\n", game->utilities[utilityId].purchasePrice);

       if (ownerId == NO_OWNER)
       {
              if (shouldBuyUtility(game, playerId, utilityId) == 1)
              {
                     buyUtility(game, playerId, utilityId);
              }
              else
              {
                     printf("%s decided not to buy %s \n", game->players[playerId].name, game->utilities[utilityId].name);

                     /* auction will add later*/
              }
       }
       else if (ownerId == playerId)
       {
              printf("%s already owns this utility.\n", game->players[playerId].name);
       }
       else
       {
              printf("This utility is owned by %s.\n", game->players[ownerId].name);

              payUtilityRent(game, playerId, utilityId, diceValue);
       }
}

void sendPlayerToJail(GameplayState *game, int playerId)
{
       game->players[playerId].position = 10; // change position to square 10
       game->players[playerId].inJail = 1;
       game->players[playerId].jailTurns = 0;

       printf("%s was sent to jail \n", game->players[playerId].name);

       printf("%s is now on square %d: %s\n", game->players[playerId].name, game->players[playerId].position, game->board[10].name);
}