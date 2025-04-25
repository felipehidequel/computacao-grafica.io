#include <stdio.h>
#include <stdlib.h>

// (x,y) = (p2 - p1)t + p1

#define h 256
#define w 256

unsigned char img[h][w][3];

void setPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
  img[x][y][0] = r;
  img[x][y][1] = g;
  img[x][y][2] = b;
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

void salvarImg() {
  FILE *fp = fopen("saida.ppm", "w");

  fprintf(fp, "P3\n %d \t %d\n 255\n", h, w);
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      for (int c = 0; c < 3; c++) {
        fprintf(fp, "%d \t", img[i][j][c]);
      }
      fprintf(fp, "\n");
    }
  }

  fclose(fp);
}

void drawLine(int x0, int y0, int x1, int y1, unsigned char r, unsigned char g,
              unsigned char b) {
  for (float t = 0.0; t < 1; t += 0.00001) {
    setPixel((int)(x1 - x0) * t + x0, (int)(y1 - y0) * t + y0, r, g, b);
  }
}

int main() {
  clearImg();

  drawLine((int)(h / 2), (int)(w / 2), h - 1, w - 1, 255, 0, 0);

  salvarImg();

  return 0;
}