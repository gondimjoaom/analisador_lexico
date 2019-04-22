%{
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define   QTD_SLOT 100
#define   TAM_LEXEMA 100
#define		IDENT		11
#define		NUM			12
#define		STRING		13

#define		OP_SOMA 	21
#define		OP_SUB		22	
#define		OP_MULT		23	
#define		OP_DIV		24
#define		OP_EXP		24
#define		OP_INCRE 	25
#define		OP_DECRE 	26

#define		OP_AND		31
#define		OP_OR		32
#define		OP_NOT		33

#define		OP_MENOR		41
#define		OP_MENOR_IGUAL	42
#define		OP_MAIOR		43
#define		OP_MAIOR_IGUAL	44
#define		OP_IGUAL		45
#define		OP_DIFERENTE	46

#define		OP_CONCAT	51
#define		OP_ATRIB	52

#define		FUNC_SIZE	61
#define		FUNC_NEW	62
#define		FUNC_TO_I	63
#define		FUNC_TO_F	64
#define		FUNC_TO_S	65
#define		COMENTARIO	66
#define   COMENTARIO_LINHA  67

#define		SIMB_PARENT_E	71
#define		SIMB_PARENT_D	72
#define   SIMB_CHAVE_E 73
#define   SIMB_CHAVE_D 74
#define		SIMB_FIM_SETEN	75
#define		SIMB_SEPARADOR	76

#define		ER_IF		81
#define		ER_WHILE	82
#define		ER_FOR		83
#define		ER_DO		84

#define   PALAVRA_BOOL 90

/* ---------------------------------------------------------------------------*/
/* ----- DEFINICAO DA ESTRUTURA NO DA LISTA ----------------------------------*/
/* ---------------------------------------------------------------------------*/
struct lista_no {   
   char lexema[TAM_LEXEMA]; 
   struct lista_no *prox; 
};
typedef struct lista_no LISTA; 

LISTA *tab[QTD_SLOT];

/* ---------------------------------------------------------------------------*/
/* ----- PROTÓTIPO DAS FUNCOES -----------------------------------------------*/
/* ---------------------------------------------------------------------------*/

LISTA *criar(void); 
LISTA *insere(LISTA * a, char* lexema);
int hash(int v,int n);
void imprimir(LISTA *a);
void insertID(int slot,char* lexema);

%}

/*============ DEFINICAO DAS REGRAS DOS TOKENS A SEREM RECONHECIDOS ============*/

delim		[ \t\n]
ws			{delim}+
fim_setenca \;
separador 	\,

parent_e	\(
parent_d	\)
chave_e  \{
chave_d  \}
tudo		(.|\n)*

sinal     ([-+])?
digito		[0-9]
digitos		({digito})*
fracao		(\.{digitos})?
expoente	((E([+|-])?)?{digitos}+)?
numeral		{sinal}{digitos}{fracao}{expoente}

