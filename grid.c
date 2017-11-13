#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#endif

#include "Vector3D.h"

#define HEIGHT 10
#define WIDTH 10
#define SIZE 1 

GLfloat vertices[(WIDTH + 1) * (HEIGHT + 1) * 3];
unsigned int triangles[(WIDTH + 1) * (HEIGHT + 1) * 3 * 2];
GLfloat normals[(WIDTH + 1) * (HEIGHT + 1) * 3];

void initialize_grid() {  
	int index = 0;
	for(int z = 0; z < HEIGHT + 1; z++) {
		for(int x = 0; x < WIDTH + 1; x++) { 
			vertices[index++] = x * SIZE;
			vertices[index++] = 0;
			vertices[index++] = z * SIZE;
		}
	}

	index = 0; 
	for(int z = 0; z < HEIGHT; z++) {
		for(int x = 0; x < WIDTH; x++) {
			//top left
			triangles[index++] = z * (WIDTH + 1) + x; 
			triangles[index++] = (z + 1) * (WIDTH + 1) + x; 
			triangles[index++] = z * (WIDTH + 1) + x + 1; 

			//bottom right
			triangles[index++] = z * (WIDTH + 1) + x + 1;
			triangles[index++] = (z + 1) * (WIDTH + 1) + x; 
			triangles[index++] = (z + 1) * (WIDTH + 1)+ x + 1;
		}
	}
}

void draw_grid() {
	glEnableClientState(GL_VERTEX_ARRAY);
	//normal

	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawElements(GL_TRIANGLES, (WIDTH + 1) * (HEIGHT + 1) * 3 * 2, GL_UNSIGNED_INT, triangles);

	glDisableClientState(GL_VERTEX_ARRAY);
}

//Creates vector from two points
//First x,y,z is the origin of the vector
Vector3D create_vector(float x1, float y1, float z1, float x2, float y2, float z2) {
	return NewVector3D(x2 - x1, y2 - y1, z2 - z1);
}

int vertex_index(int z, int x) {
	return (z * WIDTH + x) * 3;
}

void generate_normals() {
	//create the vectors for the 4 faces
	int indexCheck;
	int x0, y0, z0; //centre vertex 
	Vector3D v1, v2, v3, v4, v5, v6; 
	Vector3D vA, vB, vC, vD;

	for(int z = 0; z < HEIGHT+1; z++) {
		for(int x = 0; x < WIDTH+1; x++) {
			unsigned int origin_vertex_index = vertex_index(z, x);
			x0 = vertices[origin_vertex_index];
			y0 = vertices[origin_vertex_index + 1];
			z0 = vertices[origin_vertex_index + 2];

			//v1
			unsigned int vi = vertex_index(z-1, x);
			if(vi > (WIDTH + 1) * (HEIGHT + 1)) {
				v1 = create_vector(x0, y0, z0, 1, 1, 1);
			} else {
				v1 = create_vector(
					x0,
					y0,
					z0,
					vertices[vi],
					vertices[vi + 1],
					vertices[vi + 2]);
			}

			//v2
			vi = vertex_index(z+1, x+1);
			if(vi > (WIDTH + 1) * (HEIGHT + 1)) {
				v2 = create_vector(x0, y0, z0, 1, 1, 1);
			} else {
				v2 = create_vector(
					x0,
					y0, 
					z0,
					vertices[vi],
					vertices[vi+1],
					vertices[vi+2]
				);
			}

			//v3
			vi = vertex_index(z, x+1);
			if(vi > (WIDTH + 1) * (HEIGHT + 1)) {
				v3 = create_vector(x0, y0, z0, 1, 1, 1);
			} else {
				v3 = create_vector(
					x0,
					y0, 
					z0,
					vertices[vi],
					vertices[vi+1],
					vertices[vi+2]
				);
			}

			//v4
			vi = vertex_index(z+1, x);
			if(vi > (WIDTH + 1) * (HEIGHT + 1)) {
				v4 = create_vector(x0, y0, z0, 1, 1, 1);
			} else {
				v4 = create_vector(
					x0,
					y0, 
					z0,
					vertices[vi],
					vertices[vi+1],
					vertices[vi+2]
				);
			}

			//v5
			vi = vertex_index(z+1, x-1);
			if(vi > (WIDTH + 1) * (HEIGHT + 1)) {
				v5 = create_vector(x0, y0, z0, 1, 1, 1);
			} else {
				v5 = create_vector(
					x0,
					y0, 
					z0,
					vertices[vi],
					vertices[vi+1],
					vertices[vi+2]
				);
			}

			//v6
			vi = vertex_index(z, x-1);
			if(vi > (WIDTH + 1) * (HEIGHT + 1)) {
				v6 = create_vector(x0, y0, z0, 1, 1, 1);
			} else {
				v6 = create_vector(
					x0,
					y0, 
					z0,
					vertices[vi],
					vertices[vi+1],
					vertices[vi+2]
				);
			}
			CrossProduct(&v1, &v2, &vA);
			CrossProduct(&v3, &v4, &vB);
			CrossProduct(&v4, &v5, &vC);
			CrossProduct(&v6, &v1, &vD);

			//normalize vectors
			Normalize(&vA);
			Normalize(&vB);
			Normalize(&vC);
			Normalize(&vD);

			Vector3D vSum; //Vector Normal
			Add(&vA, &vB, &vSum);
			Add(&vSum, &vC, &vSum);
			Add(&vSum, &vD, &vSum); 

			vi = vertex_index(z, x);
			normals[vi] = vSum.x;
			normals[vi+1] = vSum.y;
			normals[vi+2] = vSum.z;
		}
	}
} 

void test_normals() {
	vertices[1] = -10;
}


//Returns cross product from given three vertices
//First vertex is the origin point
/*
Vector3D calculateNormal(Vector3D *a, Vector3D *b)  
return null;
}
*/