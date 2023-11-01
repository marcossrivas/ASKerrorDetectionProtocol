#include <iostream>
#include <bitset>
#include <stdint.h>

int main()

{
    int8_t lowdata_in= 0b11000111 ;
    int8_t highdata_in= 0b00000011;

    int countlow = 0;
//cuento bits parte baja
int8_t lowdata = lowdata_in;
for(int i=0; i<8; i++)
{
    countlow += lowdata & 1;
    lowdata = lowdata >> 1;
}

    int counthigh = 0;
//cuento bits parte alta
int8_t highdata = highdata_in;
for(int i= 0; i<2; i++)
{
    counthigh += highdata & 1;
    highdata = highdata >> 1;
}
//checksum

 int sum = counthigh + countlow;


//paridad data
 int paridad_data_bit;//par
if (sum % 2 == 0) 
{
    paridad_data_bit = 0;
    } else {
    paridad_data_bit = 1;
    }
 std::cout << paridad_data_bit << std::endl;



 //paridad checksum
 int countchecksum;
 int checksum = sum;
 int paridad_checksum_bit;
 for(int i = 0; i<4; i++)
 {
    countchecksum += checksum & 1;
    checksum = checksum >> 1;
 }
if(countchecksum %2 == 0){
    paridad_checksum_bit = 0;
}
else {
    paridad_checksum_bit = 1;
}

std::cout << paridad_checksum_bit << std::endl;



 // create output data

    int8_t lowdata_out= lowdata_in; // se mantiene igual


    int8_t highdata_out = (countchecksum*64) + (sum*4) + highdata_in;


    std::cout << "lowdataout " << std::bitset<8>(lowdata_out)  << std::endl;
    std::cout << "highdataout " << std::bitset<8>(highdata_out)  << std::endl;
    return 0;
}