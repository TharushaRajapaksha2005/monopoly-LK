#ifndef TYPES_H
#define TYPES_H

#define BOARD_SIZE 40
#define MAX_PLAYERS 4

#define MAX_PROPERTIES 22
#define MAX_RAILWAY 4
#define MAX_UTILITY 2

#define NO_OWNER -1
#define NO_ASSET -1

#define STARTING_CASH 30000

typedef enum
{
    START,
    PROPERTY,
    RAILWAY,
    UTILITY,
    EVENT,
    TAX,
    JAIL,
    FREE_PARKING,
    GO_TO_JAIL,
    BANK,
    INSURANCE
} SquareType;

typedef enum
{
    BROWN,
    LIGHT_BLUE,
    PINK,
    ORANGE,
    RED,
    YELLOW,
    GREEN,
    DARK_BLUE,
    NO_CLOUR
} PropertyGroup;

typedef enum
{
    AGGRESSIVE,
    CONSERVATIVE,
    RISK_TAKER,
    OPPORTUNISTIC
} PlayerStrategy;

typedef enum
{
    NO_INSURANCE,
    BASIC_INSURANCE,
    COMPREHENSIVE_INSURANCE,
    BUSINESS_INTERRUPTION_INSURANCE
} InsuranceType;

typedef struct
{
    int squareId;
    char name[30];
    SquareType type;
    int propertyId; // -1 if not a property
} BoardSquare;

typedef struct
{
    int propertyId;
    char name[30];

    PropertyGroup group;

    int purchasePrice;
    int currentMarketValue;
    int mortgageValue;
    int baseRent;

    int houseCost;
    int hotelCost;

    int owner;

    int mortgaged;

    int houses;
    int hotel;

} Property;

typedef struct
{
    int railwayId;
    char name[30];

    int purchasePrice;
    int currentMarketValue;
    int mortgageValue;

    int owner;
    int mortgaged;

} Railway;

typedef struct
{
    int utilityId;
    char name[30];

    int purchasePrice;
    int currentMarketValue;
    int mortgageValue;

    int owner;
    int mortgaged;

} Utility;

typedef enum
{
    BOC
} Bank;

typedef enum
{
    Sri_Lanka_Insurance,
    Ceylinco_Insurance
} Insurance;

typedef struct
{
    int playerId;
    char name[50];
    PlayerStrategy strategy;

    int cash;
    int position;

    int isbankrupt;

    int inJail;
    int jailTurns;

    int loanActive;
    int loanAmount;
    int loanRoundsRemaining;
    int loanInterestRate;

    /*tax not yet added */
} Player;

typedef struct
{
    BoardSquare board[BOARD_SIZE];

    Property properties[MAX_PROPERTIES];
    Railway railways[MAX_RAILWAY];
    Utility utilities[MAX_UTILITY];

    Player players[MAX_PLAYERS];

    int turnOrder[MAX_PLAYERS];
    int currentRound;

    float incomeTaxRate;
    float communityFundRate;

    int loanInterestRate;

    int inflationRate;
    int currentLoanInteresetRate;

    /*event and economy not yet added */

} GameplayState;

/*functions in board.c */

void initializeProperties(GameplayState *game);
void initializeRailways(GameplayState *game);
void initializeUtilities(GameplayState *game);
void initializeBoard(GameplayState *game);
void initializeGameBoard(GameplayState *game);

void movePlayer(GameplayState *game, int playerId, int diceValue);

void resolveLanding(GameplayState *game, int playerId, int diceValue);

void handlePropertyLanding(GameplayState *game, int playerId);
void handleRailwayLanding(GameplayState *game, int playerId);
void handleUtilityLanding(GameplayState *game, int playerId, int diceValue);

void sendPlayerToJail(GameplayState *game, int playerId);

/*functions in player.c */

void initializePlayers(GameplayState *game);

int shouldBuyProperty(GameplayState *game, int playerId, int propertyId);
int shouldBuyRailway(GameplayState *game, int playerId, int railwayId);
int shouldBuyUtility(GameplayState *game, int playerId, int utilityId);

int shouldBidProperty(GameplayState *game, int playerId, int propertyId, int currentBid);
int shouldBidRailway(GameplayState *game, int playerId, int railwayId, int currentBid);
int shouldBidUtility(GameplayState *game, int playerId, int utilityId, int currentBid);

int hasMonopoly(GameplayState *game, int playerId, PropertyGroup group);
int canBuildHouse(GameplayState *game, int playerId, int propertyId);
int canBuildHotel(GameplayState *game, int playerId, int propertyId);

void buildHouse(GameplayState *game, int playerId, int propertyId);
void buildHotel(GameplayState *game, int playerId, int propertyId);

int shouldBuildHouse(GameplayState *game, int playerId, int propertyId);
int shouldBuildHotel(GameplayState *game, int playerId, int propertyId);
void developMonopoly(GameplayState *game, int playerId, PropertyGroup group);

/*functions in game.c */

int rollDice(void);

void sortTurnOrder(int turnOrder[], int diceValues[], int start, int end);

void resolveTiedGroup(GameplayState *game, int start, int end);

void determineTurnOrder(GameplayState *game);

void playTurn(GameplayState *game, int playerId);

void handleJailTurn(GameplayState *game, int playerId);

void playRound(GameplayState *game);

/* functions in finance.c */
void buyProperty(GameplayState *game, int playerId, int propertyId);
void payPropertyRent(GameplayState *game, int playerId, int propertyId);

void buyRailway(GameplayState *game, int playerId, int railwayId);
int countOwnedRailways(GameplayState *game, int playerId);
void payRailwayRent(GameplayState *game, int playerId, int railwayId);

void buyUtility(GameplayState *game, int playerId, int utilityId);
int countOwnedUtilities(GameplayState *game, int playerId);
void payUtilityRent(GameplayState *game, int playerId, int utilityId, int diceValue);

int payJailBail(GameplayState *game, int playerId);

int calculatePropertyAssetValue(GameplayState *game, int playerId);
void payCommunityDevelopmentFund(GameplayState *game, int playerId);

void auctionProperty(GameplayState *game, int propertyId);
void auctionRailway(GameplayState *game, int railwayId);
void auctionUtility(GameplayState *game, int utilityId);

int mortgageProperty(GameplayState *game, int playerId, int propertyId);
int mortgageRailway(GameplayState *game, int playerId, int railwayId);
int mortgageUtility(GameplayState *game, int playerId, int utilityId);

int calculateCollateralValue(GameplayState *game, int playerId);
int calculateMaxLoan(GameplayState *game, int playerId);
int takeLoan(GameplayState *game, int playerId, int amount);
void updateLoanAfterRound(GameplayState *game, int playerId);

#endif
