#include "Vector3D.h"

void initialize_grid();
void draw_grid();
Vector3D create_vector(float x1, float y1, float z1, float x2, float y2, float z2);
int vertex_index(unsigned int z, unsigned int x);
void generate_normals();