
#include<stdio.h>
#include <string.h>
#include <stralign.h>
#include"Application/app.h"

int main()
{
	appStart();
	return 0;
}
/*
project note 

these is payment application seperates into 4 stages each stage has functions 
which do specific instructons 

first stage is card moudle which make check if card holder name is correct or not
and PAN(primary acount number ) is correct or not then check the expire date of card 
store the data in struct ST_cardData_t

second stage is transaction stage which check if trans amount fit with max amount or not
and transaction date and compares it with card date if expired or not

third stage is server stage which check the account state block or running has good balance to make transaction or not
and save the transaction data 

fourth stage is application which run the payment application by integrates all functions 

 Ziad Elkholy...............................
*/