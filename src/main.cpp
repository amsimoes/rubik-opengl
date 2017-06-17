#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef __linux__
	#include <GL/glut.h>
#else
	#include <GLUT/glut.h>	
#endif

#include "RgbImage.h"


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
GLfloat   xC=15.0, yC=15.0, zC=30.0;
GLfloat		xZ=30.0, yZ=30.0, zZ=0.0;
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
GLuint  texture[10];
GLuint cube_textures[6];
GLuint  tex;
int azulejo = 0;
RgbImage imag;


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
	loadTextures( );
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}


void resizeWindow(GLsizei w, GLsizei h)
{
 	wScreen=w;
	hScreen=h;
	glutPostRedisplay();
}

void drawWalls() {

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Chao y=0
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i( 0,  0, 0 );
			glTexCoord2f(10.0f,0.0f); glVertex3i( xC, 0, 0 );
			glTexCoord2f(10.0f,10.0f); glVertex3i( xC, 0, xC);
			glTexCoord2f(0.0f,10.0f); glVertex3i( 0,  0,  xC);
		glEnd();
	glPopMatrix();
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Teto y=xC
	glDisable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i( 0,  xC, 0 );
			glTexCoord2f(10.0f,0.0f); glVertex3i( xC, xC, 0 );
			glTexCoord2f(10.0f,10.0f); glVertex3i( xC, xC, xC);
			glTexCoord2f(0.0f,10.0f); glVertex3i( 0,  xC,  xC);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	// Parede z=0
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i( 0,  0, 0);
			glTexCoord2f(3.0f+azulejo%5,0.0f); glVertex3i( 0, xC, 0);
			glTexCoord2f(3.0f+azulejo%5,3.0f+azulejo%5); glVertex3i( 0, xC, xC);
			glTexCoord2f(0.0f,3.0f+azulejo%5); glVertex3i( 0,  0, xC);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	// Parede z=xC
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i( xC,  0, 0);
			glTexCoord2f(3.0f+azulejo%5,0.0f); glVertex3i( xC, xC, 0);
			glTexCoord2f(3.0f+azulejo%5,3.0f+azulejo%5); glVertex3i( xC, xC, xC);
			glTexCoord2f(0.0f,3.0f+azulejo%5); glVertex3i( xC,  0, xC);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	// Parede x=0
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i( 0,  0, 0);
			glTexCoord2f(3.0f,0.0f); glVertex3i( 0, xC, 0);
			glTexCoord2f(3.0f,3.0f); glVertex3i( xC, xC, 0);
			glTexCoord2f(0.0f,3.0f); glVertex3i( xC,  0, 0);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	// Parede x=0
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i( 0,  0, xC);
			glTexCoord2f(3.0f,0.0f); glVertex3i( 0, xC, xC);
			glTexCoord2f(3.0f,3.0f); glVertex3i( xC, xC, xC);
			glTexCoord2f(0.0f,3.0f); glVertex3i( xC,  0, xC);
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawCube(GLfloat xCubeSize, GLfloat yCubeSize, GLfloat zCubeSize) {
	// Lado branco - FRENTE
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,cube_textures[0]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); 
			glVertex3f(  xCubeSize, -yCubeSize, zCubeSize );
			glTexCoord2f(1.0f,0.0f); 
			glVertex3f(  xCubeSize,  yCubeSize, zCubeSize );
			glTexCoord2f(1.0f,1.0f); 
			glVertex3f( -xCubeSize,  yCubeSize, zCubeSize );
			glTexCoord2f(0.0f,1.0f); 
			glVertex3f( -xCubeSize, -yCubeSize, zCubeSize );
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
 
	// Lado roxo - DIREITA
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,cube_textures[1]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); 
			glVertex3f( xCubeSize, -yCubeSize, -zCubeSize );
			glTexCoord2f(1.0f,0.0f); 
			glVertex3f( xCubeSize,  yCubeSize, -zCubeSize );
			glTexCoord2f(1.0f,1.0f);
			glVertex3f( xCubeSize,  yCubeSize,  zCubeSize );
			glTexCoord2f(0.0f,1.0f); 
			glVertex3f( xCubeSize, -yCubeSize,  zCubeSize );
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
 
	// Lado verde - ESQUERDA
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,cube_textures[2]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f( -xCubeSize, -yCubeSize,  zCubeSize );
			glTexCoord2f(1.0f,0.0f); 
			glVertex3f( -xCubeSize,  yCubeSize,  zCubeSize );
			glTexCoord2f(1.0f,1.0f);
			glVertex3f( -xCubeSize,  yCubeSize, -zCubeSize );
			glTexCoord2f(0.0f,1.0f); 
			glVertex3f( -xCubeSize, -yCubeSize, -zCubeSize );
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// Lado azul - TOPO
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,cube_textures[3]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(  xCubeSize,  yCubeSize,  zCubeSize );
			glTexCoord2f(1.0f,0.0f);
			glVertex3f(  xCubeSize,  yCubeSize, -zCubeSize );
			glTexCoord2f(1.0f,1.0f);
			glVertex3f( -xCubeSize,  yCubeSize, -zCubeSize );
			glTexCoord2f(0.0f,1.0f);
			glVertex3f( -xCubeSize,  yCubeSize,  zCubeSize );
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	// Lado vermelho - BASE
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,cube_textures[4]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(  xCubeSize, -yCubeSize, -zCubeSize );
			glTexCoord2f(1.0f,0.0f);
			glVertex3f(  xCubeSize, -yCubeSize,  zCubeSize );
			glTexCoord2f(1.0f,1.0f);
			glVertex3f( -xCubeSize, -yCubeSize,  zCubeSize );
			glTexCoord2f(0.0f,1.0f);
			glVertex3f( -xCubeSize, -yCubeSize, -zCubeSize );
		glEnd();
	glPopMatrix(); 
	glDisable(GL_TEXTURE_2D);

	//
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,cube_textures[5]);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(  xCubeSize, -yCubeSize, -zCubeSize );
			glTexCoord2f(1.0f,0.0f);
			glVertex3f(  xCubeSize,  yCubeSize, -zCubeSize );
			glTexCoord2f(1.0f,1.0f);
			glVertex3f( -xCubeSize,  yCubeSize, -zCubeSize );
			glTexCoord2f(0.0f,1.0f);
			glVertex3f( -xCubeSize, -yCubeSize, -zCubeSize );
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

void drawRubiks() {
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			for(int k=0; k<3; k++){
				drawCube(cubeSize,cubeSize,cubeSize);
				glTranslatef(i*cubeSize+0.5, j*cubeSize+0.5, k*cubeSize+0.5);
			}
		}
	}
}
void drawScene(){

	//drawWalls();
	//drawRubiks();


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

void display(void){

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Apagar ]
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Janela Visualizacao ]
	glViewport (0,0,wScreen, hScreen);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Projeccao]
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch (defineProj) {
		case 1: gluPerspective(88.0, wScreen/hScreen, 0.1, zC); break;
		default: glOrtho (-xC,xC,-yC,yC,-zC,zC);
			break;
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Modelo+View(camera/observador) ]
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], 0,0,0, 0, 1, 0);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~[ Objectos ]
	drawScene();

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
