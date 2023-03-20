/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 2
#define YYMINOR 0
#define YYPATCH 20220114

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#undef YYBTYACC
#define YYBTYACC 0
#define YYDEBUGSTR YYPREFIX "debug"
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "grammar.y"
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "lex.yy.c"
    
	static void yyerror(const char* msg);

    struct symbol {
        char * id_name;
        char * data_type;
        int line;
    };
    
    struct table_elem {
    	struct symbol row;
    	struct table_elem *next;
    };
	
	struct node {
	  	struct node *left;
	  	struct node *right;
	  	char *token;
		char typenode[10];	/* NULL if is a variable     */
	};
    
	static void addError(char *);
    static void save_type();
    static int search(char *);
	static void insert_row(struct table_elem *);
    static void add();
	static struct node* mknode(struct node *, struct node *, char *);
	static int check_declaration(char *);
	static int compare_types(char *, char *);
	static char *get_type(char *);
	static int check_assignment(char *, char *);
	static int check_compare(char *, char *);
	static int getConvtype(char *);
	static char *getVal(struct node *);
	static char *getCondition(struct node *);
	static char *getConditions(struct node *);
	static char *getDeclaration(struct node *);
	static char *getAssignment(struct node *);
	static char *getWhile(struct node *);
	static char *getIfElse(struct node *);
	static char *getIO(struct node *);
	static char *getStatement(struct node *);
	static char *generateCode(struct node *);
	static void returnTree(struct node *, int);
	static void freeTable();
	static void freeTree();
	void getTable();
    void getTree();
	void getCode(FILE *);
	void getErrors();
	void freeAll();

    extern int countln;     						/* variable in lexer.l that counts the lines*/
	static struct table_elem *first, *last, *selected;		/* pointers for symbol table*/
	static struct node *head = NULL;						/* head of the parse tree*/
    static char type[10];             						/* used to set the variable type*/
	static char **errors = NULL;
	int err_num=0;
	static char *includes = "#include <stdio.h>\n#include <string.h>\n#include <stdlib.h>\n\n";
	static char *cts = "char * charToStr(char c) {char *temp = (char *) malloc (sizeof(char)); temp[0]=c; return temp;}\n";
	static char *cnct = "char * concat(char *dest, char *src) {char *temp; temp = strdup(dest); strcat(temp, src); return temp;}\n";
	static char *sbstr = "int isSubstr(char *str, char *substr) { if(strstr(str,substr)==NULL) return 0; else return 1; }\n";
	static char *gcn = "char getCharN(char *str, int n) {if(n<strlen(str)) return str[n]; else return 0; }\n";
	static char *dnc = "char *delNChar(char *str, int n, int s) { switch(s) { case 0: { if(n>=strlen(str)) { return strdup(\"\"); } else { char temp[strlen(str)-n+1]; for(int i=0; i<strlen(str); i++) { temp[i] = str[n+i]; } temp[strlen(str)+1]=0; return strdup(temp); } break; } case 1: { if(n>=strlen(str)) { return strdup(\"\"); } else { char temp[strlen(str)-n+1]; for(int i=0; i<strlen(str)-n; i++) { temp[i] = str[i]; } temp[strlen(str)-n+1]=0; return strdup(temp); } break; } } }\n";
	static char *getStr = "char * getStringa() { char temp[BUFSIZ]; scanf(\"%s\", temp); getchar(); return strdup(temp); }\n";
	static char *mn = "\nint main(){\n";
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 74 "grammar.y"
typedef union YYSTYPE { 
	struct { 
		char *name; 
		struct node* nd;
	} nd_obj;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 109 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

#if !(defined(yylex) || defined(YYSTATE))
int YYLEX_DECL();
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define INTERO 257
#define REALE 258
#define CARATTERE 259
#define STRINGA 260
#define READ 261
#define WRITE 262
#define LESS 263
#define LEQ 264
#define GRTR 265
#define GEQ 266
#define NEQ 267
#define EQUALS 268
#define ADD 269
#define SUB 270
#define MUL 271
#define DIV 272
#define MOD 273
#define AND 274
#define OR 275
#define SE 276
#define ALLORA 277
#define ALTRIMENTI 278
#define MENTRE 279
#define LEFTBRKT 280
#define RIGHTBRKT 281
#define LEFT 282
#define RIGHT 283
#define ID 284
#define NUMINT 285
#define NUMDBL 286
#define CHAR 287
#define TEXT 288
#define NEWLINE 289
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    1,    1,    1,    1,    1,    1,    2,    2,
    3,    3,    4,   12,    5,    5,   10,   10,   10,    6,
    6,    6,    6,   11,   11,   11,   11,    7,    7,    7,
    7,    7,    7,    8,    8,    8,    8,    8,    9,    9,
};
static const YYINT yylen[] = {                            2,
    2,    3,    2,    3,    1,    7,    8,    0,    5,    0,
    3,    1,    3,    3,    3,    3,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
};
static const YYINT yydefred[] = {                         0,
   20,   21,   22,   23,    0,    0,    0,    0,    0,    0,
    0,    5,    0,    0,    0,   34,   35,   36,   37,   38,
   17,   24,   25,   26,   27,    0,    0,    0,    0,   18,
   19,    0,    0,    0,    3,   15,   16,    0,   39,   40,
    0,    0,   28,   29,   30,   31,   33,   32,    0,    0,
    4,    2,    0,   11,   14,   13,    0,    0,    0,    0,
    0,    0,    6,    0,    7,    0,    0,    0,    9,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  257,  258,  259,  260,  261,  262,  276,  279,  284,  291,
  292,  296,  297,  283,  282,  269,  270,  271,  272,  273,
  284,  285,  286,  287,  288,  294,  295,  299,  301,  302,
  303,  294,  282,  289,  284,  284,  301,  277,  274,  275,
  300,  301,  263,  264,  265,  266,  267,  268,  298,  277,
  301,  291,  280,  294,  301,  301,  280,  289,  289,  291,
  291,  281,  281,  278,  293,  280,  289,  291,  281,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                         10,
   11,   65,   26,   27,   12,   13,   49,   28,   41,   29,
   30,   31,
};
static const YYINT yysindex[] = {                      -238,
    0,    0,    0,    0, -280, -268, -222, -222, -267,    0,
 -273,    0, -259, -254, -222,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0, -260, -263, -222, -258,    0,
    0, -251, -222, -238,    0,    0,    0, -249,    0,    0,
 -222, -222,    0,    0,    0,    0,    0,    0, -222, -248,
    0,    0, -256,    0,    0,    0, -253, -238, -238, -242,
 -241, -236,    0, -237,    0, -245, -238, -229,    0,
};
static const YYINT yyrindex[] = {                      -244,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0, -224,    0,    0,    0,
    0,    0,    0,    1,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -244, -244,    0,
    0, -235,    0,    0,    0,    0, -244,    0,    0,
};
#if YYBTYACC
static const YYINT yycindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
#endif
static const YYINT yygindex[] = {                       -30,
    0,    0,   -6,    0,    0,    0,    0,    0,    0,  -15,
    0,    0,
};
#define YYTABLESIZE 290
static const YYINT yytable[] = {                         37,
    1,   32,   14,   52,   43,   44,   45,   46,   47,   48,
   39,   40,   42,   15,   33,   34,   38,   51,    1,    2,
    3,    4,    5,    6,   35,   50,   55,   60,   61,   36,
   53,   57,   58,   56,   54,   59,   68,    7,   62,   63,
    8,   64,   66,   67,    8,    9,   16,   17,   18,   19,
   20,   69,   12,   10,    0,    0,    0,    0,    0,    0,
    0,   21,   22,   23,   24,   25,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    1,    0,    0,    0,    0,    0,    0,    0,    8,
};
static const YYINT yycheck[] = {                         15,
    0,    8,  283,   34,  263,  264,  265,  266,  267,  268,
  274,  275,   28,  282,  282,  289,  277,   33,  257,  258,
  259,  260,  261,  262,  284,  277,   42,   58,   59,  284,
  280,  280,  289,   49,   41,  289,   67,  276,  281,  281,
  279,  278,  280,  289,  289,  284,  269,  270,  271,  272,
  273,  281,  277,  289,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  284,  285,  286,  287,  288,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  281,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  289,
};
#if YYBTYACC
static const YYINT yyctable[] = {                        -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
};
#endif
#define YYFINAL 10
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 289
#define YYUNDFTOKEN 304
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"$end",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"error","INTERO","REALE","CARATTERE",
"STRINGA","READ","WRITE","LESS","LEQ","GRTR","GEQ","NEQ","EQUALS","ADD","SUB",
"MUL","DIV","MOD","AND","OR","SE","ALLORA","ALTRIMENTI","MENTRE","LEFTBRKT",
"RIGHTBRKT","LEFT","RIGHT","ID","NUMINT","NUMDBL","CHAR","TEXT","NEWLINE",
"$accept","statements","statement","else","conditions","condition","io","type",
"compare","mathop","logicop","val","value","operation","illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : statements",
"statements : statement NEWLINE",
"statements : statement NEWLINE statements",
"statement : type ID",
"statement : ID LEFT val",
"statement : io",
"statement : MENTRE conditions ALLORA LEFTBRKT NEWLINE statements RIGHTBRKT",
"statement : SE conditions ALLORA LEFTBRKT NEWLINE statements RIGHTBRKT else",
"statement :",
"else : ALTRIMENTI LEFTBRKT NEWLINE statements RIGHTBRKT",
"else :",
"conditions : condition logicop conditions",
"conditions : condition",
"condition : val compare val",
"operation : mathop val val",
"io : READ RIGHT ID",
"io : WRITE LEFT val",
"val : ID",
"val : value",
"val : operation",
"type : INTERO",
"type : REALE",
"type : CARATTERE",
"type : STRINGA",
"value : NUMINT",
"value : NUMDBL",
"value : CHAR",
"value : TEXT",
"compare : LESS",
"compare : LEQ",
"compare : GRTR",
"compare : GEQ",
"compare : EQUALS",
"compare : NEQ",
"mathop : ADD",
"mathop : SUB",
"mathop : MUL",
"mathop : DIV",
"mathop : MOD",
"logicop : AND",
"logicop : OR",

};
#endif

