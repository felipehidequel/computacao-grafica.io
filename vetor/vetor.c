#include "vetor.h"
#include <math.h>
#include <stdio.h>

Ponto2d criarPonto2d(float x, float y) {
  Ponto2d a = {x, y};
  return a;
}

Ponto3d criarPonto3d(float x, float y, float z) {
  Ponto3d a = {x, y, z};
  return a;
}

void imprimirPonto2d(Ponto2d p) { printf("(%.1f, %.1f)\n", p.x, p.y); }
void imprimirPonto3d(Ponto3d p) {
  printf("(%.1f, %.1f, %.1f)\n", p.x, p.y, p.z);
}

Vetor2d criarVetor2d(float x, float y) {
  Ponto2d p = {x, y};
  Vetor2d vetor = {p};
  return vetor;
}

Vetor3d criarVetor3d(float x, float y, float z) {
  Ponto3d p = {x, y, z};
  Vetor3d vetor = {p};
  return vetor;
}

Vetor2d encontrarVetor2d(Ponto2d a, Ponto2d b) {
  Vetor2d ab;
  Ponto2d coord = {b.x - a.x, b.y - a.y};
  ab.coordenadas = coord;
  return ab;
}

Vetor3d encontrarVetor3d(Ponto3d a, Ponto3d b) {
  Vetor3d ab;
  Ponto3d coord = {b.x - a.x, b.y - a.y, b.z - a.z};
  ab.coordenadas = coord;
  return ab;
}

void imprimirVetor2d(Vetor2d vetor) {
  printf("<%.1f, %.1f>\n", vetor.coordenadas.x, vetor.coordenadas.y);
}

void imprimirVetor3d(Vetor3d vetor) {
  printf("<%.1f, %.1f, %.1f>\n", vetor.coordenadas.x, vetor.coordenadas.y,
         vetor.coordenadas.z);
}

float calcularNorma2d(Vetor2d vetor) {
  printf("\nVetor:\n");
  imprimirVetor2d(vetor);

  float norma = pow(vetor.coordenadas.x, 2) + pow(vetor.coordenadas.y, 2);

  norma = sqrt(norma);

  printf("Norma: %f\n", norma);

  return norma;
}

float calcularNorma3d(Vetor3d vetor) {
  printf("\nVetor:\n");
  imprimirVetor3d(vetor);

  float norma = pow(vetor.coordenadas.x, 2) + pow(vetor.coordenadas.y, 2) +
                pow(vetor.coordenadas.z, 2);

  norma = sqrt(norma);

  printf("Norma: %f\n", norma);

  return norma;
}

Ponto2d deslocarPonto2d(Ponto2d p, Vetor2d v) {
  p.x += v.coordenadas.x;
  p.y += v.coordenadas.y;

  return p;
}

Ponto3d deslocarPonto3d(Ponto3d p, Vetor3d v) {
  p.x += v.coordenadas.x;
  p.y += v.coordenadas.y;
  p.z += v.coordenadas.z;

  return p;
}

Vetor2d somarVetores2d(Vetor2d v1, Vetor2d v2) {
  v1.coordenadas.x += v2.coordenadas.x;
  v1.coordenadas.y += v2.coordenadas.y;

  return v1;
}

Vetor3d somarVetores3d(Vetor3d v1, Vetor3d v2) {
  v1.coordenadas.x += v2.coordenadas.x;
  v1.coordenadas.y += v2.coordenadas.y;
  v1.coordenadas.z += v2.coordenadas.z;

  return v1;
}

Vetor2d subtrairVetores2d(Vetor2d v1, Vetor2d v2) {
  v1.coordenadas.x -= v2.coordenadas.x;
  v1.coordenadas.y -= v2.coordenadas.y;

  return v1;
}

Vetor3d subtrairVetores3d(Vetor3d v1, Vetor3d v2) {
  v1.coordenadas.x -= v2.coordenadas.x;
  v1.coordenadas.y -= v2.coordenadas.y;
  v1.coordenadas.z -= v2.coordenadas.z;

  return v1;
}

Vetor2d multiplicarVetores2d(Vetor2d v1, float escalar) {
  v1.coordenadas.x *= escalar;
  v1.coordenadas.y *= escalar;

  return v1;
}
Vetor3d multiplicarVetores3d(Vetor3d v1, float escalar) {
  v1.coordenadas.x *= escalar;
  v1.coordenadas.y *= escalar;
  v1.coordenadas.z *= escalar;

  return v1;
}

Vetor2d normalizarVetor2d(Vetor2d v) {
  float norma = pow(v.coordenadas.x, 2) + pow(v.coordenadas.y, 2);
  norma = sqrt(norma);

  v.coordenadas.x /= norma;
  v.coordenadas.y /= norma;

  return v;
}

Vetor3d normalizarVetor3d(Vetor3d v) {
  float norma = pow(v.coordenadas.x, 2) + pow(v.coordenadas.y, 2) +
                pow(v.coordenadas.z, 2);
  norma = sqrt(norma);

  v.coordenadas.x /= norma;
  v.coordenadas.y /= norma;
  v.coordenadas.z /= norma;

  return v;
}

float produtoInterno2d(Vetor2d v1, Vetor2d v2) {
  float prod;
  prod = (v1.coordenadas.x * v2.coordenadas.x) +
         (v1.coordenadas.y * v2.coordenadas.y);

  return prod;
}

float produtoInterno3d(Vetor3d v1, Vetor3d v2) {
  float prod;
  prod = (v1.coordenadas.x * v2.coordenadas.x) +
         (v1.coordenadas.y * v2.coordenadas.y) +
         (v1.coordenadas.z * v2.coordenadas.z);

  return prod;
}

Vetor2d criarVetorUnitario2d(Vetor2d v) {
  float norma = pow(v.coordenadas.x, 2) + pow(v.coordenadas.y, 2);
  norma = sqrt(norma);

  v.coordenadas.x /= norma;
  v.coordenadas.y /= norma;

  return v;
}
Vetor3d criarVetorUnitario3d(Vetor3d v) {
  float norma = pow(v.coordenadas.x, 2) + pow(v.coordenadas.y, 2) +
                pow(v.coordenadas.z, 2);
  norma = sqrt(norma);

  v.coordenadas.x /= norma;
  v.coordenadas.y /= norma;
  v.coordenadas.z /= norma;

  return v;
}

float produtoVetorial2d(Vetor2d v1, Vetor2d v2) {
  return (v1.coordenadas.x * v2.coordenadas.y) -
         (v2.coordenadas.x * v1.coordenadas.y);
}

Vetor3d produtoVetorial3d(Vetor3d v, Vetor3d w) {
  Vetor3d resultado;

  resultado.coordenadas.x =
      v.coordenadas.y * w.coordenadas.z - v.coordenadas.z * w.coordenadas.y;
  resultado.coordenadas.y =
      v.coordenadas.z * w.coordenadas.x - v.coordenadas.x * w.coordenadas.z;
  resultado.coordenadas.z =
      v.coordenadas.x * w.coordenadas.y - v.coordenadas.y * w.coordenadas.x;

  return resultado;
}
