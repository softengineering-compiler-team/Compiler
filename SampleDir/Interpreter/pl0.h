#include <stdio.h>
#define cxmax      2000           // size of code array
#define nmax       14             // max. no. of digits in numbers

enum fct {
    lit, opr, lod, sto, cal, Int, jmp, jpc,say,lay,jpq//放整型常量         // functions
};

typedef struct{
    enum fct f;		// function code
    long l; 		// level
    double a; 		// displacement address
} instruction;


instruction code[cxmax+1];
#define stacksize 5000
double s[stacksize];	// datastore