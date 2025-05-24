/**
 * \file model.c
 *
 * \brief Implementação das funções de manipulação do modelo 3D.
 *
 * \author
 * Petrucio Ricardo Tavares de Medeiros \n
 * Universidade Federal Rural do Semi-Árido \n
 * Departamento de Engenharias e Tecnologia \n
 * petrucio at ufersa (dot) edu (dot) br
 *
 * \version 1.0
 * \date May 2025
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "model.h"

unsigned char image[HEIGHT][WIDTH][3];

void set_pixel(int x, int y, unsigned char r, unsigned char g,
               unsigned char b) {
  if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
    image[y][x][0] = r;
    image[y][x][1] = g;
    image[y][x][2] = b;
  }
}

void draw_line(int x0, int y0, int x1, int y1) {
  for (float t = 0.0; t < 1.0; t = t + 0.0001)
    set_pixel((int)x0 + (x1 - x0) * t, (int)y0 + (y1 - y0) * t, 0, 0, 0);
}

void clr() {
  for (int i = 0; i < WIDTH; i++)
    for (int j = 0; j < HEIGHT; j++)
      for (int c = 0; c < 3; c++)
        image[i][j][c] = 255;
}

void clr_C() {
  for (int i = 0; i < WIDTH; i++)
    for (int j = 0; j < HEIGHT; j++)
      for (int c = 0; c < 3; c++)
        image[i][j][c] = 0;
}

void save(const char *saida) {
  FILE *f = fopen(saida, "w");
  if (f == NULL) {
    perror("Erro ao salvar imagem");
    exit(1);
  }

  fprintf(f, "P3\n %d \t %d\n 255\n", WIDTH, HEIGHT);
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      for (int c = 0; c < 3; c++) {
        fprintf(f, "%d \t", image[i][j][c]);
      }
      fprintf(f, "\n");
    }
  }

  fclose(f);
}

int load_obj(const char *filename, Vertex *vertices, int *vcount, Face *faces,
             int *fcount) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Erro ao abrir o arquivo");
    return 0;
  }

  char line[512];
  *vcount = 0;
  *fcount = 0;

  while (fgets(line, sizeof(line), file)) {
    if (strncmp(line, "v ", 2) == 0) {
      if (sscanf(line + 2, "%f %f %f", &vertices[*vcount].x,
                 &vertices[*vcount].y, &vertices[*vcount].z) == 3) {
        (*vcount)++;
      }
    } else if (strncmp(line, "f ", 2) == 0) {
      Face face = {.n = 0};
      char *token = strtok(line + 2, " \n");
      while (token && face.n < MAX_FACE_VERTS) {
        int index;
        if (sscanf(token, "%d", &index) == 1) {
          face.verts[face.n++] = index;
        }
        token = strtok(NULL, " \n");
      }
      faces[(*fcount)++] = face;
    }
  }

  fclose(file);
  return 1;
}

void resizing(Vertex v0, Vertex v1) {
  int x0 = (int)((v0.x + 1.0f) * WIDTH / 2.0f);
  int y0 = (int)((1.0f - v0.y) * HEIGHT / 2.0f);
  int x1 = (int)((v1.x + 1.0f) * WIDTH / 2.0f);
  int y1 = (int)((1.0f - v1.y) * HEIGHT / 2.0f);

  draw_line(x0, y0, x1, y1);
}

void resizing_c(Vertex v0, Vertex v1) {
  int x0 = (int)((v0.x + 1.0f) * WIDTH / 2.0f);
  int y0 = (int)((1.0f - v0.y) * HEIGHT / 2.0f);
  int x1 = (int)((v1.x + 1.0f) * WIDTH / 2.0f);
  int y1 = (int)((1.0f - v1.y) * HEIGHT / 2.0f);

  set_pixel(x0, y0, 255, 0, 0);
  set_pixel(x1, y1, 255, 0, 0);
}

void render_faces(Vertex *vertices, Face *faces, int vcount, int fcount) {
  for (int i = 0; i < fcount; i++) {
    Face face = faces[i];
    for (int j = 0; j < face.n; j++) {
      Vertex v0 = vertices[face.verts[j] - 1];
      Vertex v1 = vertices[face.verts[(j + 1) % face.n] - 1];
      resizing(v0, v1);
    }
  }
}

void render_faces_c(Vertex *vertices, Face *faces, int vcount, int fcount) {
  for (int i = 0; i < fcount; i++) {
    Face face = faces[i];
    for (int j = 0; j < face.n; j++) {
      Vertex v0 = vertices[face.verts[j] - 1];
      Vertex v1 = vertices[face.verts[(j + 1) % face.n] - 1];
      resizing_c(v0, v1);
    }
  }
}

void rotate_vertex(Vertex *v, float beta, float delta, float phi) {
  float x = v->x, y = v->y, z = v->z;

  // Rotação em torno de X (Roll)
  float y1 = y * cos(beta) - z * sin(beta);
  float z1 = y * sin(beta) + z * cos(beta);
  y = y1;
  z = z1;

  // Rotação em torno de Y (Pitch)
  float x1 = x * cos(delta) + z * sin(delta);
  z1 = -x * sin(delta) + z * cos(delta);
  x = x1;
  z = z1;

  // Rotação em torno de Z (Yaw)
  x1 = x * cos(phi) - y * sin(phi);
  y1 = x * sin(phi) + y * cos(phi);
  x = x1;
  y = y1;

  // Atualiza o vértice
  v->x = x;
  v->y = y;
  v->z = z;
}

void espelhar_vertice_x_pelo_yz(Vertex *v) { v->x = -v->x; }
void espelhar_vertice_y_pelo_xz(Vertex *v) { v->y = -v->y; }
void espelhar_vertice_z_pelo_xy(Vertex *v) { v->z = -v->z; }

void cisalhar_x(Vertex *v, float angulo){
  float x = v->x, y = v->y, z = v->z;

  float x1 = x + y * tan(angulo);
  v->x = x1;
}

void cisalhar_y(Vertex *v, float angulo){
  float x = v->x, y = v->y, z = v->z;

  float y1 = y + x * tan(angulo);
  v->y = y1;
}

void cisalhar_xy(Vertex *v, float fator) {
    float cx = WIDTH / 2;
    float cy = HEIGHT / 2;
    v->x -= cx;
    v->y -= cy;

    float x = v->x, y = v->y;

    float x1 = x + y * fator;
    float y1 = y + x * fator;

    v->x = x1 + cx;
    v->y = y1 + cy;
}