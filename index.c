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

// typedef struct Node {
//   int l;
//   int c;
//   int pontos;
//   Node *prox;
// }Node;

// // escolhe a posição para jogar
// void escolhejogada(int tabuleiro[8][8], int cor, int *linha, int *coluna) {
//   Node *HEAD;
//   HEAD = malloc(sizeof (Node));
//   HEAD->prox = NULL;
//   Node *jogadas_possiveis = HEAD;

//   int cor_oponente = 1;
//   if (cor == 1) cor_oponente = -1;

  
// }

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
      if (aux == cor) fecha = 1;
      break;
    }
    cerca += 1;
  }
  if (cerca >= 1 && fecha == 1) return cerca;
  return 0;
}

// deve retornar 1 ou 0 (verdadeiro ou falso)
int podejogar(int tabuleiro[8][8], int cor, int l, int c) {
  int jogada = tabuleiro[l][c];

  // se já houver uma peça na posição, retorne falso
  if (jogada != 0) return 0;

  int qtd_cerca = 0;

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      qtd_cerca = v_reta(tabuleiro, cor, l, c, i, j);
      if (qtd_cerca > 0) break;
    }
    if (qtd_cerca > 0) break;
  }

  if (qtd_cerca > 0) {
    return 1;
  }
  return 0;
}

void transforma_reta(int tabuleiro[8][8], int cor, int l, int c, int direcao_l, int direcao_c) {
  int i = l;
  int j = c;

  while (i >= 0 && j >= 0 && i < 8 && j < 8) {
    if (direcao_c == -1) j--;
    if (direcao_c == 1) j++;
    if (direcao_l == -1) i--;
    if (direcao_l == 1) i++;

    if (i < 0 || j < 0 || i == 8 || j == 8) break;

    int aux = tabuleiro[i][j];

    if (aux == 0 || aux == cor) {
      break;
    }
    tabuleiro[i][j] = cor;
  }
}

// altera o tabuleiro
void joga(int tabuleiro[8][8], int cor, int l, int c) {
  int qtd_cerca = 0;

  tabuleiro[l][c] = cor;

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      qtd_cerca = v_reta(tabuleiro, cor, l, c, i, j);
      if (qtd_cerca > 0) {
        transforma_reta(tabuleiro, cor, l, c, i, j);
      }
    }
  }

  return;
}

int main() {
  int tabuleiro[8][8]= {0} ;
  inicializar(tabuleiro);
  
  imprimir(tabuleiro);

  int x,y,cor;
  scanf("%d", &cor);

  imprimir(tabuleiro);

  // gameloop
  while(1) {
    if (cor == 1) cor = -1;
    else if (cor == -1) cor = 1;

    printf("vez da cor %d\n", cor);

    scanf("%d %d", &x, &y);
    if (x == -1 && y == -1) break;

    int pode_jogar = podejogar(tabuleiro, cor, x, y);
    printf("%d\n", pode_jogar);

    if (pode_jogar == 1) {
      joga(tabuleiro, cor, x, y);
    }
    imprimir(tabuleiro);
  }
  return 0;
}