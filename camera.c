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
#include "Matrix3D.h"
#include "Vector3D.h"
#include "camera.h"
#include <stdio.h>
#include <math.h>

void position_camera(float xzAngle, float yAngle) {
	glLoadIdentity();
	
	Matrix3D m = NewIdentity();
	// Matrix3D xzRotate = NewRotateY(xzAngle);
	// Matrix3D yRotate = NewRotateX(yAngle); //rotate about x axis
	// Matrix3D translate = NewTranslate(0.0, 0.0, 15);

	// MatrixLeftMultiply(&m, &xzRotate);
	// MatrixLeftMultiply(&m, &yRotate);
	// MatrixLeftMultiply(&m, &translate);

	MatrixLeftMultiplyV(&m, NewTranslate(0, 0, radius));
	MatrixLeftMultiplyV(&m, NewRotateX(yAngle)); // h-rotate
	MatrixLeftMultiplyV(&m, NewRotateY(xzAngle)); // h-rotate

	Vector3D point = NewVector3D(0, 0, 0);
	VectorLeftMultiply(&point, &m);

	gluLookAt(point.x, point.y, point.z, 0, 0, 0, 0, 1, 0);
	//gluLookAt(10, 15, 10, 0, 0, 0, 0, 1, 0);
}