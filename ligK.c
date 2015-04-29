/***************************************************************/
/**                                                           **/
/**   Fulano de Tal                              Numero USP   **/
/**   Exercicio-Programa 4                                    **/
/**   Professor: Ciclano de Tal                               **/
/**   Turma: (de 1 a 12 ou Pt)                                **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>

#define MAXLIN (9+2)
#define MAXCOL (9+2)

#define IMPOSSIVEL 0
#define POSSIVEL   1

#define COMPLETO   2
#define INCOMPLETO 3

#define BRANCO  ' '
#define MOLDURA 'm'
#define XIS     'X'
#define BOLA    'O'
#define VAZIO   'V'

#define ENTRA 4
#define SAI 5


int carrega_configuracao(char tabuleiro[MAXLIN][MAXCOL], int *k,
                         int *nlin, int *ncol, char *tipo_xis, char *tipo_bola);

void coloca_moldura(char tabuleiro[MAXLIN][MAXCOL], int nlin, int ncol);

void imprime_tabuleiro(char tabuleiro[MAXLIN][MAXCOL], int nlin, int ncol);

void inicializa_tabuleiro(char tabuleiro[MAXLIN][MAXCOL], int *k,
                          int *nlin, int *ncol);

int verifica_tabuleiro_cheio(char tabuleiro[MAXLIN][MAXCOL], int ncol);

char determina_vez(char tabuleiro[MAXLIN][MAXCOL], int nlin, int ncol);

int joga(char tabuleiro[MAXLIN][MAXCOL], int coluna, char marca_jogador);

int conta_ligados(char tabuleiro[MAXLIN][MAXCOL], int coluna);

void salva_configuracao(char tabuleiro[MAXLIN][MAXCOL], int k,
                        int nlin, int ncol, char tipo_xis, char tipo_bola);

int coluna_central(int coluna1, int coluna2, int ncol);

int melhor_jogada(char tabuleiro[MAXLIN][MAXCOL], int k,
                  int ncol, char marca_jogador);

void DigiteEnter();



int main()
{
    char tabuleiro[MAXLIN][MAXCOL];      /* tabuleiro do jogo */
    int nlin;  /* numero de linhas do tabuleiro */
    int ncol;  /* numero de colunas do tabuleiro */

    int k;         /* ordem do jogo */

    char tipo_xis;  /* tipo do jogador Xis    (HUMANO ou COMPUTADOR) */
    char tipo_bola; /* tipo do jogador Bola   (HUMANO ou COMPUTADOR) */
    char tipo_partida; /*Escolhe entre iniciar ou carregar*/
    char escolha; /*Salva jogada se for digitado 's'*/
    int coluna;
    int retorna; /*Retorna a jogada caso a coluna ja esteja cheia*/
    int j;
    coluna=0;

    printf("Voce quer (i)niciar uma nova partida ou\n(c)arregar uma partida salva: ");
    scanf(" %c", &tipo_partida);
    if(tipo_partida=='i'){

    inicializa_tabuleiro(tabuleiro, &k, &nlin, &ncol);
    printf("Escolha jogador Xis: (h)umano ou (c)omputador: ");
    scanf(" %c", &tipo_xis);
    printf("Escolha jogador Bola: (h)umano ou (c)omputador: ");
    scanf(" %c", &tipo_bola);

    imprime_tabuleiro(tabuleiro, nlin, ncol);

    while(verifica_tabuleiro_cheio(tabuleiro, ncol)==INCOMPLETO){
        retorna=ENTRA;
        while(retorna==ENTRA){/*Isso eh feito para caso a coluna escolhida esteja cheia, uma nova chance de escolha eh dada*/
            retorna=SAI;
         printf("\nLig-%d    Vez do jogador Xis\n", k);
         /*Caso xis seja humano*/
         if(tipo_xis=='h'){
         printf("Digite coluna da jogada (ou 's' para salvar a partida): ");
         scanf(" %c", &escolha);
         if(escolha=='s'){
             salva_configuracao(tabuleiro, k, nlin, ncol, tipo_xis, tipo_bola);
             return 0;
         }
         else{
             escolha=escolha-'0';
             coluna=escolha;
         if(joga(tabuleiro, coluna, 'X')==POSSIVEL){
         imprime_tabuleiro(tabuleiro, nlin, ncol);

           for(j=1; j<=ncol; j++)
           if(conta_ligados(tabuleiro, j)==k){
           printf("\nO jogador Xis ganhou!\n");
           return 0;
         }


         }

         else{
         printf("\nColuna %d ja' esta' cheia\nTente outra coluna", coluna);
         retorna=ENTRA;
         }
         }

         }
        }


         /*Caso xis seja computador*/
         if(tipo_xis=='c'){
         coluna=melhor_jogada(tabuleiro, k, ncol, 'X');
         joga(tabuleiro, coluna, 'X');
         imprime_tabuleiro(tabuleiro, nlin, ncol);
         for(j=1; j<=ncol; j++)
           if(conta_ligados(tabuleiro, j)==k){
           printf("\nO jogador Xis ganhou!\n");
           return 0;
           }
         }
         retorna=ENTRA;
         while(retorna==ENTRA){
             retorna=SAI;
             printf("\nLig-%d    Vez do jogador Bola\n", k);
             /*Caso bola seja humano*/
            if(tipo_bola=='h'){
             printf("Digite coluna da jogada (ou 's' para salvar a partida): ");
             scanf(" %c", &escolha);
             if(escolha=='s'){
                 salva_configuracao(tabuleiro, k, nlin, ncol, tipo_xis, tipo_bola);
                 return 0;
         }
            else{
              escolha=escolha-'0';
              coluna=escolha;
            if(joga(tabuleiro, coluna, 'O')==POSSIVEL){
              imprime_tabuleiro(tabuleiro, nlin, ncol);

              for(j=1; j<=ncol; j++)
              if(conta_ligados(tabuleiro, j)==k){
              printf("\nO jogador Bola ganhou!\n");
              return 0;
         }

         }

             else{
             printf("\nColuna %d ja' esta' cheia\nTente outra coluna", coluna);
             retorna=ENTRA;
             }
         }

         }
         }

         /*Caso bola seja computador*/
         if(tipo_bola=='c'){
         coluna=melhor_jogada(tabuleiro, k, ncol, 'O');
         joga(tabuleiro, coluna, 'O');
         imprime_tabuleiro(tabuleiro, nlin, ncol);
         for(j=1; j<=ncol; j++)
           if(conta_ligados(tabuleiro, j)==k){
           printf("\nO jogador Bola ganhou!\n");
           return 0;
           }
         }


}


}
if(tipo_partida=='c'){
     carrega_configuracao(tabuleiro, &k, &nlin, &ncol, &tipo_xis, &tipo_bola);
     imprime_tabuleiro(tabuleiro, nlin, ncol);

     if(determina_vez(tabuleiro, nlin, ncol)=='X'){
     while(verifica_tabuleiro_cheio(tabuleiro, ncol)==INCOMPLETO){
         retorna=ENTRA;
         while(retorna==ENTRA){
             retorna=SAI;
         printf("\nLig-%d    Vez do jogador Xis\n", k);
         /*Caso xis seja humano*/
         if(tipo_xis=='h'){
         printf("Digite coluna da jogada (ou 's' para salvar a partida): ");
         scanf(" %c", &escolha);
         if(escolha=='s'){
             salva_configuracao(tabuleiro, k, nlin, ncol, tipo_xis, tipo_bola);
             return 0;
         }
         else{
             escolha=escolha-'0';
             coluna=escolha;
         if(joga(tabuleiro, coluna, 'X')==POSSIVEL){
         imprime_tabuleiro(tabuleiro, nlin, ncol);

           for(j=1; j<=ncol; j++)
           if(conta_ligados(tabuleiro, j)==k){
           printf("\nO jogador Xis ganhou!\n");
           return 0;
         }

         }

         else{
         printf("\nColuna %d ja' esta' cheia\nTente outra coluna", coluna);
         retorna=ENTRA;
         }

         }
         }



         /*Caso xis seja computador*/
         if(tipo_xis=='c'){
         coluna=melhor_jogada(tabuleiro, k, ncol, 'X');
         joga(tabuleiro, coluna, 'X');
         imprime_tabuleiro(tabuleiro, nlin, ncol);
         for(j=1; j<=ncol; j++)
           if(conta_ligados(tabuleiro, j)==k){
           printf("\nO jogador Xis ganhou!\n");
           return 0;
           }
         }

         retorna=ENTRA;
         while(retorna==ENTRA){
         retorna=SAI;
         printf("\nLig-%d    Vez do jogador Bola\n", k);
         /*Caso bola seja humano*/
         if(tipo_bola=='h'){
         printf("Digite coluna da jogada (ou 's' para salvar a partida): ");
         scanf(" %c", &escolha);
         if(escolha=='s'){
             salva_configuracao(tabuleiro, k, nlin, ncol, tipo_xis, tipo_bola);
             return 0;
         }
         else{
             escolha=escolha-'0';
             coluna=escolha;
         if(joga(tabuleiro, coluna, 'O')==POSSIVEL){
         imprime_tabuleiro(tabuleiro, nlin, ncol);

           for(j=1; j<=ncol; j++)
           if(conta_ligados(tabuleiro, j)==k){
           printf("\nO jogador Bola ganhou!\n");
           return 0;
         }

         }

         else{
         printf("\nColuna %d ja' esta' cheia\nTente outra coluna", coluna);
         retorna=ENTRA;
         }
         }

         }
         }

         /*Caso bola seja computador*/
         if(tipo_bola=='c'){
         coluna=melhor_jogada(tabuleiro, k, ncol, 'O');
         joga(tabuleiro, coluna, 'O');
         imprime_tabuleiro(tabuleiro, nlin, ncol);
         for(j=1; j<=ncol; j++)
           if(conta_ligados(tabuleiro, j)==k){
           printf("\nO jogador Bola ganhou!\n");
           return 0;
           }
         }


}


}
     }
     if(determina_vez(tabuleiro, nlin, ncol)=='O'){
         while(verifica_tabuleiro_cheio(tabuleiro, ncol)==INCOMPLETO){
             retorna=ENTRA;
             while(retorna==ENTRA){
                 retorna=SAI;
         printf("\nLig-%d    Vez do jogador Bola\n", k);
         /*Caso bola seja humano*/
         if(tipo_bola=='h'){
         printf("Digite coluna da jogada (ou 's' para salvar a partida): ");
         scanf(" %c", &escolha);
         if(escolha=='s'){
             salva_configuracao(tabuleiro, k, nlin, ncol, tipo_xis, tipo_bola);
             return 0;
         }
         else{
             escolha=escolha-'0';
             coluna=escolha;
         if(joga(tabuleiro, coluna, 'O')==POSSIVEL){
         imprime_tabuleiro(tabuleiro, nlin, ncol);

           for(j=1; j<=ncol; j++)
           if(conta_ligados(tabuleiro, j)==k){
           printf("\nO jogador Bola ganhou!\n");
           return 0;
         }
         }

         else{
         printf("\nColuna %d ja' esta' cheia\nTente outra coluna", coluna);
         retorna=ENTRA;
         }
         }
             }

         /*Caso bola seja computador*/
         if(tipo_bola=='c'){
         coluna=melhor_jogada(tabuleiro, k, ncol, 'O');
         joga(tabuleiro, coluna, 'O');
         imprime_tabuleiro(tabuleiro, nlin, ncol);
         for(j=1; j<=ncol; j++)
           if(conta_ligados(tabuleiro, j)==k){
           printf("\nO jogador Bola ganhou!\n");
           return 0;
           }
         }
             }

         retorna=ENTRA;
         while(retorna==ENTRA){
         retorna=SAI;
         printf("\nLig-%d    Vez do jogador Xis\n", k);
         /*Caso xis seja humano*/
         if(tipo_xis=='h'){
         printf("Digite coluna da jogada (ou 's' para salvar a partida): ");
         scanf(" %c", &escolha);
         if(escolha=='s'){
             salva_configuracao(tabuleiro, k, nlin, ncol, tipo_xis, tipo_bola);
             return 0;
         }
         else{
             escolha=escolha-'0';
             coluna=escolha;
         if(joga(tabuleiro, coluna, 'X')==POSSIVEL){
         imprime_tabuleiro(tabuleiro, nlin, ncol);

           for(j=1; j<=ncol; j++)
           if(conta_ligados(tabuleiro, j)==k){
           printf("\nO jogador Xis ganhou!\n");
           return 0;
         }
         }
         else{
         printf("\nColuna %d ja' esta' cheia\nTente outra coluna", coluna);
         retorna=ENTRA;
         }
         }
         }
         /*Caso xis seja computador*/
         if(tipo_xis=='c'){
         coluna=melhor_jogada(tabuleiro, k, ncol, 'X');
         joga(tabuleiro, coluna, 'X');
         imprime_tabuleiro(tabuleiro, nlin, ncol);
         for(j=1; j<=ncol; j++)
           if(conta_ligados(tabuleiro, j)==k){
           printf("\nO jogador Xis ganhou!\n");
           return 0;
           }
         }
     }
     }
     }
     }



