#include <stdio.h>
#include <string.h>

#define norw 15 /* number of reserved words */
#define imax 32767 /* maximum integer value */
#define cmax 12 /* maximum number of chars for idents */
#define strmax 256 /* maximum length of strings */
#define MAX_TOKENS 1000


enum token_type{
    skipsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
    multsym = 6, slashsym = 7, fisym = 8, eqlsym = 9, neqsym = 10, lessym = 11, leqsym =
    12, gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17,
    semicolonsym = 18, periodsym = 19, becomessym = 20,
    beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26,
    callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31,
    readsym = 32, elsesym = 33, } ;

typedef struct Table{
    char lexeme[MAX_TOKENS][11];
    int tokenType[MAX_TOKENS];
    int size;
} Table;

void printProgram(FILE* fptr, FILE* output){
    fprintf(output, "Source Program:\n");
    printf("Source Program:\n");
    char c = fgetc(fptr);
    while(c != EOF){
        printf("%c", c);
        fprintf(output, "%c", c);
        c = fgetc(fptr);
    }
}

/* Adds entry with name lexeme and value value into table at table->size position */
void addEntry(Table* table, char* lexeme, int value){
    strcpy(table->lexeme[table->size], lexeme);
    table->tokenType[table->size] = value;
    table->size ++;
}

void printTable(Table* table, FILE* output){

    printf("\n%-16s|%5s\n", "Lexeme", " Token Type");
    fprintf(output, "\n%-16s%5s\n", "Lexeme", " Token Type");
    for(int i = 0; i < table->size; i++){
        if(table->tokenType[i] == 2 && length(table->lexeme[i]) > 11){
            printf("%-16s %-5s\n", table->lexeme[i], "Error: Ident length too long.");
            fprintf(output, "%-16s %-5s\n", table->lexeme[i], "Error: Ident length too long.");
            continue;
        }
        else if(table->tokenType[i] == 3 && length(table->lexeme[i]) > 5){
            printf("%-16s %-5s\n", table->lexeme[i], "Error: Number length too long.");
            fprintf(output, "%-16s %-5s\n", table->lexeme[i], "Error: Number length too long.");
            continue;
        }
        else if (table->tokenType[i] == 0){
            printf("%-16s %-5s\n", table->lexeme[i], "Error: Invalid Symbol.");
            fprintf(output, "%-16s %-5s\n", table->lexeme[i], "Error: Invalid Symbol.");
            continue;
        }
        printf("%-16s %-5d\n", table->lexeme[i], table->tokenType[i]);
        fprintf(output, "%-16s %-5d\n", table->lexeme[i], table->tokenType[i]);
    }
}

void printTokens(char tokenList[MAX_TOKENS][cmax], int tokenIndex){
    printf("\n");
    for( int i = 0; i < tokenIndex; i++){
        printf("%s ", tokenList[i]);
    }
}

char symbols[] = "+-*/()=,.#<>%;:\0";
/* Returns 1 if c is a special symbol, 0 otherwise*/
int isSymbol(char c){
    for (int i = 0; symbols[i] != '\0'; i++){
        if (symbols[i] == c) return 1;
    }
    return 0;
}

char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\0";
/* Returns 1 if c is a letter, 0 otherwise*/
int isLetter(char c){
    for (int i = 0; letters[i] != '\0'; i++){
        if (letters[i] == c) return 1;
    }
    return 0;
}


char digits[] = "0123456789\0";
/* Returns 1 if c is a digit, 0 otherwise*/
int isDigit(char c){
    for (int i = 0; digits[i] != '\0'; i++){
        if (digits[i] == c) return 1;
    }
    return 0;
}

char whiteSpace[] = " \t\n\0";
/* Returns 1 if c is whitespace, 0 otherwise*/
int isWhiteSpace(char c){
    for (int i = 0; whiteSpace[i] != '\0'; i++){
        if (whiteSpace[i] == c) return 1;
    }
    return 0;
}



/* list of reserved word names */
char *word [] = { "null", "begin", "call", "const", "do", "else", "end", "if",
    "odd", "procedure", "read", "then", "var", "while", "write"};