#if YYDEBUG
int      yydebug;
#endif

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;
int      yynerrs;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
YYLTYPE  yyloc; /* position returned by actions */
YYLTYPE  yylloc; /* position from the lexer */
#endif

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#ifndef YYLLOC_DEFAULT
#define YYLLOC_DEFAULT(loc, rhs, n) \
do \
{ \
    if (n == 0) \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 0).last_line; \
        (loc).first_column = YYRHSLOC(rhs, 0).last_column; \
        (loc).last_line    = YYRHSLOC(rhs, 0).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, 0).last_column; \
    } \
    else \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 1).first_line; \
        (loc).first_column = YYRHSLOC(rhs, 1).first_column; \
        (loc).last_line    = YYRHSLOC(rhs, n).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, n).last_column; \
    } \
} while (0)
#endif /* YYLLOC_DEFAULT */
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#if YYBTYACC

#ifndef YYLVQUEUEGROWTH
#define YYLVQUEUEGROWTH 32
#endif
#endif /* YYBTYACC */

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#ifndef YYINITSTACKSIZE
#define YYINITSTACKSIZE 200
#endif

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  *p_base;
    YYLTYPE  *p_mark;
#endif
} YYSTACKDATA;
#if YYBTYACC

struct YYParseState_s
{
    struct YYParseState_s *save;    /* Previously saved parser state */
    YYSTACKDATA            yystack; /* saved parser stack */
    int                    state;   /* saved parser state */
    int                    errflag; /* saved error recovery status */
    int                    lexeme;  /* saved index of the conflict lexeme in the lexical queue */
    YYINT                  ctry;    /* saved index in yyctable[] for this conflict */
};
typedef struct YYParseState_s YYParseState;
#endif /* YYBTYACC */
/* variables for the parser stack */
static YYSTACKDATA yystack;
#if YYBTYACC

/* Current parser state */
static YYParseState *yyps = 0;

/* yypath != NULL: do the full parse, starting at *yypath parser state. */
static YYParseState *yypath = 0;

/* Base of the lexical value queue */
static YYSTYPE *yylvals = 0;

/* Current position at lexical value queue */
static YYSTYPE *yylvp = 0;

/* End position of lexical value queue */
static YYSTYPE *yylve = 0;

/* The last allocated position at the lexical value queue */
static YYSTYPE *yylvlim = 0;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
/* Base of the lexical position queue */
static YYLTYPE *yylpsns = 0;

/* Current position at lexical position queue */
static YYLTYPE *yylpp = 0;

/* End position of lexical position queue */
static YYLTYPE *yylpe = 0;

/* The last allocated position at the lexical position queue */
static YYLTYPE *yylplim = 0;
#endif

/* Current position at lexical token queue */
static YYINT  *yylexp = 0;

static YYINT  *yylexemes = 0;
#endif /* YYBTYACC */
#line 309 "grammar.y"

static void addError(char *s) {
	errors = (char **) realloc(errors, (err_num+1)*sizeof(char *));
	errors[err_num++] = strdup(s);
}

static void save_type() {	// saves data type of the last variable initialized
    strcpy(type, yytext);
}

static int search(char *id) {	// test if the variable was already declared
	int res=0;
    for (selected=first; selected!=NULL; selected=selected->next) {
        if (!strcmp(selected->row.id_name, id)) {   
            res=1;
        }
		else if (selected->next == NULL) last = selected;
    } 
    return res;
}

static void insert_row(struct table_elem *elem) {	// insert row in symbol table
	elem->row.id_name = strdup(yytext);
	elem->row.data_type = strdup(type);
	elem->row.line = countln;
}

static void add() {	// insert variable in symbol table
	char temp_error[BUFSIZ];
    if (first != NULL) {
		if (!(search(yytext))) {
			selected = last;
			selected->next = (struct table_elem *) malloc (sizeof(struct table_elem));
			selected = selected->next;
			insert_row(selected);
		}
		else {
			sprintf(temp_error, "Line %d: Multiple declarations of \"%s\"\n", countln, yytext);
			addError(temp_error);
		}
    }
	else {
		first = (struct table_elem *) malloc (sizeof(struct table_elem));
		insert_row(first);
	}
}

static struct node* mknode(struct node *l, struct node *r, char *t) {	// initialize the node of nd_obj
	struct node *newnode = (struct node *) malloc(sizeof(struct node));
	newnode->left = l;
	newnode->right = r;
	newnode->token = strdup(t);
	return newnode;
}

static int check_declaration(char * c) {	// check if a variable was declared before usage, generating an error if not
	int res=1;
	if (!(search(c))) {
		char temp[BUFSIZ];
		errors = (char **) realloc(errors, (err_num+1)*sizeof(char *));
		sprintf(temp, "Line %d: Variable \"%s\" not declared before usage\n", countln, c);
		errors[err_num++] = strdup(temp);
		res=0;
	}
	return res;
}

static int compare_types(char *type1, char *type2) { // analyze the types of the operands to understand which casting to do
	int res=0;	// if it's not modified than the types are the same
	if ((!strcmp(type1, "Intero") && !strcmp(type2, "Carattere")) || (!strcmp(type1, "Carattere") && !strcmp(type2, "Intero"))) res=1;
	else if ((!strcmp(type1, "Reale") && (!strcmp(type2, "Intero") || !strcmp(type2, "Carattere"))) || (!strcmp(type2, "Reale") && (!strcmp(type1, "Intero") || !strcmp(type1, "Carattere")))) res=2;
	else if ((!strcmp(type1, type2) && !strcmp(type1, "Carattere")) || (!strcmp(type1, "Stringa") && !strcmp(type2, "Carattere")) || (!strcmp(type1, "Carattere") && !strcmp(type2, "Stringa"))) res=3;
	else if ((!strcmp(type1, "Stringa") && !strcmp(type2, "Intero")) || (!strcmp(type1, "Stringa") && !strcmp(type2, "Reale"))) res=4;
	else if ((!strcmp(type1, "Intero") && !strcmp(type2, "Stringa"))) res=-1;
	else if ((!strcmp(type1, "Reale") && !strcmp(type2, "Stringa"))) res=-2;
	return res;
}