printf("\nA partida empatou.\n");
return 0;

}




void coloca_moldura(char tabuleiro[MAXLIN][MAXCOL], int nlin, int ncol)
{
    int i;
    for(i=0; i<=ncol+1; i++)
    tabuleiro[0][i]=MOLDURA;
    for(i=0; i<=ncol+1; i++)
    tabuleiro[nlin+1][i]=MOLDURA;
    for(i=0; i<=nlin+1; i++)
    tabuleiro[i][0]=MOLDURA;
    for(i=0; i<=nlin+1; i++)
    tabuleiro[i][ncol+1]=MOLDURA;
}



void inicializa_tabuleiro(char tabuleiro[MAXLIN][MAXCOL], int *k,
                          int *nlin, int *ncol)
{
    int i, j;
    printf("Digite o valor de k para o Lig-k: ");
    scanf("%d", &*k);
    printf("Digite numero de linhas e de colunas: ");
    scanf("%d %d", &*nlin, &*ncol);
    coloca_moldura(tabuleiro, *nlin, *ncol);
    for(j=1; j<=*nlin; j++)
    for(i=1; i<=*ncol; i++)
    tabuleiro[j][i]=BRANCO;
}




void imprime_tabuleiro(char tabuleiro[MAXLIN][MAXCOL], int nlin, int ncol)
{
    int i, j;
    for(i=1; i<=nlin; i++)
    {
        printf("  ");
        for(j=0; j<ncol; j++)
            printf("+---");
        printf("+\n");
        printf("%d ", i);
        for(j=1; j<=ncol; j++)
            printf("| %c ", tabuleiro[i][j]);
        printf("|\n");
    }
    printf("  ");
    for(j=0; j<ncol; j++)
        printf("+---");
    printf("+\n");
    printf("    ");
    for(j=0; j<ncol; j++)
        printf("%d   ", j+1);

}




