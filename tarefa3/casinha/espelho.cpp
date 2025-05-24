#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define h 256
#define w 256

typedef void (*Transformacao)(int *, int *);
typedef void (*Transformacao2)(int *, int *, float);
unsigned char img[h][w][3];

void aplicarTransformacao(int *x0, int *y0, int *x1, int *y1, Transformacao t) {
  t(x0, y0);
  t(x1, y1);
}

void aplicarTransformacao2(int *x0, int *y0, int *x1, int *y1,
                           Transformacao2 t) {
  t(x0, y0, 30);
  t(x1, y1, 30);
}


void espelharVertical(int *x, int *y) { *y = h - 1 - *y; }

void espelharHorizontal(int *x, int *y) { *x = w - 1 - *x; }

void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
  if (x >= 0 && x < w && y >= 0 && y < h) {
    img[y][x][0] = r;
    img[y][x][1] = g;
    img[y][x][2] = b;
  }
}

void clearImg() {
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      for (int c = 0; c < 3; c++) {
        img[i][j][c] = 255;
      }
    }
  }
}

void redimensionarLinha(int *x0, int *x1, int *y0, int *y1, int escalar) {
  *x0 *= escalar;
  *y0 *= escalar;
  *x1 *= escalar;
  *y1 *= escalar;
}

void salvarImg(char *nome) {
  FILE *fp = fopen(nome, "w");
  fprintf(fp, "P3\n%d %d\n255\n", w, h);
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      fprintf(fp, "%d %d %d ", img[i][j][0], img[i][j][1], img[i][j][2]);
    }
    fprintf(fp, "\n");
  }
  fclose(fp);
}

void drawLine(int x0, int y0, int x1, int y1, unsigned char r, unsigned char g,
              unsigned char b) {
  for (float t = 0.0; t < 1.0; t += 0.0001) {
    int x = (int)((x1 - x0) * t + x0);
    int y = (int)((y1 - y0) * t + y0);
    setPixel(x, y, r, g, b);
  }
}

void rotacionarPonto(int *x, int *y, float anguloGraus) {
  float anguloRad = anguloGraus * M_PI / 180.0;
  float cosA = cos(anguloRad);
  float sinA = sin(anguloRad);
  int x_orig = *x;
  int y_orig = *y;

  *x = (int)(x_orig * cosA - y_orig * sinA);
  *y = (int)(x_orig * sinA + y_orig * cosA);
}

void rotacionarEmTornoDoCentro(int *x, int *y, float anguloGraus) {
  int cx = w / 2;
  int cy = h / 2;

  *x -= cx;
  *y -= cy;

  rotacionarPonto(x, y, anguloGraus);

  *x += cx;
  *y += cy;
}

void cisalhamentoX(int *x, int *y, float anguloGraus = 30.0) {
  int cx = w / 2;
  int cy = h / 2;

  *x -= cx;
  *y -= cy;

  float anguloRad = anguloGraus * M_PI / 180.0;
  float tanA = tan(anguloRad);
  int x_orig = *x;
  int y_orig = *y;

  *y = y_orig;

  *x += cx;
  *y += cy;
}

void cisalhamentoY(int *x, int *y, float anguloGraus = 30.0) {
  int cx = w / 2;
  int cy = h / 2;

  *x -= cx;
  *y -= cy;

  float anguloRad = anguloGraus * M_PI / 180.0;
  float tanA = tan(anguloRad);
  int x_orig = *x;
  int y_orig = *y;

  *x = x_orig;
  *y = (int)(y_orig + x_orig * tanA);

  *x += cx;
  *y += cy;
}