static int check_assignment(char *ltype, char *rtype) {	// check if the assignment is possible given the types of left and right val
	int res=0;	// if it's not modified than the types are the same
	if (!strcmp(ltype, "Intero")) {
		if (!strcmp(rtype, "Reale")) res=1;
		else if (!strcmp(rtype, "Carattere")) res=2;
		else if (!strcmp(rtype, "Stringa")) res=-1;
	}
	else if (!strcmp(ltype, "Reale")) {
		if (!strcmp(rtype, "Intero")) res=3;
		else if (!strcmp(rtype, "Carattere")) res=4;
		else if (!strcmp(rtype, "Stringa")) res=-2;
	}
	else if (!strcmp(ltype, "Carattere")) {
		if (!strcmp(rtype, "Intero")) res=5;
		else if (!strcmp(rtype, "Reale")) res=6;
		else if (!strcmp(rtype, "Stringa")) res=-3;
	}
	else if (!strcmp(ltype, "Stringa")) {
		if (!strcmp(rtype, "Intero")) res=-4;
		else if (!strcmp(rtype, "Reale")) res=-5;
		else if (!strcmp(rtype, "Carattere")) res=7;
	}
	return res;
}

static int check_compare(char *ltype, char *rtype) {	// check if the compare can be done given the types of left and right val
	int res=0;	// if it's not modified than the types are the same
	if (!strcmp(ltype, "Intero")) {
		if (!strcmp(rtype, "Reale")) res=1;
		else if (!strcmp(rtype, "Carattere")) res=2;
		else if (!strcmp(rtype, "Stringa")) res=-1;
	}
	else if (!strcmp(ltype, "Reale")) {
		if (!strcmp(rtype, "Intero")) res=3;
		else if (!strcmp(rtype, "Carattere")) res=4;
		else if (!strcmp(rtype, "Stringa")) res=-2;
	}
	else if (!strcmp(ltype, "Carattere")) {
		if (!strcmp(rtype, "Intero")) res=5;
		else if (!strcmp(rtype, "Reale")) res=6;
		else if (!strcmp(rtype, "Stringa")) res=-3;
	}
	else if (!strcmp(ltype, "Stringa")) {
		if (!strcmp(rtype, "Intero")) res=-4;
		else if (!strcmp(rtype, "Reale")) res=-5;
		else if (!strcmp(rtype, "Carattere")) res=-6;
	}
	return res;
}

static char * get_type(char *var) {	// return the data type of the given variable
	char *res=NULL;
	for (selected = first; selected != NULL; selected = selected->next) {
        if (!strcmp(selected->row.id_name, var)) {   
            res = selected->row.data_type;
        }
    }
	return res;	
}

static int getConvtype(char *type) {	// returns the converted type in C language given the one of BPLC
	int res;
	if (!strcmp(type, "Intero")) res=0;
	else if (!strcmp(type, "Reale")) res=1;
	else if (!strcmp(type, "Carattere")) res=2;
	else if (!strcmp(type, "Stringa")) res=3;
	return res;
}

static char * getVal(struct node *n) {		// returns val converted in C language
	char *val, *Lval, *Rval, *typeLvalue, *typeRvalue, convtype[7];
	if (n->left==NULL && n->right==NULL) {
		val = (char *) malloc (strlen(n->token)+1);
		sprintf(val, "%s", n->token);
	}
	else {
		typeLvalue = (get_type(n->left->token) == NULL) ? n->left->typenode : get_type(n->left->token);
		typeRvalue = (get_type(n->right->token) == NULL) ? n->right->typenode : get_type(n->right->token);
		Lval = getVal(n->left);
		Rval = getVal(n->right);
		switch(getConvtype(n->typenode)) {
			case 0: {
				strcpy(convtype, "int");
				break;
			}
			case 1: {
				strcpy(convtype, "double");
				break;
			}
			case 2: {
				strcpy(convtype, "char");
				break;
			}
			case 3: {
				strcpy(convtype, "char *");
				break;
			}
		}
		switch (compare_types(typeLvalue, typeRvalue)) {
			case 1:
			case 2: {
				val = (char *) malloc (24+strlen(Lval)+strlen(Rval));
				sprintf(val, "((%s)%s %s (%s)%s)", convtype, Lval, n->token, convtype, Rval);
				break;
			}
			case 3: {
				if(!strcmp(typeLvalue, "Stringa")) {
					if (!strcmp(n->token, "+")) {
						val = (char *) malloc (30+strlen(Lval)+strlen(Rval));
						sprintf(val, "strdup(concat(%s, charToStr(%s)))", Lval, Rval);
					}
					else if (!strcmp(n->token, "%")) {
						val = (char *) malloc (26+strlen(Lval)+strlen(Rval));
						sprintf(val, "isSubstr(%s, charToStr(%s))", Lval, Rval);
					}
				}
				else {
					if (!strcmp(n->token, "+")) {
						val = (char *) malloc (30+strlen(Lval)+strlen(Rval));
						sprintf(val, "strdup(concat(charToStr(%s), %s))", Lval, Rval);
					}
					else if (!strcmp(n->token, "%")) {
						val = (char *) malloc (24+strlen(Lval)+strlen(Rval));
						sprintf(val, "isSubstr(charToStr(%s), %s)", Lval, Rval);
					}
				}
				break;
			}
			case 4: {
				if (!strcmp(n->token, "*")) {
					val = (char *) malloc (18+strlen(Lval)+strlen(Rval));
					sprintf(val, "getCharN(%s, (int)%s)", Lval, Rval);
				}
				else if (!strcmp(n->token, "-")) {
					val = (char *) malloc (21+strlen(Lval)+strlen(Rval));
					sprintf(val, "delNChar(%s, (int)%s, 1)", Lval, Rval);
				}
				else if (!strcmp(n->token, "/")) {
					val = (char *) malloc (21+strlen(Lval)+strlen(Rval));
					sprintf(val, "delNChar(%s, (int)%s, 0)", Lval, Rval);
				}
				break;
			}
			default: {
				if(!strcmp(typeLvalue, "Stringa")) {
					if (!strcmp(n->token, "+")) {
						val = (char *) malloc (18+strlen(Lval)+strlen(Rval));
						sprintf(val, "strdup(concat(%s, %s))", Lval, Rval);
					}
					else if (!strcmp(n->token, "%")) {
						val = (char *) malloc (13+strlen(Lval)+strlen(Rval));
						sprintf(val, "isSubstr(%s, %s)", Lval, Rval);
					}
				}
				else {
					val = (char *) malloc (5+strlen(Lval)+strlen(Rval));
					sprintf(val, "(%s %s %s)", Lval, n->token, Rval);
				}
				break;
			}
		}
	}
	return val;
}

static char * getCondition(struct node *n) {	// returns the condition in C language
	char *condition, operator[3], *Lval, *Rval, *typeLvalue, *typeRvalue; 
	Lval = getVal(n->left);
	Rval = getVal(n->right);
	typeLvalue = (get_type(n->left->token) == NULL) ? n->left->typenode : get_type(n->left->token);
	typeRvalue = (get_type(n->right->token) == NULL) ? n->right->typenode : get_type(n->right->token);
	if(!strcmp(n->token, "<")) strcpy(operator, "<");
	else if (!strcmp(n->token, "<=")) strcpy(operator, "<=");
	else if (!strcmp(n->token, ">")) strcpy(operator, ">");
	else if (!strcmp(n->token, ">=")) strcpy(operator, ">=");
	else if (!strcmp(n->token, "=")) strcpy(operator, "==");
	else strcpy(operator, "!=");
	if(strcmp(typeLvalue, "Stringa")) {
		switch(check_compare(typeLvalue,typeRvalue)) {
			case 1:
			case 2: {
				condition = (char *) malloc (11+strlen(Lval)+strlen(Rval));
				sprintf(condition, "%s %s (int)%s", Lval, operator, Rval);
				break;
			}
			case 3: {
				condition = (char *) malloc (14+strlen(Lval)+strlen(Rval));
				sprintf(condition, "%s %s (double)%s", Lval, operator, Rval);
				break;
			}
			case 4: {
				condition = (char *) malloc (19+strlen(Lval)+strlen(Rval));
				sprintf(condition, "%s %s (double)(int)%s", Lval, operator, Rval);
				break;
			}
			case 5: {
				condition = (char *) malloc (12+strlen(Lval)+strlen(Rval));
				sprintf(condition, "%s %s (char)%s", Lval, operator, Rval);
				break;
			}
			case 6: {
				condition = (char *) malloc (17+strlen(Lval)+strlen(Rval));
				sprintf(condition, "%s %s (char)(int)%s", Lval, operator, Rval);
				break;
			}
			default: {
				condition = (char *) malloc (5+strlen(Lval)+strlen(Rval));
				sprintf(condition, "%s %s %s", Lval, operator, Rval);
				break;
			}
		}
	}
	else {
		condition = (char *) malloc (16+strlen(Lval)+strlen(Rval));
		sprintf(condition, "strcmp(%s, %s) %s 0", Lval, operator, Rval);
	}
	return condition;
}

