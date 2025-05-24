#include <stdio.h>
#include <stdlib.h>

#define h 256
#define w 256

unsigned char img[h][w][3];

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

void redimensionarLinhaComCentro(int *x0, int *y0, int *x1, int *y1,
                                 float escalar, int cx, int cy) {
  *x0 = (int)((*x0 - cx) * escalar + cx);
  *y0 = (int)((*y0 - cy) * escalar + cy);
  *x1 = (int)((*x1 - cx) * escalar + cx);
  *y1 = (int)((*y1 - cy) * escalar + cy);
}

void salvarImg() {
  FILE *fp = fopen("saida.ppm", "w");
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

int main() {
  clearImg();

  int meio_w = (w - 1) / 2;
  int base_x0 = meio_w - 25;
  int base_x1 = base_x0 + 50;
  int base_y0 = (h - 1);
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

  int teto_meio_x = (teto_x0 + teto_x1) / 2;
  int teto_meio_y = teto_y0 - 30;

  int telhado_left_x0 = teto_x0;
  int telhado_left_y0 = teto_y1;
  int telhado_left_x1 = teto_meio_x;
  int telhado_left_y1 = teto_meio_y;

  int telhado_rigth_x0 = telhado_left_x1;
  int telhado_rigth_y0 = telhado_left_y1;
  int telhado_rigth_x1 = teto_x1;
  int telhado_rigth_y1 = teto_y0;

  int altura_porta = 10*2;
  int largura_porta = 5*2;

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

  int centro_x = (base_x0 + base_x1) / 2;
  int centro_y = (teto_y0 + base_y0) / 2;

  float escala = 1.5f;
  altura_porta *= (int)escala;
  largura_porta *= (int)escala;

  redimensionarLinhaComCentro(&base_x0, &base_y0, &base_x1, &base_y1, escala,
                              centro_x, centro_y);
  redimensionarLinhaComCentro(&teto_x0, &teto_y0, &teto_x1, &teto_y1, escala,
                              centro_x, centro_y);
  redimensionarLinhaComCentro(&left_wall_x0, &left_wall_y0, &left_wall_x1,
                              &left_wall_y1, escala, centro_x, centro_y);
  redimensionarLinhaComCentro(&rigth_wall_x0, &rigth_wall_y0, &rigth_wall_x1,
                              &rigth_wall_y1, escala, centro_x, centro_y);
  redimensionarLinhaComCentro(&telhado_left_x0, &telhado_left_y0,
                              &telhado_left_x1, &telhado_left_y1, escala,
                              centro_x, centro_y);
  redimensionarLinhaComCentro(&telhado_rigth_x0, &telhado_rigth_y0,
                              &telhado_rigth_x1, &telhado_rigth_y1, escala,
                              centro_x, centro_y);
  redimensionarLinhaComCentro(&base_porta_x0, &base_porta_y0, &base_porta_x1,
                              &base_porta_y1, escala, centro_x, centro_y);
  redimensionarLinhaComCentro(&topo_porta_x0, &topo_porta_y0, &topo_porta_x1,
                              &topo_porta_y1, escala, centro_x, centro_y);
  redimensionarLinhaComCentro(&porta_left_x0, &porta_left_y0, &porta_left_x1,
                              &porta_left_y1, escala, centro_x, centro_y);
  redimensionarLinhaComCentro(&porta_rigth_x0, &porta_rigth_y0, &porta_rigth_x1,
                              &porta_rigth_y1, escala, centro_x, centro_y);

  drawLine(base_x0, base_y0, base_x1, base_y1, 0, 0, 0);
  drawLine(teto_x0, teto_y0, teto_x1, teto_y1, 0, 0, 0);
  drawLine(left_wall_x0, left_wall_y0, left_wall_x1, left_wall_y1, 0, 0, 0);
  drawLine(rigth_wall_x0, rigth_wall_y0, rigth_wall_x1, rigth_wall_y1, 0, 0, 0);
  drawLine(telhado_left_x0, telhado_left_y0, telhado_left_x1, telhado_left_y1,
           100, 0, 0);
  drawLine(telhado_rigth_x0, telhado_rigth_y0, telhado_rigth_x1,
           telhado_rigth_y1, 100, 0, 0);
  drawLine(base_porta_x0, base_porta_y0, base_porta_x1, base_porta_y1, 139, 69,
           19);
  drawLine(topo_porta_x0, topo_porta_y0, topo_porta_x1, topo_porta_y1, 139, 69,
           19);
  drawLine(porta_left_x0, porta_left_y0, porta_left_x1, porta_left_y1, 139, 69,
           19);
  drawLine(porta_rigth_x0, porta_rigth_y0, porta_rigth_x1, porta_rigth_y1, 139,
           69, 19);

  salvarImg();

  return 0;
}
