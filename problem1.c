#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    size_t LENGTH = 1000;

    int intcode[LENGTH];

    FILE * file;
    file = fopen("input", "r");

    for (size_t i = 0; i < LENGTH; i++)
    {
        int line = fscanf(file, "%d,", &intcode[i]);
        if (line == EOF) { break; }
    }

    int flag = 1;
    for (int i = 0; flag;)
    {
        const int p1 = (intcode[i] / 100) % 10;
        const int p2 = (intcode[i] / 1000) % 10;
        const int p3 = (intcode[i] / 10000) % 10;

        int opcode = intcode[i] % 100;
        int *a = (p1) ? &intcode[i + 1] : &intcode[intcode[i + 1]];
        int *b = (p2) ? &intcode[i + 2] : &intcode[intcode[i + 2]];
        int *c = (p3) ? &intcode[i + 3] : &intcode[intcode[i + 3]];

        switch (opcode)
        {
            case 1:
                *c = *a + *b;
                i += 4;
                break;

            case 2:
                *c = *a * *b;
                i += 4;
                break;
            
            case 3:
                printf(": ");
                scanf("%d", a);
                i += 2;
                break;
            
            case 4:
                printf(": %d\n", *a);
                i += 2;
                break;
                
            case 99:
                printf("Program finished. position 0 -> %d\n", intcode[0]);
                flag = 0;
                break;

            default:
                printf("Something went wrong! opcode %d\n", opcode);
                flag = 0;
        }
    }
    
    return 0;
}

