// HEADER FILE GUARD FOR CARD_H
#ifndef CARD_H
#define CARD_H

#include <string.h>
#include"../Std/std.h" // DATA TYPES HEADER FILE 


typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

typedef enum EN_cardError_t
{

    CARD_OK /*0*/, WRONG_NAME /*1*/, WRONG_EXP_DATE/*2*/, WRONG_PAN /*2*/
}EN_cardError_t;


EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);

#endif 


