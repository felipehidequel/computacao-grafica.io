#include "vetor.h"
#include <stdio.h>

void encontrar_vetores();
void encontrar_norma();
void realize_deslocamento();
void multiplique_normalize();
void produto_interno();
void produto_vetorial();
void soma_subtracao();

int main() {
  // encontrar os vetores a partir dos pontos
  encontrar_vetores();

  // encontre a norma
  encontrar_norma();

  // deslocamento
  realize_deslocamento();
  soma_subtracao();

  // multiplique e normalize
  multiplique_normalize();

  // produto escalar e vetores unitarios
  produto_interno();

  produto_vetorial();
  return 0;
}

void encontrar_vetores() {
  // encontre os vetores a partir dos pontos
  Ponto2d a1, b1;
  Ponto2d a2, b2;
  Ponto3d a3, b3;
  Ponto3d a4, b4;
  Vetor2d a1b1, a2b2;
  Vetor3d a3b3, a4b4;

  a1 = criarPonto2d(2, 4);
  b1 = criarPonto2d(6, 2);

  a2 = criarPonto2d(6, 7);
  b2 = criarPonto2d(-1, -2);

  a3 = criarPonto3d(2, 2, 4);
  b3 = criarPonto3d(1, 1, 1);

  a4 = criarPonto3d(-2, 4, -5);
  b4 = criarPonto3d(5, 2, -5);

  printf("Encontre o vetor a partir dos pontos: \n");
  printf("\na1 e b1: \n");
  imprimirPonto2d(a1);
  imprimirPonto2d(b1);

  a1b1 = encontrarVetor2d(a1, b1);
  imprimirVetor2d(a1b1);

  printf("\na2 e b2: \n");

  imprimirPonto2d(a2);
  imprimirPonto2d(b2);

  a2b2 = encontrarVetor2d(a2, b2);
  imprimirVetor2d(a2b2);

  printf("\na3 e b3: \n");

  imprimirPonto3d(a3);
  imprimirPonto3d(b3);

  a3b3 = encontrarVetor3d(a3, b3);
  imprimirVetor3d(a3b3);

  printf("\na4 e b4: \n");

  imprimirPonto3d(a4);
  imprimirPonto3d(b4);

  a4b4 = encontrarVetor3d(a4, b4);
  imprimirVetor3d(a4b4);
}

void encontrar_norma() {
  Vetor2d a = criarVetor2d(2, -5);
  Vetor2d b = criarVetor2d(4, 2);
  Vetor3d c = criarVetor3d(3, 5, -6);
  Vetor3d d = criarVetor3d(6, -2, 1);
  float norma;

  printf("\nEncontre a norma dos seguintes vetores: \n");
  norma = calcularNorma2d(a);
  norma = calcularNorma2d(b);
  norma = calcularNorma3d(c);
  norma = calcularNorma3d(d);
}

void realize_deslocamento() {
  Ponto2d a1 = criarPonto2d(2, -5);
  Ponto3d a2 = criarPonto3d(3, 5, -6);

  Vetor2d v1 = criarVetor2d(2, 4);
  Vetor3d v2 = criarVetor3d(-3, 2, -3);

  printf("Realize o deslocamento dos pontos usando os vetores.\n");

  printf("A: \n");
  imprimirPonto2d(a1);
  printf("V: \n");
  imprimirVetor2d(v1);

  a1 = deslocarPonto2d(a1, v1);
  printf("Resposta:\n");
  imprimirPonto2d(a1);

  printf("\nA: \n");
  imprimirPonto3d(a2);
  printf("V: \n");
  imprimirVetor3d(v2);

  a2 = deslocarPonto3d(a2, v2);
  printf("Resposta:\n");
  imprimirPonto3d(a2);
}

