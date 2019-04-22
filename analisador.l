/*** Definition Section has one variable 
which can be accessed inside yylex() 
and main() ***/
%{ 

#include <stdio.h>

int linha = 1;
int coluna = 0;
%} 

DIGIT	[0-9]
SYMBOLS "+"|"-"|"*"|"/"

%% 

{DIGIT}+[a-z]	{
	//erro com número seguido de letra
	//printf("esse\n");
	coluna = coluna + yyleng - 1;
	printf("%d %d\n", linha, coluna);
	yyless(yyleng-1);
	
}

[+]{2,}	{
	//erro mais de um símbolo
	coluna = coluna + yyleng - 1;
	printf("%d %d\n", linha, coluna);
	coluna++;
}



[.]{2,} {
	//printf("%d\n", yyleng);
	/*coluna = coluna + 1;
	printf("bla\n");
	printf("%d %d\n", linha, coluna);
	yyless(coluna);*/
	int y = 0;
	while(yytext[y] != '\0'){
		y++;
	}
	printf("%d %d\n", linha, y);
	yyless(--y);
	//coluna++;
}

[a-zA-Z_][a-zA-Z0-9]*	{
	//IDENTIFICADOR
	//printf("%s\n", yytext);
	//printf("aqui IDENTIFICADOR\n");
	//yyless(yyleng);
	coluna = coluna + yyleng;
}

{SYMBOLS} {
	//printf("aqui SYMBOLS\n");
	coluna = coluna + yyleng;
}

{DIGIT}+ {
	//printf("aqui DIGIT\n");
	//printf("%s\n", yytext);
	coluna = coluna + yyleng;
}

{DIGIT}+"."{DIGIT}*	{
	//NUMERO
	//printf("%s\n", yytext);
	//yyless(yyleng);
	//printf("aqui\n");
	coluna = coluna + yyleng;
}

\n	{
	linha++;
	coluna = 0;
	//printf("new line\n");
}
<<EOF>> {return 0;}

%% 

int yywrap(){} 
int main(){ 

// Explanation: 
// yywrap() - wraps the above rule section 
/* yyin - takes the file pointer 
		which contains the input*/
/* yylex() - this is the main flex function 
		which runs the Rule Section*/
// yytext is the text in the buffer

// Uncomment the lines below 
// to take input from file 
FILE *fp; 
//char filename[]; 
// printf("Enter the filename: \n"); 
//scanf("%s",filename); 
//fp = fopen("exemplos.txt","r");
//fp = fopen(filename,"r");
//string g;
//yyin = fp; 

yylex(); 
//printf("\nNumber of Captial letters "
//	"in the given input - %d\n", count); 

return 0; 
} 
