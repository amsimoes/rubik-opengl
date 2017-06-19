#ifndef PARTICLES_H
#define PARTICLES_H

typedef struct {
	float size;			// tamanho
	float	life;		// vida
	float	fade;		// fade
	float	r, g, b;    // color
	GLfloat x, y, z;    // posicao
	GLfloat vx, vy, vz; // velocidade
    GLfloat ax, ay, az; // aceleracao
} Particle;

#define MAX_PARTICLES 2000

Particle particle1[MAX_PARTICLES];
Particle particle2[MAX_PARTICLES];
Particle particle3[MAX_PARTICLES];
Particle particle4[MAX_PARTICLES];
Particle particle5[MAX_PARTICLES];
Particle particle6[MAX_PARTICLES];

#endif