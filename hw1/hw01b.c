#include <stdio.h>
#include <stdbool.h>

#define pat 16
#define L 10

#define Px1 0
#define Px2 1
#define Px3 2
#define Px4 3
#define Py21 4
#define Py22 5
#define Pa 6
#define Pb 7
#define Pc 8
#define Pz 9



// Fault list
int Lx1[pat][L];    
int Lx2[pat][L];    // 0 - 9: x1, x2, x3, x4, y21, y22, a, b, c, z
int Lx3[pat][L]; 
int Lx4[pat][L];;     
int Ly21[pat][L];
int Ly22[pat][L];
int La[pat][L];;
int Lb[pat][L];
int Lc[pat][L];
int Lz[pat][L];

int Lx1_SA1[pat][L];    
int Lx2_SA1[pat][L];    // 0 - 9: x1, x2, x3, x4, y21, y22, a, b, c, z
int Lx3_SA1[pat][L]; 
int Lx4_SA1[pat][L];;     
int Ly21_SA1[pat][L];
int Ly22_SA1[pat][L];
int La_SA1[pat][L];;
int Lb_SA1[pat][L];
int Lc_SA1[pat][L];
int Lz_SA1[pat][L];


void initFaultList(int (*List)[pat][L]);
void printArray (int (*List)[pat][L]);
void PI(int (*List)[pat][L], bool SA, bool PI, int row, int p);

void DecductNot(int (*List1)[pat][L], int (*List2)[pat][L], int row, int p, bool output, bool SA);
void DecductBranch(int (*List1)[pat][L], int (*List2)[pat][L], int row, int p);

void printFault(int (*List1)[pat][L], int (*List2)[pat][L], bool SA);

void DeductAnd(int (*List1)[pat][L], int (*List2)[pat][L], int (*List3)[pat][L], int row, bool input1, bool input2, bool output, int p, bool SA);
void DeductNor(int (*List1)[pat][L], int (*List2)[pat][L], int (*List3)[pat][L], int row, bool input1, bool input2, bool output, int p, bool SA);

void DeductOr2(int (*List1)[pat][L], int (*List2)[pat][L], int (*List3)[pat][L], int row, bool input1, bool input2, bool output, int p, bool SA);
void DeductOr3(int (*List1)[pat][L], int (*List2)[pat][L], int (*List3)[pat][L], int (*List4)[pat][L], int row, bool input1, bool input2, bool input3, bool output, int p, bool SA);


int main(void) 
{
    bool x1, x2, x3, x4;     // primary input
    bool z;                  // primary output
    int i, j, k,l;           // loop index
    bool a, b, c, x;         // output signals of logic gates
    bool y21, y22;           // Two branches of x2
    int num = 0;
    bool SA = false;
    int m;

    x1 = true;
    x2 = true;
    x3 = true;
    x4 = true;
   
    initFaultList(&Lx1);
    initFaultList(&Lx2);
    initFaultList(&Lx3);
    initFaultList(&Lx4);
    initFaultList(&Ly21);
    initFaultList(&Ly22);
    initFaultList(&La);
    initFaultList(&Lb);
    initFaultList(&Lc);
    initFaultList(&Lz);

    initFaultList(&Lx1_SA1);
    initFaultList(&Lx2_SA1);
    initFaultList(&Lx3_SA1);
    initFaultList(&Lx4_SA1);
    initFaultList(&Ly21_SA1);
    initFaultList(&Ly22_SA1);
    initFaultList(&La_SA1);
    initFaultList(&Lb_SA1);
    initFaultList(&Lc_SA1);
    initFaultList(&Lz_SA1);
   

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
                    // b = (x2 || x3);
                    c = !x4;
                    z = (a || b) || c;
                    x = (a || b);
                    y21 = x2;
                    y22 = x2;
                    // printf("x1 = %d, x2 = %d, x3 = %d, x4 = %d a = %d, b = %d, c = %d\n", x1, x2, x3, x4, a, b, c);

                    SA = false;
                    PI(&Lx1, SA, x1, num, Px1);
                    PI(&Lx2, SA, x2, num, Px2);
                    PI(&Lx3, SA, x3, num, Px3);
                    PI(&Lx4, SA, x4, num, Px4);
                    DecductBranch(&Ly21, &Lx2, num, Py21);
                    DecductBranch(&Ly22, &Lx2, num, Py22);
                    DecductNot(&Lc, &Lx4, num, Pc, c, SA);

                    DeductAnd(&Lx1, &Ly21, &La, num, x1, y21, a, Pa, SA);
                    // DeductOr2(&Ly22, &Lx3, &Lb, num, y22, x3, b, Pb, SA);

                    DeductNor(&Ly22, &Lx3, &Lb, num, y22, x3, b, Pb, SA);

                    DeductOr3(&La, &Lb, &Lc, &Lz, num, a, b, c, z, Pz, SA);

                    SA = true;
                    PI(&Lx1_SA1, SA, x1, num, Px1);
                    PI(&Lx2_SA1, SA, x2, num, Px2);
                    PI(&Lx3_SA1, SA, x3, num, Px3);
                    PI(&Lx4_SA1, SA, x4, num, Px4);
                    DecductBranch(&Ly21_SA1, &Lx2_SA1, num, Py21);
                    DecductBranch(&Ly22_SA1, &Lx2_SA1, num, Py22);
                    DecductNot(&Lc_SA1, &Lx4_SA1, num, Pc, c, SA);

                    DeductAnd(&Lx1_SA1, &Ly21_SA1, &La_SA1, num, x1, y21, a, Pa, SA);
                    // DeductOr2(&Ly22, &Lx3, &Lb, num, y22, x3, b, Pb, SA);

                    DeductNor(&Ly22_SA1, &Lx3_SA1, &Lb_SA1, num, y22, x3, b, Pb, SA);

                    DeductOr3(&La_SA1, &Lb_SA1, &Lc_SA1, &Lz_SA1, num, a, b, c, z, Pz, SA);

                   

                    
                    num++;
                }
            }
        }
    }

    // printArray(&Lx1);
    // printArray(&Lx2);
    // printArray(&Lx3);
    // printArray(&Lx4);
    // printArray(&Lc);
    // printArray(&Lz);
    // printf("Lx1: \n");
    // printFault(&Lx1, SA);
    // printf("Lx2: \n");
    // printFault(&Lx2, SA);
    // printf("Lx3: \n");
    // printFault(&Lx3, SA);
    // printf("Lx4: \n");
    // printFault(&Lx4, SA);
    // printf("Ly21: \n");
    // printFault(&Ly21, SA);
    // printf("Ly22: \n");
    // printFault(&Ly22, SA);
    // printf("Lc: \n");
    // printFault(&Lc, SA);
    // printf("La: \n");
    // printFault(&La, SA);
    // printf("Lb: \n");
    // printFault(&Lb, SA);
    // printf("Lz: \n");
    printFault(&Lz, &Lz_SA1, SA);
    return 0;
}

