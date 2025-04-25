#include <stdio.h>
#include <stdlib.h>

void altera_valor_pixel(int *matriz, int x, int y, int width, int r, int g,
                        int b) {
  int index = (y * width + x) * 3;
  matriz[index] = r;
  matriz[index + 1] = g;
  matriz[index + 2] = b;
}

void inicializa_branca(int *matriz, int width, int heigt) {
  for (int i = 0; i < heigt * width * 3; i++) {
    matriz[i] = 255;
  }
}

void inicializa_preto(int *matriz, int width, int heigt) {
  for (int i = 0; i < heigt * width * 3; i++) {
    matriz[i] = 0;
  }
}

int salva_ppm(int width, int height, FILE *file, int *matriz) {
  fprintf(file, "P3\n%d %d\n255\n", width, height);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int index = (i * width + j) * 3;
      fprintf(file, "%d %d %d\n", matriz[index], matriz[index + 1],
              matriz[index + 2]);
    }
  }
  return 1;
}

int main() {
  FILE *file = fopen("saida.ppm", "w");
  if (file == NULL) {
    printf("Open file error\n");
    return -1;
  }

  int width = 100, height = 100;
  int *matriz = malloc(width * height * 3 * sizeof(int));
  if (matriz == NULL) {
    printf("Memory allocation error\n");
    fclose(file);
    return -1;
  }

  // Pixel vermelho no centro
  int centro_x = width / 2;
  int centro_y = height / 2;
  inicializa_branca(matriz, width, height);
  inicializa_preto(matriz, width, height);

  altera_valor_pixel(matriz, centro_x, centro_y, width, 255, 0, 0);

  altera_valor_pixel(matriz, centro_x + 1, centro_y, width, 255, 0, 0);
  altera_valor_pixel(matriz, centro_x + 1, centro_y, width, 255, 0, 0);
  altera_valor_pixel(matriz, centro_x - 1, centro_y, width, 255, 0, 0);
  altera_valor_pixel(matriz, centro_x - 1, centro_y, width, 255, 0, 0);

  altera_valor_pixel(matriz, centro_x, centro_y + 1, width, 255, 0, 0);
  altera_valor_pixel(matriz, centro_x, centro_y + 2, width, 255, 0, 0);
  altera_valor_pixel(matriz, centro_x, centro_y + 1, width, 255, 0, 0);

  salva_ppm(width, height, file, matriz);
  free(matriz);
  fclose(file);
  return 0;
}
