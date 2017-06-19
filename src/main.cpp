#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __linux__
	#include <GL/glut.h>
#else
	#include <GLUT/glut.h>	
#endif

#include "RgbImage.h"
#include "rubikcube.hpp"
#include "main.hpp"
#include "particles.hpp"

//--------------------------------- Definir cores
#define frand()			((float)rand()/RAND_MAX)
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define PI		 3.14159

//================================================================================
//===========================================================Variaveis e constantes

//------------------------------------------------------------ Sistema Coordenadas
GLfloat	  skybox = 50.0;
GLfloat   xC=10.0f, yC=2.5, zC=30.0;
GLfloat	  xZ=30.0, yZ=30.0, zZ=0.0;
GLint     wScreen=800, hScreen=600;

//------------------------------------------------------------ Observador
GLint    defineView=0;
GLint    defineProj=1;
GLfloat  raio   = 20;
GLfloat  angulo = 0.35*PI;
GLfloat  obsP[] = {raio*cos(angulo), 5.5, raio*sin(angulo)};
GLfloat  incy   = 0.5;
GLfloat  inca   = 0.03;
GLfloat  angBule = 0;
GLfloat  incBule = 1;
GLfloat  cubeSize = 2.5;
GLint offset_reflect = 1;
GLint floorSize = 30;
GLint reflect = 0;

//------------------------------------------------------------ Texturas
GLint    msec=10;					//.. definicao do timer (actualizacao)

//================================================================================
//=========================================================================== INIT
//------------------------------------------------------------ Texturas

GLuint cube_textures[6];
GLuint texture[10];
GLuint floor_texture[0];
GLuint skybox_textures[6];
GLuint particle_textures[6];

GLuint  tex;
int azulejo = 0;
RgbImage imag;

RubikCube rubik(3);
float alpha = 0.0;

void loadParticles() {
	glGenTextures(1, &particle_textures[0]);
	imag.LoadBmpFile("../assets/texturas_cubo/amarelo.bmp");
	glBindTexture(GL_TEXTURE_2D, particle_textures[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	            imag.GetNumCols(),
	            imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
	            imag.ImageData());
	/*for (int i=0; i < 6; i++) {
		glGenTextures(1, &particle_textures[i]);
		imag.LoadBmpFile(particles_assets[i]);
		glBindTexture(GL_TEXTURE_2D, particle_textures[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexImage2D(GL_TEXTURE_2D, 0, 3,
		            imag.GetNumCols(),
		            imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		            imag.ImageData());
	}*/
}

void loadSkybox() {
	glGenTextures(1, &skybox_textures[0]);
		glBindTexture(GL_TEXTURE_2D, skybox_textures[0]);
		imag.LoadBmpFile("../assets/skybox/skybox1.bmp");
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());	

	glGenTextures(1, &skybox_textures[1]);
		glBindTexture(GL_TEXTURE_2D, skybox_textures[1]);
		imag.LoadBmpFile("../assets/skybox/skybox2.bmp");
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());	
				
	glGenTextures(1, &skybox_textures[2]);
		glBindTexture(GL_TEXTURE_2D, skybox_textures[2]);
		imag.LoadBmpFile("../assets/skybox/skybox3.bmp");
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());	

	glGenTextures(1, &skybox_textures[3]);
		glBindTexture(GL_TEXTURE_2D, skybox_textures[3]);
		imag.LoadBmpFile("../assets/skybox/skybox4.bmp");
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());	


	glGenTextures(1, &skybox_textures[4]);
		glBindTexture(GL_TEXTURE_2D, skybox_textures[4]);
		imag.LoadBmpFile("../assets/skybox/skybox5.bmp");
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());	


	glGenTextures(1, &skybox_textures[5]);
		glBindTexture(GL_TEXTURE_2D, skybox_textures[5]);
		imag.LoadBmpFile("../assets/skybox/skybox6.bmp");
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());		

}