/* Returns 1 if token is a recognized keyword, otherwise 0 */
int isKeyword(char token[strmax]){
    for( int i = 0; i < norw; i++){
        if (strcmp(word[i], token) == 0) return 1;
    }
    return 0;
}

/* Returns 1 if token is a number, otherwise 0 */
int isNumber(char token[strmax]){
    for( int i = 0; token[i] != '\0'; i++){
        if (!isDigit(token[i])) return 0;
    }
    return 1;
}

/* Returns 1 if token is a valid ident, otherwise 0 */
int isIdentifier(char token[strmax]){
    if(!isLetter(token[0])) return 0; // first char is not a letter
    for( int i = 1; token[i] != '\0'; i++){
        if (!(isDigit(token[i]) || isLetter(token[i]))) return 0;
    }
    return 1;
}

/* Returns the enum value of the keyword, otherwise 0 */
int getKeywordNumber(char keyword[256]){
    if(strcmp("begin", keyword) == 0) return beginsym;
    else if(strcmp("end", keyword) == 0) return endsym;
    else if(strcmp("if", keyword) == 0) return ifsym;
    else if(strcmp("else", keyword) == 0) return elsesym;
    else if(strcmp("then", keyword) == 0) return thensym;
    else if(strcmp("while", keyword) == 0) return whilesym;
    else if(strcmp("do", keyword) == 0) return dosym;
    else if(strcmp("call", keyword) == 0) return callsym;
    else if(strcmp("const", keyword) == 0) return constsym;
    else if(strcmp("var", keyword) == 0) return varsym;
    else if(strcmp("procedure", keyword) == 0) return procsym;
    else if(strcmp("write", keyword) == 0) return writesym;
    else if(strcmp("read", keyword) == 0) return readsym;
    return 0;
}

/* Returns the enum value of the symbol, otherwise 0 */
int getSymbolNumber(char symbol[3]){
    if(strcmp("null", symbol) == 0) return skipsym;
    else if(strcmp("+", symbol) == 0) return plussym;
    else if(strcmp("-", symbol) == 0) return minussym;
    else if(strcmp("*", symbol) == 0) return multsym;
    else if(strcmp("/", symbol) == 0) return slashsym;
    else if(strcmp("=", symbol) == 0) return eqlsym;
    else if(strcmp("<", symbol) == 0) return lessym;
    else if(strcmp("<=", symbol) == 0) return leqsym;
    else if(strcmp(">", symbol) == 0) return gtrsym;
    else if(strcmp("<>", symbol) == 0) return neqsym;
    else if(strcmp(">=", symbol) == 0) return geqsym;
    else if(strcmp("(", symbol) == 0) return lparentsym;
    else if(strcmp(")", symbol) == 0) return rparentsym;
    else if(strcmp(",", symbol) == 0) return commasym;
    else if(strcmp(";", symbol) == 0) return semicolonsym;
    else if(strcmp(".", symbol) == 0) return periodsym;
    else if(strcmp(":=", symbol) == 0) return becomessym;
    return 0;
}


