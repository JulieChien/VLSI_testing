#include <stdio.h>
#include <stdbool.h>

void fault_free(void);

int main (void)
{
    
    fault_free();
 
    
    return 0;
}

void fault_free(void)
{
    bool x1, x2, x3, x4;     // primary input
    bool z;                  // primary output
    int i, j, k,l;           // loop index
    bool a, b, c;         // output signals of logic gates
    int cnt = 0;

    x1 = true;
    x2 = true;
    x3 = true;
    x4 = true;
    printf("------------------------------------------\n");
    printf("| no | x1 | x2 | x3 | x4 | a | b | c | z |\n");

    for (i = 0; i <= 1; i++) {
        x1 = !x1;
        for (j = 0; j <= 1; j++) {
            x2 = !x2;
            for (k = 0; k <= 1; k++) {
                x3 = !x3;
                for (l = 0; l <= 1; l++) {
                    x4 = !x4;
                    
                    a = x1 && x2;
                    b = !(x2 || x3);
                    c = !x4;
                    z = (a || b) || c;

                    printf("------------------------------------------\n");
                    printf("| %2d | %2d | %2d | %2d | %2d | %d | %d | %d | %d |\n", cnt++, x1, x2, x3, x4, a, b, c, z);
                }
            }
        }
    }
        printf("------------------------------------------\n");}

