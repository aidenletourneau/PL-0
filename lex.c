#include <stdio.h>
#include <string.h>

#define norw 15 /* number of reserved words */
#define imax 32767 /* maximum integer value */
#define cmax 12 /* maximum number of chars for idents */
#define strmax 256 /* maximum length of strings */
#define MAX_TOKENS 1000
#define NUM_MAX 5


enum token_type{
    skipsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5,
    multsym = 6, slashsym = 7, fisym = 8, eqlsym = 9, neqsym = 10, lessym = 11, leqsym =
    12, gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17,
    semicolonsym = 18, periodsym = 19, becomessym = 20,
    beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26,
    callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31,
    readsym = 32, elsesym = 33, invalidERRORsym = 34, identERRORsym = 35, numERRORsym = 36 } ;

typedef struct Table{
    char lexeme[MAX_TOKENS][strmax];
    int tokenType[MAX_TOKENS];
    int size;
} Table;


int length(char* s){
    int i;
    for(i = 0; s[i] != '\0'; i++);
    return i;
}

void printProgram(FILE* inputFptr, FILE* outputFptr){
    fprintf(outputFptr, "Source Program:\n");
    printf("Source Program:\n");
    char c = fgetc(inputFptr);
    while(c != EOF){
        printf("%c", c);
        fprintf(outputFptr, "%c", c);
        c = fgetc(inputFptr);
    }
}

/* Adds entry with name lexeme and value value into table at table->size position */
void addEntry(Table* table, char* lexeme, int value){
    strcpy(table->lexeme[table->size], lexeme);
    table->tokenType[table->size] = value;
    table->size ++;
}

