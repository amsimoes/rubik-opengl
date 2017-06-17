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

//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED 	 1.0, 0.0, 0.0, 1.0
#define YELLOW   1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define ORANGE   1.0, cubeSize, 0.1, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GRAY     0.9, 0.92, 0.29, 1.0
#define PI		 3.14159

//================================================================================
//===========================================================Variaveis e constantes

//------------------------------------------------------------ Sistema Coordenadas
GLfloat   xC=3.0f, yC=15.0, zC=30.0;
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

//------------------------------------------------------------ Texturas
GLint    repete=1;
GLfloat    rr=1;
GLint    maxR  =20;
GLint    msec=10;					//.. definicao do timer (actualizacao)

//================================================================================
//=========================================================================== INIT
//------------------------------------------------------------ Texturas

GLuint cube_textures[6];
GLuint  texture[10];
GLuint  tex;
int azulejo = 0;
RgbImage imag;

RubikCube rubik(3);


void loadTextures()
{
	// YELLOW
	glGenTextures(1, &cube_textures[0]);
	glBindTexture(GL_TEXTURE_2D, cube_textures[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	imag.LoadBmpFile("../assets/texturas_cubo/verde.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
			imag.GetNumCols(),
			imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
			imag.ImageData());


	// WALL TEST
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("../assets/texturas_cubo/branco.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
	imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
}


void init(void)
{
	glClearColor(BLACK);
	glShadeModel(GL_SMOOTH);
	loadTextures();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}


void resizeWindow(GLsizei w, GLsizei h)
{
 	wScreen=w;
	hScreen=h;
	glutPostRedisplay();
}

void drawWalls(float trans_constant, float trans_j, float trans_k) {

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Chao y=0
	glPushMatrix();
		glTranslatef(trans_j, trans_constant*-1.0f, trans_k);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[0]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i( -xC,  -xC, -xC );
			glTexCoord2f(1.0f,0.0f); glVertex3i( xC, -xC, -xC );
			glTexCoord2f(1.0f,1.0f); glVertex3i( xC, -xC, xC);
			glTexCoord2f(0.0f,1.0f); glVertex3i( -xC,  -xC,  xC);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Teto y=xC
	glPushMatrix();
		glTranslatef(trans_j, trans_constant, trans_k);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[0]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i( -xC,  xC, -xC );
			glTexCoord2f(1.0f,0.0f); glVertex3i( xC, xC, -xC );
			glTexCoord2f(1.0f,1.0f); glVertex3i( xC, xC, xC);
			glTexCoord2f(0.0f,1.0f); glVertex3i( -xC,  xC,  xC);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Parede z=0
	glPushMatrix();
		glTranslatef(-trans_constant, trans_k, trans_j);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[0]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3i( -xC, -xC, -xC);
			glTexCoord2f(1.0f, 0.0f); glVertex3i( -xC, xC, -xC);
			glTexCoord2f(1.0f, 1.0f); glVertex3i( -xC, xC, xC);
			glTexCoord2f(0.0f, 1.0f); glVertex3i( -xC,  -xC, xC);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Parede z=xC
	glPushMatrix();
		glTranslatef(trans_constant, trans_k, trans_j);	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[0]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i( xC,  -xC, -xC);
			glTexCoord2f(1.0f,0.0f); glVertex3i( xC, xC, -xC);
			glTexCoord2f(1.0f,1.0f); glVertex3i( xC, xC, xC);
			glTexCoord2f(0.0f,1.0f); glVertex3i( xC,  -xC, xC);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Parede x=0
	glPushMatrix();
		glTranslatef(trans_k, trans_j, -trans_constant);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[0]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i( -xC,  -xC, -xC);
			glTexCoord2f(1.0f,0.0f); glVertex3i( -xC, xC, -xC);
			glTexCoord2f(1.0f,1.0f); glVertex3i( xC, xC, -xC);
			glTexCoord2f(0.0f,1.0f); glVertex3i( xC,  -xC, -xC);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	// Parede x=xC
	glPushMatrix();
		glTranslatef(trans_k, trans_j, trans_constant);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,texture[0]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i( -xC, -xC, xC);
			glTexCoord2f(1.0f,0.0f); glVertex3i( -xC, xC, xC);
			glTexCoord2f(1.0f,1.0f); glVertex3i( xC, xC, xC);
			glTexCoord2f(0.0f,1.0f); glVertex3i( xC, -xC, xC);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void drawLines() {
	glColor4f(WHITE);
	glBegin(GL_LINES);
		glVertex3i( 0, 0, 0);
		glVertex3i(10, 0, 0);
	glEnd();
	glBegin(GL_LINES);
		glVertex3i(0,  0, 0);
		glVertex3i(0, 10, 0);
	glEnd();
	glBegin(GL_LINES);
		glVertex3i( 0, 0, 0);
		glVertex3i( 0, 0,10);
	glEnd();
}

void drawScene(){
	float trans_constant = xC*2;
	float trans = xC*2;

	for (int i=1; i >= -1; i--) {
		for (int j=1; j >= -1; j--) {
			printf("trans_constant = %f\n", trans_constant);
			printf("trans = %f\n", trans);
			printf("trans * %d = %f\n", i, trans*i);
			printf("trans * %d = %f\n", j, trans*j);
			drawWalls(trans_constant, trans*i, trans*j);
		}	
	}

	//drawLines();

}

void display(void){
	int orthoX, orthoY, orthoZ;
	orthoX = 15;
	orthoY = 15;
	orthoZ = 30;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Apagar ]
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Janela Visualizacao ]
	glViewport (0,0,wScreen, hScreen);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Projeccao]
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch (defineProj) {
		case 1: gluPerspective(88.0, wScreen/hScreen, 0.1, zC); break;
		default: glOrtho (-orthoX/2, orthoX/2, -orthoY/2, orthoY/2, -orthoZ/2, orthoZ/2);
			break;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Modelo+View(camera/observador) ]
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], 0,0,0, 0, 1, 0);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Objectos ]
	drawScene();

	rubik.glDisplay();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Actualizacao
	glutSwapBuffers();
}


void Timer(int value)
{
	//angBule=angBule+incBule;
	glutPostRedisplay();
	glutTimerFunc(msec,Timer, 1);
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y){
	switch (key) {
		case 'q':
		case 'Q':
			defineProj = (defineProj + 1) % 2;
			glutPostRedisplay();
			break;

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

	if (obsP[1]> yC)
		obsP[1]= yC;
    if (obsP[1]<-yC)
		obsP[1]=-yC;

    obsP[0] = raio*cos(angulo);
	obsP[2] = raio*sin(angulo);

	glutPostRedisplay();
}

//======================================================= MAIN
int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
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