int main(int argc, char** argv){

    char tokenList[MAX_TOKENS][strmax];
    int tokenIndex = 0;
    FILE * output = fopen("output.txt", "w");
    FILE* fptr = fopen("input2.txt", "r");
    
    
    // prints input program to both terminal and output file
    printProgram(fptr, output);
    rewind(fptr);
    char c = fgetc(fptr);
    int i = 0;
    


    // removes whitespace and separates program into tokens in the tokenList array
    while(c != EOF){
        if(isSymbol(c)){ // special symbol
            if (i != 0) {
                tokenList[tokenIndex++][i] = '\0'; // start new token if not already in a new token
                i = 0;
            }

            // special cases
            if (c == ':'){  // looking for :=
                if(fgetc(fptr) == '='){
                    tokenList[tokenIndex][0] = ':';
                    tokenList[tokenIndex][1] = '=';
                    tokenList[tokenIndex++][2] = '\0';
                }
                else fseek(fptr, -1, SEEK_CUR);
            }
            else if (c == '/'){ // looking for /*
                if(fgetc(fptr) == '*'){ // we are inside a potential comment block, we will need to see if its closed
                    long pos = ftell(fptr);
                    
                    // looking for close comment
                    c = fgetc(fptr);
                    while (c != EOF){
                        if (c == '*'){
                            if(fgetc(fptr) == '/'){ // found a closing comment
                                goto exit_comment;
                            }
                            else fseek(fptr, -1, SEEK_CUR);
                        }
                        c = fgetc(fptr);
                    }
                    tokenList[tokenIndex][0] = '/';
                    tokenList[tokenIndex++][1] = '\0';
                    tokenList[tokenIndex][0] = '*';
                    tokenList[tokenIndex++][1] = '\0';
                    fseek(fptr, pos, SEEK_SET); // return opening comment
                    
                    
                }else {
                    tokenList[tokenIndex][0] = '/';
                    tokenList[tokenIndex++][1] = '\0';
                    fseek(fptr, -1, SEEK_CUR);
                }
            }
            else if (c == '<'){  // looking for <>
                char temp = fgetc(fptr);
                if(temp == '>'){
                    tokenList[tokenIndex][0] = '<';
                    tokenList[tokenIndex][1] = '>';
                    tokenList[tokenIndex++][2] = '\0';
                }
                else if (temp == '='){ // looking for <=
                    tokenList[tokenIndex][0] = '<';
                    tokenList[tokenIndex][1] = '=';
                    tokenList[tokenIndex++][2] = '\0';
                }
                else {
                    tokenList[tokenIndex][0] = '<';
                    tokenList[tokenIndex++][1] = '\0';
                    fseek(fptr, -1, SEEK_CUR); 
                }
            }
            else if (c == '>'){  // looking for >=
                if (fgetc(fptr) == '='){
                    tokenList[tokenIndex][0] = '>';
                    tokenList[tokenIndex][1] = '=';
                    tokenList[tokenIndex++][2] = '\0';
                }
                else {
                    tokenList[tokenIndex][0] = '>';
                    tokenList[tokenIndex++][1] = '\0';
                    fseek(fptr, -1, SEEK_CUR); 
                }
            }
            else{
                tokenList[tokenIndex][0] = c;
                tokenList[tokenIndex++][1] = '\0';
            }
            i = 0;

        }
        else if(isDigit(c) || isLetter(c)) { // letter or digit
            tokenList[tokenIndex][i++] = c;
        }
        else if(isWhiteSpace(c)){ // space or tab or newline
            if (i != 0){
                tokenList[tokenIndex++][i] = '\0';
                i=0;
            }
        }else{ // invalid input symbol
            if (i != 0){
                tokenList[tokenIndex++][i] = '\0';
                tokenList[tokenIndex][0] = c;
                tokenList[tokenIndex++][1] = '\0';
                i = 0;
            }
            else{
                tokenList[tokenIndex][0] = c;
                tokenList[tokenIndex++][1] = '\0';
            }
        }
        exit_comment:
        c = fgetc(fptr);
    }

    fclose(fptr);
    // tokenList;
    
    fprintf(output, "\n\nLexeme Table: \n");
    printf("\n\nLexeme Table: \n");
    Table table;
    table.size = 0;
    for(int i = 0; i < tokenIndex; i++){

        if(isKeyword(tokenList[i])){
            addEntry(&table, tokenList[i], getKeywordNumber(tokenList[i]));
        }
        else if(isSymbol(tokenList[i][0])){
            addEntry(&table, tokenList[i], getSymbolNumber(tokenList[i]));
        }
        else if(isNumber(tokenList[i])){
            addEntry(&table, tokenList[i], 3);
        }
        else if(isIdentifier(tokenList[i])){

            addEntry(&table, tokenList[i], 2);

        }
        else{ // not a recognized token
            addEntry(&table, tokenList[i], 0);
        }
    }
    printTable(&table, output);
    
    printf("\nToken List: \n");
    fprintf(output, "\nToken List: \n");

    for(int i = 0; i < table.size; i++){
        printf("%d ", table.tokenType[i]);
        fprintf(output, "%d ", table.tokenType[i]);
        if (table.tokenType[i] == 2 || table.tokenType[i] == 3){ // ident or number
            printf("%s ", table.lexeme[i]);
            fprintf(output, "%s ", table.lexeme[i]);
        }
    }


    return 1;
}

int length(char* s){
    int i;
    for(i = 0; s[i] != '\0'; i++);
    return i;
}