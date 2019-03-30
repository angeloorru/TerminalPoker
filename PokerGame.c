//Simple C app for playing poker in terminal

#include<stdio.h>
#include<time.h>
#include<ctype.h>
#include<stdlib.h>

#define FALSE 0
#define TRUE 1

void printGreeting();
int getBet();
char getSuit(int suit);
char getRank(int rank);
void getFirstHand(int cardRank[], int cardsuit[]);
void getFinalHand(int cardRank[], int cardsuit[], int finalRank[], 
                  int finalSuit[], int ranksInHand[], int suitsInHand[]);
int analyseHand(int ranksInHand[], int suitsInHand[]);

int main()
{
    int bet;
    int bank = 10000;
    int i;
    int cardRank[5];
    int cardSuit[5];
    int finalRank[5];
    int finalSuit[5];
    int ranksInHand[13];
    int suitsInHand[4];
    int winnings;
    time_t t;
    char suit, rank, stillPlay;

    /*
     * Say hello... 
     */
    printGreeting();

    //Play a hand as many times you'd want to...
    do
    {
        bet = getBet();
        srand(time(&t));
        getFirstHand(cardRank, cardSuit);
        printf("Your five cards: \n");

        for (i = 0; i < 5; i++)
        {
            suit = getSuit(cardSuit[i]);
            rank = getRank(cardRank[i]);
            printf("Card #%d: %c%c\n", i+1, rank, suit);
        }

        // Figure out the value of the player's hand.
        // They must be zeroed out in case the user plays multiple hands
        for (i = 0; i < 4; i++)
        {
            suitsInHand[i] = 0;
        }
        for (i = 0; i < 13; i++)
        {
            ranksInHand[i] = 0;
        }

        getFinalHand(cardRank, cardSuit, finalRank, finalSuit, ranksInHand, suitsInHand);

        printf("Your five final cards: \n");

        for (i = 0; i < 5; i++)
        {
            suit = getSuit(finalSuit[i]);
            rank = getRank(finalRank[i]);
            printf("Card #%d: %c%c\n", i+1, rank, suit);
        }

        winnings = analyseHand(ranksInHand, suitsInHand);
        int winning = bet*winnings;
        printf("You won %d!!\n", winning);
        
        bank = bank-bet+(bet*winning);
        printf("\nYour bank is now %d.\n", bank);
        printf("Do you want to play again? ");
        
          printf("Bet is %d",bet);
        printf(" Bank is %d",bank);
        printf(" Winnings is %d", winning);
        
        scanf(" %c", &stillPlay);

        } while (toupper(stillPlay) == 'Y');
    return (0);
}

/****************************************************************/

// Print a quick greeting as well as tell the users the value of different winning hands

void printGreeting()
{
    printf("**********************************************************");
    printf("\n\n\tWelcome to Bello Casino !!\n\n ");
    printf("\tHome of video draw poker\n\n");
    printf("**********************************************************");

    printf("Here are the rules:\n");
    printf("You start with 10000 credits, and you make a bet from ");
    printf("1 to 5000 credits.\n");
    printf("You are dealt with 5 cards, and you then choose which card to keep or discard.\n");
    printf("\nHere is the table for the winnings (assuming a bet of 1 credit):\n");
    printf("Pair \t\t\t\t1 credit\n");
    printf("Two pairs\t\t\t2 credits\n");
    printf("Three of a kind\t\t\t3 credits\n");
    printf("Straight\t\t\t4 credits\n");
    printf("Flush\t\t\t\t5 credits\n");
    printf("Full house \t\t\t8 credits\n");
    printf("Four of a kind \t\t\t10 credits\n");
    printf("Straight flush \t\t\t20 credits\n");
    printf("\nHave fun!!\n\n");
}

// Deal with the first hand of cards
void getFirstHand(int cardRank[], int cardSuit[])
{
    int i,j;
    int cardDup;

    for(i = 0; i < 5; i++)
    {
        cardDup = 0;
        do {
            // card rank is one of the 13 (2-10, J,Q,K,A)
            cardRank[i] = (rand() %13);
            // card suit is one of 4
            // club, diamonds, heart, spade
            cardSuit[i] = (rand() %4);

            // Ensure each card is unique
            for (j = 0; j < i; j++)
            {
                if ((cardRank[i] == cardRank[j]) &&
                    (cardSuit[i] == cardSuit[j]))
                {
                    cardDup = 1;
                }
            }
        } while (cardDup == 1);
    }
}

// Change the suit integer value to a character that represents the suit
char getSuit(int suit)
{
    switch(suit)
    {
    case 0:
        return('c');
    case 1:
        return('d');
    case 2:
        return('h');
    case 3:
        return('s');
    }
}

