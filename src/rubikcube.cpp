#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifdef __linux__
	#include <GL/glut.h>
#else
	#include <GLUT/glut.h>	
#endif

#include "rubikcube.hpp"
#include "main.hpp"


RubikCube::RubikCube(int cube_size) {	// Constructor
	this->cube_size = cube_size;
	this->rotationHigh = 0;

	face_color = new Color**[6];

	for (int i=0; i < 6; i++) {
		face_color[i] = new Color*[cube_size];

		for (int j=0; j < cube_size; j++)
			face_color[i][j] = new Color[cube_size];
	}

	resetColors();
}

RubikCube::~RubikCube() {	// Destructor
	for (int i=0; i<6; i++) {
		for (int j=0; j<cube_size; j++) {
			delete[] face_color[i][j];
		}

		delete[] face_color[i];
	}

	delete[] face_color;
}

void RubikCube::resetColors() {
	for (int k=0; k<6; k++) {
		for (int i=0; i < cube_size; i++) {
			for (int j=0; j < cube_size; j++) {
				face_color[k][i][j] = static_cast<Color>( 1+k );
			}
		}
	}
}

void RubikCube::glDisplay() {
	glDisable(GL_TEXTURE_2D);

	for (int x=0; x<cube_size; x++) {
		for (int y=0; y<cube_size; y++) {
			for (int z=0; z<cube_size; z++) {
				glPushMatrix();

				//glDrawCube(x, y, z)

				glPopMatrix();
			}
		}
	}
}

void RubikCube::glRotate(int msdelay, int fps) {
	const float framedelay = 1.0 / fps;
	const float nrFrames = (msdelay / 1000.0) / framedelay;
	const float degPerFrame = 90.0 / nrFrames;
	rotationHigh = 0;

	while (rotationHigh < 90.0) {
		usleep( (int) (framedelay * 1000 * 1000));
		rotationHigh += degPerFrame;
		display();
		glutPostRedisplay();
	}

	rotateColors();
	rotationHigh = 0;
} 

void RubikCube::rotateColors() {
	// piu
}

void RubikCube::glDrawCube(int x, int y, int z, Color front, Color left, Color right, Color back, Color top, Color bottom) {

	float fx, fy, fz;

	const float elm_size = 1.0 / cube_size;
	const float gap_faces = 0.01;

	const float esn = elm_size * (1 - 2 * gap_faces);

	fx = x * elm_size - 0.5 + elm_size * gap_faces;
	fy = y * elm_size - 0.5 + elm_size * gap_faces;
	fz = z * elm_size - 0.5 + elm_size * gap_faces;


	// Front face
	glBegin(GL_QUADS);
		glSetColor(front);
		glNormal3f(0, 0, 1);
		glVertex3f(fx + 0.0, fy + 0.0, fz + esn);
		glVertex3f(fx + esn, fy + 0.0, fz + esn);
		glVertex3f(fx + esn, fy + esn, fz + esn);
		glVertex3f(fx + 0.0, fy + esn, fz + esn);
	glEnd();

	// Left face
	glBegin(GL_QUADS);
		glSetColor(left);
		glNormal3f( -1, 0, 0 );
		glVertex3f( fx + 0.0, fy + 0.0, fz + 0.0);
		glVertex3f( fx + 0.0, fy + 0.0, fz + esn);
		glVertex3f( fx + 0.0, fy + esn, fz + esn);
		glVertex3f( fx + 0.0, fy + esn, fz + 0.0);
	glEnd();

	// Right face
	glBegin(GL_QUADS);
		glSetColor(right);
		glNormal3f( 1, 0, 0 );
		glVertex3f( fx + esn, fy + 0.0, fz + 0.0);
		glVertex3f( fx + esn, fy + esn, fz + 0.0);
		glVertex3f( fx + esn, fy + esn, fz + esn);
		glVertex3f( fx + esn, fy + 0.0, fz + esn);
	glEnd();	

	// Back face
	glBegin(GL_QUADS);
		glSetColor(back);
		glNormal3f( 0, 0, -1 );
		glVertex3f( fx + 0.0, fy + 0.0, fz + 0.0);
		glVertex3f( fx + 0.0, fy + esn, fz + 0.0);
		glVertex3f( fx + esn, fy + esn, fz + 0.0);
		glVertex3f( fx + esn, fy + 0.0, fz + 0.0);
	glEnd();

	// Top face
	glBegin(GL_QUADS);
		glSetColor(top);
		glNormal3f( 0, 0, 1 );
		glVertex3f( fx + 0.0, fy + esn, fz + 0.0);
		glVertex3f( fx + 0.0, fy + esn, fz + esn);
		glVertex3f( fx + esn, fy + esn, fz + esn);
		glVertex3f( fx + esn, fy + esn, fz + 0.0);
	glEnd();

	// Bottom face
	glBegin(GL_QUADS);
		glSetColor(bottom);
		glNormal3f( 0, 0, -1 );
		glVertex3f( fx + 0.0, fy + 0.0, fz + 0.0);
		glVertex3f( fx + esn, fy + 0.0, fz + 0.0);
		glVertex3f( fx + esn, fy + 0.0, fz + esn);
		glVertex3f( fx + 0.0, fy + 0.0, fz + esn);
	glEnd();

}

void RubikCube::glSetColor(Color color) {
	static float mat_rgb[] = {0, 0, 0, 1};
	static float actual_rgb[] = {0, 0, 0, 1};

	switch (color) {
		case black:
			mat_rgb[0] = 0.4;
			mat_rgb[1] = 0.4;
			mat_rgb[2] = 0.4;
			break;
		case white:
			mat_rgb[0] = 1;
			mat_rgb[1] = 1;
			mat_rgb[2] = 1;
			break;
		case red:
			mat_rgb[0] = 1;
			mat_rgb[1] = 0;
			mat_rgb[2] = 0;
			break;	
		case green:
			mat_rgb[0] = 0;
			mat_rgb[1] = 1;
			mat_rgb[2] = 0;
			break;
		case blue:
			mat_rgb[0] = 0;
			mat_rgb[1] = 0;
			mat_rgb[2] = 1;
			break;
		case yellow:
			mat_rgb[0] = 0;
			mat_rgb[1] = 1;
			mat_rgb[2] = 1;
			break;
		case orange:
			mat_rgb[0] = 1;
			mat_rgb[1] = 0.6;
			mat_rgb[2] = 0;
			break;
	}

	actual_rgb[0] = mat_rgb[0];
	actual_rgb[1] = mat_rgb[1];
	actual_rgb[2] = mat_rgb[2];
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, actual_rgb);

	actual_rgb[0] = 0.1*mat_rgb[0];
	actual_rgb[1] = 0.1*mat_rgb[1];
	actual_rgb[2] = 0.1*mat_rgb[2];
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, actual_rgb);


	actual_rgb[0] = actual_rgb[1] = actual_rgb[2] = 0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, actual_rgb);
}