int verifica_tabuleiro_cheio(char tabuleiro[MAXLIN][MAXCOL], int ncol)
{
    int i, j, linha;
    for(linha=1; tabuleiro[linha][1]!='m'; linha++)
    ;
    for(j=1; j<linha; j++)
    for(i=1; i<=ncol; i++)
    if(tabuleiro[j][i]==' ')
    return INCOMPLETO;

    return COMPLETO;
}




char determina_vez(char tabuleiro[MAXLIN][MAXCOL], int nlin, int ncol)
{
        int i, j;
    int contX, contO;
    contX=0;
    contO=0;
    for(j=1; j<=nlin; j++)
    for(i=1; i<=ncol; i++){
        if(tabuleiro[j][i]=='X')
        contX++;
        if(tabuleiro[j][i]=='O')
        contO++;
    }
    if(contX==contO)
    return XIS;
    else
    return BOLA;
}



int joga(char tabuleiro[MAXLIN][MAXCOL], int coluna, char marca_jogador)
{
     int i;
     /*for(i=MAXLIN-1; i>0; i--)
     if(tabuleiro[i][coluna]==' '){
     tabuleiro[i][coluna]=marca_jogador;
     return POSSIVEL;
     }
     return IMPOSSIVEL;
     */
     if(tabuleiro[1][coluna]!=' ')
     return IMPOSSIVEL;
     for(i=1; tabuleiro[i][coluna]==' '; i++)
     ;
     tabuleiro[i-1][coluna]=marca_jogador;
     return POSSIVEL;
}




