#include "mcc_generated_files/mcc.h"


int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    SLAVE1_Program();
    SLAVE1_Start();

    while (1);

    return 1; 
}