void multiplique_normalize() {
  printf("Multiplique o vetor <2,4> pelo escalar 3\n");

  Vetor2d v1 = criarVetor2d(2, 4);

  v1 = multiplicarVetores2d(v1, 3);
  imprimirVetor2d(v1);

  printf("Multiplique o vetor <1,7,5> pelo escalar -5\n");

  Vetor3d v2 = criarVetor3d(1, 7, 5);

  v2 = multiplicarVetores3d(v2, -5);
  imprimirVetor3d(v2);

  // normalização

  printf("\nNormalize o vetor v =< 12, 3 >\n");
  Vetor2d v3 = criarVetor2d(13, 3);

  v3 = normalizarVetor2d(v3);

  imprimirVetor2d(v3);

  printf("\nNormalize o vetor v =< -3, 4, -5 >\n");
  Vetor3d v4 = criarVetor3d(-3, 4, -5);

  v4 = normalizarVetor3d(v4);

  imprimirVetor3d(v4);
}

void produto_interno() {
  Vetor2d a1, b1;
  Vetor3d a2, b2;

  a1 = criarVetor2d(2, -4);
  b1 = criarVetor2d(5, 3);
  float produto = produtoInterno2d(a1, b1);

  printf("Calcule o produto escalar entre os vetores a =< 2, −4 > e b =< 5, 3 "
         ">;\n");
  printf("%f\n", produto);

  printf("Calcule o produto interno entre os vetores a =< 1, 7, 5 > e b =< 2, "
         "4, 5 >;\n");
  a2 = criarVetor3d(1, 7, 5);
  b2 = criarVetor3d(2, 4, 5);

  produto = produtoInterno3d(a2, b2);
  printf("%f\n", produto);

  printf("Transforme o vetor v =< 12, 3 > em vetor unitário;\n");
  Vetor2d v1 = criarVetor2d(12, 3);
  Vetor3d v2 = criarVetor3d(-3, 4, -5);

  v1 = criarVetorUnitario2d(v1);
  imprimirVetor2d(v1);

  printf("Transforme o vetor v =< −3, 4, −5 > em vetor unitário\n");
  v2 = criarVetorUnitario3d(v2);
  imprimirVetor3d(v2);
}

void produto_vetorial() {
  printf("Calcule o produto vetorial entre os vetores a =< 2, −4 > e b =< 5, 3 "
         ">;\n");
  Vetor2d a1, b1;

  a1 = criarVetor2d(2, -4);
  b1 = criarVetor2d(5, 3);

  float produto = produtoVetorial2d(a1, b1);

  printf("%f\n", produto);

  printf("Calcule o produto vetorial entre os vetores a =< 1, 7, 5 > e b =< 2, "
         "4, 5 >;\n");

  Vetor3d a2, b2;

  a2 = criarVetor3d(1, 7, 5);
  b2 = criarVetor3d(2, 4, 5);

  Vetor3d produto3d = produtoVetorial3d(a2, b2);

  imprimirVetor3d(produto3d);
}

void soma_subtracao() {
  printf("\nSoma entre a =< 2, −5 > e v =< 2, 4 >;\n");
  Vetor2d a, b;
  a = criarVetor2d(2, -5);
  b = criarVetor2d(2, 4);

  a = somarVetores2d(a, b);
  imprimirVetor2d(a);

  printf("Subtracao entre a =< 3, 2 > e v =< 1, 7 >;\n");

  a = criarVetor2d(3, 2);
  b = criarVetor2d(1, 7);

  a = subtrairVetores2d(a, b);
  imprimirVetor2d(a);

  printf("Soma entre a =< 3, 5, −6 > e v =< −3, 2, −3 >;\n");
  Vetor3d c, d;
  c = criarVetor3d(3, 5, -6);
  d = criarVetor3d(-3, 2, -3);

  c = somarVetores3d(c, d);

  imprimirVetor3d(c);

  printf("Subtracao entre a =< 5, 5, 1 > e v =< 3, 1, 7 >;\n");
  c = criarVetor3d(5, 5, 1);
  d = criarVetor3d(3, 1, 7);

  c = subtrairVetores3d(c, d);

  imprimirVetor3d(c);
}