int conta_ligados(char tabuleiro[MAXLIN][MAXCOL], int coluna)
{
    int vert, maior, hor, diagp, diags;
    int i, j, linha;

    for(linha=1; tabuleiro[linha][coluna]==' '; linha++);
    if(tabuleiro[linha][coluna]=='X'||tabuleiro[linha][coluna]=='O'){

    /*Analise da vertical*/
    vert=0;
    for(i=linha; tabuleiro[linha][coluna]==tabuleiro[i][coluna]; i++)
    vert++;

    maior=vert;

    /*Analise da horizontal*/
    hor=0;
    for(j=coluna; tabuleiro[linha][coluna]==tabuleiro[linha][j]; j++)
    hor++;
    for(j=coluna-1; tabuleiro[linha][coluna]==tabuleiro[linha][j]; j--)/*O menos é para o elmento nao ser contado duas vezes*/
    hor++;

    if(hor>maior)
    maior=hor;

    /*Analise da diagonal principal*/
    diagp=0;
    i=linha;
    j=coluna;
    while(tabuleiro[linha][coluna]==tabuleiro[i][j]){
        diagp++;
        i++;
        j++;
    }
    i=linha-1;
    j=coluna-1;
    while(tabuleiro[linha][coluna]==tabuleiro[i][j]){
        diagp++;
        i--;
        j--;
    }

    if(diagp>maior)
    maior=diagp;

    /*Analise da diagonal secundaria*/
    diags=0;
    i=linha;
    j=coluna;
    while(tabuleiro[linha][coluna]==tabuleiro[i][j]){
        diags++;
        i--;
        j++;
    }
    i=linha+1;
    j=coluna-1;
    while(tabuleiro[linha][coluna]==tabuleiro[i][j]){
        diags++;
        i++;
        j--;
    }

    if(diags>maior)
    maior=diags;

    return maior;
    }

    else
    return 0;
}




