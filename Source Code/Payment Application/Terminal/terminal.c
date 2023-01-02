#include"terminal.h"
#include<time.h>
#include<stdio.h>
#include<stralign.h>
//This function will ask for the transaction dateand store it in terminal data.
//Transaction date is 10 characters string in the format DD / MM / YYYY, e.g 25 / 06 / 2022.
//25/06/2022 10 characters 
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	//uint8_t ter_error[12] = { NULL };
	//uint32_t DD = 0, MM = 0, YY = 0;
	//uint32_t i = 0; // max 10 itrations
	/*
	for (i = 0; i < 11; i++)
	{
		termData->transactionDate[i] = NULL;
	}
	*/
	printf("Please Enter the Transaction Date (DD/MM/YYYY) ");

	scanf("%[^\n]%*c", &termData->transactionDate);
	//DD = (termData->transactionDate[0] - '0') * 10 + (termData->transactionDate[0] - '0');
   //MM = (termData->transactionDate[3] - '0') * 10 + (termData->transactionDate[4] - '0'); // for comparison between transiction date and card expire
	//YY = (termData->transactionDate[6] - '0') * 1000 + (termData->transactionDate[7] - '0') * 100
		//+ (termData->transactionDate[8] - '0') * 10 + (termData->transactionDate[9] - '0');

	if ((strlen(termData->transactionDate) == NULL) 
		|| (strlen(termData->transactionDate) < 10 )
		|| (strlen(termData->transactionDate) > 10)
		|| (termData->transactionDate[2] != '/') 
		|| (termData->transactionDate[5] != '/')
		|| (termData->transactionDate[0] == '4') // error day ex = 40
		|| (termData->transactionDate[0] == '5')
		|| (termData->transactionDate[0] == '6')
		|| (termData->transactionDate[0] == '7')
		|| (termData->transactionDate[0] == '8')
		|| (termData->transactionDate[0] == '9')
		|| (termData->transactionDate[3] == '2')
		|| (termData->transactionDate[3] == '3')
		|| (termData->transactionDate[3] == '4')
		|| (termData->transactionDate[3] == '5')
		|| (termData->transactionDate[3] == '6')
		|| (termData->transactionDate[3] == '7')
		|| (termData->transactionDate[3] == '8')
		|| (termData->transactionDate[3] == '9')
		||((termData->transactionDate[3] == '1')&&(termData->transactionDate[4] == '3')) // 13 error 
		||((termData->transactionDate[3] == '1') && (termData->transactionDate[4] == '4'))
		||((termData->transactionDate[3] == '1') && (termData->transactionDate[4] == '5'))
		||((termData->transactionDate[3] == '1') && (termData->transactionDate[4] == '6'))
		|| ((termData->transactionDate[3] == '1') && (termData->transactionDate[4] == '7'))
		|| ((termData->transactionDate[3] == '1') && (termData->transactionDate[4] == '8'))
		|| ((termData->transactionDate[3] == '1') && (termData->transactionDate[4] == '9')))
	{
		//printf("WRONG Transaction DATE\n");
		return WRONG_DATE;
	}
	else 
	{
		//printf("Terminal OK\n");
		return TERMINAL_OK;
	}

	/*else if ((DD < 1 && DD>31) && (MM < 1 && MM > 12) && (YY < 2003)) // Enter any day or mounth by mistake 
	{
		return WRONG_DATE;
	}
	else
	{
		printf("Date is : %s", ter_error);
		return TERMINAL_OK;
	}
*/	
}
//If the card expiration date is before the transaction date will return EXPIRED_CARD, else return TERMINAL_OK
	EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
	{

		uint32_t MM_tran, YY_tran, MM_card, YY_card;
		// transaction date
		MM_tran = ((termData->transactionDate[3] - '0') * 10) + ((termData->transactionDate[4] - '0'));
		YY_tran = (termData->transactionDate[8] - '0') * 10 + (termData->transactionDate[9] - '0'); // last two number from year of transaction 
		// Card expire date
		MM_card = (cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[0] - '0');
		YY_card = (cardData->cardExpirationDate[3] - '0') * 10 + (cardData->cardExpirationDate[4] - '0');
		if ((YY_card > YY_tran))
		{
			//printf("\nCard OK\n");
			return TERMINAL_OK;
		}
		else if (((MM_card < MM_tran) && (YY_card == YY_tran)) || (YY_card < YY_tran))
		{
			//printf("\nCard expierd\n");
			printf("Expierd from %d year", abs((YY_tran - YY_card)));
			return EXPIRED_CARD;
		
		}
		/*
		else
		{
			printf("Card OK");
			return TERMINAL_OK;
		}
		*/
	}
	
	//If the transaction amount is less than or equal to 0 will return INVALID_AMOUNT, else return TERMINAL_OK.
	EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
	{
		f32 a;//amount 
		printf("The Amount = ");
		scanf("%f", &a);
		if (a <= 0)
		{
			//printf("\nInvalid Amount\n");
			return INVALID_AMOUNT;
		}
		else
		{
			
			termData->transAmount = a;
			//printf("\nAmount of transaction = %f\n",a);
			return TERMINAL_OK;
		}
	}
	
	
	
	//This function takes the maximum allowed amount and stores it into terminal data.
	//If transaction max amount less than or equal to 0 will return the INVALID_MAX_AMOUNT error, else return TERMINAL_OK.
	EN_terminalError_t setMaxAmount(ST_terminalData_t* termData,float maxAmount)
	{
	
		if (maxAmount <= 0)
		{
			//printf("\nInvalid Max Amount\n");
			return INVALID_MAX_AMOUNT;
		}
		else 
		{
			//printf("\nValid Max Amount\n");
			termData->maxTransAmount = maxAmount;
			printf("\nMaxAmount of transaction = %f\n", maxAmount);
			return TERMINAL_OK;
		}
	}
	
	//If the transaction amount is larger than the terminal max allowed amount will return EXCEED_MAX_AMOUNT, else return TERMINAL_OK.
	EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
	{
		if ((termData->transAmount)>(termData->maxTransAmount))
		{
			//printf("\nExcess MAX Amount\n");
			return EXCEED_MAX_AMOUNT;
	    }
		else
		{
			//printf("\nBelow MAX Amount\n");
			return TERMINAL_OK;
		}
	}

