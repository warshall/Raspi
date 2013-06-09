#include <iostream>
#include <wiringPi.h>
#include <wiringPiI2C.h>

using namespace std; 

int main ()
{
int Mcp ;

Mcp = wiringPiI2CSetup (0x20) ;

wiringPiI2CWriteReg8 (Mcp, 0x00, 0x00) ;

for (;;)
{
wiringPiI2CWriteReg8 (Mcp, 0x09, 0x01) ;
delay (1000) ;
wiringPiI2CWriteReg8 (Mcp, 0x09, 0x00) ;
delay (1000) ;
}

cout << "Hello world!" << endl ;

return 0;
}
