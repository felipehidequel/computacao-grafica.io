/**
 * \file model.h
 *
 * \brief Header com protótipos de funções para manipulação de modelo 3D.
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

#ifndef MODEL_H
#define MODEL_H

#define WIDTH 800
#define HEIGHT 800
#define MAX_VERTICES 50000
#define MAX_FACES 50000
#define MAX_FACE_VERTS 32
# define M_PI           3.14159265358979323846  /* pi */
typedef struct {
  float x, y, z;
} Vertex;

typedef struct {
  int verts[MAX_FACE_VERTS];
  int n;
} Face;

extern unsigned char image[HEIGHT][WIDTH][3];

void set_pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);

void clr();
void clr_C();

void resizing_c(Vertex v0, Vertex v1);
void render_faces_c(Vertex *vertices, Face *faces, int vcount, int fcount);

void save(const char *saida);

void draw_line(int x0, int y0, int x1, int y1);

int load_obj(const char *filename, Vertex *vertices, int *vcount, Face *faces,
             int *fcount);

void resizing(Vertex v0, Vertex v1);

void render_faces(Vertex *vertices, Face *faces, int vcount, int fcount);

void rotate_vertex(Vertex *v, float beta, float delta, float phi);

void espelhar_vertice_x_pelo_yz(Vertex *v);
void espelhar_vertice_y_pelo_xz(Vertex *v);
void espelhar_vertice_z_pelo_xy(Vertex *v);

void cisalhar_x(Vertex *v, float angulo);
void cisalhar_y(Vertex *v, float angulo);
void cisalhar_z(Vertex *v, float angulo);

#endif