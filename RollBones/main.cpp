/*
Program Name: Roll Bones
Date: 2022-9-16
Author: Ji Min Yoon
Module Purpose: To create that program that simulates a dice game with stakes and bets.
*/

#include <string>//   This is needed to use strings.
#include <stdio.h>//   This allows the user to press enter key once or twice.
#include <iostream>//  This contains all the functions of the program like cout, cin etc.
using namespace std;
int dice1;//   This is the value of dice 1.
int dice2;//   This is the value of dice 2.
int total;//   This is the value of dice 1 and dice 2 combined.
int stakeAmount;//   This is the total amount of money the user is willing to bet.
int bet;//   This is the amount of money the user is betting that round.
int rolls = 0;//   This is the counts the number of dice rolls.
/*   

This method uses the rand() method to produce two random numbers between 1 and 6 for dice1 and dice2,
 adds the two rolls together to find the total of the dice roll, and increase the value of rolls by one which counts how many
 times the dice has been thrown. 
   
   */
void rollDice()
{
    cout << "Press enter key once or twice to throw the dice" << endl;
    cin.ignore();
    cin.get();//   This allows the user to press enter twice.

    srand(time(0));//    This reseed the random number generation so that each run of the program has different throw results.
    dice1 = (rand() % 6) + 1;//   This generates number between 1-6.
    dice2 = (rand() % 6) + 1;
    total = dice1 + dice2;

    rolls++;//   Increases one each time the rollDice() method has been called to count how many times the player rolled the dice.
}
//   Prints the value of die 1, die 2, and two combined.
void printDiceVal()
{
    cout << "Die 01 is " << dice1 << endl;
    cout << "Die 02 is " << dice2 << endl;
    cout << "The dice throw results : " << total << " !\n"<<endl;
}
/*

  Has a parameter int point which takes in the value of the dice roll which wasn't a win or a loss
keep throwing the dice until the players gets the same value as point and win, or get the value of 7 and lose.

*/
void point(int point)
{
    for (int i = 0; i < 1; i++)//   The for loop is set to iterate one time.
    {
        cout << "\nThe point is " << point << endl;
        cout << "Throw em again and hope that luck's on your side!\n" << endl;

        rollDice();
        printDiceVal();

        if (point == total)//  This is the winning condition.
        {
            cout << "We've got ourselves a winner!" << endl;
            stakeAmount += bet;//   Increases the total money(stakeAmount) by bet when user wins.
        }
        else if (total == 7)//   This is the losing condition.
        {
            cout << "You lost :(" << endl;
            stakeAmount -= bet;//   Decreases the total money(stakeAmount) by bet when user loses.
        }
        else//  Allows the user to roll the dice again because user didnt win or lose; decrease the value i by one to make the for loop iterate one more time. 
        {
            i--;
        }
    }
}
//   Determines if the value of the roll dice are a win, loss, or a point.
void outcome(int total)
{
    
    if (total == 7 || total == 11)//  This is the winning condition.
    {
        cout << "We've got ourselves a winner!" << endl;
        stakeAmount += bet;//   Increases the total money(stakeAmount) by bet when user wins.
    }
    else if (total == 2 || total == 3 || total == 12)//   This is the losing condition.
    {
        cout << "You lost :(" << endl;
        stakeAmount -= bet;//   Decreases the total money(stakeAmount) by bet when the user loses.
    }
    else//   If the user doesn't win or lose, system will determine an outcome through point.
    {
        point(total);
    }
   
}
//   Allows the user to enter the total amount of money they want to bet.
void enterStakeAmount()
{
    do
    {
        cout << "What is your stake amount ? ";
        cin >> stakeAmount;//   Assigns the user input to the variable stakeAmount.

        if (stakeAmount <=0)//   Prints out a warning to enter a valid stake amount if the stake amount is below zero or zero. 
            cout << "\nYou must enter a 0 or positive amount of money to bet with. Try again! " << endl;
    } while (stakeAmount<=0);/*
    
    The do while makes sure the stake entered is above zero, if not the loop iterates again until the user
    input a valid amount.
    
    */
    cout << "\nCurrent Stake Amount : " << stakeAmount << endl;
}
//   Allows the user to enter the amount of money they want to bet that round.
void betAmount()
{
    cout << "\nWhat will you bet ? ";
    cin >> bet;//   Assigns the user input to the variable bet.
    cout << endl;//   This produces an extra blank line so the outcome looks neat.
}
//   Prints the end results of users performance.
void printEndResults()
{
    cout << "Roll Count : " << rolls << endl;//   Prints how many dice rolls they rolled.
    cout << "Final Stake Amount : " << stakeAmount << endl;//   Prints their initial stake amount plus what they earned/ lost.
    cout << "Press enter key once or twice once or twice to end..." << endl;
    cin.ignore();
    cin.get();//   Allows the user to press enter twice before ending program.
}
//   Prints outs different statement based on user input, and returns 1 if the bet amount is invalid and 0 if it is valid.
int betRange(int bet)
{
    if (bet > stakeAmount)//   If bet amount is higher than stakeAmount.
    {
        cout << "Bet amount too high. Try again!" << endl;
        return 1;//   Returns one if the bet amount is not valid.
    }
    
    if (bet < 0)//   If bet amount is negative.
    {
        cout << "Bet amount cannot be negative. Try again!" << endl;
        return 1;//   Returns one if the bet amount is not valid.
    }
    
    return 0;//   Returns zero if the bet amount is valid.
}
int main()
{
    bool gameStatus = true;
    enterStakeAmount();

  do
  {
        if (stakeAmount <= 0)//   If the stakeAmount reaches zero, the game automatically ends by breaking the loop.
        {
            cout << "Player ran out of money" << endl;
            break;
        }

        do
        {
            betAmount();
        } while ((betRange(bet)) != 0);//   Iterates the loop until the bet amount is valid.

       if (bet == 0)//   If the bet amount is  zero, the game ends by breaking the loop.
        {
           cout << "Player ends Game" << endl;
           break;
        }else//   Else the game continues normally.
        {
            rollDice();
            printDiceVal();
            outcome(total);
            cout << "Current Stake Amount : " << stakeAmount << endl;
        }

    }while (gameStatus);//   Iterates the loop forever until conditions break the loop.

    printEndResults();
}