static char * getConditions(struct node *n) {	// returns the conditions in C language
	char *conditions, *Lval, *Rval;
	if(!strcmp(n->right->token, "AND") || !strcmp(n->right->token, "OR")) {	// multiple conditions branch
		Lval = getCondition(n->left);
		Rval = getConditions(n->right);
		conditions = (char *) malloc (5+strlen(Lval)+strlen(Rval));
		if (!strcmp(n->token, "AND")) {
			sprintf(conditions, "%s && %s", Lval, Rval);
		}
		else if (!strcmp(n->token, "OR")) {
			sprintf(conditions, "%s || %s", Lval, Rval);
		}
	}
	else {
		if (!strcmp(n->token, "AND")) {	// couple conditions branch
			Lval = getCondition(n->left);
			Rval = getCondition(n->right);
			conditions = (char *) malloc (5+strlen(Lval)+strlen(Rval));
			sprintf(conditions, "%s && %s", Lval, Rval);
		}
		else if (!strcmp(n->token, "OR")) {
			Lval = getCondition(n->left);
			Rval = getCondition(n->right);
			conditions = (char *) malloc (5+strlen(Lval)+strlen(Rval));
			sprintf(conditions, "%s || %s", Lval, Rval);
		}
		else { // single condition branck
			conditions = getCondition(n);
		}
	}
	return conditions;
}

static char * getDeclaration(struct node *n) {		// returns the declaration in C language
	char *declaration, convtype[7];
	switch(getConvtype(get_type(n->right->token))) {
		case 0: {
			strcpy(convtype, "int");
			break;
		}
		case 1: {
			strcpy(convtype, "double");
			break;
		}
		case 2: {
			strcpy(convtype, "char");
			break;
		}
		case 3: {
			strcpy(convtype, "char *");
			break;
		}
	}
	declaration = (char *) malloc (8+strlen(n->right->token));
	sprintf(declaration, "%s %s;\n", convtype, n->right->token);
	return declaration;
}

static char * getAssignment(struct node *n) {		// returns the assignment in C language
	char *assignment, *Rval, *typeRvalue ;
	Rval = getVal(n->right);
	typeRvalue = (get_type(n->right->token) == NULL) ? n->right->typenode : get_type(n->right->token);
	switch(check_assignment(get_type(n->left->token), typeRvalue)) {
		case 0: {
			if(strcmp(get_type(n->left->token), "Stringa")) {
				assignment = (char *) malloc (strlen(n->left->token)+strlen(Rval));
				sprintf(assignment, "%s = %s;\n", n->left->token, Rval);
			}
			else {
				assignment = (char *) malloc (13+strlen(n->left->token)+strlen(Rval));
				sprintf(assignment, "strcpy(%s, %s);\n", n->left->token, Rval);
			}
			break;
		}
		case 1:
		case 2: {
			assignment = (char *) malloc (12+strlen(n->left->token)+strlen(Rval));
			sprintf(assignment, "%s = (int) %s;\n", n->left->token, Rval);
			break;
		}
		case 3:
		case 4: {
			assignment = (char *) malloc (15+strlen(n->left->token)+strlen(Rval));
			sprintf(assignment, "%s = (double) %s;\n", n->left->token, Rval);
			break;
		}
		case 5:
		case 6: {
			assignment = (char *) malloc (19+strlen(n->left->token)+strlen(Rval));
			sprintf(assignment, "%s = (char) (int) %s;\n", n->left->token, Rval);
			break;
		}
		case 7: {
			assignment = (char *) malloc (17+strlen(n->left->token)+strlen(Rval));
			sprintf(assignment, "%s = charToStr(%s);\n", n->left->token, Rval);
			break;
		}
	}
	return assignment;
}

static char * getWhile(struct node *n) {	// returns the while in C language
	char *whileBlock, *whileCond, *whileCode;
	whileCond = getConditions(n->left);
	whileCode = generateCode(n->right);
	whileBlock = (char *) malloc (14+strlen(whileCond)+strlen(whileCode));
	sprintf(whileBlock, "while (%s) {\n%s}\n", whileCond, whileCode);
	return whileBlock;
}

static char * getIfElse(struct node *n) {	// retruns the if-else in C language
	char *ifBlock, *elseBlock, *ifCond, *ifCode, *elseCode;
	ifCond = getCondition(n->left->left);
	ifCode = generateCode(n->left->right);
	ifBlock = (char *) malloc (11+strlen(ifCond)+strlen(ifCode));
	sprintf(ifBlock, "if (%s) {\n%s}\n", ifCond, ifCode);
	if (n->right != NULL) {
		elseCode = generateCode(n->right->right);
		elseBlock = (char *) malloc (10+strlen(elseCode));
		sprintf(elseBlock, "else {\n%s}\n", elseCode);
		strcat(ifBlock,elseBlock);
	}
	return ifBlock;
}

static char * getIO(struct node *n) {		// returns I/O operations from stdin and stdout in C language
	char *inputOutput, convpattern[4], *type, *Rval;
	type = (get_type(n->right->token)!=NULL) ? get_type(n->right->token) : n->right->typenode;
	if (!strcmp(type, "Intero")) strcpy(convpattern, "%d");
	else if (!strcmp(type, "Reale")) strcpy(convpattern, "%lf");
	else if (!strcmp(type, "Carattere")) strcpy(convpattern, "%c");
	else if (!strcmp(type, "Stringa")) strcpy(convpattern, "%s");
	if(!strcmp(n->left->token, "LEGGI")) {
		inputOutput = (char *) malloc (18+strlen(n->right->token));
		if(strcmp(type, "Stringa")) {
			sprintf(inputOutput, "scanf(\"%s\", &%s);\n", convpattern, n->right->token);
		} 
		else {
			sprintf(inputOutput, "%s = getStringa();\n", n->right->token);
		}
	}
	else {
		Rval = getVal(n->right);
		inputOutput = (char *) malloc (18+strlen(Rval));
		sprintf(inputOutput, "printf(\"%s\", %s);\n", convpattern, Rval);
	}
	return inputOutput;
}

static char * getStatement(struct node *n) {	// returns any statement in C language
	char *stat;
	if (!strcmp(n->token, "DICHIARAZIONE")) {
		stat = getDeclaration(n);
	}
	else if (!strcmp(n->token, "ASSEGNAMENTO")) {
		stat = getAssignment(n);
	}
	else if (!strcmp(n->token, "MENTRE")) {
		stat = getWhile(n);
	}
	else if (!strcmp(n->token, "SE-ALTRIMENTI")) {
		stat = getIfElse(n);
	}
	else if (!strcmp(n->token, "I/O")) {
		stat = getIO(n);
	}
	return stat;
}

static char * generateCode(struct node *n) {	// generates the whole code in C language
	char *Lbranch, *Rbranch;
	if (n!=NULL && !strcmp(n->token, "STATEMENTS")) {
		Lbranch = (n->left!=NULL) ? strdup(getStatement(n->left)) : strdup("");
		Rbranch = (n->right!=NULL) ? strdup(generateCode(n->right)) : strdup("");
		return strcat(Lbranch, Rbranch);
	}
	else {
		return strdup(getStatement(n));
	}
}

static void returnTree(struct node *tree, int indent) {	// fun to print parse tree
	printf("%s\n", tree->token);
	if (tree->left) {
		for(int i=0; i<=indent; printf("\t"),i++);
		returnTree(tree->left, indent+1);
	}
	if (tree->right) {
		for(int i=0; i<=indent; printf("\t"),i++);
		returnTree(tree->right, indent+1);
	}
}

static void freeTable() {
	if(first) {
		selected = first;
		while(selected->next!=NULL) {
			last = selected;
			selected = selected->next;
			free(last);
		}
	}
}

static void freeTree(struct node *tree) {
	if (tree) {
		if (tree->left) {
			freeTree(tree->left);
		}
		if (tree->right) {
			freeTree(tree->right);
		}
		free(tree);
	}
}

void getTable() {	// fun to print symbol table
	printf("SYMBOL\t\tDATATYPE\t\tLINE\n\n");
	for (selected = first; selected != NULL; selected = selected->next) {
		printf("%s\t\t%s\t\t%d\n", selected->row.id_name, selected->row.data_type, selected->row.line);
	}
	printf("\n");
}
    
