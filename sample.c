#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "head.h"
#define INPUT_SIZE 12
//#define testing



#ifdef testing
void test(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
#endif

// Define variables
BYTE input[INPUT_SIZE] = {0x00, 0x01, 0x00, 0x02, 0x00, 0x06, 0x03, 0x06, 0x00, 0x02, 0x00, 0x03};
WORD Reg[100] = {0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e, 0x0065, 0x2217, 0x1123, 0x1321, 0x3A2B, 0x3c7e};
BYTE output[100]; // Assuming output array size is 100
int increment; // Global declaration of increment variable

void in_func(void);
void test(const char *format, ...);

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

#ifdef testing
    // Printing the output in string format
    test("Output string: ");
    for (increment = 4; increment < 9 + output[8]; increment++) {
        test("%02X ", output[increment]);
    }
    test("\n");
#endif
   
    
    while(1)
    {
    //output[99] = 1;
    }
    
    return 0;
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

#ifdef testing
    test("Transaction Identifier: %04X\n", parse.transaction_identifier.Val);
    test("Protocol Identifier: %04X\n", parse.protocol_identifier.Val);
    test("Length: %04X\n", parse.length.Val);
    test("Unit Identifier: %02X\n", parse.unit_identifier);
    test("Function Code: %02X\n", parse.function_code);
    test("Start Address: %04X\n", parse.start_address.Val);
    test("Address Length: %04X\n", parse.address_length.Val);
#endif
}