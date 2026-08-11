#include <stdio.h>
#include "types.h"

int main(void)
{
    GameplayState game;

    initializeGameBoard(&game);
    initializePlayers(&game);

    printf("=== LOAN INTEREST TEST ===\n\n");

    /*
        Stable economy = 8% interest.
    */
    game.loanInterestRate = 8;

    /*
        Give Player 0 an active loan.
    */
    game.players[0].loanActive = 1;
    game.players[0].loanAmount = 1000;
    game.players[0].loanRoundsRemaining = 20;

    printf("BEFORE ROUND UPDATE\n");

    printf("Loan Amount: LKR %d\n",
           game.players[0].loanAmount);

    printf("Interest Rate: %d%%\n",
           game.loanInterestRate);

    printf("Rounds Remaining: %d\n\n",
           game.players[0].loanRoundsRemaining);


    /*
        End of round 1.
    */
    printf("=== AFTER ROUND 1 ===\n");

    updateLoanAfterRound(&game, 0);

    printf("\n");


    /*
        End of round 2.
    */
    printf("=== AFTER ROUND 2 ===\n");

    updateLoanAfterRound(&game, 0);

    printf("\n");


    /*
        Test a player without a loan.
    */
    printf("=== PLAYER WITHOUT LOAN ===\n");

    game.players[1].loanActive = 0;
    game.players[1].loanAmount = 0;
    game.players[1].loanRoundsRemaining = 0;

    updateLoanAfterRound(&game, 1);

    printf("Player 1 Loan Amount: LKR %d\n",
           game.players[1].loanAmount);

    printf("Player 1 Rounds Remaining: %d\n",
           game.players[1].loanRoundsRemaining);

    return 0;
}