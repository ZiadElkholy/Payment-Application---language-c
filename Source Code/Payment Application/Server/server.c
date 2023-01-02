#include"server.h"
#include <string.h>
#include<stdio.h>
//Create a global array of ST_accountsDB_t for the valid accounts database.
//ST_accountsDB_t accountsDB[255];
//Fill in the array initially with any valid data.
//This array has a maximum of 255 element / account data.
//You can fill up to 10 different accounts for the sake of testing.
//Example of a running account : {2000.0, RUNNING, "8989374615436851"}.
//Example of a blocked account, its card is stolen : {100000.0, BLOCKED, "5807007076043875"}.

static uint32_t ref;
uint32_t s = 0;// sequance
ST_accountsDB_t accountsDB[255] =
{

{ 2000,RUNNING,"898937461543685111"},//0
{ 2000,RUNNING,"498946461543685133"},//1
{ 1050,RUNNING,"598937461543685164"},//2
{ 2055,RUNNING,"498946461543685195"},//3
{ 2300,RUNNING,"498946461543685126"},//4
{ 2000,RUNNING,"498946461543685157"},//5
{ 3000,BLOCKED,"398947461543685118"},//6
{ 1200,BLOCKED,"198947461543685239"},//7
{ 3200,BLOCKED,"798947477543685142"},//8
{ 1111,RUNNING,"798944461543685151"},//9
};
ST_accountsDB_t* accp = 0;

//create a global array of ST_transaction_t.
//Fill in the array initially with Zeros.
//This array has a maximum of 255 element / transaction data.

struct ST_transaction_t transactiondata[255] = { 0 };
static ST_transaction_t  transData;
static uint32_t cou = 1;

//This function will take all transaction data and validate its data, it contains all server logic.
//It checks the account detailsand amount availability.
//If the account does not exist return FRAUD_CARD ..
//if the amount is not available will return DECLINED_INSUFFECIENT_FUND..
//if the account is blocked will return DECLINED_STOLEN_CARD,
//if a transaction can't be saved will return INTERNAL_SERVER_ERROR ,
//else returns APPROVED.
//It will update the database with the new balance.
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{

	if (isValidAccount(&transData->cardHolderData, &accountsDB[ref]) == ACCOUNT_NOT_FOUND)
	{
		transData->transState = FRAUD_CARD;
		saveTransaction(transData);
		return FRAUD_CARD;
	}
	else if (isAmountAvailable(&transData->terminalData, &accountsDB[ref]) == LOW_BALANCE)
	{
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		saveTransaction(transData);
		return DECLINED_INSUFFECIENT_FUND;
	}
	else if (isBlockedAccount(&accountsDB[ref]) == BLOCKED_ACCOUNT)
	{
		transData->transState = DECLINED_STOLEN_CARD;
		saveTransaction(transData);
		return DECLINED_STOLEN_CARD;
	}
	else if (saveTransaction(transData) == SAVING_FAILED)
	{
		transData->transState = INTERNAL_SERVER_ERROR;
		saveTransaction(transData);
		return INTERNAL_SERVER_ERROR;
	}
	else
	{

		printf("Your new balance in the account=%f", ((accountsDB[ref].balance) - (transData->terminalData.transAmount)));
		return APPROVED;
	}
}

//This function will take card data and validate if the account related to this card exists or not.
//It checks if the PAN exists or not in the server's database (searches for the card PAN in the DB).
//If the PAN doesn't exist will return ACCOUNT_NOT_FOUND and the account reference will be NULL,
//else will return SERVER_OK and return a reference to this account in the DB.
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
	accp = 0;
	if (cardData == NULL)
	{
		printf("Account not valid\n");
		return ACCOUNT_NOT_FOUND;
	}
	for (uint32_t i = 0; i < 10; i++)
	{
		if (strcmp((cardData->primaryAccountNumber), (accountsDB[i].primaryAccountNumber)) == 0)
		{
			//accountRefrence->balance = accountsDB[i].balance;
			ref = i;
			//strncpy_s(accountRefrence->primaryAccountNumber,20, accountsDB[i].primaryAccountNumber,_TRUNCATE);
			//accountRefrence->state = accountsDB[i].state;
			accountRefrence = &(accountsDB[i]);

			accp = accountRefrence;
			printf("Acount is valid : %s\n", cardData->primaryAccountNumber);
			return SERVER_OK;

		}


	}


	{
		accountRefrence = NULL;
		printf("#Account not found\n");
		return ACCOUNT_NOT_FOUND;
	}

}



//This function takes a reference to the account into the databaseand verifies if it is blocked or not.
//If the account is running it will return SERVER_OK,
//else if the account is blocked it will return BLOCKED_ACCOUNT.
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	if (accountRefrence->state == RUNNING)
	{
		return SERVER_OK;
	}
	else if (accountRefrence->state == BLOCKED)
	{
		return BLOCKED_ACCOUNT;
	}
}