void cisalhamentoXY(int *x, int *y, float anguloGraus = 30.0) {
  int cx = w / 2;
  int cy = h / 2;

  *x -= cx;
  *y -= cy;

  float anguloRad = anguloGraus * M_PI / 180.0;
  float tanA = tan(anguloRad);
  int x_orig = *x;
  int y_orig = *y;

  *x = (int)(x_orig + y_orig * tanA);
  *y = (int)(y_orig + x_orig * tanA);

  *x += cx;
  *y += cy;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: %s <nome do arquivo de saida>\n", argv[0]);
    return 1;
  }
  char *nomeArquivo = argv[1];

  clearImg();

  int meio_w = (w - 1) / 2;
  int base_x0 = (w - meio_w);
  int base_x1 = base_x0 + 50;
  int base_y0 = h - 1;
  int base_y1 = base_y0;

  int teto_x0 = base_x0;
  int teto_x1 = base_x1;
  int teto_y0 = base_y0 - 50;
  int teto_y1 = teto_y0;

  int left_wall_x0 = base_x0;
  int left_wall_y0 = base_y0;
  int left_wall_x1 = left_wall_x0;
  int left_wall_y1 = teto_y0;

  int rigth_wall_x0 = base_x1;
  int rigth_wall_y0 = base_y0;
  int rigth_wall_x1 = rigth_wall_x0;
  int rigth_wall_y1 = teto_y0;

  // telhado
  int teto_meio_x = (teto_x0 + teto_x1) / 2;
  int teto_meio_y = teto_y0 - 30; // altura do telhado

  int telhado_left_x0 = teto_x0;
  int telhado_left_y0 = teto_y1;
  int telhado_left_x1 = teto_meio_x;
  int telhado_left_y1 = teto_meio_y;

  int telhado_rigth_x0 = telhado_left_x1;
  int telhado_rigth_y0 = telhado_left_y1;
  int telhado_rigth_x1 = teto_x1;
  int telhado_rigth_y1 = teto_y0;

  // porta

  int altura_porta = 10;
  int largura_porta = 5;

  int base_porta_x0 = (base_x0 + base_x1) / 2 - largura_porta / 2;
  int base_porta_y0 = base_y0;
  int base_porta_x1 = base_porta_x0 + largura_porta;
  int base_porta_y1 = base_y0;

  int topo_porta_x0 = base_porta_x0;
  int topo_porta_y0 = base_y0 - altura_porta;
  int topo_porta_x1 = base_porta_x1;
  int topo_porta_y1 = topo_porta_y0;

  int porta_left_x0 = base_porta_x0;
  int porta_left_y0 = base_porta_y0;
  int porta_left_x1 = porta_left_x0;
  int porta_left_y1 = topo_porta_y1;

  int porta_rigth_x0 = base_porta_x1;
  int porta_rigth_y0 = base_porta_y0;
  int porta_rigth_x1 = porta_rigth_x0;
  int porta_rigth_y1 = topo_porta_y1;

  //   rotacionarEmTornoDoCentro(&base_x0, &base_y0, 180.0);
  //   rotacionarEmTornoDoCentro(&base_x1, &base_y1, 180.0);
  //   rotacionarEmTornoDoCentro(&teto_x0, &teto_y0, 180.0);
  //   rotacionarEmTornoDoCentro(&teto_x1, &teto_y1, 180.0);
  //   rotacionarEmTornoDoCentro(&left_wall_x0, &left_wall_y0, 180.0);
  //   rotacionarEmTornoDoCentro(&left_wall_x1, &left_wall_y1, 180.0);
  //   rotacionarEmTornoDoCentro(&rigth_wall_x0, &rigth_wall_y0, 180.0);
  //   rotacionarEmTornoDoCentro(&rigth_wall_x1, &rigth_wall_y1, 180.0);
  //   rotacionarEmTornoDoCentro(&telhado_left_x0, &telhado_left_y0, 180.0);
  //   rotacionarEmTornoDoCentro(&telhado_left_x1, &telhado_left_y1, 180.0);
  //   rotacionarEmTornoDoCentro(&telhado_rigth_x0, &telhado_rigth_y0, 180.0);
  //   rotacionarEmTornoDoCentro(&telhado_rigth_x1, &telhado_rigth_y1, 180.0);
  //   rotacionarEmTornoDoCentro(&base_porta_x0, &base_porta_y0, 180.0);
  //   rotacionarEmTornoDoCentro(&base_porta_x1, &base_porta_y1, 180.0);
  //   rotacionarEmTornoDoCentro(&topo_porta_x0, &topo_porta_y0, 180.0);
  //   rotacionarEmTornoDoCentro(&topo_porta_x1, &topo_porta_y1, 180.0);
  //   rotacionarEmTornoDoCentro(&porta_left_x0, &porta_left_y0, 180.0);
  //   rotacionarEmTornoDoCentro(&porta_left_x1, &porta_left_y1, 180.0);
  //   rotacionarEmTornoDoCentro(&porta_rigth_x0, &porta_rigth_y0, 180.0);
  //   rotacionarEmTornoDoCentro(&porta_rigth_x1, &porta_rigth_y1, 180.0);

  //   drawLine(telhado_left_x0, telhado_left_y0, telhado_left_x1,
  //   telhado_left_y1,
  //            100, 0, 0); // telhado left

  //   drawLine(telhado_rigth_x0, telhado_rigth_y0, telhado_rigth_x1,
  //            telhado_rigth_y1, 100, 0, 0);                 // telhado rigth
  //   drawLine(base_x0, base_y0, base_x1, base_y1, 0, 0, 0); // base
  //   drawLine(teto_x0, teto_y0, teto_x1, teto_y1, 0, 0, 0); // teto
  //   drawLine(left_wall_x0, left_wall_y0, left_wall_x1, left_wall_y1, 0, 0,
  //            0); // left wall
  //   drawLine(rigth_wall_x0, rigth_wall_y0, rigth_wall_x1, rigth_wall_y1, 0,
  //   0,
  //            0); // rigth wall

  //   drawLine(base_x0, base_y0, base_x1, base_y1, 0, 0, 0); // base
  //   drawLine(teto_x0, teto_y0, teto_x1, teto_y1, 0, 0, 0); // teto
  //   drawLine(left_wall_x0, left_wall_y0, left_wall_x1, left_wall_y1, 0, 0,
  //            0); // left wall
  //   drawLine(rigth_wall_x0, rigth_wall_y0, rigth_wall_x1, rigth_wall_y1, 0,
  //   0,
  //            0); // rigth wall
  //   drawLine(base_porta_x0, base_porta_y0, base_porta_x1, base_porta_y0, 139,
  //   69,
  //            19); // base da porta
  //   drawLine(topo_porta_x0, topo_porta_y0, topo_porta_x1, topo_porta_y0, 139,
  //   69,
  //            19); // topo da porta
  //   drawLine(porta_left_x0, porta_left_y0, porta_left_x1, porta_left_y1, 139,
  //   69,
  //            19); // porta left

  //   drawLine(porta_rigth_x0, porta_rigth_y0, porta_rigth_x1, porta_rigth_y1,
  //   139,
  //            69,
  //            19); // porta rigth

  //   // Espelhar a imagem
  //   espelharVertical(&base_x0, &base_y0);
  //   espelharVertical(&base_x1, &base_y1);
  //   espelharVertical(&teto_x0, &teto_y0);
  //   espelharVertical(&teto_x1, &teto_y1);
  //   espelharVertical(&left_wall_x0, &left_wall_y0);
  //   espelharVertical(&left_wall_x1, &left_wall_y1);
  //   espelharVertical(&rigth_wall_x0, &rigth_wall_y0);
  //   espelharVertical(&rigth_wall_x1, &rigth_wall_y1);
  //   espelharVertical(&telhado_left_x0, &telhado_left_y0);
  //   espelharVertical(&telhado_left_x1, &telhado_left_y1);
  //   espelharVertical(&telhado_rigth_x0, &telhado_rigth_y0);
  //   espelharVertical(&telhado_rigth_x1, &telhado_rigth_y1);
  //   espelharVertical(&base_porta_x0, &base_porta_y0);
  //   espelharVertical(&base_porta_x1, &base_porta_y1);
  //   espelharVertical(&topo_porta_x0, &topo_porta_y0);
  //   espelharVertical(&topo_porta_x1, &topo_porta_y1);
  //   espelharVertical(&porta_left_x0, &porta_left_y0);
  //   espelharVertical(&porta_left_x1, &porta_left_y1);
  //   espelharVertical(&porta_rigth_x0, &porta_rigth_y0);
  //   espelharVertical(&porta_rigth_x1, &porta_rigth_y1);

  //   drawLine(telhado_left_x0, telhado_left_y0, telhado_left_x1,
  //   telhado_left_y1,
  //            100, 0, 0); // telhado left

  //   drawLine(telhado_rigth_x0, telhado_rigth_y0, telhado_rigth_x1,
  //            telhado_rigth_y1, 100, 0, 0);                 // telhado rigth
  //   drawLine(base_x0, base_y0, base_x1, base_y1, 0, 0, 0); // base
  //   drawLine(teto_x0, teto_y0, teto_x1, teto_y1, 0, 0, 0); // teto
  //   drawLine(left_wall_x0, left_wall_y0, left_wall_x1, left_wall_y1, 0, 0,
  //            0); // left wall
  //   drawLine(rigth_wall_x0, rigth_wall_y0, rigth_wall_x1, rigth_wall_y1, 0,
  //   0,
  //            0); // rigth wall

  //   drawLine(base_x0, base_y0, base_x1, base_y1, 0, 0, 0); // base
  //   drawLine(teto_x0, teto_y0, teto_x1, teto_y1, 0, 0, 0); // teto
  //   drawLine(left_wall_x0, left_wall_y0, left_wall_x1, left_wall_y1, 0, 0,
  //            0); // left wall
  //   drawLine(rigth_wall_x0, rigth_wall_y0, rigth_wall_x1, rigth_wall_y1, 0,
  //   0,
  //            0); // rigth wall
  //   drawLine(base_porta_x0, base_porta_y0, base_porta_x1, base_porta_y0, 139,
  //   69,
  //            19); // base da porta
  //   drawLine(topo_porta_x0, topo_porta_y0, topo_porta_x1, topo_porta_y0, 139,
  //   69,
  //            19); // topo da porta
  //   drawLine(porta_left_x0, porta_left_y0, porta_left_x1, porta_left_y1, 139,
  //   69,
  //            19); // porta left

  //   drawLine(porta_rigth_x0, porta_rigth_y0, porta_rigth_x1, porta_rigth_y1,
  //   139,
  //            69,
  //            19); // porta rigth

  //   aplicarTransformacao(&base_x0, &base_y0, &base_x1, &base_y1,
  //                        espelharHorizontal);
  //   aplicarTransformacao(&teto_x0, &teto_y0, &teto_x1, &teto_y1,
  //                        espelharHorizontal);
  //   aplicarTransformacao(&left_wall_x0, &left_wall_y0, &left_wall_x1,
  //                        &left_wall_y1, espelharHorizontal);
  //   aplicarTransformacao(&rigth_wall_x0, &rigth_wall_y0, &rigth_wall_x1,
  //                        &rigth_wall_y1, espelharHorizontal);
  //   aplicarTransformacao(&telhado_left_x0, &telhado_left_y0,
  //   &telhado_left_x1,
  //                        &telhado_left_y1, espelharHorizontal);
  //   aplicarTransformacao(&telhado_rigth_x0, &telhado_rigth_y0,
  //   &telhado_rigth_x1,
  //                        &telhado_rigth_y1, espelharHorizontal);
  //   aplicarTransformacao(&base_porta_x0, &base_porta_y0, &base_porta_x1,
  //                        &base_porta_y1, espelharHorizontal);
  //   aplicarTransformacao(&topo_porta_x0, &topo_porta_y0, &topo_porta_x1,
  //                        &topo_porta_y1, espelharHorizontal);
  //   aplicarTransformacao(&porta_left_x0, &porta_left_y0, &porta_left_x1,
  //                        &porta_left_y1, espelharHorizontal);
  //   aplicarTransformacao(&porta_rigth_x0, &porta_rigth_y0, &porta_rigth_x1,
  //                        &porta_rigth_y1, espelharHorizontal);

  //   drawLine(telhado_left_x0, telhado_left_y0, telhado_left_x1,
  //   telhado_left_y1,
  //            100, 0, 0); // telhado left

  //   drawLine(telhado_rigth_x0, telhado_rigth_y0, telhado_rigth_x1,
  //            telhado_rigth_y1, 100, 0, 0);                 // telhado rigth
  //   drawLine(base_x0, base_y0, base_x1, base_y1, 0, 0, 0); // base
  //   drawLine(teto_x0, teto_y0, teto_x1, teto_y1, 0, 0, 0); // teto
  //   drawLine(left_wall_x0, left_wall_y0, left_wall_x1, left_wall_y1, 0, 0,
  //            0); // left wall
  //   drawLine(rigth_wall_x0, rigth_wall_y0, rigth_wall_x1, rigth_wall_y1, 0,
  //   0,
  //            0); // rigth wall

  //   drawLine(base_x0, base_y0, base_x1, base_y1, 0, 0, 0); // base
  //   drawLine(teto_x0, teto_y0, teto_x1, teto_y1, 0, 0, 0); // teto
  //   drawLine(left_wall_x0, left_wall_y0, left_wall_x1, left_wall_y1, 0, 0,
  //            0); // left wall
  //   drawLine(rigth_wall_x0, rigth_wall_y0, rigth_wall_x1, rigth_wall_y1, 0,
  //   0,
  //            0); // rigth wall
  //   drawLine(base_porta_x0, base_porta_y0, base_porta_x1, base_porta_y0, 139,
  //   69,
  //            19); // base da porta
  //   drawLine(topo_porta_x0, topo_porta_y0, topo_porta_x1, topo_porta_y0, 139,
  //   69,
  //            19); // topo da porta
  //   drawLine(porta_left_x0, porta_left_y0, porta_left_x1, porta_left_y1, 139,
  //   69,
  //            19); // porta left

  //   drawLine(porta_rigth_x0, porta_rigth_y0, porta_rigth_x1, porta_rigth_y1,
  //   139,
  //            69,
  //            19); // porta rigth

  // cisalhamento X
  aplicarTransformacao2(&base_x0, &base_y0, &base_x1, &base_y1, cisalhamentoXY);
  aplicarTransformacao2(&teto_x0, &teto_y0, &teto_x1, &teto_y1, cisalhamentoXY);
  aplicarTransformacao2(&left_wall_x0, &left_wall_y0, &left_wall_x1,
                        &left_wall_y1, cisalhamentoXY);
  aplicarTransformacao2(&rigth_wall_x0, &rigth_wall_y0, &rigth_wall_x1,
                        &rigth_wall_y1, cisalhamentoXY);
  aplicarTransformacao2(&telhado_left_x0, &telhado_left_y0, &telhado_left_x1,
                        &telhado_left_y1, cisalhamentoXY);
  aplicarTransformacao2(&telhado_rigth_x0, &telhado_rigth_y0, &telhado_rigth_x1,
                        &telhado_rigth_y1, cisalhamentoXY);
  aplicarTransformacao2(&base_porta_x0, &base_porta_y0, &base_porta_x1,
                        &base_porta_y1, cisalhamentoXY);
  aplicarTransformacao2(&topo_porta_x0, &topo_porta_y0, &topo_porta_x1,
                        &topo_porta_y1, cisalhamentoXY);
  aplicarTransformacao2(&porta_left_x0, &porta_left_y0, &porta_left_x1,
                        &porta_left_y1, cisalhamentoXY);
  aplicarTransformacao2(&porta_rigth_x0, &porta_rigth_y0, &porta_rigth_x1,
                        &porta_rigth_y1, cisalhamentoXY);

  drawLine(telhado_left_x0, telhado_left_y0, telhado_left_x1, telhado_left_y1,
           100, 0, 0); // telhado left

  drawLine(telhado_rigth_x0, telhado_rigth_y0, telhado_rigth_x1,
           telhado_rigth_y1, 100, 0, 0);                 // telhado rigth
  drawLine(base_x0, base_y0, base_x1, base_y1, 0, 0, 0); // base
  drawLine(teto_x0, teto_y0, teto_x1, teto_y1, 0, 0, 0); // teto
  drawLine(left_wall_x0, left_wall_y0, left_wall_x1, left_wall_y1, 0, 0,
           0); // left wall
  drawLine(rigth_wall_x0, rigth_wall_y0, rigth_wall_x1, rigth_wall_y1, 0, 0,
           0); // rigth wall

  drawLine(base_x0, base_y0, base_x1, base_y1, 0, 0, 0); // base
  drawLine(teto_x0, teto_y0, teto_x1, teto_y1, 0, 0, 0); // teto
  drawLine(left_wall_x0, left_wall_y0, left_wall_x1, left_wall_y1, 0, 0,
           0); // left wall
  drawLine(rigth_wall_x0, rigth_wall_y0, rigth_wall_x1, rigth_wall_y1, 0, 0,
           0); // rigth wall
  drawLine(base_porta_x0, base_porta_y0, base_porta_x1, base_porta_y0, 139, 69,
           19); // base da porta
  drawLine(topo_porta_x0, topo_porta_y0, topo_porta_x1, topo_porta_y0, 139, 69,
           19); // topo da porta
  drawLine(porta_left_x0, porta_left_y0, porta_left_x1, porta_left_y1, 139, 69,
           19); // porta left

  drawLine(porta_rigth_x0, porta_rigth_y0, porta_rigth_x1, porta_rigth_y1, 139,
           69,
           19); // porta rigth

  salvarImg(nomeArquivo);
  printf("Imagem salva como %s\n", nomeArquivo);

  return 0;
}
