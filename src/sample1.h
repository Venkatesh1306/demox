#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "head.h"

#define INPUT_SIZE 12


#define Read_Coil_Status 0x01
#define READ_HOLDING_REGISTERS 0x03
#define WRITE_SINGLE_REGISTER 0x06 

typedef struct {
    WORD_VAL transaction_identifier;
    WORD_VAL protocol_identifier;
    WORD_VAL length;
    BYTE unit_identifier;
    BYTE function_code;
    WORD_VAL start_address;
    WORD_VAL address_length;
} Modbus;

Modbus parse;


BYTE input[INPUT_SIZE] = {0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x03, 0x00, 0x05, 0x00, 0x04};
WORD Reg[100] = {0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e};
BYTE output[26]; // Assuming output array size is 100
int increment; // Global declaration of increment variable
BYTE output1[26] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x03, 0x03,0x08, 0x13, 0x21, 0x3A, 0x2B, 0x3c, 0x7e, 0x00 ,0x65};

int test_res;