void loadTextures()
{
	//loadSkybox();

	// FLOOR
	/*glGenTextures(1, &floor_texture[0]);
	glBindTexture(GL_TEXTURE_2D, floor_texture[0]);
	imag.LoadBmpFile("../assets/floor_reflect.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());*/

	// YELLOW
	glGenTextures(1, &cube_textures[0]);
	glBindTexture(GL_TEXTURE_2D, cube_textures[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile("../assets/texturas_cubo/amarelo.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	// WHITE
	glGenTextures(1, &cube_textures[1]);
	glBindTexture(GL_TEXTURE_2D, cube_textures[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile("../assets/texturas_cubo/branco.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	// RED
	glGenTextures(1, &cube_textures[2]);
	glBindTexture(GL_TEXTURE_2D, cube_textures[2]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile("../assets/texturas_cubo/vermelho.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	// ORANGE
	glGenTextures(1, &cube_textures[3]);
	glBindTexture(GL_TEXTURE_2D, cube_textures[3]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile("../assets/texturas_cubo/laranja.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	// BLUE
	glGenTextures(1, &cube_textures[4]);
	glBindTexture(GL_TEXTURE_2D, cube_textures[4]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile("../assets/texturas_cubo/azul.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
			imag.GetNumCols(),
			imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
			imag.ImageData());

	// GREEN
	glGenTextures(1, &cube_textures[5]);
	glBindTexture(GL_TEXTURE_2D, cube_textures[5]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile("../assets/texturas_cubo/verde.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
			imag.GetNumCols(),
			imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
			imag.ImageData());


	//loadParticles();
}

void showParticles(Particle *particle) {
	for (int i=0; i < MAX_PARTICLES; i++) {
		glColor4f(particle[i].r, particle[i].g, particle[i].b, particle[i].life);

		glBegin(GL_QUADS);
			glTexCoord2d(0,0); glVertex3f(particle[i].x - particle[i].size, particle[i].y - particle[i].size, particle[i].z);
			glTexCoord2d(1,0); glVertex3f(particle[i].x + particle[i].size, particle[i].y - particle[i].size, particle[i].z);
			glTexCoord2d(1,1); glVertex3f(particle[i].x + particle[i].size, particle[i].y + particle[i].size, particle[i].z);
			glTexCoord2d(0,1); glVertex3f(particle[i].x - particle[i].size, particle[i].y + particle[i].size, particle[i].z);
		glEnd();

		particle[i].x += particle[i].vx;
		particle[i].y += particle[i].vy;
		particle[i].z += particle[i].vz;
		particle[i].vx += particle[i].ax;
		particle[i].vy += particle[i].ay;
		particle[i].vz += particle[i].az;
		particle[i].life -= particle[i].fade;		
	}
}

void initParticles(Particle *particle) {
	GLfloat v, theta, phi;
	GLfloat px, py, pz;
	GLfloat ps;

	px = -0.0;
	py = 200.0;
	pz = -200.0;
	ps = 0.5;

	for (int i=0; i < MAX_PARTICLES; i++) {
		v = 2 * frand() + 0.02;
		theta = 2.0 * frand() * PI;
		phi = frand() * PI;

		particle[i].size = ps;
		particle[i].x = 10.0;
		particle[i].y = 0.0;
		particle[i].z = 0.0;

		particle[i].vx = v * cos(theta) * sin(phi);
		particle[i].vy = v * cos(phi);
		particle[i].vz = v * sin(theta) * sin(phi);
		particle[i].ax = 0.05f;
		particle[i].ay = -0.05f;
		particle[i].az = 0.05f;

		particle[i].r = 1.0f;
		particle[i].g = 0.0f;
		particle[i].b = 1.0f;
		particle[i].life = 11.0f;
		particle[i].fade = 0.01f;
	}
}

void drawWalls(float trans_constant, float trans_j, float trans_k, int j, int k) {

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Chao y=0
	glPushMatrix();
		glTranslatef(trans_j, trans_constant*-1.0f, trans_k);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cube_textures[rubik.cube_color[4][j][k]]);
		//glColor4f(1,1,1,0.25);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3f( -xC,  -xC, -xC );
			glTexCoord2f(1.0f,0.0f); glVertex3f( xC, -xC, -xC );
			glTexCoord2f(1.0f,1.0f); glVertex3f( xC, -xC, xC);
			glTexCoord2f(0.0f,1.0f); glVertex3f( -xC,  -xC,  xC);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Teto y=xC
	glPushMatrix();
		glTranslatef(trans_j, trans_constant, trans_k);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cube_textures[rubik.cube_color[5][j][k]]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3f( -xC,  xC, -xC );
			glTexCoord2f(1.0f,0.0f); glVertex3f( xC, xC, -xC );
			glTexCoord2f(1.0f,1.0f); glVertex3f( xC, xC, xC);
			glTexCoord2f(0.0f,1.0f); glVertex3f( -xC,  xC,  xC);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Parede z=0
	glPushMatrix();
		glTranslatef(-trans_constant, trans_k, trans_j);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cube_textures[rubik.cube_color[2][k][j]]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( -xC, -xC, -xC);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( -xC, xC, -xC);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( -xC, xC, xC);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( -xC,  -xC, xC);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Parede z=xC
	glPushMatrix();
		glTranslatef(trans_constant, trans_k, trans_j);	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cube_textures[rubik.cube_color[3][k][j]]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3f( xC,  -xC, -xC);
			glTexCoord2f(1.0f,0.0f); glVertex3f( xC, xC, -xC);
			glTexCoord2f(1.0f,1.0f); glVertex3f( xC, xC, xC);
			glTexCoord2f(0.0f,1.0f); glVertex3f( xC,  -xC, xC);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Parede x=0
	glPushMatrix();
		glTranslatef(trans_k, trans_j, -trans_constant);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cube_textures[rubik.cube_color[0][k][j]]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3f( -xC,  -xC, -xC);
			glTexCoord2f(1.0f,0.0f); glVertex3f( -xC, xC, -xC);
			glTexCoord2f(1.0f,1.0f); glVertex3f( xC, xC, -xC);
			glTexCoord2f(0.0f,1.0f); glVertex3f( xC,  -xC, -xC);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Parede x=xC
	glPushMatrix();
		glTranslatef(trans_k, trans_j, trans_constant);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, cube_textures[rubik.cube_color[1][k][j]]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3f( -xC, -xC, xC);
			glTexCoord2f(1.0f,0.0f); glVertex3f( -xC, xC, xC);
			glTexCoord2f(1.0f,1.0f); glVertex3f( xC, xC, xC);
			glTexCoord2f(0.0f,1.0f); glVertex3f( xC, -xC, xC);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void drawLines() {
	glColor4f(WHITE);
	glBegin(GL_LINES);
		glVertex3f( 0, 0, 0);
		glVertex3f(10, 0, 0);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(0,  0, 0);
		glVertex3f(0, 10, 0);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f( 0, 0, 0);
		glVertex3f( 0, 0,10);
	glEnd();
}

void drawFloor() {
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(0.0,offset_reflect,0.0);
	glBindTexture(GL_TEXTURE_2D, floor_texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glBegin(GL_QUADS);
	
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-floorSize / 2, 0, floorSize / 2);
	glTexCoord2f(1, 0);
	glVertex3f(floorSize / 2, 0, floorSize / 2);
    glTexCoord2f(1, 1);
	glVertex3f(floorSize / 2, 0, -floorSize / 2);	
	glTexCoord2f(0, 1);
	glVertex3f(-floorSize / 2, 0, -floorSize / 2);
			
	glEnd();
	glPopMatrix();
}

void drawSkybox() {
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, skybox_textures[0]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3f( -skybox,  -skybox, -skybox );
			glTexCoord2f(1.0f,0.0f); glVertex3f( skybox, -skybox, -skybox );
			glTexCoord2f(1.0f,1.0f); glVertex3f( skybox, -skybox, skybox);
			glTexCoord2f(0.0f,1.0f); glVertex3f( -skybox,  -skybox,  skybox);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Teto y=xC
	/*glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, skybox_textures[1]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3f( -skybox,  skybox, -skybox );
			glTexCoord2f(1.0f,0.0f); glVertex3f( skybox, skybox, -skybox );
			glTexCoord2f(1.0f,1.0f); glVertex3f( skybox, skybox, skybox);
			glTexCoord2f(0.0f,1.0f); glVertex3f( -skybox,  skybox,  skybox);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Parede z=0
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, skybox_textures[2]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f( -skybox, -skybox, -skybox);
			glTexCoord2f(1.0f, 0.0f); glVertex3f( -skybox, skybox, -skybox);
			glTexCoord2f(1.0f, 1.0f); glVertex3f( -skybox, skybox, skybox);
			glTexCoord2f(0.0f, 1.0f); glVertex3f( -skybox,  -skybox, skybox);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Parede z=xC
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, skybox_textures[3]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3f( skybox,  -skybox, -skybox);
			glTexCoord2f(1.0f,0.0f); glVertex3f( skybox, skybox, -skybox);
			glTexCoord2f(1.0f,1.0f); glVertex3f( skybox, skybox, skybox);
			glTexCoord2f(0.0f,1.0f); glVertex3f( skybox,  -skybox, skybox);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Parede x=0
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, skybox_textures[4]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3f( -skybox,  -skybox, -skybox);
			glTexCoord2f(1.0f,0.0f); glVertex3f( -skybox, skybox, -skybox);
			glTexCoord2f(1.0f,1.0f); glVertex3f( skybox, skybox, -skybox);
			glTexCoord2f(0.0f,1.0f); glVertex3f( skybox,  -skybox, -skybox);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Parede x=xC
	glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, skybox_textures[5]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3f( -skybox, -skybox, skybox);
			glTexCoord2f(1.0f,0.0f); glVertex3f( -skybox, skybox, skybox);
			glTexCoord2f(1.0f,1.0f); glVertex3f( skybox, skybox, skybox);
			glTexCoord2f(0.0f,1.0f); glVertex3f( skybox, -skybox, skybox);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();*/
}
void drawReflection(){
	glPushMatrix();
	glTranslatef(0,-cubeSize*2,0);

	glEnable(GL_STENCIL_TEST); //Activa o uso do stencil buffer 
    glColorMask(0, 0, 0, 0); //Nao escreve no color buffer 
    glDisable(GL_DEPTH_TEST); //Torna inactivo o teste de profundidade 
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    //Coloca a 1 todos os pixels no stencil buffer que representam a superfície reflectora
    //DESENHAR SUPERFÍCIE REFLECTORA
    glColorMask(1, 1, 1, 1); //Activa a escrita de cor
    drawFloor();
    glEnable(GL_DEPTH_TEST); //Activa o teste de profundidade
    glStencilFunc(GL_EQUAL, 1, 1);//O stencil test passa apenas quando o pixel tem o valor 1 no stencil buffer
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //Stencil buffer read-only
    //Desenha o objecto com a reflexão onde stencil buffer é 1
    glPushMatrix();
    glTranslatef(0, -cubeSize*1.5, 0);
    glScalef(1, -1, 1);
    // Faz o cubo ir para a parte de baixo da superfície refletora
    //glTranslatef(0, cubeSize*1.5, 0);
    // Desenhar cubo ( reflexão )
    rubik.glDisplay();
    glPopMatrix();
    //DESENHAR OBJECTO REFLECTIDO
    glDisable(GL_STENCIL_TEST); //Desactiva a utilização do stencil buffer 

    //Blending
	glEnable(GL_BLEND);
	glColor4f(1, 1, 1, 0.25);
	drawFloor();
	glDisable(GL_BLEND);
	glPopMatrix();
}

void drawScene(){



	if(reflect == 1)
		drawReflection();

	glPushMatrix();
	rubik.glDisplay();
	glPopMatrix();

	
	float trans_constant = xC*2;
	float trans = xC*2;

	//drawSkybox();
				

	glEnable(GL_BLEND);
	for (int i=1; i >= -1; i--) {
		for (int j=1; j >= -1; j--) {
			// 1-i , 1-j

			glPushMatrix();

			glColor4f(1, 1, 1, alpha);
			drawWalls(trans_constant, trans*i, trans*j, (-1-i)*-1, (-1-j)*-1);

			glPopMatrix();
		}	
	}
	glDisable(GL_BLEND);

}

void display(void){
	float orthoX, orthoY, orthoZ;
	orthoX = 3;
	orthoY = 2.5;
	orthoZ = 30;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Apagar ]
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Janela Visualizacao ]
	glViewport (0,0,wScreen, hScreen);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~Per~~~~~~~~~~~~~~~~~~~~~~~~[ Projeccao]
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch (defineProj) {
		case 1: gluPerspective(1000.0, wScreen/hScreen, 0.1, 1000); break;
		case 2:	gluPerspective(100.0, wScreen/hScreen, 0.1, 100); break;
		default: glOrtho (-orthoX*5, orthoX*5, -orthoY*5, orthoY*5, -orthoZ*5, orthoZ*5);
			break;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Modelo+View(camera/observador) ]
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], 0,0,0, 0, 1, 0);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Objectos ]

	drawScene();
	glutSwapBuffers();
}


void Timer(int value)
{
	//initParticles(particle1);

	//angBule=angBule+incBule;
	glutPostRedisplay();
	glutTimerFunc(msec,Timer, 1);
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y){
	switch (key) {
		case '1':	// FRONT: LEFT <-
			rubik.highlight = 0;
			glutPostRedisplay();
			rubik.glRotate();
			break;
		case '2':	// FRONT: RIGHT ->
			rubik.highlight = 1;
			glutPostRedisplay();
			rubik.glRotate();
			break;
		case '3':	// LEFT: LEFT <-
			rubik.highlight = 2;
			glutPostRedisplay();
			rubik.glRotate();
			break;
		case '4':   // LEFT: RIGHT ->
			rubik.highlight = 3;
			glutPostRedisplay();
			rubik.glRotate();
			break;
		case '5':   // RIGHT: LEFT <-
			rubik.highlight = 4;
			glutPostRedisplay();
			rubik.glRotate();
			break;
		case '6':   // RIGHT: RIGHT ->
			rubik.highlight = 5;
			glutPostRedisplay();
			rubik.glRotate();
			break;
		case '7':   // BACK: LEFT <-
			rubik.highlight = 6;
			glutPostRedisplay();
			rubik.glRotate();
			break;
		case '8':   // BACK: RIGHT ->
			rubik.highlight = 7;
			glutPostRedisplay();
			rubik.glRotate();
			break;
		case '9':   // TOP: LEFT <-
			rubik.highlight = 8;
			glutPostRedisplay();
			rubik.glRotate();
			break;
		case '0':   // TOP: RIGHT ->
			break;

		case 'q':
		case 'Q':
			if(defineProj <= 2)
				defineProj += 1;
			else
				defineProj = 1;
			glutPostRedisplay();
			break;
		case 'b':
		case 'B':
			if(reflect != 1)
				reflect = 1;
			else
				reflect = 0;
			break;

		case 'e':
		case 'E':
			printf("TECLA EEEE\n");
			//initParticles(particle1);
			//showParticles(particle1);
			glutPostRedisplay();
			break;

		case 't':
		case 'T':
			if (alpha < 1.0)
				alpha += 0.1f;
			printf("alpha = %f\n", alpha);
			break;
		case 'r':
		case 'R':
			if (alpha >= 0.1f)
				alpha -= 0.1f;
			break;

		case '+':
			printf("xC = %f\n", xC);
			printf("rubik.scale_factor = %f\n", rubik.scale_factor);
			rubik.scale_factor += xC / 30;
			printf("rubik.scale_factor = %f\n", rubik.scale_factor);
			break;
		case '-':
			if (rubik.scale_factor > xC / 30)
				rubik.scale_factor -= xC / 30;
			break;

		case ' ':
			rubik.highlightNext();
			printf("highlight = %d\n", rubik.highlight);
			glutPostRedisplay();
			break;

		case 13:
			rubik.glRotate();
			break;

		case 27:	// ESC
			exit(0);
			break;
  	}
}

void teclasNotAscii(int key, int x, int y){
    if(key == GLUT_KEY_UP)
		obsP[1]=obsP[1]+incy;
	if(key == GLUT_KEY_DOWN)
		obsP[1]=obsP[1]-incy;
	if(key == GLUT_KEY_LEFT)
		angulo=angulo+inca;
	if(key == GLUT_KEY_RIGHT)
		angulo=angulo-inca;

	if (obsP[1]> yC*2)
		obsP[1]= yC*2;
    if (obsP[1]<-yC)
		obsP[1]=-yC;

    obsP[0] = raio*cos(angulo);
	obsP[2] = raio*sin(angulo);

	glutPostRedisplay();
}

void init(void)
{
	glClearColor(BLACK);
	glShadeModel(GL_SMOOTH);
	loadTextures();
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	//initParticles(particle1);
}


void resizeWindow(GLsizei w, GLsizei h)
{
 	wScreen=w;
	hScreen=h;
	glutPostRedisplay();
}

//======================================================= MAIN
int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL );
	glutInitWindowSize (wScreen, hScreen);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("CUBO RUBIK");

	init();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutReshapeFunc(resizeWindow);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}
