#include "model.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Para memcpy

int main(int argc, char *argv[]) {
  Vertex vertices[MAX_VERTICES];
  Vertex espelhado[MAX_VERTICES]; // nova cópia dos vértices
  Face faces[MAX_FACES];
  int vcount, fcount;

  if (argc < 5) {
    printf("Usage: <executavel> <modelo> <saida> <tipo (a|c)> <transformacao>\n");
    return 1;
  }

  char *obj = argv[1];
  char *saida = argv[2];
  char *tipo = argv[3];
  char *transformacao = argv[4];

  if (*tipo != 'a' && *tipo != 'c') {
    printf("Tipos de saída:\n\ta - Aramado\n\tc - Nuvem de pontos\n");
    return 1;
  }

  clr();

  if (!load_obj(obj, vertices, &vcount, faces, &fcount)) {
    return 1;
  }

  memcpy(espelhado, vertices, sizeof(Vertex) * vcount);

  if (*transformacao == '1') { // Exemplo: espelhamento pelo plano XY
    for (int i = 0; i < vcount; i++) {
      espelhar_vertice_y_pelo_xz(&espelhado[i]);
    }
  }
  else if (*transformacao == '2') { // Exemplo: espelhamento pelo plano YZ (apenas um eixo)
    for (int i = 0; i < vcount; i++) {
      espelhar_vertice_x_pelo_yz(&espelhado[i]);
    }
  }
  else if (*transformacao == '3') { // Exemplo: cisalhamento em X
    float angulo = M_PI / 4;
    for (int i = 0; i < vcount; i++) {
      cisalhar_x(&vertices[i], angulo);
    }
  }
  else if (*transformacao == '4') {
    float roll  = M_PI / 6;   // 30 graus
    float pitch = M_PI / 4;   // 45 graus
    float yaw   = M_PI / 3;   // 60 graus

    for (int i = 0; i < vcount; i++) {
      rotate_vertex(&vertices[i], roll, pitch, yaw);
      rotate_vertex(&espelhado[i], roll, pitch, yaw);
    }
  }
  else {
    printf("Transformação desconhecida.\n");
    return 1;
  }

  if (*tipo == 'c') {
    clr_C();
    render_faces_c(vertices, faces, vcount, fcount);
    render_faces_c(espelhado, faces, vcount, fcount); // renderiza a cópia transformada
  } else {
    render_faces(vertices, faces, vcount, fcount);
    render_faces(espelhado, faces, vcount, fcount); // renderiza a cópia transformada
  }

  save(saida);
  return 0;
}