carac_espec	[^\n]
letra		[a-zA-Z]
letras		{letra}+
ident		(_|{letra})({letras}|{digitos}|_)*
comentario	\/\*{tudo}*\*\/
comentario_linha \/\/([^\n])*
string    ((\"){carac_espec}*(\"))

if 			([iI][fF])
while 		([wW][hH][iI][lL][eE])
for 		([fF][oO][rR])
do 			([dD][oO])

and			([aA][nN][dD])
or 			([oO][rR])
not 		([nN][oO][tT])

size 		([sS][iI][zZ][eE])
to_i 		([tT][oO]_[iI])
to_f 		([tT][oO]_[fF])
to_s 		([tT][oO]_[sS])
new 		([nN][eE][wW])


/*============ DEFINICAO DAS ACOES A SEREM EXECUTADAS DEPOIS DE ENCONTRAR O PADRAO ============*/
%%

"+"			{printf("\n<OP_SOMA,%s,%d>",yytext,OP_SOMA);return OP_SOMA;}	
"-"			{printf("\n<OP_SUB,%s,%d>",yytext,OP_SUB);return OP_SUB;}	
"*"			{printf("\n<OP_MULT,%s,%d>",yytext,OP_MULT);return OP_MULT;}	
"/"			{printf("\n<OP_DIV,%s,%d>",yytext,OP_DIV);return OP_DIV;}	
"^"			{printf("\n<OP_EXP,%s,%d>",yytext,OP_EXP);return OP_EXP;}
"="			{printf("\n<OP_ATRIB,%s,%d>",yytext,OP_ATRIB);return OP_ATRIB;}

{and} 		{printf("\n<OP_AND,%s,%d>",yytext,OP_AND);return OP_AND;}
{or} 		{printf("\n<OP_OR,%s,%d>",yytext,OP_OR);return OP_OR;}
{not} 		{printf("\n<OP_NOT,%s,%d>",yytext,OP_NOT);return OP_NOT;}

"<"			{printf("\n<OP_MENOR,%s,%d>",yytext,OP_MENOR);return OP_MENOR;}
"<="		{printf("\n<OP_MENOR_IGUAL,%s,%d>",yytext,OP_MENOR_IGUAL);return OP_MENOR_IGUAL;}
">"			{printf("\n<OP_MAIOR,%s,%d>",yytext,OP_MAIOR);return OP_MAIOR;}
">="		{printf("\n<OP_MAIOR_IGUAL,%s,%d>",yytext,OP_MAIOR_IGUAL);return OP_MAIOR_IGUAL;}
"=="		{printf("\n<OP_IGUAL,%s,%d>",yytext,OP_IGUAL);return OP_IGUAL;}
"!="		{printf("\n<OP_DIFERENTE,%s,%d>",yytext,OP_DIFERENTE);return OP_DIFERENTE;}

"true"    {printf("\n<PALAVRA_BOOL,%s,%d>",yytext,PALAVRA_BOOL);return PALAVRA_BOOL;}
"false"    {printf("\n<PALAVRA_BOOL,%s,%d>",yytext,PALAVRA_BOOL);return PALAVRA_BOOL;}

{size}		{printf("\n<FUNC_SIZE,%s,%d>",yytext,FUNC_SIZE);return FUNC_SIZE;}
{to_i}		{printf("\n<FUNC_TO_I,%s,%d>",yytext,FUNC_TO_I);return FUNC_TO_I;}
{to_f}		{printf("\n<FUNC_TO_F,%s,%d>",yytext,FUNC_TO_F);return FUNC_TO_F;}
{to_s}		{printf("\n<FUNC_TO_S,%s,%d>",yytext,FUNC_TO_S);return FUNC_TO_S;}
{new}		  {printf("\n<FUNC_NEW,%s,%d>",yytext,FUNC_NEW);return FUNC_NEW;}

{if} 		  {printf("\n<EF_IF,%s,%d>",yytext,ER_IF);return ER_IF;}
{while}		{printf("\n<EF_WHILE,%s,%d>",yytext,ER_WHILE);return ER_WHILE;}
{for} 		{printf("\n<EF_FOR,%s,%d>",yytext,ER_FOR);return ER_FOR;}
{do} 		  {printf("\n<EF_DO,%s,%d>",yytext,ER_DO);return ER_DO;}

{parent_e}	{printf("\n<PARENTESE_E,%s,%d>",yytext,SIMB_PARENT_E);return SIMB_PARENT_E;}
{parent_d}	{printf("\n<PARENTESE_D,%s,%d>",yytext,SIMB_PARENT_D);return SIMB_PARENT_D;}
{chave_d}  {printf("\n<CHAVE_D,%s,%d>",yytext,SIMB_CHAVE_D);return SIMB_CHAVE_D;}
{chave_e}  {printf("\n<CHAVE_E,%s,%d>",yytext,SIMB_CHAVE_E);return SIMB_CHAVE_E;}
{fim_setenca}	{printf("\n<FIM_SETENCA,%s,%d>",yytext,SIMB_FIM_SETEN);return SIMB_FIM_SETEN;}
{separador} {printf("\n<SIMB_SEPARADOR,%s,%d>",yytext,SIMB_SEPARADOR);return SIMB_SEPARADOR;}

{ws}		{/* nao executa nada*/}
{comentario}	{printf("\n<COMENT_MULT_LINHA,%s,%d>",yytext,COMENTARIO);return COMENTARIO;}
{comentario_linha}  {printf("\n<COMENT_LINHA,%s,%d>",yytext,COMENTARIO_LINHA);return COMENTARIO_LINHA;}
{ident}			{printf("\n<IDENTIFICADOR,%s,%d>",yytext,IDENT);return IDENT;}
{numeral}		{printf("\n<NUMERAL,%s,%d>",yytext,NUM);return NUM;}
{string}    {printf("\n<STRING,%s,%d>",yytext,STRING);return STRING;}
<<EOF>>     {printf("\n<EOF,%s,%d>",yytext,-1);return -1;}
.  {printf("\n<SIMBOLO_INVALIDO,%s,%d>",yytext,-2);return -2;}
%%

/* ---------------------------------------------------------------------------*/
/* --------------------------------- MAIN ------------------------------------*/
/* ---------------------------------------------------------------------------*/

main(void)
{
    int nextToken = -1;
    int index = 0;    
    LISTA *p;         

        /* ---------------------------------------------------------------------------*/    
        /* --------------------------- CRIANDO A TABELA ------------------------------*/        
        /* ---------------------------------------------------------------------------*/

        printf("\nCriando tabela...");   
        // inicializando a tabela
        for (index = 0; index < QTD_SLOT; index++){  
            tab[index] = criar(); 
        }  

        /* ---------------------------------------------------------------------------*/
        /* --- ANALISA OS LEXEMAS RETORNADOS PELO LEX --------------------------------*/        
        /* ---------------------------------------------------------------------------*/
        while(nextToken = yylex()){                   
          if(nextToken == -1){ 
            break;
          }else if(nextToken == -2){
            printf("\n[ERRO] Lexema invalido.");
          }
          else if(yyleng > TAM_LEXEMA){
            printf("\n[ERRO] Lexema com tamanho superior a 100.");
          }
          else if(yyleng == 0){
              printf("\n[ERRO] Lexema não pertence a linguagem.");

          } 
          else if(
            nextToken == IDENT 
            || nextToken == FUNC_SIZE
            || nextToken == FUNC_NEW
            || nextToken == FUNC_TO_I
            || nextToken == FUNC_TO_S
            || nextToken == FUNC_TO_F          
            || nextToken == PALAVRA_BOOL
            ){             
                insertID(nextToken,yytext);         
            }
        }
        
        /* ---------------------------------------------------------------------------*/
        /* ---------------------- IMPRIME A TABELA -----------------------------------*/
        /* ---------------------------------------------------------------------------*/                             
        printf("\n* --------------------------------------------------*");   
        printf("\n* ---------------- IMPRIME A TABELA ----------------*");   
        printf("\n* --------------------------------------------------*");   

        for(index=0;index<QTD_SLOT;index++){  
          printf("\nSLOT [%d]:",index);   
          imprimir(tab[index]); 
        }     
             
        system("pause");
        return (0); 
}

/* ---------------------------------------------------------------------------*/
/* ----FUNCAO: insertID-------------------------------------------------------*/  
/* ---------------------------------------------------------------------------*/
/* --- INSERE OS LEXEMAS QUE CORRESPONDEM AOS TOKEN DE IDENTIFICADORES ----*/        
/* ---------------------------------------------------------------------------*/

void insertID(int slot,char* lexema){
      tab[slot] = insere(tab[slot],yytext);
}

/* ---------------------------------------------------------------------------*/
/* ----FUNCAO: insere---------------------------------------------------------*/  
/* ---------------------------------------------------------------------------*/
/* --- INSERE OS LEXEMAS NO SLOT DA TABELA, SE O SLOT JA ESTIVER PREECHIDO ---*/
/* --- ELE ALOCA NO PROXIMO NO DA LISTA --------------------------------------*/        
/* ---------------------------------------------------------------------------*/

LISTA* insere(LISTA* a, char* lexema)
{ 
  LISTA *ant = NULL;   /*  aponta para lista anterior  */
  LISTA *p = a;  
  LISTA *colisao = NULL;
              
  if(a!=NULL){
        
        while (p != NULL){   /*   faz uma busca na tabela     */

              if(strcmp(p->lexema, lexema) == 0){

                  printf("\n[AVISO] Lexema [%s] ja existe na tabela de simbolos.",lexema);  
                  return a;

              }

              if(p->prox == NULL){ /*cheguei no final da lista*/
                  
                  printf("\n[AVISO] Inserindo o Lexema [%s] no SLOT nao vazio da tabela de simbolos",lexema);  
                  colisao = ( LISTA* )malloc(sizeof(LISTA));                               
                  colisao->prox = NULL;
                  strcpy(colisao->lexema, lexema);   
                  p->prox = colisao;           
                  return a;              
              }
       
               ant = p;
               p = p->prox;       
        }
  }

  if (a == NULL){   /* chave não encontrada ---> CRIANDO o NÓ -----------------*/

        printf("\n[AVISO] Inserindo o Lexema [%s] no SLOT vazio da tabela de simbolos",lexema);  
        colisao = ( LISTA* )malloc(sizeof(LISTA));                     
        colisao->prox = NULL;
        strcpy(colisao->lexema, lexema);   

        return colisao;                   
     }     
}   

/* ----------------------------------------------------------------------------------------------------------*/
/* ----FUNCAO: imprimir--------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------------------------------*/
/* --- DESCRICAO: FUNCAO QUE IMPRIME O CONTEUDO DA TABELA E OPERA DE MANEIRA RECURSIVA NA LISTA ENCADEADA ---*/
/* ----------------------------------------------------------------------------------------------------------*/

void imprimir( LISTA *a ){
      LISTA *p = a;      
       if (p != NULL){             
           printf("[ %s ] -> ",a->lexema);
           imprimir(p = p->prox); 
       }    
}

/* ----------------------------------------------------------------------------------------------------------*/
/* ----FUNCAO: criar-----------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------------------------------*/
/* --- DESCRICAO: FUNCAO QUE INICIALIZA COM O VALOR NULL AS POSICOES DA TABELA ------------------------------*/
/* ----------------------------------------------------------------------------------------------------------*/

LISTA* criar(){
	 	return NULL;  
}