//This function will take terminal dataand a reference to the account in the databaseand check if the account has a sufficient amount to withdraw or not.
//It checks if the transaction's amount is available or not.
//If the transaction amount is greater than the balance in the database will return LOW_BALANCE,
//else will return SERVER_OK.
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	if (termData->transAmount > accountRefrence->balance)
	{
		return LOW_BALANCE;
	}
	else
	{
		return SERVER_OK;
	}
}

//This function will store all transaction data in the transactions database.
//It gives a sequence number to a transaction, this number is incremented once a transaction is processed into the server, you must check the last sequence number in the server to give the new transaction a new sequence number.
//It saves any type of transaction, APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR.
//It will list all saved transactions using the listSavedTransactions function.
//Assuming that the connection between the terminaland server is always connected, then it will return SERVER_OK.

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	if (s >= 255)
	{
		printf("SAVING FAILED");
		return SAVING_FAILED;
	}
	else
	{
		//s=cou-1;
		transData->transactionSequenceNumber = s;
		// holder name
		//printf("\nplease Enter Card holder name\n ");
		//scanf("%[^\n]%*c",& transData->cardHolderData.cardHolderName);
		strcpy(transactiondata[s].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);

		// expiration date
		//printf("\nplease Enter Card Expiration date\n ");
		//scanf("%[^\n]%*c", &transData->cardHolderData.cardExpirationDate);
		strcpy(transactiondata[s].cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate);

		//Card pan
		//printf("\nplease Enter Card PAN\n  ");
		//scanf("%[^\n]%*c", &transData->cardHolderData.primaryAccountNumber);
		strcpy(transactiondata[s].cardHolderData.primaryAccountNumber, transData->cardHolderData.primaryAccountNumber);

		//Transaction date
		//printf("\nplease Transaction date\n ");
		//scanf("%[^\n]%*c", &transData->terminalData.transactionDate);
		strcpy(transactiondata[s].terminalData.transactionDate, transData->terminalData.transactionDate);

		//Transaction Max amount
		//printf("\nplease enter Max allowable amount\n ");
		//scanf("%[^\n]%*c", &transData->terminalData.maxTransAmount);
		transactiondata[s].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;

		//Transaction amount
		//printf("\nplease enter amount\n ");
		//scanf("%[^\n]%*c", &transData->terminalData.transAmount);
		transactiondata[s].terminalData.transAmount = transData->terminalData.transAmount;

		//transactiondata[s].transactionSequenceNumber = transData->transactionSequenceNumber;
		transData->transactionSequenceNumber = s;
		transactiondata[s].transState = transData->transState;
		//s++;
		listSavedTransactions();
		return SERVER_OK;
	}
}

void listSavedTransactions(void)
{
	transactiondata;
	printf("Card Holder Name: %s \n", transactiondata[s - 1].cardHolderData.cardHolderName);
	printf("Card PAN:  %s \n", transactiondata[s - 1].cardHolderData.primaryAccountNumber);
	printf("Card Expiration Date:  %s \n", transactiondata[s - 1].cardHolderData.cardExpirationDate);

	printf("Transaction Date:  %s \n", transactiondata[s - 1].terminalData.transactionDate);
	printf("Transaction Amount:  %f \n", transactiondata[s - 1].terminalData.transAmount);
	printf("Transaction Max Amount:  %f \n", transactiondata[s - 1].terminalData.maxTransAmount);


	printf("Transaction SequenceNumber:  %d \n", s/* transactiondata[s].transactionSequenceNumber*/);
	printf("Transaction state:  %d \n", transactiondata[s - 1].transState);

}

void isValidAccounttest(void)
{
	ST_cardData_t cardData;
	ST_terminalData_t termData;
	//ST_terminalData_t pan;
	uint8_t pan[20];
	//ST_accountsDB_t ref;
	uint32_t Compare = 0;

	printf("\nTester Name : Ziad Ahmed\n");
	printf("Function Name : isValidAccount\ntest \"198947461543685239\" \n");

	printf("please Enter Card PAN ");
	scanf("%[^\n]%*c", &pan);

	//printf("\nChoose Case ");
	//uint32_t n;
//	scanf("%d",&n);
	//switch(n)
	//{
	uint32_t i;
	//case 1:

		//printf("\nFirst case - Account number you entered is  %s\n",pan);
	Compare = strcmp((accountsDB[7].primaryAccountNumber), pan);
	if (Compare == 0)
	{

		//for ( i=0; i <10; i++)
		//{
		//}

		printf("OK Card \n");
	}

	else //(Compare != 0)
	{
		//if (accountsDB[i].state == RUNNING)
		printf("Not Valid Card ");
	}
	//if(accountsDB[i].state==RUNNING)
// if (Compare == 0)
 //{
 //}
	  //  break;
 //case 2:
	 //printf("\nSecond- Account number %s\n",pan);
	 //for (i = 0; i < 10; i++)
	 //{
		 //Compare = strcmp(accountsDB[i].primaryAccountNumber, pan);
	 //}


	 //break;

 //}


 //getCardPAN(&termData);
 //uint32_t accountRefrence;
 //printf("Please Enter Acount Refrence ");
 //scanf("%d",&accountRefrence);
 //printf("Please Enter Acount PAN ");
 //scanf("%s", &cardData);
 //printf("Enter PAN account \n");
 //scanf("%d", &pan);
 //printf("Enter Refrence account \n");
 //scanf("%d",&termData);
 //printf("Enter PAN account \n");
 //scanf("%S", &pan);
 //isValidAccount(&termData, &ref);
}