void getTree() {	// fun to print the parse tree
	returnTree(head, 0);
}

void getCode(FILE *out) {	// fun to get the compiled code
	char *code = generateCode(head);
	fprintf(out, "%s", includes);
	fprintf(out, "%s", cts);
	fprintf(out, "%s", cnct);
	fprintf(out, "%s", sbstr);
	fprintf(out, "%s", gcn);
	fprintf(out, "%s", dnc);
	fprintf(out, "%s", getStr);
	fprintf(out, "%s", mn);
	fprintf(out, "%s", code);
	fprintf(out, "}\n");
	free(code);
}

void getErrors() {	// fun to print the errors generated during the compiling
	printf("%d errors\n", err_num);
	for (int i=0; i<err_num; i++) {
		printf("%s", errors[i]);
		free(errors[i]);
    }
	free(errors);
}

void freeAll() {
	freeTable();
	freeTree(head);
}

void yyerror(const char* msg) {		// it's called by default by lex/yacc when a syntax error occours
	char temp_error[BUFSIZ];
	sprintf(temp_error, "Line %d: %s\n", countln, msg);
	addError(temp_error);
}
#line 1102 "y.tab.c"

/* For use in generated program */
#define yydepth (int)(yystack.s_mark - yystack.s_base)
#if YYBTYACC
#define yytrial (yyps->save)
#endif /* YYBTYACC */

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE *newps;
#endif

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    newps = (YYLTYPE *)realloc(data->p_base, newsize * sizeof(*newps));
    if (newps == 0)
        return YYENOMEM;

    data->p_base = newps;
    data->p_mark = newps + i;
#endif

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;

#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%sdebug: stack size increased to %d\n", YYPREFIX, newsize);
#endif
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    free(data->p_base);
#endif
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif /* YYPURE || defined(YY_NO_LEAKS) */
#if YYBTYACC

static YYParseState *
yyNewState(unsigned size)
{
    YYParseState *p = (YYParseState *) malloc(sizeof(YYParseState));
    if (p == NULL) return NULL;

    p->yystack.stacksize = size;
    if (size == 0)
    {
        p->yystack.s_base = NULL;
        p->yystack.l_base = NULL;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        p->yystack.p_base = NULL;
#endif
        return p;
    }
    p->yystack.s_base    = (YYINT *) malloc(size * sizeof(YYINT));
    if (p->yystack.s_base == NULL) return NULL;
    p->yystack.l_base    = (YYSTYPE *) malloc(size * sizeof(YYSTYPE));
    if (p->yystack.l_base == NULL) return NULL;
    memset(p->yystack.l_base, 0, size * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    p->yystack.p_base    = (YYLTYPE *) malloc(size * sizeof(YYLTYPE));
    if (p->yystack.p_base == NULL) return NULL;
    memset(p->yystack.p_base, 0, size * sizeof(YYLTYPE));
#endif

    return p;
}

static void
yyFreeState(YYParseState *p)
{
    yyfreestack(&p->yystack);
    free(p);
}
#endif /* YYBTYACC */

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab
#if YYBTYACC
#define YYVALID        do { if (yyps->save)            goto yyvalid; } while(0)
#define YYVALID_NESTED do { if (yyps->save && \
                                yyps->save->save == 0) goto yyvalid; } while(0)
#endif /* YYBTYACC */

int
YYPARSE_DECL()
{
    int yym, yyn, yystate, yyresult;
#if YYBTYACC
    int yynewerrflag;
    YYParseState *yyerrctx = NULL;
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  yyerror_loc_range[3]; /* position of error start/end (0 unused) */
#endif
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
    if (yydebug)
        fprintf(stderr, "%sdebug[<# of symbols on state stack>]\n", YYPREFIX);
#endif
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    memset(yyerror_loc_range, 0, sizeof(yyerror_loc_range));
#endif

#if YYBTYACC
    yyps = yyNewState(0); if (yyps == 0) goto yyenomem;
    yyps->save = 0;
#endif /* YYBTYACC */
    yym = 0;
    /* yyn is set below */
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base;
#endif
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
#if YYBTYACC
        do {
        if (yylvp < yylve)
        {
            /* we're currently re-reading tokens */
            yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc = *yylpp++;
#endif
            yychar = *yylexp++;
            break;
        }
        if (yyps->save)
        {
            /* in trial mode; save scanner results for future parse attempts */
            if (yylvp == yylvlim)
            {   /* Enlarge lexical value queue */
                size_t p = (size_t) (yylvp - yylvals);
                size_t s = (size_t) (yylvlim - yylvals);

                s += YYLVQUEUEGROWTH;
                if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL) goto yyenomem;
                if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL) goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL) goto yyenomem;
#endif
                yylvp   = yylve = yylvals + p;
                yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp   = yylpe = yylpsns + p;
                yylplim = yylpsns + s;
#endif
                yylexp  = yylexemes + p;
            }
            *yylexp = (YYINT) YYLEX;
            *yylvp++ = yylval;
            yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *yylpp++ = yylloc;
            yylpe++;
#endif
            yychar = *yylexp++;
            break;
        }
        /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
        yychar = YYLEX;
#if YYBTYACC
        } while (0);
#endif /* YYBTYACC */
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, " <%s>", YYSTYPE_TOSTRING(yychar, yylval));
#endif
            fputc('\n', stderr);
        }
#endif
    }
#if YYBTYACC

    /* Do we have a conflict? */
    if (((yyn = yycindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
        yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        YYINT ctry;

        if (yypath)
        {
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: CONFLICT in state %d: following successful trial parse\n",
                                YYDEBUGSTR, yydepth, yystate);
#endif
            /* Switch to the next conflict context */
            save = yypath;
            yypath = save->save;
            save->save = NULL;
            ctry = save->ctry;
            if (save->state != yystate) YYABORT;
            yyFreeState(save);

        }
        else
        {

            /* Unresolved conflict - start/continue trial parse */
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
            {
                fprintf(stderr, "%s[%d]: CONFLICT in state %d. ", YYDEBUGSTR, yydepth, yystate);
                if (yyps->save)
                    fputs("ALREADY in conflict, continuing trial parse.\n", stderr);
                else
                    fputs("Starting trial parse.\n", stderr);
            }
#endif
            save                  = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (save == NULL) goto yyenomem;
            save->save            = yyps->save;
            save->state           = yystate;
            save->errflag         = yyerrflag;
            save->yystack.s_mark  = save->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (save->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            save->yystack.l_mark  = save->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (save->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            save->yystack.p_mark  = save->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (save->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            ctry                  = yytable[yyn];
            if (yyctable[ctry] == -1)
            {
#if YYDEBUG
                if (yydebug && yychar >= YYEOF)
                    fprintf(stderr, "%s[%d]: backtracking 1 token\n", YYDEBUGSTR, yydepth);
#endif
                ctry++;
            }
            save->ctry = ctry;
            if (yyps->save == NULL)
            {
                /* If this is a first conflict in the stack, start saving lexemes */
                if (!yylexemes)
                {
                    yylexemes = (YYINT *) malloc((YYLVQUEUEGROWTH) * sizeof(YYINT));
                    if (yylexemes == NULL) goto yyenomem;
                    yylvals   = (YYSTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYSTYPE));
                    if (yylvals == NULL) goto yyenomem;
                    yylvlim   = yylvals + YYLVQUEUEGROWTH;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpsns   = (YYLTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYLTYPE));
                    if (yylpsns == NULL) goto yyenomem;
                    yylplim   = yylpsns + YYLVQUEUEGROWTH;
#endif
                }
                if (yylvp == yylve)
                {
                    yylvp  = yylve = yylvals;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp  = yylpe = yylpsns;
#endif
                    yylexp = yylexemes;
                    if (yychar >= YYEOF)
                    {
                        *yylve++ = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                        *yylpe++ = yylloc;
#endif
                        *yylexp  = (YYINT) yychar;
                        yychar   = YYEMPTY;
                    }
                }
            }
            if (yychar >= YYEOF)
            {
                yylvp--;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp--;
#endif
                yylexp--;
                yychar = YYEMPTY;
            }
            save->lexeme = (int) (yylvp - yylvals);
            yyps->save   = save;
        }
        if (yytable[yyn] == ctry)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                                YYDEBUGSTR, yydepth, yystate, yyctable[ctry]);
#endif
            if (yychar < 0)
            {
                yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp++;
#endif
                yylexp++;
            }
            if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                goto yyoverflow;
            yystate = yyctable[ctry];
            *++yystack.s_mark = (YYINT) yystate;
            *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *++yystack.p_mark = yylloc;
#endif
            yychar  = YYEMPTY;
            if (yyerrflag > 0) --yyerrflag;
            goto yyloop;
        }
        else
        {
            yyn = yyctable[ctry];
            goto yyreduce;
        }
    } /* End of code dealing with conflicts */
