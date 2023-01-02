#include"app.h"
f32 max;
EN_cardError_t correct;
EN_terminalError_t term;
EN_transState_t trans;

ST_cardData_t cardData;
ST_terminalData_t termData;
ST_transaction_t transData;
void appStart(void) // Starting Function
{
	printf("\t\t\t\t\t Welcome To The Server\n\n");

	//////////////////////////////CARD FUNCTION TEST/////////////////////////
	printf("---->CARD DATA\n");
	// Card holder name test function
	printf("please Enter Card holder name: ");
	uint8_t name[80];
	correct = getCardHolderName(name);
	while (correct == WRONG_NAME)
	{
		// when card holder name wrong will return wrong and ask again
		printf("\nPlease enter Card Holder Name again ");
		correct = getCardHolderName(&cardData);
	}

	// Card expiry date  test function
	correct = getCardExpiryDate(&cardData);
	while (correct == WRONG_EXP_DATE)
	{
		printf("enter expiry date again \n");
		correct = getCardExpiryDate(&cardData);
	}

	// Card PAN  test function
	correct = getCardPAN(&cardData);
	while (correct == WRONG_PAN)
	{
		printf("\n enter PAN again  \n");
		correct = getCardPAN(&cardData);
	}


	///////////////////// TRANSACTION FUNCTION TEST ///////////////////////////////////
	printf("---->TRANSACTION DATA\n");
	// transiction date test function
	term = getTransactionDate(&termData);

	while (term == WRONG_DATE)
	{
		printf("\n enter Transaction date again \n");
		term = getTransactionDate(&termData);
	}

	// Card expiration and transaction date test function
	term = isCardExpired(&cardData, &termData);
	//if (term = EXPIRED_CARD)
	  // {
		//exit(0); // will close the transaction operation
	   //}
	// Set Max Amount test first
	printf("Please Enter Max Amount Transaction ");
	scanf("%f", &max);
	term = setMaxAmount(&termData, max);
	while (term == INVALID_MAX_AMOUNT)
	{
		printf(" \nEnter Max Amount again \n");
		scanf("%f", &max);
		term = setMaxAmount(&termData, max);
		//break;
	}

	// Transaction Amount
	term = getTransactionAmount(&termData);
	while (term == INVALID_AMOUNT)
	{

		printf("\nEnter Amount again\n");
		term = getTransactionAmount(&termData);
	}

	// Test Amount is below max or not
	term = isBelowMaxAmount(&termData);










	///////////////////////////////// Transaction Test/////////////////////////////////
	//uint8_t ref[50] = { NULL };
	//printf("Please Enter Acount refrence ");
	//scanf("%[^\n]%*c", ref);
	//isValidAccount(&cardData, ref);


	//saveTransaction(&transData);

	//printf("\t\t--------------------------------------------------------------------------------------------------------\n");

	transData.cardHolderData = cardData;
	transData.terminalData = termData;

	trans = recieveTransactionData(&transData);

	if (trans == DECLINED_STOLEN_CARD)
	{
		printf("\n DECLINED_STOLEN_CARD/INVALID\n");
	}
	else if (trans == DECLINED_INSUFFECIENT_FUND) {
		printf("\nDECLINED_INSUFFECIENT_FUND\n");
	}
	else if (trans == FRAUD_CARD)
	{
		printf("\n FRAUD_CARD \n");
	}
	else if (trans == APPROVED)
	{
		printf("\n Approved  \n");
	}
	printf("\t\t--------------------------------------------------------------------------------------------------------\n");



	/*
	/**************************SERVER FUNCTION TEST***************
	//isValidAccounttest();
	//isBlockedAccounttest();
	//isAmountAvailabletest();
	//saveTransactiontest();
	//printf("\t\t--------------------------------------------------------------------------------------------------------\n");
	//listSavedTransactions();
	*/


	/*
		stories
		1- As a bank customer have an account and has a valid and not expired card,
		I want to withdraw an amount of money less than the maximum allowed and less than or equal to the amount in my balance,
		so that I am expecting that the transaction is approved and my account balance is reduced by the withdrawn amount.


		2- As a bank customer have an account, that has a valid and not expired card,
		I want to withdraw an amount of money that exceeds the maximum allowed amount so
		that I am expecting the transaction declined.


		3-As a bank customer have an account and a valid but expired card,
		I want to withdraw an amount of money so that I expect that the transaction declined.

		4-As a bank customer have an account and has a valid and not expired but stolen card,
		I want to block anyone from using my card so that I am expecting that any transaction made by this card is declined.

		5-As a bank customer have an account and a valid but expired card,
		I want to withdraw an amount of money so that I expect that the transaction declined.


		*/




	printf("\n\n\t\t\t\t\t Thanks For Using The Server\n ");
	printf("\t\t\t\t\t\t Ziad Elkholy \n");



















}