void salva_configuracao(char tabuleiro[MAXLIN][MAXCOL], int k,
                        int nlin, int ncol, char tipo_xis, char tipo_bola)
{
    FILE *arq;
    char nome[80];
    int i, j;
    printf("Digite nome do arquivo sem espacos para salvar a partida: ");
    scanf("%s", nome);
    arq=fopen(nome, "w");
    if(arq==NULL){
    printf("Partida %s nao pode ser salvo\n", nome);
    return;
    }
      fprintf(arq, "%d %d %d %c %c \n", k, nlin, ncol, tipo_xis, tipo_bola);
      for(i=1; i<=nlin; i++){
      for(j=1; j<=ncol; j++){
          if(tabuleiro[i][j]==' ')
          fprintf(arq, "V");
          else
          fprintf(arq, "%c", tabuleiro[i][j]);
      }
      fprintf(arq, "\n");
      }

      fclose(arq);
      printf("A partida foi salva com sucesso.\n");
      return;
}



int coluna_central(int coluna1, int coluna2, int ncol)
{
    float central;
    int coluna_central;
    coluna_central=0;
    if(ncol%2!=0){
        central=(ncol+1)/2.0;
        if((coluna1-central)*(coluna1-central)<=(coluna2-central)*(coluna2-central))
        coluna_central=coluna1;
        if((coluna1-central)*(coluna1-central)>=(coluna2-central)*(coluna2-central))
        coluna_central=coluna2;
    }

    if(ncol%2==0){
        central=(ncol+1)/2.0;
        if((float)(coluna1-central)*(float)(coluna1-central)<=(float)(coluna2-central)*(float)(coluna2-central))
        coluna_central=coluna1;
        if((float)(coluna1-central)*(float)(coluna1-central)>=(float)(coluna2-central)*(float)(coluna2-central))
        coluna_central=coluna2;
    }
    return coluna_central;

}