#endif /* YYBTYACC */
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                            YYDEBUGSTR, yydepth, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yylloc;
#endif
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;
#if YYBTYACC

    yynewerrflag = 1;
    goto yyerrhandler;
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */

yyerrlab:
    /* explicit YYERROR from an action -- pop the rhs of the rule reduced
     * before looking for error recovery */
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif

    yynewerrflag = 0;
yyerrhandler:
    while (yyps->save)
    {
        int ctry;
        YYParseState *save = yyps->save;
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: ERROR in state %d, CONFLICT BACKTRACKING to state %d, %d tokens\n",
                            YYDEBUGSTR, yydepth, yystate, yyps->save->state,
                    (int)(yylvp - yylvals - yyps->save->lexeme));
#endif
        /* Memorize most forward-looking error state in case it's really an error. */
        if (yyerrctx == NULL || yyerrctx->lexeme < yylvp - yylvals)
        {
            /* Free old saved error context state */
            if (yyerrctx) yyFreeState(yyerrctx);
            /* Create and fill out new saved error context state */
            yyerrctx                 = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (yyerrctx == NULL) goto yyenomem;
            yyerrctx->save           = yyps->save;
            yyerrctx->state          = yystate;
            yyerrctx->errflag        = yyerrflag;
            yyerrctx->yystack.s_mark = yyerrctx->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (yyerrctx->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yyerrctx->yystack.l_mark = yyerrctx->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (yyerrctx->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yyerrctx->yystack.p_mark = yyerrctx->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (yyerrctx->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yyerrctx->lexeme         = (int) (yylvp - yylvals);
        }
        yylvp          = yylvals   + save->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yylpp          = yylpsns   + save->lexeme;
#endif
        yylexp         = yylexemes + save->lexeme;
        yychar         = YYEMPTY;
        yystack.s_mark = yystack.s_base + (save->yystack.s_mark - save->yystack.s_base);
        memcpy (yystack.s_base, save->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
        yystack.l_mark = yystack.l_base + (save->yystack.l_mark - save->yystack.l_base);
        memcpy (yystack.l_base, save->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yystack.p_mark = yystack.p_base + (save->yystack.p_mark - save->yystack.p_base);
        memcpy (yystack.p_base, save->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
        ctry           = ++save->ctry;
        yystate        = save->state;
        /* We tried shift, try reduce now */
        if ((yyn = yyctable[ctry]) >= 0) goto yyreduce;
        yyps->save     = save->save;
        save->save     = NULL;
        yyFreeState(save);

        /* Nothing left on the stack -- error */
        if (!yyps->save)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%sdebug[%d,trial]: trial parse FAILED, entering ERROR mode\n",
                                YYPREFIX, yydepth);
#endif
            /* Restore state as it was in the most forward-advanced error */
            yylvp          = yylvals   + yyerrctx->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylpp          = yylpsns   + yyerrctx->lexeme;
#endif
            yylexp         = yylexemes + yyerrctx->lexeme;
            yychar         = yylexp[-1];
            yylval         = yylvp[-1];
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc         = yylpp[-1];
#endif
            yystack.s_mark = yystack.s_base + (yyerrctx->yystack.s_mark - yyerrctx->yystack.s_base);
            memcpy (yystack.s_base, yyerrctx->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yystack.l_mark = yystack.l_base + (yyerrctx->yystack.l_mark - yyerrctx->yystack.l_base);
            memcpy (yystack.l_base, yyerrctx->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yystack.p_mark = yystack.p_base + (yyerrctx->yystack.p_mark - yyerrctx->yystack.p_base);
            memcpy (yystack.p_base, yyerrctx->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yystate        = yyerrctx->state;
            yyFreeState(yyerrctx);
            yyerrctx       = NULL;
        }
        yynewerrflag = 1;
    }
    if (yynewerrflag == 0) goto yyinrecovery;
#endif /* YYBTYACC */

    YYERROR_CALL("syntax error");
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yyerror_loc_range[1] = yylloc; /* lookahead position is error start position */
#endif

#if !YYBTYACC
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
#endif
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: state %d, error recovery shifting to state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* lookahead position is error end position */
                yyerror_loc_range[2] = yylloc;
                YYLLOC_DEFAULT(yyloc, yyerror_loc_range, 2); /* position of error span */
                *++yystack.p_mark = yyloc;
#endif
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: error recovery discarding state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* the current TOS position is the error start position */
                yyerror_loc_range[1] = *yystack.p_mark;
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
                if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark, yystack.p_mark);
#else
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
                --yystack.s_mark;
                --yystack.l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                --yystack.p_mark;
#endif
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, error recovery discarding token %d (%s)\n",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
        }
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval, &yylloc);
#else
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
    yym = yylen[yyn];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: state %d, reducing by rule %d (%s)",
                        YYDEBUGSTR, yydepth, yystate, yyn, yyrule[yyn]);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            if (yym > 0)
            {
                int i;
                fputc('<', stderr);
                for (i = yym; i > 0; i--)
                {
                    if (i != yym) fputs(", ", stderr);
                    fputs(YYSTYPE_TOSTRING(yystos[yystack.s_mark[1-i]],
                                           yystack.l_mark[1-i]), stderr);
                }
                fputc('>', stderr);
            }
#endif
        fputc('\n', stderr);
    }
#endif
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)

    /* Perform position reduction */
    memset(&yyloc, 0, sizeof(yyloc));
#if YYBTYACC
    if (!yytrial)
#endif /* YYBTYACC */
    {
        YYLLOC_DEFAULT(yyloc, &yystack.p_mark[-yym], yym);
        /* just in case YYERROR is invoked within the action, save
           the start of the rhs as the error start position */
        yyerror_loc_range[1] = yystack.p_mark[1-yym];
    }