void initFaultList(int (*List)[pat][L])
{
    int i, j;

    for (i = 0; i < pat; i++) {
        for (j = 0; j < L; j++) {
            (*List)[i][j] = 0;
        }
    }
    
}

void printArray (int (*List)[pat][L])
{
    int i, j;

    for (i = 0; i < pat; i++) {
        for (j = 0; j < L; j++) {
            printf("%d ", (*List)[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void PI(int (*List)[pat][L], bool SA, bool PI, int row, int p)
{
    int i;
    if (PI != SA)  (*List)[row][p] = 1;
   
}

void DecductNot(int (*List1)[pat][L], int (*List2)[pat][L], int row, int p, bool output, bool SA)
{
    int i;

    if (output != SA) {
        for (i = 0; i < L; i++) {
        (*List1)[row][i] = (*List2)[row][i];
    }
    (*List1)[row][p] = 1;
    }   
}

void DecductBranch(int (*List1)[pat][L], int (*List2)[pat][L], int row, int p)
{
    int i;

    for (i = 0; i < L; i++) {
        (*List1)[row][i] = (*List2)[row][i];
    }
    
}


void printFault(int (*List1)[pat][L], int (*List2)[pat][L], bool SA)
{
    int i, j;
    int sum = 0;

    for (i = 0; i < pat; i++) {
        printf("pat %d: ", i);
        sum = 0;
        for (j = 0; j < L; j++) {
            sum += (*List1)[i][j];
            sum += (*List2)[i][j];
            if ((*List1)[i][j] != 0) {
                switch (j)
                {
                case 0: printf("x1-S-A-%d ", SA); break;
                case 1: printf("x2-S-A-%d ", SA); break;
                case 2: printf("x3-S-A-%d ", SA); break;
                case 3: printf("x4-S-A-%d ", SA); break;
                case 4: printf("y21-S-A-%d ", SA); break;
                case 5: printf("y22-S-A-%d ", SA); break;
                case 6: printf("a-S-A-%d ", SA); break;
                case 7: printf("b-S-A-%d ", SA); break;
                case 8: printf("c-S-A-%d ", SA); break;
                case 9: printf("z-S-A-%d ", SA); break;
                }
                // printf("\n");
            }

            if ((*List2)[i][j] != 0) {
                switch (j)
                {
                case 0: printf("x1-S-A-%d ", SA); break;
                case 1: printf("x2-S-A-%d ", SA); break;
                case 2: printf("x3-S-A-%d ", SA); break;
                case 3: printf("x4-S-A-%d ", SA); break;
                case 4: printf("y21-S-A-%d ", SA); break;
                case 5: printf("y22-S-A-%d ", SA); break;
                case 6: printf("a-S-A-%d ", SA); break;
                case 7: printf("b-S-A-%d ", SA); break;
                case 8: printf("c-S-A-%d ", SA); break;
                case 9: printf("z-S-A-%d ", SA); break;
                }
                // printf("\n");
            }
            
        }

        printf("\nthere %d faults detected.\n", sum);
    }
}

void DeductAnd(int (*List1)[pat][L], int (*List2)[pat][L], int (*List3)[pat][L], int row, bool input1, bool input2, bool output, int p, bool SA)
{
     int i;
    if (output != SA) {
        if (input1 && input2 && output) {    
        for (i = 0; i < L; i++) {
            (*List3)[row][i] = (*List1)[row][i] || (*List2)[row][i];
        }
        (*List3)[row][p] = 1;
    } else if (input1 && (!input2) && (!output)) { 
        for (i = 0; i < L; i++) {
            (*List3)[row][i] = (!(*List1)[row][i]) && (*List2)[row][i];
        }
        (*List3)[row][p] = 1;
        
    } else if (input2 && (!input1) && (!output)) {
        for (i = 0; i < L; i++) {
            (*List3)[row][i] = (!(*List2)[row][i]) && (*List1)[row][i];
        }
        (*List3)[row][p] = 1;

    } else if ((!input2) && (!input1) && (!output)) {
        for (i = 0; i < L; i++) {
            (*List3)[row][i] = (*List2)[row][i] && (*List1)[row][i];
        }
        (*List3)[row][p] = 1;
    }
    }

    
    
}

void DeductOr2(int (*List1)[pat][L], int (*List2)[pat][L], int (*List3)[pat][L], int row, bool input1, bool input2, bool output, int p, bool SA)
{
    int i;
    if (output != SA) {
        if ((!input1) && (!input2) && (!output)) {
        
        for (i = 0; i < L; i++) {
            (*List3)[row][i] = (*List1)[row][i] || (*List2)[row][i];
        }
        (*List3)[row][p] = 1;
        } else if (input1 && (!input2) && output) {
            
            for (i = 0; i < L; i++) {
                (*List3)[row][i] = (!(*List2)[row][i]) && (*List1)[row][i];
            }
            (*List3)[row][p] = 1;

        } else if (input2 && (!input1) && output) {
            
            for (i = 0; i < L; i++) {
                (*List3)[row][i] = (!(*List1)[row][i]) && (*List2)[row][i];
            }
            (*List3)[row][p] = 1;

        } else if (input2 && input1 && output) {
            
            for (i = 0; i < L; i++) {
                (*List3)[row][i] = (*List2)[row][i] && (*List1)[row][i];
            }

            (*List3)[row][p] = 1;
        }
    }
   

}

void DeductOr3(int (*List1)[pat][L], int (*List2)[pat][L], int (*List3)[pat][L], int (*List4)[pat][L], int row, bool input1, bool input2, bool input3, bool output, int p, bool SA)
{
    bool x;
    int Lx[pat][L] = {{0}};

    x = input1 || input2;

    int i;
    
    if ((!input1) && (!input2) && (!x)) {
       
        for (i = 0; i < L; i++) {
            Lx[row][i] = (*List1)[row][i] || (*List2)[row][i];
        }
    } else if (input1 && (!input2) && x) {
       
        for (i = 0; i < L; i++) {
            Lx[row][i] = (!(*List2)[row][i]) && (*List1)[row][i];
        }
        
    } else if (input2 && (!input1) && x) {
       
        for (i = 0; i < L; i++) {
            Lx[row][i] = (!(*List1)[row][i]) && (*List2)[row][i];
        }
        
    } else if (input2 && input1 && x) {
        
        for (i = 0; i < L; i++) {
            Lx[row][i] = (*List2)[row][i] && (*List1)[row][i];
        }
    }

    DeductOr2(&Lx, List3, List4, row, x, input3, output, p, SA);
    
}


void DeductNor(int (*List1)[pat][L], int (*List2)[pat][L], int (*List3)[pat][L], int row, bool input1, bool input2, bool output, int p, bool SA)
{
    bool x; 
    int Lx[pat][L] = {{0}};
    int i;
    
    x = input1 || input2;

    if ((!input1) && (!input2) && (!x)) {
        
        for (i = 0; i < L; i++) {
           Lx[row][i] = (*List1)[row][i] || (*List2)[row][i];
        }
       
    } else if (input1 && (!input2) && x) {
        
        for (i = 0; i < L; i++) {
           Lx[row][i] = (!(*List2)[row][i]) && (*List1)[row][i];
        }
       

    } else if (input2 && (!input1) && x) {
        
        for (i = 0; i < L; i++) {
           Lx[row][i] = (!(*List1)[row][i]) && (*List2)[row][i];
        }
       

    } else if (input2 && input1 && x) {
        
        for (i = 0; i < L; i++) {
           Lx[row][i] = (*List2)[row][i] && (*List1)[row][i];
        }

    }

    DecductNot(List3, &Lx, row, p, output, SA);

    
    
}
