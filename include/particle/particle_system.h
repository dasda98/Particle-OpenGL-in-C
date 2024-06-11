#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

#include <shader/shader.h>

#include <glad/glad.h>
#include <cglm/cglm.h>
#include <cglm/call.h>

#define MAX_PARTICLES 3000

typedef struct {
    vec3 position;
    vec3 velocity;
    vec4 color;
    float life;
} Particle;

typedef struct {
    Particle particles[MAX_PARTICLES];
    GLuint VAO, VBO;
} ParticleSystem;

void initParticleSystem(ParticleSystem* ps);
void fillParticle(Particle* p);
void updateParticles(ParticleSystem* ps, float deltaTime);
void renderParticles(ParticleSystem* ps);
void deleteParticleSystem(ParticleSystem* ps);


#endif //PARTICLE_SYSTEM_H
