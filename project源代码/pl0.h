#include <stdio.h>

#define norw       11             // no. of reserved words
#define txmax      100            // length of identifier table
#define nmax       14             // max. no. of digits in numbers
#define al         10             // length of identifiers
#define amax       2047           // maximum address
#define levmax     3              // maximum depth of block nesting
#define cxmax      2000           // size of code array

#define now        10             //数组的最大维数
#define pnum 10
#define nul	   0x1
#define ident      0x2
#define number     0x4
#define plus       0x8
#define minus      0x10
#define times      0x20
#define slash      0x40
#define oddsym     0x80
#define eql        0x100
#define neq        0x200
#define lss        0x400
#define leq        0x800
#define gtr        0x1000
#define geq        0x2000
#define lparen     0x4000
#define rparen     0x8000
#define comma      0x10000
#define semicolon  0x20000
#define period     0x40000
#define becomes    0x80000
#define beginsym   0x100000
#define endsym     0x200000
#define ifsym      0x400000
#define thensym    0x800000
#define whilesym   0x1000000
#define dosym      0x2000000
#define callsym    0x4000000
#define constsym   0x8000000
#define varsym     0x10000000
#define procsym    0x20000000

#define typesym    0x40000000
#define arraysym   0x80000000
#define ofsym      0x100000000
#define intersym   0x200000000
#define realsym    0x400000000
#define Boolsym    0x800000000
#define funcsym    0x1000000000
#define elsesym    0x2000000000
#define writesym   0x4000000000
#define readsym    0x8000000000
#define exitsym    0x10000000000
#define or         0x20000000000
#define and        0x40000000000
#define not        0x80000000000
#define div        0x100000000000
#define mod        0x200000000000
#define truesym    0x400000000000
#define falsesym   0x800000000000
#define lmparen    0x1000000000000
#define rmparen    0x2000000000000
#define typeerror  0x4000000000000
#define voiderror  0x8000000000000
#define dotdot     0x10000000000000

enum object {
    constant, variable, proc ,type ,func
};

enum fct {
    lit, opr, lod, sto, cal, Int, jmp, jpc ,say, lay, jpq        // functions
};

typedef struct{
    enum fct f;		// function code
    long l; 		// level
    long a; 		// displacement address
} instruction;
/*  lit 0, a : load constant a
    opr 0, a : execute operation a
    lod l, a : load variable l, a
    sto l, a : store variable l, a
    cal l, a : call procedure a at level l
    Int 0, a : increment t-register by a
    jmp 0, a : jump to a
    jpc 0, a : jump conditional to a       */

char ch;               // last character read
unsigned long sym;     // last symbol read
char id[al+1];         // last identifier read
long num;              // last number read
long cc;               // character count
long ll;               // line length
long kk, err;
long cx;               // code allocation index

char line[81];
char a[al+1];
instruction code[cxmax+1];
char word[norw][al+1];
unsigned long wsym[norw];
unsigned long ssym[256];

char mnemonic[8][3+1];
unsigned long declbegsys, statbegsys, facbegsys;

struct{
    char name[al+1];
    enum object kind;
    long val;
    long level;
    long addr;
	long funcaddr;     //给函数使用，记录函数在符号表中的地址偏移量
    __int64 paral[pnum]; //存放函数参数类型，用于类型检查
	__int64 type1;     //在符号表中增加类型项
    long size;         //若是数组类型还要记录大小
	long drt;            //数组维数
	long low[now];          //数组每一维下界
	long high[now];         //数组每一维上界
	__int64 type2;     //数组元素的类型
	int n;             //过程或函数的参数个数
}table[txmax+1];

char infilename[80];
FILE* infile;

// the following variables for block
long dx;		// data allocation index
long lev;		// current depth of block nesting
long tx;		// current table index

// the following array space for interpreter
#define stacksize 50000
long s[stacksize];	// datastore
