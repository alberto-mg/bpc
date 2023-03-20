#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "y.tab.c"

int main(int argc, char *argv[]) {
    int symbolTable=0, parseTree=0, generate=0;
    char *CName, *ExName, temp[BUFSIZ];
    FILE *compiled;
    extern int err_num;
    extern FILE *yyin;
    if(argc <= 3 && argc >=2) {
        if(argv[1][0]!='-' && argv[2]==NULL) {
            if(strstr(argv[1], ".bpc")) {
                yyin = fopen(argv[1], "r");
                if(yyin != NULL) {
                    yyparse();
                    if(err_num) {
                        getErrors();
                    }
                    else {
                        CName = (char *) malloc (strlen(argv[1]));
                        for (int i=0; argv[1][i-1]!='.'; i++) {
                            if(argv[1][i]!='.') CName[i]=argv[1][i];
                            else CName[i]='\0';
                        }
                        ExName = strdup(CName);
                        strcat(CName, ".c");
                        compiled = fopen(CName, "w");
                        getCode(compiled);
                        fclose(compiled);
                        sprintf(temp, "gcc %s -o %s", CName, ExName);
                        system(temp);
                        remove(CName);
                    }
                    fclose(yyin);
                }
                else {
                    printf("File not found\n");
                }
                freeAll();
            }
            else {
                printf("File format not recognized, the file must be a .bpc\n");
            }
        }
        else if(argv[1][0]=='-' && argv[1][1]=='h') {
            printf("The input must be './bpc [options] file'\nThe available options are:\n\t-s: print symbol table\n\t-p: print parse tree\n\t-c: generate C code\nIf no option is specified the file will be compiled\n");
        }
        else if(argv[1][0]=='-' && argv[2]!=NULL) {
            if(strstr(argv[2], ".bpc")) {
                yyin = fopen(argv[2], "r");
                if(yyin != NULL) {
                    yyparse();
                    if(err_num) {
                        getErrors();
                    }
                    else {
                        int i=0;
                        while(argv[1][i]!='\0') {
                            switch(argv[1][i]) {
                                case 's': {
                                    if(!symbolTable) {
                                        printf("SYMBOL TABLE:\n\n");
                                        getTable();
                                    }
                                    symbolTable=1;
                                    break;
                                }
                                case 'p': {
                                    if(!parseTree) {
                                        printf("PARSE TREE:\n\n");
                                        getTree();
                                    }
                                    parseTree=1;
                                    break;
                                }
                                case 'c': {
                                    if(!generate) {
                                        CName = (char *) malloc (strlen(argv[2]));
                                        for (int i=0; argv[2][i-1]!='.'; i++) {
                                            if(argv[2][i]!='.') CName[i]=argv[2][i];
                                            else CName[i]='\0';
                                        }
                                        strcat(CName, ".c");
                                        compiled = fopen(CName, "w");
                                        getCode(compiled);
                                        fclose(compiled);
                                    }
                                    generate=1;
                                    break;
                                }
                            }
                            i++;
                        }
                        fclose(yyin);
                    }
                }
                else {
                    printf("File not found\n");
                }
                freeAll();
            }
            else {
                printf("File format not recognized, the file must be a .bpc\n");
            }
        }
        else {
            printf("Invalid arguments, the input must be './bpc [options] file', try to use -h to see the options\n");
        }
    } 
    else {
        printf("Invalid arguments, the input must be './bpc [options] file', try to use -h to see the options\n");
    }
}
