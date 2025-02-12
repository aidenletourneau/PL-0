#include <stdio.h>
#include <string.h>

#define norw 15 /* number of reserved words */
#define imax 32767 /* maximum integer value */
#define cmax 11 /* maximum number of chars for idents */
#define strmax 256 /* maximum length of strings */

enum token_type{
    skipsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
    multsym = 6, slashsym = 7, fisym = 8, eqlsym = 9, neqsym = 10, lessym = 11, leqsym =
    12, gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17,
    semicolonsym = 18, periodsym = 19, becomessym = 20,
    beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26,
    callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31,
    readsym = 32, elsesym = 33} ;


/* internal representation of reserved words */
int lsym [ ] = { skipsym, identsym, numbersym, plussym, minussym,
    multsym, slashsym, fisym, eqlsym, neqsym, lessym, leqsym, 
    gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
    periodsym, becomessym, beginsym, endsym, ifsym, thensym, whilesym, 
    dosym, callsym, constsym, varsym, procsym, writesym,
    readsym, elsesym};

/* list of special symbols */



typedef struct Table{
    char lexeme[100][20];
    int tokenType[100];
    int size;
} Table;

/* Adds entry with name lexeme and value value into table at table->size position */
void addEntry(Table* table, char* lexeme, int value){
    strcpy(table->lexeme[table->size], lexeme);
    table->tokenType[table->size] = value;
    table->size ++;
}

void printTable(Table* table){
    printf("\n%-7s|%5s\n", "Lexeme", " Token Type");
    for(int i = 0; i < table->size; i++){
        printf("%-7s| %-5d\n", table->lexeme[i], table->tokenType[i]);
    }
}

void printTokens(char tokenList[100][256], int tokenIndex){
    printf("\n");
    for( int i = 0; i < tokenIndex; i++){
        printf("%s ", tokenList[i]);
    }
}

char symbols[] = "+-*/()=,.#<>$%;:\0";
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
int isKeyword(char token[256]){
    for( int i = 0; i < 15; i++){
        if (strcmp(word[i], token) == 0) return 1;
    }
    return 0;
}

/* Returns 1 if token is a number, otherwise 0 */
int isNumber(char token[256]){
    for( int i = 0; token[i] != '\0'; i++){
        if (!isDigit(token[i])) return 0;
    }
    return 1;
}

/* Returns 1 if token is a valid ident, otherwise 0 */
int isIdentifier(char token[256]){
    if(!isLetter(token[0])) return 0; // first char is not a letter
    for( int i = 1; token[i] != '\0'; i++){
        if (!(isDigit(token[i]) || isLetter(token[i]))) return 0;
    }
    return 1;
}

/* Returns the enum value of the keyword, otherwise 0 */
int getKeywordNumber(char keyword[256]){
    if(strcmp("begin", keyword) == 0) return beginsym;
    if(strcmp("end", keyword) == 0) return endsym;
    if(strcmp("if", keyword) == 0) return ifsym;
    if(strcmp("then", keyword) == 0) return thensym;
    if(strcmp("while", keyword) == 0) return whilesym;
    if(strcmp("do", keyword) == 0) return dosym;
    if(strcmp("call", keyword) == 0) return whilesym;
    if(strcmp("const", keyword) == 0) return whilesym;
    if(strcmp("var", keyword) == 0) return varsym;
    if(strcmp("procedure", keyword) == 0) return procsym;
    if(strcmp("write", keyword) == 0) return writesym;
    if(strcmp("read", keyword) == 0) return readsym;
    return 0;
}

/* Returns the enum value of the symbol, otherwise 0 */
int getSymbolNumber(char symbol[3]){
    if(strcmp("null", symbol) == 0) return skipsym;
    if(strcmp("+", symbol) == 0) return plussym;
    if(strcmp("-", symbol) == 0) return minussym;
    if(strcmp("*", symbol) == 0) return multsym;
    if(strcmp("/", symbol) == 0) return slashsym;
    if(strcmp("=", symbol) == 0) return eqlsym;
    if(strcmp("!=", symbol) == 0) return neqsym;
    if(strcmp("<", symbol) == 0) return lessym;
    if(strcmp("<=", symbol) == 0) return leqsym;
    if(strcmp(">", symbol) == 0) return gtrsym;
    if(strcmp(">=", symbol) == 0) return geqsym;
    if(strcmp("(", symbol) == 0) return lparentsym;
    if(strcmp(")", symbol) == 0) return rparentsym;
    if(strcmp(",", symbol) == 0) return commasym;
    if(strcmp(";", symbol) == 0) return semicolonsym;
    if(strcmp(".", symbol) == 0) return periodsym;
    if(strcmp(":=", symbol) == 0) return becomessym;
    return 0;
}


int main(int argc, char** argv){
    int ssym[256];
    ssym['+']=plussym; ssym['-']= minussym; ssym['*']=multsym;
    ssym['/']=slashsym; ssym['(']=lparentsym; ssym[')']=rparentsym;
    ssym['=']=eqlsym; ssym[',']=commasym; ssym['.']=periodsym;
    ssym['#']=neqsym; ssym['<']=lessym; ssym['>']=gtrsym;
    ssym['$']=leqsym; ssym['%']=geqsym; ssym[';']=semicolonsym;

    char tokenList[100][256];
    int tokenIndex = 0;

    FILE* fptr = fopen("input.txt", "r");
    
    
    
    printf("Source Program:\n");
    char c = fgetc(fptr);
    int i = 0;
    
    // removes whitespace and separates program into tokens in the tokenList array
    while(c != EOF){

        if(isSymbol(c)){ // special symbol
            if (i != 0) tokenList[tokenIndex++][i] = '\0'; // start new token if not already in a new token

            if (c == ':'){
                if(fgetc(fptr) == '='){
                    tokenList[tokenIndex][0] = c;
                    tokenList[tokenIndex][1] = '=';
                    tokenList[tokenIndex++][2] = '\0';
                }
                else fseek(fptr, -1, SEEK_CUR); // return fptr to correct position if (fgetc(fptr) != '=')
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
        }
        printf("%c", c);
        c = fgetc(fptr);
    }
    fclose(fptr);
    // tokenList;
    
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
    printTable(&table);
    
    printf("\nToken List: \n");

    for(int i = 0; i < table.size; i++){
        printf("%d ", table.tokenType[i]);
        if (table.tokenType[i] == 2 || table.tokenType[i] == 3){ // ident or number
            printf("%s ", table.lexeme[i]);
        }
    }


    return 1;
}









/*
Input: 
        var x, y;
        begin
            y := 3;
            x := y + 56;
        end.

Output: 

        Source Program:
        var x, y;
        begin
            y := 3;
            x := y + 56;
        end.

        Lexeme Table:

        lexeme| token type
        var     29
        x       2
        ,       17
        y       2
        ;       18
        begin   21
        y       2
        :=      20
        3       3
        ;       18
        x       2
        :=      20
        y       2
        +       4
        56      3
        ;       18
        end     22
        .       19

        Token List:
        29 2 x 17 2 y 18 21 2 y 20 3 3 18 2 x 20 2 y 4 3 56 18 22 19
*/