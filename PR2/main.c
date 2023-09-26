#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void checkCasinoFund(int balance, int bet){
    unsigned int casinoFund = balance + bet;
    if (casinoFund > 2147483647){
        printf("You're very lucky, so you got thrown out of the casino!");
        exit(0);
    }
}

int main() {
    srand(time(NULL));

    int bet = 0;
    int balance = 10000;
    int lengthOfSlots = 3;
    int choice = 0;

    printf("Welcome to the 'One-Armed Bandit' game!\n");

    while(1){

        printf("|Balance: %10d |\n", balance);
        printf("|1.Play              |\n");
        printf("|2.Exit              |\n");
        printf("|=>");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                {
                    if (balance == 0) {
                        printf("You don't have enough money\n");
                        break;
                    }

                    while (1){
                        printf("Enter your bet: ");
                        if(scanf("%d", &bet) != 1){
                            printf("Wrong bet. Try again!\n");
                            getchar();
                        }else if (bet <= 0) {
                            printf("Wrong bet. Try again!\n");
                        }else{
                            break;
                        }
                    }

                    if (bet > balance) {
                        printf("The bet exceeds your balance. Your balance: %d\n", balance);
                        break;
                    }else if(bet == balance){
                        printf("ALL IN!\n");
                    }

                    int randomNumbers[lengthOfSlots];
                    int i, j;
                    printf("|=> ");
                    for (i = 0; i < lengthOfSlots; i++) {
                        randomNumbers[i] = rand() % 9 + 1;
                        printf("%d ", randomNumbers[i]);
                    }
                    printf("<=|\n");

                    int matchingCount = 0;
                    int sevenCount = 0;
                    for (i = 0; i < lengthOfSlots; i++) {
                        if (randomNumbers[i] == 7) {
                            sevenCount++;
                        }
                        for (j = i + 1; j < lengthOfSlots; j++) {
                            if (randomNumbers[i] == randomNumbers[j]) {
                                matchingCount++;
                            }
                        }
                    }

                    if (sevenCount == lengthOfSlots) {
                        printf("You win %d!\n", bet * 3);
                        bet = bet * 3;
                    }else if(sevenCount > 0){
                        printf("You win %d!\n", bet);
                    }else if (matchingCount == lengthOfSlots) {
                        printf("You win %d!\n", bet * 2);
                        bet = bet * 2;
                    } else if (matchingCount > 0) {
                        printf("You win %d!\n", bet);
                    } else {
                        printf("You lose %d!\n", bet);
                        balance -= bet;
                        continue;
                    }

                    checkCasinoFund(balance, bet);
                    balance += bet;

                }
                break;
            case 2:
                printf("Good luck");
                return 0;
            default:
                printf("Unknown command, try again\n");
                getchar();
                break;
        }
    }

}