/* Prints Lexeme table */
void printTable(Table* table, FILE* outputFptr){
    fprintf(outputFptr, "\n\nLexeme Table: \n");
    printf("\n\nLexeme Table: \n");
    
    printf("\n%-15s%5s\n", "lexeme", " token Type");
    fprintf(outputFptr, "\n%-16s%5s\n", "Lexeme", " Token Type");
    for(int i = 0; i < table->size; i++){
        if(table->tokenType[i] == identERRORsym){
            printf("%-15s %-5s\n", table->lexeme[i], "Error: Ident length too long.");
            fprintf(outputFptr, "%-15s %-5s\n", table->lexeme[i], "Error: Ident length too long.");
            continue;
        }
        else if(table->tokenType[i] == numERRORsym){
            printf("%-15s %-5s\n", table->lexeme[i], "Error: Number length too long.");
            fprintf(outputFptr, "%-15s %-5s\n", table->lexeme[i], "Error: Number length too long.");
            continue;
        }
        else if (table->tokenType[i] == invalidERRORsym){
            printf("%-15s %-5s\n", table->lexeme[i], "Error: Invalid Symbol.");
            fprintf(outputFptr, "%-15s %-5s\n", table->lexeme[i], "Error: Invalid Symbol.");
            continue;
        }
        printf("%-15s %-5d\n", table->lexeme[i], table->tokenType[i]);
        fprintf(outputFptr, "%-15s %-5d\n", table->lexeme[i], table->tokenType[i]);
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
    else if(strcmp("null", keyword) == 0) return skipsym;
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

/* Parses full symbol */
void symbolHandler(char c, int* charIndex, int* tokenIndex, char tokenList[MAX_TOKENS][strmax], FILE* inputFptr){
    
    // start new token if not already in a new token 
    if ((*charIndex) != 0) {
        tokenList[(*tokenIndex)++][(*charIndex)] = '\0'; 
        (*charIndex) = 0;
    }

    char nextChar;

    switch(c){
        case ':': // looking for ":="
            if(fgetc(inputFptr) == '='){
                tokenList[(*tokenIndex)][0] = ':';
                tokenList[(*tokenIndex)][1] = '=';
                tokenList[(*tokenIndex)++][2] = '\0';
            }
            else fseek(inputFptr, -1, SEEK_CUR);
            break;
        case '/': // looking for "/*"
            if(fgetc(inputFptr) == '*'){ // we are inside a potential comment block, we will need to see if its closed

                // save FILE* position in case there is no closing */
                long pos = ftell(inputFptr);
                
                // looking for close comment
                c = fgetc(inputFptr);
                while (c != EOF){
                    if (c == '*'){ 
                        c = fgetc(inputFptr);
                        if(c == '/'){ // found a closing comment
                            return;
                        }
                    }
                    else c = fgetc(inputFptr);
                }
                tokenList[(*tokenIndex)][0] = '/';
                tokenList[(*tokenIndex)++][1] = '\0';
                tokenList[(*tokenIndex)][0] = '*';
                tokenList[(*tokenIndex)++][1] = '\0';
                fseek(inputFptr, pos, SEEK_SET); // return opening comment
                
            }else {
                tokenList[(*tokenIndex)][0] = '/';
                tokenList[(*tokenIndex)++][1] = '\0';
                fseek(inputFptr, -1, SEEK_CUR);
            }
            break;
        case '<': // looking for "<>"
            c = fgetc(inputFptr);
            if(c == '>'){
                tokenList[(*tokenIndex)][0] = '<';
                tokenList[(*tokenIndex)][1] = '>';
                tokenList[(*tokenIndex)++][2] = '\0';
            }
            else if (c == '='){ // looking for "<="
                tokenList[(*tokenIndex)][0] = '<';
                tokenList[(*tokenIndex)][1] = '=';
                tokenList[(*tokenIndex)++][2] = '\0';
            }
            else {
                tokenList[(*tokenIndex)][0] = '<';
                tokenList[(*tokenIndex)++][1] = '\0';
                fseek(inputFptr, -1, SEEK_CUR); 
            }
            break;
        case '>': // looking for ">="
            if (fgetc(inputFptr) == '='){
                tokenList[(*tokenIndex)][0] = '>';
                tokenList[(*tokenIndex)][1] = '=';
                tokenList[(*tokenIndex)++][2] = '\0';
            }
            else {
                tokenList[(*tokenIndex)][0] = '>';
                tokenList[(*tokenIndex)++][1] = '\0';
                fseek(inputFptr, -1, SEEK_CUR); 
            }
            break;
        default:
            tokenList[(*tokenIndex)][0] = c;
            tokenList[(*tokenIndex)++][1] = '\0';
            break;
    }
    (*charIndex) = 0;
}

/* Parses full number */
void numberHandler(char c, int* charIndex, int* tokenIndex, char tokenList[MAX_TOKENS][strmax], FILE* inputFptr){
    tokenList[(*tokenIndex)][(*charIndex)++] = c;
    c = fgetc(inputFptr);
    while(isDigit(c)){
        tokenList[(*tokenIndex)][(*charIndex)++] = c;
        c = fgetc(inputFptr);
    }
    tokenList[(*tokenIndex)++][(*charIndex)] = '\0';
    (*charIndex) = 0;
    fseek(inputFptr, -1, SEEK_CUR); // return file pointer to new non-number character
}

/* Parses full ident or keyword */
void identKeywordHandler(char c, int* charIndex, int* tokenIndex, char tokenList[MAX_TOKENS][strmax], FILE* inputFptr){

    tokenList[(*tokenIndex)][(*charIndex)++] = c;
    c = fgetc(inputFptr);
    while(isDigit(c) || isLetter(c)){
        tokenList[(*tokenIndex)][(*charIndex)++] = c;
        c = fgetc(inputFptr);
    }
    tokenList[(*tokenIndex)++][(*charIndex)] = '\0';
    (*charIndex) = 0;
    fseek(inputFptr, -1, SEEK_CUR); // return file pointer to new non-numberletter character

}

/* Generates Lexeme table based on token list */
void generateTable(Table* table, char tokenList[MAX_TOKENS][strmax], int tokenIndex){

    table->size = 0;

    for(int i = 0; i < tokenIndex; i++){
        if(isKeyword(tokenList[i])){
            addEntry(table, tokenList[i], getKeywordNumber(tokenList[i]));
        }
        else if(isSymbol(tokenList[i][0])){
            addEntry(table, tokenList[i], getSymbolNumber(tokenList[i]));
        }
        else if(isNumber(tokenList[i])){
            if(length(tokenList[i]) > NUM_MAX) addEntry(table, tokenList[i], numERRORsym);
            else addEntry(table, tokenList[i], 3);
        }
        else if(isIdentifier(tokenList[i])){
            if(length(tokenList[i]) > cmax) addEntry(table, tokenList[i], identERRORsym);
            else addEntry(table, tokenList[i], 2);
        }
        else{ // not a recognized token
            addEntry(table, tokenList[i], invalidERRORsym);
        }
    }
}

/* Returns Number of Tokens in program */
int tokenizeProgram(FILE* inputFptr, char tokenList[MAX_TOKENS][strmax]){
    
    
    int tokenIndex = 0;
    char c = fgetc(inputFptr);
    int charIndex = 0;

    // removes whitespace and separates program into tokens in the tokenList array
    while(c != EOF){
        if(isSymbol(c)){ // special symbol
            
            symbolHandler(c, &charIndex, &tokenIndex, tokenList, inputFptr);
        
        }
        else if(isDigit(c)){ // number literal

            numberHandler(c, &charIndex, &tokenIndex, tokenList, inputFptr);

        }        
        else if(isLetter(c)) { // could be identifier or keyword

            identKeywordHandler(c, &charIndex, &tokenIndex, tokenList, inputFptr);

        }
        else if(isWhiteSpace(c)){ // space or tab or newline
            if (charIndex != 0){
                tokenList[tokenIndex++][charIndex] = '\0';
                charIndex = 0;
            }
        }else{ // invalid input symbol
            if (charIndex != 0){
                tokenList[tokenIndex++][charIndex] = '\0';
            }
            tokenList[tokenIndex][0] = c;
            tokenList[tokenIndex++][1] = '\0';
            charIndex = 0;
        }
        c = fgetc(inputFptr);
    }
    
    return tokenIndex;

}

/* Prints final parsed token list */
void printTokenList(FILE* outputFptr, Table* table, char tokenList[MAX_TOKENS][strmax]){
    printf("\nToken List: \n");
    fprintf(outputFptr, "\nToken List: \n");

    for(int i = 0; i < table->size; i++){
        printf("%d ", table->tokenType[i]);
        fprintf(outputFptr, "%d ", table->tokenType[i]);
        if (table->tokenType[i] == identsym || table->tokenType[i] == numbersym){ // ident or number
            printf("%s ", table->lexeme[i]);
            fprintf(outputFptr, "%s ", table->lexeme[i]);
        }
    }
}

int main(int argc, char** argv){

    // initialize data structures
    char tokenList[MAX_TOKENS][strmax];
    int numTokens;
    Table table;
    FILE* outputFptr = fopen("output.txt", "w");
    FILE* inputFptr = fopen(argv[1], "r");


    // ===============================PRINT RAW PROGRAM===============================
    printProgram(inputFptr, outputFptr);
    rewind(inputFptr);


    // ===============================TOKENIZE PROGRAM===============================
    numTokens = tokenizeProgram(inputFptr, tokenList);
    fclose(inputFptr);


    // ===============================LEXEME TABLE===============================
    generateTable(&table, tokenList, numTokens);
    printTable(&table, outputFptr);
    

    // ===============================TOKEN LIST===============================
    printTokenList(outputFptr, &table, tokenList);


    return 1;
}

