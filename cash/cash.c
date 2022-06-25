#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    /*
    Implement get_cents in such a way that the function prompts the user for a number of cents using get_int and then returns that number as an int. If the user inputs a negative int, your code should prompt the user again. (But you don’t need to worry about the user inputting, e.g., a string, as get_int will take care of that for you.) Odds are you’ll find a do while loop of help, as in mario.c!
    */
    do {
        int cents = get_int("Enter number of cents > ");
    } while(cents < 0);
    return cents;
}

int calculate_quarters(int cents)
{
    /*
    Implement calculate_quarters in such a way that the function calculates (and returns as an int) how many quarters a customer should be given if they’re owed some number of cents. For instance, if cents is 25, then calculate_quarters should return 1. If cents is 26 or 49 (or anything in between, then calculate_quarters should also return 1. If cents is 50 or 74 (or anything in between), then calculate_quarters should return 2. And so forth.
    */
    return cents / 25;
}

int calculate_dimes(int cents)
{
    return cents / 10;
}

int calculate_nickels(int cents)
{
    return cents / 5;
}

int calculate_pennies(int cents)
{
    return cents;
}
