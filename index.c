#include<stdio.h>

typedef struct Pos {
  int l;
  int c;
} Pos;

#define cor_pretas -1
#define cor_brancas 1
#define cor_vazio 0 

void inicializar(int tabuleiro[8][8]) {
  Pos inicial_brancas[2];
  Pos inicial_pretas[2];
  inicial_brancas[0].l = 3;
  inicial_brancas[0].c = 3;
  inicial_brancas[1].l = 4;
  inicial_brancas[1].c = 4;
  inicial_pretas[0].l = 4;
  inicial_pretas[0].c = 3;
  inicial_pretas[1].l = 3;
  inicial_pretas[1].c = 4;
  
  for (int i = 0; i < 2; i++) {
    tabuleiro[inicial_brancas[i].l][inicial_brancas[i].c] = 1;
    tabuleiro[inicial_pretas[i].l][inicial_pretas[i].c] = -1;
  }
}

void imprimir(int tabuleiro[8][8]) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      printf("%d ", tabuleiro[i][j]);
    }
    printf("\n");
  }
}

// escolhe a posição para jogar
void escolhejogada(int tabuleiro[8][8], int cor, int *linha, int *coluna);

int v_reta(int tabuleiro[8][8], int cor, int l, int c, int direcao_l, int direcao_c) {
  int i = l;
  int j = c;

  // checa se as peças do oponente são cercadas
  int cerca = 0; // false
  
  // checa o cercamento é fechado 
  int fecha = 0; // false

  while (i >= 0 && j >= 0 && i < 8 && j < 8) {
    if (direcao_c == -1) j--;
    if (direcao_c == 1) j++;
    if (direcao_l == -1) i--;
    if (direcao_l == 1) i++;

    if (i < 0 || j < 0 || i == 8 || j == 8) break;

    int aux = tabuleiro[i][j];

    if (aux == 0 || aux == cor) {
      fecha = 1; //true
      break;
    }
    cerca += 1;
  }
  if (cerca >= 1 && fecha == 1) return 1;
  return 0;
}

// deve retornar 1 ou 0 (verdadeiro ou falso)
int podejogar(int tabuleiro[8][8], int cor, int l, int c) {
  int jogada = tabuleiro[l][c];

  // se já houver uma peça na posição, retorne falso
  if (jogada != 0) return 0;

  int valido = 0;

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      valido = v_reta(tabuleiro, cor, l, c, i, j);
      if (valido == 1) break;
    }
    if (valido == 1) break;
  }

  return valido;
}

// altera o tabuleiro
void joga(int tabuleiro[8][8], int cor, int l, int c);

int main() {
  int tabuleiro[8][8]= {0} ;
  inicializar(tabuleiro);
  
  imprimir(tabuleiro);

  int x,y,cor;
  scanf("%d", &cor);
  scanf("%d %d", &x, &y);

  printf("%d\n", podejogar(tabuleiro, cor, x, y));

  // gameloop
  // while(1) {

  // }
  return 0;
}