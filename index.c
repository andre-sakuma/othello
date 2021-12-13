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

// verifica se o jogador tem jogadas disponíveis
int tem_jogada(int tabuleiro[8][8], int cor) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (podejogar(tabuleiro, cor, i, j)) {
        return 1;
      }
    }
  }
  return 0;
} 

// imprime estado atual do tabuleiro
void imprimir(int tabuleiro[8][8]) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int aux = tabuleiro[i][j];
      if (aux == -1) {
        printf("[%d ] ", aux);
      } else {
        printf("[ %d ] ", aux);
      }
    }
    printf("\n");
  }
}

// quantidade de pontos possíveis naquela posição
int qtd_pontos(int tabuleiro[8][8], int cor, int l, int c) {
  int pontos = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      pontos += v_reta(tabuleiro, cor, l, c, i, j);
    }
  }
  return pontos;
}

// escolhe a posição para jogar
void escolhejogada(int tabuleiro[8][8], int cor, int *linha, int *coluna) {
  int max_pontos = 0;

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (podejogar(tabuleiro, cor, i, j)) {
        int pontos = qtd_pontos(tabuleiro, cor, i, j);
        if (pontos > max_pontos) {
          *linha = i;
          *coluna = j;
          max_pontos = pontos;
        }
      }
    }
  } 
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

    // troca a cor do tabuleiro até encontrar a sua própria cor
    // só é possível usar essa função se garantirmos que nessa direção é possivel fazer uma jogada
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

void troca_vez(int *vez) {
  if (*vez == 1) {
    *vez = -1;
  } else {
    *vez = 1;
  }
  return;
}

// conta as peças no tabuleiro e define um vencedor
int ver_vencedor(int tabuleiro[8][8]) {
  int pretas = 0;
  int brancas = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      int aux = tabuleiro[i][j];
      if (aux == -1) pretas++;
      if (aux == 1) brancas++;
    }
  }
  if (brancas > pretas) return 1;
  return -1;
}

int main() {
  int tabuleiro[8][8]= {0} ;
  
  int x,y,cor;
  printf("Digite 1 para jogar com as brancas e -1 para jogar com as pretas.\n");
  scanf("%d", &cor);

  inicializar(tabuleiro);
  imprimir(tabuleiro);
  int vez = -1;
  int cor_pc = -1;
  if (cor == -1) cor_pc = 1;
  int vencedor = 0;

  // gameloop
  while(1) {
    if (tem_jogada(tabuleiro, vez) == 0) {
      printf("Não há movimentos válidos para você. Sua vez será pulada.\n");
      troca_vez(&vez);
      if (tem_jogada(tabuleiro, vez) == 0) {
        printf("Nenhum dos dois jogadores podem realizar um movimento, o jogo será encerrado.\n");
        vencedor = ver_vencedor(tabuleiro);
        break;
      }
    }
    if (vez == cor) {
      printf("sua vez\n");
      scanf("%d %d", &x, &y);
    } else {
      printf("vez do oponente\n");
      escolhejogada(tabuleiro, cor_pc, &x, &y);
    }

    int pode_jogar = podejogar(tabuleiro, vez, x, y);

    if (pode_jogar == 1) {
      joga(tabuleiro, vez, x, y);
    } else {
      if (vez == 1) {
        vencedor = -1;
      } else {
        vencedor = 1;
      }
      break;
    }
    imprimir(tabuleiro);
    troca_vez(&vez);
  }

  if (vencedor == cor) {
    printf("você venceu!\n");
  } else {
    printf("você perdeu!\n");
  }

  return 0;
}