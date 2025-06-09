/*
 * PL/0 complier program for win32 platform (implemented in C)
 *
 * The program has been test on Visual C++ 6.0,  Visual C++.NET and
 * Visual C++.NET 2003,  on Win98,  WinNT,  Win2000,  WinXP and Win2003
 *
 */

typedef enum {
    false,
    true
} bool;


#define norw 17     /* ؼָ */
#define txmax 100   /* ֱ */
#define nmax 14     /* numberλ */
#define al 10       /* ŵ󳤶 */
#define amax 2047   /* ַϽ*/
#define levmax 3    /* Ƕ [0,  levmax]*/
#define cxmax 500   /*  */

/*  */
enum symbol {
    nul,         ident,     number,     plus,      minus,
    times,       slash,     oddsym,     eql,       neq,
    lss,         leq,       gtr,        geq,       lparen,
    rparen,      comma,     semicolon,  period,    becomes,
    beginsym,    endsym,    ifsym,      thensym,   whilesym,
    writesym,    readsym,   dosym,      callsym,   constsym,
    varsym,      procsym,

    elsesym, untilsym, forsym, downtosym,

};
#define symnum 32

/* ֱе */
enum object {
    constant,
    variable,
    procedur,
    array       //add
};

/*  */
enum fct {
    lit,     opr,     lod,
    sto,     cal,     inte,
    jmp,     jpc,
};
#define fctnum 8

/* ṹ */
struct instruction
{
    enum fct f; /* ָ */
    int l;      /* òĲβ */
    int a;      /* fĲͬͬ */
};

FILE* fas;  /* ֱ */
FILE* fa;   /*  */
FILE* fa1;  /* ԴļжӦ׵ַ */
FILE* fa2;  /*  */
bool listswitch;    /* ʾ */
bool tableswitch;   /* ʾֱ */
char ch;            /* ȡַĻgetch ʹ */
enum symbol sym;    /* ǰķ */
char id[al+1];      /* ǰident, һֽڴ0 */
int num;            /* ǰnumber */
int cc, ll;          /* getchʹõļccʾǰַ(ch)λ */
int cx;             /* ָ, ȡֵΧ[0, cxmax-1]*/
char line[81];      /* ȡл */
char a[al+1];       /* ʱ, һֽڴ0 */
struct instruction code[cxmax]; /*  */
char word[norw][al];        /*  */
enum symbol wsym[norw];     /* ֶӦķֵ */
enum symbol ssym[256];      /* ַķֵ */
char mnemonic[fctnum][5];   /* ָ */
bool declbegsys[symnum];    /* ʾʼķż */
bool statbegsys[symnum];    /* ʾ俪ʼķż */
bool facbegsys[symnum];     /* ʾӿʼķż */

/* ֱṹ */
struct tablestruct
{
    char name[al];      /*  */
    enum object kind;   /* ͣconst, var, array or procedure */
    int val;            /* ֵconstʹ */
    int level;          /* 㣬constʹ */
    int adr;            /* ַconstʹ */
    int size;           /* Ҫռ, procedureʹ */
};

struct tablestruct table[txmax]; /* ֱ */

FILE* fin;
FILE* fout;
char fname[al];
int err; /*  */

/* лᷢfatal errorʱ-1֪ĺ˳ */
#define getsymdo                      if(-1 == getsym()) return -1
#define getchdo                       if(-1 == getch()) return -1
#define testdo(a, b, c)               if(-1 == test(a, b, c)) return -1
#define gendo(a, b, c)                if(-1 == gen(a, b, c)) return -1
#define expressiondo(a, b, c)         if(-1 == expression(a, b, c)) return -1
#define factordo(a, b, c)             if(-1 == factor(a, b, c)) return -1
#define termdo(a, b, c)               if(-1 == term(a, b, c)) return -1
#define conditiondo(a, b, c)          if(-1 == condition(a, b, c)) return -1
#define statementdo(a, b, c)          if(-1 == statement(a, b, c)) return -1
#define constdeclarationdo(a, b, c)   if(-1 == constdeclaration(a, b, c)) return -1
#define vardeclarationdo(a, b, c)     if(-1 == vardeclaration(a, b, c)) return -1

void error(int n);
int getsym();
int getch();
void init();
int gen(enum fct x, int y, int z);
int test(bool* s1, bool* s2, int n);
int inset(int e, bool* s);
int addset(bool* sr, bool* s1, bool* s2, int n);
int subset(bool* sr, bool* s1, bool* s2, int n);
int mulset(bool* sr, bool* s1, bool* s2, int n);
int block(int lev, int tx, bool* fsys);
void interpret();
int factor(bool* fsys, int* ptx, int lev);
int term(bool* fsys, int* ptx, int lev);
int condition(bool* fsys, int* ptx, int lev);
int expression(bool* fsys, int* ptx, int lev);
int statement(bool* fsys, int* ptx, int lev);
void listcode(int cx0);
int vardeclaration(int* ptx, int lev, int* pdx);
int constdeclaration(int* ptx, int lev, int* pdx);
int position(char* idt, int tx);
void enter(enum object k, int* ptx, int lev, int* pdx);
int base(int l, int* s, int b);
