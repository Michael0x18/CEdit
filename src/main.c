#include "main.h"

int main(int argc, char **argv)
{
    if(argc<2){
        os_ClrHome();
        os_PutStrFull("Usage: prgmCEDIT varname");
        while(!os_GetCSC());
        return 0;
    }
}