void isBlockedAccounttest(void)
{
	ST_cardData_t cardData;
	ST_terminalData_t termData;
	uint8_t pan[20];
	uint32_t Compare = 0;

	printf("\nTester Name : Ziad Ahmed\n");
	printf("Function Name : isblockedAccount\n");

	printf("please Enter Card PAN ");
	scanf("%[^\n]%*c", &pan);
	printf("\nChoose Case ");
	uint32_t n;
	scanf("%d", &n);
	switch (n)
	{
	case 1:
		printf("test account 198947461543685239\n");
		if (accountsDB[8].state == BLOCKED)
		{

			printf("Card BLOCKED \n");
		}

		else if (accountsDB[8].state == RUNNING)
		{
			printf("Account RUNNING ");
		}
		break;
	case 2:
		printf("test account 498946461543685126\n");
		if (accountsDB[4].state == BLOCKED)
		{

			printf("Card BLOCKED \n");
		}

		else if (accountsDB[4].state == RUNNING)
		{
			printf("Account RUNNING ");
		}

		break;

	}
}


void isAmountAvailabletest(void)
{
	ST_cardData_t cardData;
	ST_terminalData_t termData;
	uint8_t pan[20];
	uint32_t Compare = 0;

	printf("\nTester Name : Ziad Ahmed\n");
	printf("Function Name : isAmountAvailable\n");

	printf("please Enter Card PAN ");
	scanf("%[^\n]%*c", &pan);
	printf("Enter transaction amount \n");
	f32 tran;
	scanf("%f", &tran);
	printf("\nChoose Case ");
	uint32_t n;
	scanf("%d", &n);
	switch (n)
	{
	case 1:
		printf("test account 798944461543685151\n");
		if (accountsDB[9].balance >= tran)
		{

			printf("valid transaction \n");
		}

		else
		{
			printf("invalid transaction ");
		}
		break;

	case 2:
		printf("test account 498946461543685126\n");
		if (accountsDB[4].balance >= tran)
		{

			printf("valid transaction \n");
		}

		else
		{
			printf("invalid transaction ");
		}

		break;

	}
}


void saveTransactiontest(void)
{
	ST_cardData_t cardData;
	ST_terminalData_t termData;
	ST_transaction_t* tran;

	printf("\nTester Name : Ziad Ahmed\n");
	printf("Function Name : save transaction\n");

	if (s >= 255)
	{
		printf("SAVING FAILED");
		return SAVING_FAILED;
	}
	else
	{
		//s=cou-1;
		transData.transactionSequenceNumber = s;

		printf("\n-->CARD MODULE\n");
		// holder name
		printf("\n->Please Enter Card holder name\n");
		scanf("%[^\n]%*c", &transData.cardHolderData.cardHolderName);
		strcpy(transactiondata[s].cardHolderData.cardHolderName, transData.cardHolderData.cardHolderName);

		// expiration date
		printf("\n->Please Enter Card Expiration date\n");
		scanf("%[^\n]%*c", &transData.cardHolderData.cardExpirationDate);
		strcpy(transactiondata[s].cardHolderData.cardExpirationDate, transData.cardHolderData.cardExpirationDate);

		//Card pan
		printf("\n->Please Enter Card PAN\n");
		scanf("%[^\n]%*c", &transData.cardHolderData.primaryAccountNumber);
		strcpy(transactiondata[s].cardHolderData.primaryAccountNumber, transData.cardHolderData.primaryAccountNumber);

		printf("\n-->TERMINAL MODULE\n");
		//Transaction date
		printf("\n->Please Transaction date\n");
		scanf("%[^\n]%*c", &transData.terminalData.transactionDate);
		strcpy(transactiondata[s].terminalData.transactionDate, transData.terminalData.transactionDate);

		//Transaction Max amount
		printf("\n->Please enter Max allowable amount\n");
		scanf("%f", &transData.terminalData.maxTransAmount);
		transactiondata[s].terminalData.maxTransAmount = transData.terminalData.maxTransAmount;

		//Transaction amount
		printf("\n->Please enter amount\n");
		scanf("%f", &transData.terminalData.transAmount);
		transactiondata[s].terminalData.transAmount = transData.terminalData.transAmount;

		transactiondata[s].transactionSequenceNumber = transData.transactionSequenceNumber;
		transData.transactionSequenceNumber = s;
		transactiondata[s].transState = transData.transState;
		s++;

		listSavedTransactions();
		return SERVER_OK;
	}
}
