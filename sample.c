#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "head.h"
#define INPUT_SIZE 12

#define Read_Coil_Status 0x01
#define READ_HOLDING_REGISTERS 0x03
#define WRITE_SINGLE_REGISTER 0x06

// Define variables
BYTE input[INPUT_SIZE] = {0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x06, 0x00, 0x06, 0x00, 0x03};
WORD Reg[100] = {0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e};
BYTE output[100]; // Assuming output array size is 100
int increment; // Global declaration of increment variable

void in_func(void);

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

int main() {
    in_func(); // Call the function to parse input data into the structure

 
  if(parse.function_code == READ_HOLDING_REGISTERS){ 
    // Assign values to output array based on parsed data
    output[6] = parse.unit_identifier;
    output[7] = parse.function_code;
    output[8] = (BYTE)(parse.address_length.Val * 2);
    output[4] = 0x00;
    output[5] = 0x03 + output[8]; // Adjusted output[5] to output[4] to match the logic below
    
    // Generate output data from Reg array based on parsed start_address and address_length
    for (increment = 0; increment <output[8]; increment++) {
        output[9 + increment * 2] = Reg[parse.start_address.Val + increment]/0x100;   // High byte
        output[10 + increment * 2] = Reg[parse.start_address.Val + increment]%0x100; // Low byte
    }
 } 
   if(parse.function_code == WRITE_SINGLE_REGISTER){ 
    // Assign values to output array based on parsed data
    output[6]  = parse.unit_identifier;
    output[7]  = parse.function_code;
    output[8]  = parse.start_address.v[1];
    output[9]  = parse.start_address.v[0];
    output[10] = parse.address_length.v[1];  // Adjusted output[5] to output[4] to match the logic below
    output[11] = parse.address_length.v[0];
    
 } 
  while(1)
    {
    output[99] = 1;
    }
    
  
}

void in_func(void) {
    parse.transaction_identifier.v[1]   = input[0];
    parse.transaction_identifier.v[0]   = input[1];
    parse.protocol_identifier.v[1]      = input[2];
    parse.protocol_identifier.v[0]      = input[3];
    parse.length.v[1]                   = input[4];
    parse.length.v[0]                   = input[5];
    parse.unit_identifier               = input[6];
    parse.function_code                 = input[7];
    parse.start_address.v[1]            = input[8];
    parse.start_address.v[0]            = input[9];
    parse.address_length.v[1]           = input[10];
    parse.address_length.v[0]           = input[11]; 
}