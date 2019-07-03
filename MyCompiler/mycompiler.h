#include <stdio.h>

#define norw 29    // no. of reserved words 29个保留字
#define txmax 100  // length of identifier table
#define nmax 14    // max. no. of digits in numbers
#define al 10      // length of identifiers
#define amax 2047  // maximum address
#define levmax 3   // maximum depth of block nesting
#define cxmax 2000 // size of code array
#define now 10     // 数组的最大维
#define pnum 10    // 函数最大参数个数

#define nul 0x1
#define ident 0x2 //标识符
#define number 0x4
#define plus 0x8                // +
#define minus 0x10              // -
#define times 0x20              // *
#define slash 0x40              // /
#define oddsym 0x80             // odd函数
#define eql 0x100               // =
#define neq 0x200               // <>
#define lss 0x400               // <
#define leq 0x800               // <=
#define gtr 0x1000              // >
#define geq 0x2000              // >=
#define lparen 0x4000           // (
#define rparen 0x8000           // )
#define comma 0x10000           // ,
#define semicolon 0x20000       // ;
#define period 0x40000          // .
#define becomes 0x80000         // :=
#define beginsym 0x100000       // Begin
#define endsym 0x200000         // End
#define ifsym 0x400000          // if
#define thensym 0x800000        // then
#define whilesym 0x1000000      // while
#define dosym 0x2000000         // do
#define callsym 0x4000000       // call
#define constsym 0x8000000      // const
#define varsym 0x10000000       // var
#define procsym 0x20000000      // procedure
#define typesym 0x40000000      // type
#define arraysym 0x80000000     // array
#define ofsym 0x100000000       // array of ...
#define intersym 0x200000000    // integer
#define realsym 0x400000000     // real
#define Boolsym 0x800000000     // Boolean
#define funcsym 0x1000000000    // function
#define elsesym 0x2000000000    // else
#define writesym 0x4000000000   // write
#define readsym 0x8000000000    // read
#define exitsym 0x10000000000   // exit
#define or 0x20000000000        // or
#define and 0x40000000000       // and
#define not0x80000000000        // not
#define div 0x100000000000      // div(int and real)
#define mod 0x200000000000      // mod
#define truesym 0x400000000000  // true
#define falsesym 0x800000000000 //false
#define lmparen 0x1000000000000 //[
#define rmparen 0x2000000000000 //]
#define typeerror 0x4000000000000
#define voiderror 0x8000000000000
#define dotdot 0x10000000000000 // .. in array

enum object //对 主程序 前的 声明的 类别声明
{
    constant,
    variable,
    proc,
    type,
    func,
};

enum fct //中间代码的命令符
{
    lit,
    opr,
    lod,
    sto,
    cal,
    Int,
    jmp,
    jpc, // functions
    say,
    lay,
    jpq, // 计算 or短路,栈顶元素为1时跳转
};

typedef struct
{
    enum fct f; // function code
    long l;     // level
    double a;     // displacement address
} instruction;
/*  lit 0, a : load constant a
    opr 0, a : execute operation a
    lod l, a : load variable l, a
    sto l, a : store variable l, a
    cal l, a : call procedure a at level l
    Int 0, a : increment t-register by a
    jmp 0, a : jump to a
    jpc 0, a : jump conditional to a       */

char ch;           // last character read
long long sym; // last symbol read
long long lastsym; //最后一个词的词法类型
char id[al + 1];   // last identifier read
double num;          // last number read
long cc;           // character count
long ll;           // line length
long kk, err;
long cx; // code allocation index

char line[81];
char a[al + 1];
instruction code[cxmax + 1];
char word[norw][al + 1];
long long wsym[norw];
long long ssym[256];

char mnemonic[11][3 + 1];  // 注记符
long long declbegsys, statbegsys, facbegsys;

struct
{
    char name[al + 1];
    enum object kind;
    long val;
    long level;
    long addr;
    long funcaddr; // 函数在符号表中的地址偏移量
    long long paral[pnum]; // 函数参数类型
    long long type1; // 符号表类型项
    long size; // 数组类型的数组大小
    long drt; // 数组维数
    long low[now]; // 数组某一维的下界
    long high[now]; // 数组某一维的上界
    long long type2; // 数组元素类型
    int n; // 过程或函数的参数个数
} table[txmax + 1]; // 符号表

char infilename[80];
FILE *infile, *outfile;

struct prod
{
    char id[al+1]; // 参数名
    long long sym; // 参数类型
};
struct prod pnow[15]; // 记录过程或参数的参数信息

// the following variables for block
long dx;  // data allocation index
long lev; // current depth of block nesting
long tx;  // current table index
long whilenum = 0; //设置while循环次数，用于exit判断
long exitcx = 0; //记录最新的exit语句的中间代码位置

// the following array space for interpreter
#define stacksize 50000
double s[stacksize]; // datastore
