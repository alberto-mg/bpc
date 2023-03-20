#ifndef _yy_defines_h_
#define _yy_defines_h_

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
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union YYSTYPE { 
	struct { 
		char *name; 
		struct node* nd;
	} nd_obj;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

#endif /* _yy_defines_h_ */
