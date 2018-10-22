#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) 
{
	if ( argv[1] != NULL && argv[2] != NULL)
    {
		char arg_jsc[45]="../WebKitBuild/Release/bin/jsc "; //jsc
		strcat(arg_jsc,argv[1]);
        system(arg_jsc);

        printf("Done message in program\n");
        return 1;
    }
    else
    {
        printf("Error: Empty input\n");
        return 0;
    }
}