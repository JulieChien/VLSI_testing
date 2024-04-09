#include <stdio.h>
#include <stdbool.h>

#define pat 16
#define L 10

#define Px1_SA0 0
#define Px2_SA0 1
#define Px3_SA0 2
#define Px4_SA0 3
#define Py21_SA0 4
#define Py22_SA0 5
#define Pa_SA0 6
#define Pb_SA0 7
#define Pc_SA0 8
#define Pz_SA0 9

#define Px1_SA1 10
#define Px2_SA1 11
#define Px3_SA1 12
#define Px4_SA1 13
#define Py21_SA1 14
#define Py22_SA1 15
#define Pa_SA1 16
#define Pb_SA1 17
#define Pc_SA1 18
#define Pz_SA1 19

// Fault list
int Lx1[pat][L];    // 0 - 9 for SA0, 10 - 19 for SA1
int Lx2[pat][L];    // 0 - 9: x1, x2, x3, x4, y21, y22, a, b, c, z
int Lx3[pat][L]; 
int Lx4[pat][L];;     
int Ly21[pat][L];
int Ly22[pat][L];
int La[pat][L];;
int Lb[pat][L];
int Lc[pat][L];
int Lz[pat][L];
int Lx[pat] = {0};



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

