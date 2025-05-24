#ifndef VETOR_H
#define VETOR_H

typedef struct ponto2d {
  float x, y;
} Ponto2d;

typedef struct ponto3d {
  float x, y, z;
} Ponto3d;

typedef struct vetor2d {
  Ponto2d coordenadas;
} Vetor2d;

typedef struct vetor3d {
  Ponto3d coordenadas;
} Vetor3d;

Ponto2d criarPonto2d(float x, float y);
Ponto3d criarPonto3d(float x, float y, float z);

void imprimirPonto2d(Ponto2d p);
void imprimirPonto3d(Ponto3d p);

Vetor2d criarVetor2d(float x, float y);
Vetor3d criarVetor3d(float x, float y, float z);

Vetor2d encontrarVetor2d(Ponto2d a, Ponto2d b);
Vetor3d encontrarVetor3d(Ponto3d a, Ponto3d b);

void imprimirVetor2d(Vetor2d vetor);
void imprimirVetor3d(Vetor3d vetor);

float calcularNorma2d(Vetor2d vetor);
float calcularNorma3d(Vetor3d vetor);

Ponto2d deslocarPonto2d(Ponto2d p, Vetor2d v);
Ponto3d deslocarPonto3d(Ponto3d p, Vetor3d v);

Vetor2d somarVetores2d(Vetor2d v1, Vetor2d v2);
Vetor3d somarVetores3d(Vetor3d v1, Vetor3d v2);

Vetor2d subtrairVetores2d(Vetor2d v1, Vetor2d v2);
Vetor3d subtrairVetores3d(Vetor3d v1, Vetor3d v2);

Vetor2d multiplicarVetores2d(Vetor2d v1, float escalar);
Vetor3d multiplicarVetores3d(Vetor3d v1, float escalar);

Vetor2d normalizarVetor2d(Vetor2d v);
Vetor3d normalizarVetor3d(Vetor3d v);

float produtoInterno2d(Vetor2d v1, Vetor2d v2);
float produtoInterno3d(Vetor3d v1, Vetor3d v2);

Vetor2d criarVetorUnitario2d(Vetor2d v);
Vetor3d criarVetorUnitario3d(Vetor3d v);

float produtoVetorial2d(Vetor2d v1, Vetor2d v2);
Vetor3d produtoVetorial3d(Vetor3d v, Vetor3d w);

#endif // VETOR_H
