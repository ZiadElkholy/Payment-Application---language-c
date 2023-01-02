#include "card.h"
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<stddef.h>
#include<string.h>
 
#define Max_char 24 // MAX CHARACTERS
#define Min_char 20 // MIN CHARACTERS
#define Max_PAN  19 // MAX  NUMERIC CHARACTERS
#define Min_PAN  16  // MIN  NUMERIC CHARACTERS

//This function will ask for the cardholder's name and store it into card data.
//Cardholder name is 24 alphabetic characters string max and 20 min.
//If the cardholder name is NULL, less than 20 characters or more than 24 will return a WRONG_NAME error, else return CARD_OK.
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	uint8_t name[80];
	uint32_t i;
	scanf("%[^\n]%*c", &cardData->cardHolderName);
	if ((strlen(cardData->cardHolderName) == NULL) ||
		(strlen(cardData->cardHolderName) < 20) ||
		(strlen(cardData->cardHolderName) > 24))
	{
		//printf("WRONG_NAME\n");
		return WRONG_NAME;
	}
	else
	{
		//cardData->cardHolderName == name;
		//printf("CARD_OK\n");
		return CARD_OK;

	}
	/*
	// Entering name with symbol or number by mistake {0,1,..,9,/,*,+,-......}
	for (i = 0; i <= 24; i++)
	{
     if ((name[i]>65)&&(name[i] <90)&& ((name[i] > 97)&&(name[i] < 122)))
	 { 
	 // condition for check if it character or not 
	 //printf("Error Name,Write name again ");
	 return WRONG_NAME;
	 }
	}
	*/
}

// 05/25 FIVE CARACHTERS MM/YY
//If the card expiry date is NULL, less or more than 5 characters, 
//or has the wrong format will return the WRONG_EXP_DATE error, else return CARD_OK.
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)// look on expiration of card
{
	//uint32_t MM = 0, YY = 0;
	//uint32_t i = 0; // max 5 itrations
	printf("Please Enter the Card Expiration Date (MM/YY) ");
	scanf("%[^\n]%*c",&cardData->cardExpirationDate);
	//MM = (cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0');
	//YY = (cardData->cardExpirationDate[3] - '0') * 10 + (cardData->cardExpirationDate[4] - '0');
	
	if ((strlen(cardData->cardExpirationDate)== NULL) 
		|| (strlen(cardData->cardExpirationDate) <5 )
		|| (strlen(cardData->cardExpirationDate) > 5)
		|| (cardData->cardExpirationDate[2] != '/')
	    || (cardData->cardExpirationDate[0] == '2') //correct 02/20 - error 20/12
		|| (cardData->cardExpirationDate[0] == '3') 
		|| (cardData->cardExpirationDate[0] == '4')
		|| (cardData->cardExpirationDate[0] == '5')
		|| (cardData->cardExpirationDate[0] == '6')
		|| (cardData->cardExpirationDate[0] == '7')
		|| (cardData->cardExpirationDate[0] == '8')
		|| (cardData->cardExpirationDate[0] == '9')
		||((cardData->cardExpirationDate[0] == '1') // correct 12/20 // error 13/20
		&&((cardData->cardExpirationDate[1] == '3')
		|| (cardData->cardExpirationDate[1] == '4')
		|| (cardData->cardExpirationDate[1] == '5')
		|| (cardData->cardExpirationDate[1] == '6')
		|| (cardData->cardExpirationDate[1] == '7')
		|| (cardData->cardExpirationDate[1] == '8')
		|| (cardData->cardExpirationDate[0] == '9'))))// mounth not higher than 12
	{
		//printf("WRONG EXPIRATION DATE\n");
		return WRONG_EXP_DATE;
	}
	else 
	{
		//printf("CARD_OK\n");
		return CARD_OK;
	}
	
	
	/*else if ((MM >= 1 && MM <= 12) && (YY >= 0 && YY <= 99))
	{
		//printf("Expiration card date : %s\n ", cardData->cardExpirationDate);
		printf("OK");
		return CARD_OK;
	}
	else
	{
		
		printf("WRONG EXPIRATION DATE");
		return WRONG_EXP_DATE;
	}
	*/
	
}


//This function will ask for the card's Primary Account Number and store it in card data.
//PAN is 20 numeric characters string, 19 character max, and 16 character min.
//If the PAN is NULL, less than 16 or more than 19 characters, will return the WRONG_PAN error, else return CARD_OK.
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	//EN_cardError_t CARDpan = WRONG_PAN;
	uint32_t i = 0;
	uint8_t pan[50]={NULL};
	//printf("Please Enter the Card PAN ");
	//scanf("%[^\n]%*c",pan);
	/*
	while (pan[i] != NULL) 
	{
		i++;
	}
	for (i = 0; i <= 19; i++)
	{
		cardData->primaryAccountNumber[i] = pan[i];
	}
	*/
	if ((strlen(pan) >= Max_PAN) || (strlen(pan) <= Min_PAN) || (strlen(pan) == NULL))
	{
		//printf("WRONG PAN DATE\n");
		return WRONG_PAN;
	}
	else
	{
		//cardData->primaryAccountNumber == pan;
		//printf("CARD_OK\n");
		return CARD_OK;
	}
	cardData->primaryAccountNumber == "89893746154368511";
}
