#include "sample1.h"

void in_func(const BYTE *input);
void testingg(const BYTE*output,const BYTE*output1);



int main() {
    
    in_func(input); // Call the function to parse input data into the structure
   
 
  if(parse.function_code == READ_HOLDING_REGISTERS){ 
    // Assign values to output array based on parsed data
    output[6] = parse.unit_identifier;
    output[7] = parse.function_code;
    output[8] = (BYTE)(parse.address_length.Val * 2);
    output[4] = 0x00;
    output[5] = 0x03 + output[8]; // Adjusted output[5] to output[4] to match the logic below
    
    // Generate output data from Reg array based on parsed start_address and address_length
    for (increment = 0; increment <parse.address_length.Val; increment++) {
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
    
  if(parse.function_code == Read_Coil_Status) {
        output[6]  = parse.unit_identifier;
        output[7]  = parse.function_code;
        int quotient1 = parse.address_length.Val / 8;
        output[8] = quotient1 + 1;
        for(increment = 0; increment < output[8]; increment++) {
            if (((parse.address_length.Val % 8) <= 4) && ((parse.address_length.Val % 8) != 0)) {
               
                output2[increment].bits.b0 = Reg1[parse.start_address.Val + increment].bits.b7; 
                output2[increment].bits.b1 = Reg1[parse.start_address.Val + increment].bits.b6; 
                output2[increment].bits.b2 = Reg1[parse.start_address.Val + increment].bits.b5; 
                output2[increment].bits.b3 = Reg1[parse.start_address.Val + increment].bits.b4;
            } else if (((parse.address_length.Val % 8) > 4) || ((parse.address_length.Val % 8) == 0)) {    
                
                output2[increment].bits.b0 = Reg1[parse.start_address.Val + increment].bits.b0; 
                output2[increment].bits.b1 = Reg1[parse.start_address.Val + increment].bits.b1; 
                output2[increment].bits.b2 = Reg1[parse.start_address.Val + increment].bits.b2; 
                output2[increment].bits.b3 = Reg1[parse.start_address.Val + increment].bits.b3; 
                output2[increment].bits.b4 = Reg1[parse.start_address.Val + increment].bits.b4; 
                output2[increment].bits.b5 = Reg1[parse.start_address.Val + increment].bits.b5; 
                output2[increment].bits.b6 = Reg1[parse.start_address.Val + increment].bits.b6; 
                output2[increment].bits.b7 = Reg1[parse.start_address.Val + increment].bits.b7;
            }
            output[9 + increment] = output2[increment].Val; 
        }

    }
    
    testingg(output,output1);
  while(1)
    {
    output[99] = 1;
    }
    
  
}

void in_func(const BYTE *input) {
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

void testingg(const BYTE*output,const BYTE*output1) {
    test_res = 1; // Assuming the test will pass unless a mismatch is found
    for (increment = 0; increment < 26; increment++) {
        if (output[increment] != output1[increment]) {
            test_res = 0; // Set to 0 if a mismatch is found
            break; // Exit the loop since the test has failed
        }
    }
}