int melhor_jogada(char tabuleiro[MAXLIN][MAXCOL], int k, int ncol,
                  char marca_jogador)
{
    int i, j, maximo, coluna;
    coluna=0;
    /*Estrategia: adicionar um X ou um O em cada coluna (se possivel) e verificar, pelo conta_ligados, se ha' k elementos. Caso nao haja, o X ou o O e' retirado
    e o processo e' refeito na coluna seguinte*/
    if(marca_jogador=='X'){
        for(j=1; j<=ncol; j++){
        if(joga(tabuleiro, j, 'X')==POSSIVEL){
            if(conta_ligados(tabuleiro, j)==k){
                for(i=1; tabuleiro[i][j]==' '; i++)
                ;
                tabuleiro[i][j]=' ';
            return j;
            }              /*Ao usar a funcao joga, o elemento do topo deixou de ser BRANCO. Se o jogo nao terminar, e' preciso consertar isso, tornando o topo BRANCO novamente*/

            for(i=1; tabuleiro[i][j]==' '; i++)
            ;
            tabuleiro[i][j]=' ';

        }
        }
    }

    if(marca_jogador=='O'){
        for(j=1; j<=ncol; j++){
        if(joga(tabuleiro, j, 'O')==POSSIVEL){
            if(conta_ligados(tabuleiro, j)==k){
                for(i=1; tabuleiro[i][j]==' '; i++)
                ;
                tabuleiro[i][j]=' ';
                return j;
            }
                                      /*Ao usar a funcao joga, o elemento do topo deixou de ser BRANCO. Se o jogo nao terminar, e' preciso consertar isso, tornando o topo BRANCO novamente*/
            for(i=1; tabuleiro[i][j]==' '; i++)
            ;
            tabuleiro[i][j]=' ';
            }
        }
        }


    /*Caso o computador nao venca, ele nao permitira que o oponente ganhe.*/

    if(marca_jogador=='X'){
        for(j=1; j<=ncol; j++){
        if(joga(tabuleiro, j, 'O')==POSSIVEL){
            if(conta_ligados(tabuleiro, j)==k){
                for(i=1; tabuleiro[i][j]==' '; i++)
                ;
                tabuleiro[i][j]=' ';
            return j;
            }
                                /*Ao usar a funcao joga, o elemento do topo deixou de ser BRANCO. Se o jogo nao terminar, e' preciso consertar isso, tornando o topo BRANCO novamente*/
            for(i=1; tabuleiro[i][j]==' '; i++)
            ;
            tabuleiro[i][j]=' ';
            }
        }
        }


    if(marca_jogador=='O'){
        for(j=1; j<=ncol; j++){
        if(joga(tabuleiro, j, 'X')==POSSIVEL){
            if(conta_ligados(tabuleiro, j)==k){
                for(i=1; tabuleiro[i][j]==' '; i++)
                ;
                tabuleiro[i][j]=' ';
            return j;
            }
                                      /*Ao usar a funcao joga, o elemento do topo deixou de ser BRANCO. Se o jogo nao terminar, e' preciso consertar isso, tornando o topo BRANCO novamente*/
            for(i=1; tabuleiro[i][j]==' '; i++)
            ;
            tabuleiro[i][j]=' ';
            }
        }
        }


    if(marca_jogador=='X'){
        maximo=0;
        for(j=1; j<=ncol; j++){
            if(joga(tabuleiro, j, 'X')==POSSIVEL){
                if(conta_ligados(tabuleiro, j)==maximo){
                coluna=coluna_central(coluna, j, ncol);
                }
                if(conta_ligados(tabuleiro, j)>maximo){
                maximo=conta_ligados(tabuleiro, j);
                coluna=j;
                }

            for(i=1; tabuleiro[i][j]==' '; i++)
            ;
            tabuleiro[i][j]=' ';
            }
        }
        return coluna;
    }

     if(marca_jogador=='O'){
        maximo=0;
        for(j=1; j<=ncol; j++){
            if(joga(tabuleiro, j, 'O')==POSSIVEL){
                if(conta_ligados(tabuleiro, j)==maximo){
                coluna=coluna_central(coluna, j, ncol);
                }
                if(conta_ligados(tabuleiro, j)>maximo){
                maximo=conta_ligados(tabuleiro, j);
                coluna=j;
                }

            for(i=1; tabuleiro[i][j]==' '; i++)
            ;
            tabuleiro[i][j]=' ';
            }
        }
        return coluna;
    }
 return coluna;
}




int carrega_configuracao(char tabuleiro[MAXLIN][MAXCOL], int *k,
                         int *nlin, int *ncol, char *tipo_xis, char *tipo_bola)
{
  FILE *arq_partida;
  char nome[80];
  int i, j;

  printf("Digite nome do arquivo com a partida: ");
  scanf("%s", nome);

  /* abre o arquivo para leitura */
  arq_partida = fopen(nome, "r");

  /* verifica se ocorreu erro na abertura do arquivo */
  if (arq_partida == NULL) {
    printf("ERRO: arquivo %s nao pode ser aberto.\n", nome);
    return 1;
  }

  fscanf(arq_partida, "%d %d %d %c %c ", &*k, &*nlin, &*ncol, &*tipo_xis, &*tipo_bola);

  for (i = 1; i <= *nlin; i++) {
    for (j = 1; j <= *ncol; j++) {
        fscanf(arq_partida, " %c ", &tabuleiro[i][j]);
        if (tabuleiro[i][j] == VAZIO)
          tabuleiro[i][j] = BRANCO;
    }
  }

  fclose(arq_partida);

  coloca_moldura(tabuleiro, *nlin, *ncol);

  return 0;
}

void DigiteEnter()
{
  char ch;

  printf("Digite <enter> para continuar...  ");
  scanf("%c", &ch);
  while (ch != '\n')
    {
      scanf("%c", &ch);
    }
}
