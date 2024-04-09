#include <stdio.h>
#include <stdbool.h>

#define pat 16
#define L 20

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



void initFaultList(int (*List)[pat][L]);
void printArray (int (*List)[pat][L]);
void PI(int (*List)[pat][L], bool PI, int row, int p);

void DecductNot(int (*List1)[pat][L], int (*List2)[pat][L], int row, int p, bool output);
void DecductBranch(int (*List1)[pat][L], int (*List2)[pat][L], int row, int p, bool output);

void printFault(int (*List1)[pat][L]);

void DeductAnd(int (*List1)[pat][L], int (*List2)[pat][L], int (*List3)[pat][L], int row, bool input1, bool input2, bool output, int p);
void DeductNor(int (*List1)[pat][L], int (*List2)[pat][L], int (*List3)[pat][L], int row, bool input1, bool input2, bool output, int p);

void DeductOr2(int (*List1)[pat][L], int (*List2)[pat][L], int (*List3)[pat][L], int row, bool input1, bool input2, bool output, int p);
void DeductOr3(int (*List1)[pat][L], int (*List2)[pat][L], int (*List3)[pat][L], int (*List4)[pat][L], int row, bool input1, bool input2, bool input3, bool output, int p);


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

                    // SA = false;
                    PI(&Lx1, x1, num, Px1);
                    PI(&Lx2, x2, num, Px2);
                    PI(&Lx3, x3, num, Px3);
                    PI(&Lx4, x4, num, Px4);
                    DecductBranch(&Ly21, &Lx2, num, Py21, y21);
                    DecductBranch(&Ly22, &Lx2, num, Py22, y22);
                    DecductNot(&Lc, &Lx4, num, Pc, c);

                    DeductAnd(&Lx1, &Ly21, &La, num, x1, y21, a, Pa);
                    // DeductOr2(&Ly22, &Lx3, &Lb, num, y22, x3, b, Pb, SA);
                    DeductNor(&Ly22, &Lx3, &Lb, num, y22, x3, b, Pb);

                    DeductOr3(&La, &Lb, &Lc, &Lz, num, a, b, c, z, Pz);

                   
                   

                    
                    num++;
                }
            }
        }
    }

    // printArray(&Lx1);
    // printArray(&Lx2);
    // printArray(&Lx3);
    // printArray(&Lx4);
    //  printArray(&Ly21);
    // printArray(&Ly22);


    // printArray(&Lz);
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
    printFault(&Lz);
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
    printf("|x1/0 |x2/0 |x3/0 |x4/0 |y21/0|y22/0| a/0  |b/0  |c/0  |z/0  |x1/1 |x2/1 |x3/1 |x4/1 |y21/1|y22/1|a/1  |b/1  |c/1  |z/1  |\n");
    for (i = 0; i < pat; i++) {
        for (j = 0; j < L; j++) {
            printf("%5d ", (*List)[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void PI(int (*List)[pat][L], bool PI, int row, int p)
{

    
    if (PI) (*List)[row][p] = 1;
    else (*List)[row][p + 10] = 1;
     
}

void DecductNot(int (*List1)[pat][L], int (*List2)[pat][L], int row, int p, bool output)
{
    int i;
   
    for (i = 0; i < L; i++) {
        (*List1)[row][i] = (*List2)[row][i];
    }

    if (output) (*List1)[row][p] = 1;
    else (*List1)[row][p + 10] = 1;
       
}

void DecductBranch(int (*List1)[pat][L], int (*List2)[pat][L], int row, int p, bool output)
{
    int i;

    for (i = 0; i < L; i++) {
        (*List1)[row][i] = (*List2)[row][i];
    }

    if (output) (*List1)[row][p] = 1;
    else (*List1)[row][p + 10] = 1;
     
}


void printFault(int (*List1)[pat][L])
{
    int i, j;
    int sum = 0;

    for (i = 0; i < pat; i++) {
        printf("pat %d: ", i);
        sum = 0;
        for (j = 0; j < L; j++) {
            sum += (*List1)[i][j];
            
            if ((*List1)[i][j] != 0) {
                switch (j)
                {
                    case 0: printf("x1-S-A-0 "); break;
                    case 1: printf("x2-S-A-0 "); break;
                    case 2: printf("x3-S-A-0 "); break;
                    case 3: printf("x4-S-A-0 "); break;
                    case 4: printf("y21-S-A-0 "); break;
                    case 5: printf("y22-S-A-0 "); break;
                    case 6: printf("a-S-A-0 "); break;
                    case 7: printf("b-S-A-0 "); break;
                    case 8: printf("c-S-A-0 "); break;
                    case 9: printf("z-S-A-0 "); break;
                    case 10: printf("x1-S-A-1 "); break;
                    case 11: printf("x2-S-A-1 "); break;
                    case 12: printf("x3-S-A-1 "); break;
                    case 13: printf("x4-S-A-1 "); break;
                    case 14: printf("y21-S-A-1 "); break;
                    case 15: printf("y22-S-A-1 "); break;
                    case 16: printf("a-S-A-1 "); break;
                    case 17: printf("b-S-A-1 "); break;
                    case 18: printf("c-S-A-1 "); break;
                    case 19: printf("z-S-A-1 "); break;
                }
                // printf("\n");
            }

           
            
        }

        printf("\nthere %d faults detected.\n", sum);
    }
}

void DeductAnd(int (*List1)[pat][L], int (*List2)[pat][L], int (*List3)[pat][L], int row, bool input1, bool input2, bool output, int p)
{
     int i;
   
    if (input1 && input2 && output) {    
        for (i = 0; i < L; i++) {
            (*List3)[row][i] = (*List1)[row][i] || (*List2)[row][i];
        }
        (*List3)[row][p] = 1;
    } else if (input1 && (!input2) && (!output)) { 
        for (i = 0; i < L; i++) {
            (*List3)[row][i] = (!(*List1)[row][i]) && (*List2)[row][i];
        }
        (*List3)[row][p + 10] = 1;
        
    } else if (input2 && (!input1) && (!output)) {
        for (i = 0; i < L; i++) {
            (*List3)[row][i] = (!(*List2)[row][i]) && (*List1)[row][i];
        }
        (*List3)[row][p + 10] = 1;

    } else if ((!input2) && (!input1) && (!output)) {
        for (i = 0; i < L; i++) {
            (*List3)[row][i] = (*List2)[row][i] && (*List1)[row][i];
        }
        (*List3)[row][p + 10] = 1;
    }
    

    
    
}

void DeductOr2(int (*List1)[pat][L], int (*List2)[pat][L], int (*List3)[pat][L], int row, bool input1, bool input2, bool output, int p)
{
    int i;
    
    if ((!input1) && (!input2) && (!output)) {
        
        for (i = 0; i < L; i++) {
            (*List3)[row][i] = (*List1)[row][i] || (*List2)[row][i];
        }
        (*List3)[row][p + 10] = 1;
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

void DeductOr3(int (*List1)[pat][L], int (*List2)[pat][L], int (*List3)[pat][L], int (*List4)[pat][L], int row, bool input1, bool input2, bool input3, bool output, int p)
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

    DeductOr2(&Lx, List3, List4, row, x, input3, output, p);
    
}


void DeductNor(int (*List1)[pat][L], int (*List2)[pat][L], int (*List3)[pat][L], int row, bool input1, bool input2, bool output, int p)
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
    
    DecductNot(List3, &Lx, row, p, output);

    
    
}