#endif

    switch (yyn)
    {
case 1:
#line 87 "grammar.y"
	{ yyval.nd_obj.nd = yystack.l_mark[-1].nd_obj.nd; }
#line 1775 "y.tab.c"
break;
case 2:
#line 88 "grammar.y"
	{ yyval.nd_obj.nd = mknode(yystack.l_mark[-2].nd_obj.nd, yystack.l_mark[0].nd_obj.nd, "STATEMENTS"); head = yyval.nd_obj.nd; }
#line 1780 "y.tab.c"
break;
case 3:
#line 91 "grammar.y"
	{
					add(); 
					yystack.l_mark[0].nd_obj.nd = mknode(NULL, NULL, yystack.l_mark[0].nd_obj.name); 
					yyval.nd_obj.nd = mknode(yystack.l_mark[-1].nd_obj.nd, yystack.l_mark[0].nd_obj.nd, "DICHIARAZIONE");
				}
#line 1789 "y.tab.c"
break;
case 4:
#line 96 "grammar.y"
	{
					int result_check;
					char temp_error[BUFSIZ], *typeRvalue;
					yystack.l_mark[-2].nd_obj.nd = mknode(NULL, NULL, yystack.l_mark[-2].nd_obj.name); 
					yyval.nd_obj.nd = mknode(yystack.l_mark[-2].nd_obj.nd, yystack.l_mark[0].nd_obj.nd, "ASSEGNAMENTO");
					if (check_declaration(yystack.l_mark[-2].nd_obj.name)) {
						typeRvalue = (get_type(yystack.l_mark[0].nd_obj.name) == NULL) ? yystack.l_mark[0].nd_obj.nd->typenode : get_type(yystack.l_mark[0].nd_obj.name);
						result_check = check_assignment(get_type(yystack.l_mark[-2].nd_obj.name), typeRvalue);
						switch(result_check) {	/* check if the datatypes of the assignment are compatible*/
							case -1: {
								sprintf(temp_error, "Line %d: Incompatible assignment Intero <- Stringa\n", countln);
								break;	
							}
							case -2: {
								sprintf(temp_error, "Line %d: Incompatible assignment Reale <- Stringa\n", countln);
								break;	
							}
							case -3: {
								sprintf(temp_error, "Line %d: Incompatible assignment Carattere <- Stringa\n", countln);
								break;	
							}
							case -4: {
								sprintf(temp_error, "Line %d: Incompatible assignment Stringa <- Intero\n", countln);
								break;	
							}
							case -5: {
								sprintf(temp_error, "Line %d: Incompatible assignment Stringa <- Reale\n", countln);
								break;	
							}
						}
						if(result_check<0) {
							addError(temp_error);
						}
					}
				}
#line 1828 "y.tab.c"
break;
case 5:
#line 131 "grammar.y"
	{ yyval.nd_obj.nd = yystack.l_mark[0].nd_obj.nd; }
#line 1833 "y.tab.c"
break;
case 6:
#line 132 "grammar.y"
	{
					yyval.nd_obj.nd = mknode(yystack.l_mark[-5].nd_obj.nd, yystack.l_mark[-1].nd_obj.nd, yystack.l_mark[-6].nd_obj.name);
				}
#line 1840 "y.tab.c"
break;
case 7:
#line 135 "grammar.y"
	{
					struct node *se = mknode(yystack.l_mark[-6].nd_obj.nd, yystack.l_mark[-2].nd_obj.nd, yystack.l_mark[-7].nd_obj.name); 
					yyval.nd_obj.nd = mknode(se, yystack.l_mark[0].nd_obj.nd, "SE-ALTRIMENTI");
				}
#line 1848 "y.tab.c"
break;
case 8:
#line 139 "grammar.y"
	{ yyval.nd_obj.nd = NULL; }
#line 1853 "y.tab.c"
break;
case 9:
#line 142 "grammar.y"
	{
				yyval.nd_obj.nd = mknode(NULL, yystack.l_mark[-1].nd_obj.nd, yystack.l_mark[-4].nd_obj.name);
			}
#line 1860 "y.tab.c"
break;
case 10:
#line 145 "grammar.y"
	{ yyval.nd_obj.nd = NULL; }
#line 1865 "y.tab.c"
break;
case 11:
#line 148 "grammar.y"
	{ yyval.nd_obj.nd = mknode(yystack.l_mark[-2].nd_obj.nd, yystack.l_mark[0].nd_obj.nd, yystack.l_mark[-1].nd_obj.name); }
#line 1870 "y.tab.c"
break;
case 12:
#line 149 "grammar.y"
	{ yyval.nd_obj.nd = yystack.l_mark[0].nd_obj.nd; }
#line 1875 "y.tab.c"
break;
case 13:
#line 152 "grammar.y"
	{ 
					int result_check;
					char temp_error[BUFSIZ], *typeLvalue, *typeRvalue;
					yyval.nd_obj.nd = mknode(yystack.l_mark[-2].nd_obj.nd, yystack.l_mark[0].nd_obj.nd, yystack.l_mark[-1].nd_obj.name);
					typeLvalue = (get_type(yystack.l_mark[-2].nd_obj.name) == NULL) ? yystack.l_mark[-2].nd_obj.nd->typenode : get_type(yystack.l_mark[-2].nd_obj.name);
					typeRvalue = (get_type(yystack.l_mark[0].nd_obj.name) == NULL) ? yystack.l_mark[0].nd_obj.nd->typenode : get_type(yystack.l_mark[0].nd_obj.name);
					result_check = check_compare(typeLvalue, typeRvalue);
					switch(result_check) {	/* check if the datatypes of the condition are compatible*/
						case -1: {
							sprintf(temp_error, "Line %d: Incompatible comparison between Intero and Stringa\n", countln);
							break;
						}
						case -2: {
							sprintf(temp_error, "Line %d: Incompatible comparison between Reale and Stringa\n", countln);
							break;
						}
						case -3: {
							sprintf(temp_error, "Line %d: Incompatible comparison between Carattere and Stringa\n", countln);
							break;
						}
						case -4: {
							sprintf(temp_error, "Line %d: Incompatible comparison between Stringa and Intero\n", countln);
							break;
						}
						case -5: {
							sprintf(temp_error, "Line %d: Incompatible comparison between Stringa and Reale\n", countln);
							break;
						}
						case -6: {
							sprintf(temp_error, "Line %d: Incompatible comparison between Stringa and Carattere\n", countln);
							break;
						}
					}
					if(result_check<0) {
						addError(temp_error);
					}
				}
#line 1916 "y.tab.c"
break;
case 14:
#line 191 "grammar.y"
	{
				char temp_error[BUFSIZ], *typeLvalue, *typeRvalue;
				temp_error[0]=0;
				yyval.nd_obj.nd = mknode(yystack.l_mark[-1].nd_obj.nd, yystack.l_mark[0].nd_obj.nd, yystack.l_mark[-2].nd_obj.name);
				typeLvalue = (get_type(yystack.l_mark[-1].nd_obj.name) == NULL) ? yystack.l_mark[-1].nd_obj.nd->typenode : get_type(yystack.l_mark[-1].nd_obj.name);
				typeRvalue = (get_type(yystack.l_mark[0].nd_obj.name) == NULL) ? yystack.l_mark[0].nd_obj.nd->typenode : get_type(yystack.l_mark[0].nd_obj.name);
				switch (compare_types(typeLvalue, typeRvalue)) { /* check if types are comparable and if they are a datatype is assigned to the operation*/
					case 0: {
						if(strcmp(typeLvalue, "Stringa")) {
							strcpy(yyval.nd_obj.nd->typenode, typeLvalue);
						}
						else {
							if(!strcmp(yystack.l_mark[-2].nd_obj.name, "+")) strcpy(yyval.nd_obj.nd->typenode, "Stringa");
							else if(!strcmp(yystack.l_mark[-2].nd_obj.name, "%")) strcpy(yyval.nd_obj.nd->typenode, "Intero");
							else {
								sprintf(temp_error, "Line %d: Invalid operand in operation %s %s %s, %s must be a Intero or Reale\n", countln, yystack.l_mark[-2].nd_obj.name, getVal(yystack.l_mark[-1].nd_obj.nd), getVal(yystack.l_mark[0].nd_obj.nd), getVal(yystack.l_mark[0].nd_obj.nd));
							}
						}
						break;	
					}
					case 1: {
						strcpy(yyval.nd_obj.nd->typenode, "Intero");
						break;	
					}
					case 2: {
						strcpy(yyval.nd_obj.nd->typenode, "Reale");
						break;	
					}
					case 3: {
						if(!strcmp(yystack.l_mark[-2].nd_obj.name, "+")) strcpy(yyval.nd_obj.nd->typenode, "Stringa");
						else if(!strcmp(yystack.l_mark[-2].nd_obj.name, "%")) strcpy(yyval.nd_obj.nd->typenode, "Intero");
						else {
							sprintf(temp_error, "Line %d: Invalid operand in operation %s %s %s, %s must be a Intero or Reale\n", countln, yystack.l_mark[-2].nd_obj.name, getVal(yystack.l_mark[-1].nd_obj.nd), getVal(yystack.l_mark[0].nd_obj.nd), getVal(yystack.l_mark[0].nd_obj.nd));
						}
						break;	
					}
					case 4: {
						if(!strcmp(yystack.l_mark[-2].nd_obj.name, "*")) strcpy(yyval.nd_obj.nd->typenode, "Carattere");
						else if(!strcmp(yystack.l_mark[-2].nd_obj.name, "-") || !strcmp(yystack.l_mark[-2].nd_obj.name, "/")) strcpy(yyval.nd_obj.nd->typenode, "Stringa");
						else {
							sprintf(temp_error, "Line %d: Invalid operand in operation %s %s %s, %s must be a Stringa or Carattere\n", countln, yystack.l_mark[-2].nd_obj.name, getVal(yystack.l_mark[-1].nd_obj.nd), getVal(yystack.l_mark[0].nd_obj.nd), getVal(yystack.l_mark[0].nd_obj.nd));
						}
						break;
					}
					case -1: {
						sprintf(temp_error, "Line %d: Incompatible types Intero and Stringa\n", countln);
						break;	
					}
					case -2: {
						sprintf(temp_error, "Line %d: Incompatible types Reale and Stringa\n", countln);
						break;	
					}
				}
				if(temp_error[0]) {
					addError(temp_error);
				}
			}
#line 1977 "y.tab.c"
break;
case 15:
#line 250 "grammar.y"
	{ 
			if (check_declaration(yystack.l_mark[0].nd_obj.name)) {
				yystack.l_mark[-2].nd_obj.nd = mknode(NULL, NULL, yystack.l_mark[-2].nd_obj.name); 
				yystack.l_mark[0].nd_obj.nd = mknode(NULL, NULL, yystack.l_mark[0].nd_obj.name); 
				yyval.nd_obj.nd = mknode(yystack.l_mark[-2].nd_obj.nd, yystack.l_mark[0].nd_obj.nd, "I/O");
			}
		}
#line 1988 "y.tab.c"
break;
case 16:
#line 257 "grammar.y"
	{ 
			if (yystack.l_mark[0].nd_obj.nd != NULL) {
				yystack.l_mark[-2].nd_obj.nd = mknode(NULL, NULL, yystack.l_mark[-2].nd_obj.name);
				yyval.nd_obj.nd = mknode(yystack.l_mark[-2].nd_obj.nd, yystack.l_mark[0].nd_obj.nd, "I/O");
			}
  		}
#line 1998 "y.tab.c"
break;
case 17:
#line 265 "grammar.y"
	{ 
			if (check_declaration(yystack.l_mark[0].nd_obj.name)) {
				yyval.nd_obj.nd = mknode(NULL, NULL, yystack.l_mark[0].nd_obj.name);
			}
			else {
				yyval.nd_obj.nd = NULL;
			}
		}
#line 2010 "y.tab.c"
break;
case 18:
#line 273 "grammar.y"
	{ yyval.nd_obj.nd = yystack.l_mark[0].nd_obj.nd; }
#line 2015 "y.tab.c"
break;
case 19:
#line 274 "grammar.y"
	{ yyval.nd_obj.nd = yystack.l_mark[0].nd_obj.nd; }
#line 2020 "y.tab.c"
break;
case 20:
#line 277 "grammar.y"
	{ save_type(); yyval.nd_obj.nd = mknode(NULL, NULL, yystack.l_mark[0].nd_obj.name); }
#line 2025 "y.tab.c"
break;
case 21:
#line 278 "grammar.y"
	{ save_type(); yyval.nd_obj.nd = mknode(NULL, NULL, yystack.l_mark[0].nd_obj.name); }
#line 2030 "y.tab.c"
break;
case 22:
#line 279 "grammar.y"
	{ save_type(); yyval.nd_obj.nd = mknode(NULL, NULL, yystack.l_mark[0].nd_obj.name); }
#line 2035 "y.tab.c"
break;
case 23:
#line 280 "grammar.y"
	{ save_type(); yyval.nd_obj.nd = mknode(NULL, NULL, yystack.l_mark[0].nd_obj.name); }
#line 2040 "y.tab.c"
break;
case 24:
#line 283 "grammar.y"
	{ strcpy(yyval.nd_obj.name, yystack.l_mark[0].nd_obj.name); yyval.nd_obj.nd = mknode(NULL, NULL, yystack.l_mark[0].nd_obj.name); strcpy(yyval.nd_obj.nd->typenode, "Intero"); }
#line 2045 "y.tab.c"
break;
case 25:
#line 284 "grammar.y"
	{ strcpy(yyval.nd_obj.name, yystack.l_mark[0].nd_obj.name); yyval.nd_obj.nd = mknode(NULL, NULL, yystack.l_mark[0].nd_obj.name); strcpy(yyval.nd_obj.nd->typenode, "Reale"); }
#line 2050 "y.tab.c"
break;
case 26:
#line 285 "grammar.y"
	{ strcpy(yyval.nd_obj.name, yystack.l_mark[0].nd_obj.name); yyval.nd_obj.nd = mknode(NULL, NULL, yystack.l_mark[0].nd_obj.name); strcpy(yyval.nd_obj.nd->typenode, "Carattere"); }
#line 2055 "y.tab.c"
break;
case 27:
#line 286 "grammar.y"
	{ strcpy(yyval.nd_obj.name, yystack.l_mark[0].nd_obj.name); yyval.nd_obj.nd = mknode(NULL, NULL, yystack.l_mark[0].nd_obj.name); strcpy(yyval.nd_obj.nd->typenode, "Stringa"); }
#line 2060 "y.tab.c"
break;
#line 2062 "y.tab.c"
    default:
        break;
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
        {
            fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[YYFINAL], yyval));