// Change the rank integer value to a character that represents the rank
char getRank(int rank)
{
    switch (rank)
    {
    case 0:
        return('A');
    case 1:
        return('2');
    case 2:
        return('3');
    case 3:
        return('4');
    case 4:
        return('5');
    case 5:
        return('6');
    case 6:
        return('7');
    case 7:
        return('8');
    case 8:
        return('9');
    case 9:
        return('T');
    case 10:
        return('J');
    case 11:
        return('Q');
    case 12:
        return('K');
    }
}

// Function to get the user bet
int getBet()
{
    int bet;
    do
    {
        printf("How much do you want to bet? (enter a number ");
        printf("1 to 5000 or 0 to quit the game) : ");
        scanf(" %d", &bet);

        if (bet >=1 && bet <= 5000)
        {
            return(bet);
        }
        else if (bet == 0)
        {
            exit(1);
        }
        else
        {
            printf("\n\nPlease enter a bet from 1 to 5000 or 0 to quit the game.\n");
        }
    } while ((bet < 0) || (bet > 5000));
}

// View the final hand and determines the value of the hand
int analyseHand(int ranksInHand[], int suitsInHand[])
{
    int num_consec = 0;
    int i, rank, suit;
    int straight = FALSE;
    int flush = FALSE;
    int four = FALSE;
    int three = FALSE;
    int pairs = 0;

    for (suit = 0; suit < 4; suit++)

        if(suitsInHand[suit] == 5)
            flush = TRUE;
        rank = 0;
        while(ranksInHand[rank] == 0)
            rank++;
        for(; rank < 13 && ranksInHand[rank]; rank++)
            num_consec++;
        if(num_consec == 5){
            straight = TRUE;
        }
        for(rank = 0; rank < 13; rank++){
            if(ranksInHand[rank] == 4)
                four = TRUE;
            if(ranksInHand[rank] == 3)
                three = TRUE;
            if(ranksInHand[rank] == 2)
                pairs++;
        }

        if(straight && flush){
            printf("Straight flush!!\n\n");
            return(20);
        }
        else if(four){
            printf("Four of a kind!!\n\n");
            return(10);
        }
        else if(three && pairs == 1){
            printf("Full house!!\n\n");
            return(8);
        }
        else if(flush){
            printf("Flush!!\n\n");
            return(5);
        }
        else if(straight){
            printf("Straight!!\n\n");
            return(4);
        }
        else if(three){
            printf("Three of a kind!!\n\n");
            return(3);
        }
        else if(pairs == 2){
            printf("Two pairs!!\n\n");
            return(2);
        }
        else if(pairs == 1){
            printf("Pair\n\n");
            return(1);
        }
        else {
            printf("High card win!!\n\n");
            return(0);
        }
    }

    // Keep or change the cards
    void getFinalHand(int cardRank[], int cardSuit[], int finalRank[], int finalSuit[], 
        int ranksInHand[], int suitsInHand[])
    {
        int i, j, cardDup;
        char suit, rank, ans;

        for(i = 0; i < 5; i++)
        {
            suit = getSuit(cardSuit[i]);
            rank = getRank(cardRank[i]);
            printf("Do you want to keep card #%d: %c%c?", i+1, rank, suit);
            printf("\nPlease answer Y/N : ");
            scanf(" %c", &ans);
            if(toupper(ans) == 'Y')
            {
                finalRank[i] = cardRank[i];
                finalSuit[i] = cardSuit[i];
                ranksInHand[finalRank[i]]++;
                suitsInHand[finalSuit[i]]++;
                continue;
            }
            else if(toupper(ans) == 'N')
            {
                cardDup = 0;
                do{
                    cardDup = 0;
                    finalRank[i] = (rand() %13);
                    finalSuit[i] = (rand() %4);

                    // Check the five original cards to avoid duplications
                    for(j = 0; j < 5; j++)
                    {
                        if((finalRank[i] == cardRank[j]) &&
                            (finalSuit[i] == cardSuit[j]))
                        {
                            cardDup = 1;
                        }
                    }

                    // Now that we changed cards, check that there aren't any duplications in the new ones
                    for(j = 0; j < i; j++)
                    {
                        if((finalRank[i] == finalRank[j]) &&
                            (finalSuit[i] == finalSuit[j]))
                        {
                            cardDup = 1;
                        }
                    }
                } while (cardDup == 1);
            
                ranksInHand[finalRank[i]]++;
                suitsInHand[finalSuit[i]]++;
            }
        }
    }



