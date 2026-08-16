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

typedef enum{
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

typedef enum{
    BROWN,
    LIGHT_BLUE,
    PINK,
    ORANGE,
    RED,
    YELLOW,
    GREEN,
    DARK_BLUE,
    NO_GROUP
} PropertyGroup;

typedef enum{
    AGGRESSIVE,
    CONSERVATIVE,
    RISK_TAKER,
    OPPORTUNISTIC
} PlayerStrategy;

typedef enum{
    NO_INSURANCE,
    BASIC_INSURANCE,
    COMPREHENSIVE_INSURANCE,
    BUSINESS_INTERRUPTION_INSURANCE
} InsuranceType;

typedef struct{
    int squareId;
    char name[50];
    SquareType type;
    int propertyId; 
} BoardSquare;

typedef struct{
    int propertyId;
    char name[30];

    PropertyGroup group;

    int purchasePrice;
    int currentMarketValue;
    int mortgageValue;
    int baseRent;
    int age;
    int depreciationPercent;

    int houseCost;
    int hotelCost;

    // for inflation and dynamic property market effetcs 
    int normalPurchasePrice;
    int normalMarketValue;
    int normalMortgageValue;
    int normalBaseRent;
    int normalHouseCost;
    int normalHotelCost;

    int owner;
    int mortgaged;

    int houses;
    int hotel;
    int houseCondition[4];
    int hotelCondition;
    int maintenanceIgnoredRounds;
    int structuralDamage; 
    int valueBeforeStructuralDamage; 

    int loanLocked;

    int damaged;

    InsuranceType insuranceType;
    int insuranceRoundsRemaining;

} Property;

typedef struct{
    int railwayId;
    char name[30];

    int purchasePrice;
    int currentMarketValue;
    int mortgageValue;

    int owner;
    int mortgaged;

    int loanLocked;

} Railway;

typedef struct{
    int utilityId;
    char name[50];

    int purchasePrice;
    int currentMarketValue;
    int mortgageValue;

    int owner;
    int mortgaged;

    int loanLocked;

} Utility;

typedef enum{
    TOURISM_BOOM,
    FUEL_CRISIS,
    HEAVY_MONSOON,
    ECONOMIC_RECESSION,
    STOCK_MARKET_BOOM,
    GOVERNMENT_HOUSING_PROGRAMME,
    FOREIGN_INVESTMENT,
    POLITICAL_UNREST
} NationalEvent;

typedef enum{
    NO_REGULATION,
    INCREASE_PROPERTY_TAX,
    REDUCE_LOAN_INTEREST,
    HOUSING_SUBSIDY,
    LUXURY_PROPERTY_TAX,
    RAILWAY_MODERNIZATION,
    ELECTRICITY_TARIFF_REVISION,
    INSURANCE_REGULATION,
    ANTI_SPECULATION_ACT
} GovernmentRegulation;

typedef enum{
    FIRE,
    FLOOD,
    RIOT,
    BUILDING_COLLAPSE,
    ELECTRICAL_FAILURE
} DisasterType;

typedef struct{
    int playerId;
    char name[50];
    PlayerStrategy strategy;

    int cash;
    int position;
    int completedLap;

    int isbankrupt;

    int inJail;
    int jailTurns;

    int loanActive;
    int loanAmount;
    int loanRoundsRemaining;
    int loanInterestRate;

} Player;

typedef struct{
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
    int repairCost;
    int insurancePremiumFactor;

    GovernmentRegulation currentGovRegulation;
    NationalEvent currentNationalEvent;

} GameplayState;

/*functions in board.c */

void initializeProperties(GameplayState *game);
void initializeRailways(GameplayState *game);
void initializeUtilities(GameplayState *game);
void initializeBoard(GameplayState *game);
void initializeGameBoard(GameplayState *game);
void initializeGameState(GameplayState *game);

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

int shouldPayJailBail(GameplayState *game, int playerId);

int hasMonopoly(GameplayState *game, int playerId, PropertyGroup group);
int canBuildHouse(GameplayState *game, int playerId, int propertyId);
int canBuildHotel(GameplayState *game, int playerId, int propertyId);
int shouldBuildHouse(GameplayState *game, int playerId, int propertyId);
int shouldBuildHotel(GameplayState *game, int playerId, int propertyId);
void developMonopoly(GameplayState *game, int playerId, PropertyGroup group);

void makeDevelopmentDecision(GameplayState *game, int playerId);
void makeInsuranceDecision(GameplayState *game, int playerId);
void handleBankLanding(GameplayState *game, int playerId);

int countOwnedInGroup(GameplayState *game, int playerId, PropertyGroup group);
int countTotalInGroup(GameplayState *game, PropertyGroup group);
void attemptPropertyTrade(GameplayState *game, int playerId);

int raiseMoney(GameplayState *game, int playerId, int amount);

int hasDevelopmentOppertunity(GameplayState *game, int playerId);

/*functions in game.c */

int rollDice(void);
void sortTurnOrder(int turnOrder[], int diceValues[], int start, int end);
void resolveTiedGroup(GameplayState *game, int start, int end);
void determineTurnOrder(GameplayState *game);
void playTurn(GameplayState *game, int playerId);

int handleJailTurn(GameplayState *game, int playerId);

int isGameRoundComplete(GameplayState *game);
void completeGameRound(GameplayState *game);

void playTurnCycle(GameplayState *game);

void updatePropertyAge(GameplayState *game);

void updateBuildingCondition(GameplayState *game);
int getPropertyBuildingCondition(GameplayState *game, int propertyId);
void declareBankrupt(GameplayState *game, int playerId);
int hasAssets(GameplayState *game, int plyaerId);

int countSolventPlayers(GameplayState *game);

int calculateNetWorth(GameplayState *game, int playerId);
int findWinner(GameplayState *game);
void printGameResult(GameplayState *game);
void printRoundSummary(GameplayState *game);
void startGame(void);


/* functions in finance.c */
void buyProperty(GameplayState *game, int playerId, int propertyId);
void payPropertyRent(GameplayState *game, int playerId, int propertyId);

void buyRailway(GameplayState *game, int playerId, int railwayId);
int countOwnedRailways(GameplayState *game, int playerId);
void payRailwayRent(GameplayState *game, int playerId, int railwayId);

void buyUtility(GameplayState *game, int playerId, int utilityId);
int countOwnedUtilities(GameplayState *game, int playerId);
void payUtilityRent(GameplayState *game, int playerId, int utilityId, int diceValue);

int calculateTotalPropertyValue(GameplayState *game, int playerId);
void payCommunityDevelopmentFund(GameplayState *game, int playerId);
int calculateIncomeTax(GameplayState *game, int playerId);
void payIncomeTax(GameplayState *game, int playerId);

void auctionProperty(GameplayState *game, int propertyId);
void auctionRailway(GameplayState *game, int railwayId);
void auctionUtility(GameplayState *game, int utilityId);

int buildHouse(GameplayState *game, int playerId, int propertyId);
int buildHotel(GameplayState *game, int playerId, int propertyId);

int mortgageProperty(GameplayState *game, int playerId, int propertyId);
int mortgageRailway(GameplayState *game, int playerId, int railwayId);
int mortgageUtility(GameplayState *game, int playerId, int utilityId);

int calculateCollateralValue(GameplayState *game, int playerId);
int lockLoanCollateral(GameplayState *game, int playerId, int loanAmount);
void unlockLoanCollateral(GameplayState *game, int playerId);

int calculateMaxLoan(GameplayState *game, int playerId);
int takeLoan(GameplayState *game, int playerId, int amount);
void updateLoanAfterRound(GameplayState *game, int playerId);
int repayLoan(GameplayState *game, int playerId, int amount);
int increaseLoan(GameplayState *game, int playerId, int extraAmount);
void handleLoanDefault(GameplayState *game, int playerId);

int buyInsurance(GameplayState *game, int playerId, int propertyId, InsuranceType type);
void updateInsuranceAfterRound(GameplayState *game);

int repairProperty(GameplayState *game, int propertyId);
void maintainProperty(GameplayState *game, int playerId, int propertyId);
void performMaintenance(GameplayState *game, int playerId);
void updateMaintenanceNeglect(GameplayState *game);
int repaireStructuralDamage(GameplayState *game, int playerId, int propertyId);
int repaireProperty(GameplayState *game, int playerId, int propertyId);

/* functions in events.c*/
void triggerDisaster(GameplayState *game);
void applyInflation(GameplayState *game);
void triggerGovRegulation(GameplayState *game);

#endif