#endif
            fprintf(stderr, "shifting from state 0 to final state %d\n", YYFINAL);
        }
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yyloc;
#endif
        if (yychar < 0)
        {
#if YYBTYACC
            do {
            if (yylvp < yylve)
            {
                /* we're currently re-reading tokens */
                yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylloc = *yylpp++;
#endif
                yychar = *yylexp++;
                break;
            }
            if (yyps->save)
            {
                /* in trial mode; save scanner results for future parse attempts */
                if (yylvp == yylvlim)
                {   /* Enlarge lexical value queue */
                    size_t p = (size_t) (yylvp - yylvals);
                    size_t s = (size_t) (yylvlim - yylvals);

                    s += YYLVQUEUEGROWTH;
                    if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL)
                        goto yyenomem;
                    if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL)
                        goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL)
                        goto yyenomem;
#endif
                    yylvp   = yylve = yylvals + p;
                    yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp   = yylpe = yylpsns + p;
                    yylplim = yylpsns + s;
#endif
                    yylexp  = yylexemes + p;
                }
                *yylexp = (YYINT) YYLEX;
                *yylvp++ = yylval;
                yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                *yylpp++ = yylloc;
                yylpe++;
#endif
                yychar = *yylexp++;
                break;
            }
            /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
            yychar = YYLEX;
#if YYBTYACC
            } while (0);
#endif /* YYBTYACC */
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)\n",
                                YYDEBUGSTR, yydepth, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[yystate], yyval));
#endif
        fprintf(stderr, "shifting from state %d to state %d\n", *yystack.s_mark, yystate);
    }
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    *++yystack.p_mark = yyloc;
#endif
    goto yyloop;
#if YYBTYACC

    /* Reduction declares that this path is valid. Set yypath and do a full parse */
yyvalid:
    if (yypath) YYABORT;
    while (yyps->save)
    {
        YYParseState *save = yyps->save;
        yyps->save = save->save;
        save->save = yypath;
        yypath = save;
    }
#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%s[%d]: state %d, CONFLICT trial successful, backtracking to state %d, %d tokens\n",
                        YYDEBUGSTR, yydepth, yystate, yypath->state, (int)(yylvp - yylvals - yypath->lexeme));
#endif
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    yylvp          = yylvals + yypath->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yylpp          = yylpsns + yypath->lexeme;
#endif
    yylexp         = yylexemes + yypath->lexeme;
    yychar         = YYEMPTY;
    yystack.s_mark = yystack.s_base + (yypath->yystack.s_mark - yypath->yystack.s_base);
    memcpy (yystack.s_base, yypath->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
    yystack.l_mark = yystack.l_base + (yypath->yystack.l_mark - yypath->yystack.l_base);
    memcpy (yystack.l_base, yypath->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base + (yypath->yystack.p_mark - yypath->yystack.p_base);
    memcpy (yystack.p_base, yypath->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
    yystate        = yypath->state;
    goto yyloop;
#endif /* YYBTYACC */

yyoverflow:
    YYERROR_CALL("yacc stack overflow");
#if YYBTYACC
    goto yyabort_nomem;
yyenomem:
    YYERROR_CALL("memory exhausted");
yyabort_nomem:
#endif /* YYBTYACC */
    yyresult = 2;
    goto yyreturn;

yyabort:
    yyresult = 1;
    goto yyreturn;

yyaccept:
#if YYBTYACC
    if (yyps->save) goto yyvalid;
#endif /* YYBTYACC */
    yyresult = 0;

yyreturn:
#if defined(YYDESTRUCT_CALL)
    if (yychar != YYEOF && yychar != YYEMPTY)
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval, &yylloc);
#else
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */

    {
        YYSTYPE *pv;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYLTYPE *pp;

        for (pv = yystack.l_base, pp = yystack.p_base; pv <= yystack.l_mark; ++pv, ++pp)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv, pp);
#else
        for (pv = yystack.l_base; pv <= yystack.l_mark; ++pv)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
    }
#endif /* defined(YYDESTRUCT_CALL) */

#if YYBTYACC
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    while (yyps)
    {
        YYParseState *save = yyps;
        yyps = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
    while (yypath)
    {
        YYParseState *save = yypath;
        yypath = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
#endif /* YYBTYACC */
    yyfreestack(&yystack);
    return (yyresult);
}
