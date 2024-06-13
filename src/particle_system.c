#include <particle/particle_system.h>
#include <helpers.h>


void initParticleSystem(ParticleSystem* ps) {
    // Init data
    for (int i=0; i<MAX_PARTICLES; i++) {
        fillParticle(&ps->particles[i]);
    }

    glGenVertexArrays(1, &ps->VAO);
    glGenBuffers(1, &ps->VBO);

    glBindVertexArray(ps->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, ps->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Particle) * MAX_PARTICLES, NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Particle, color));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void fillParticle(Particle* p) {
    float startX = 0.0f;
    float startY = 0.0f;
    glm_vec3_copy((vec3){startX, startY, 0.0f}, p->position);

    float velocityX = randomFloat(-0.02f, 0.02f);
    float velocityY = randomFloat(0.00f, 0.15f);
    float velocityZ = randomFloat(0.00f, 0.15f);
    glm_vec3_copy((vec3){velocityX, velocityY, velocityZ}, p->velocity);

    float _tmp_life = randomFloat(0.3f, 1.0f);
    p->life = _tmp_life;

    glm_vec4_copy((vec4){1.0f, 1.0f, 1.0f, 1.0f}, p->color);
}

void updateParticles(ParticleSystem* ps, float deltaTime) {
    for (int i=0; i<MAX_PARTICLES; i++) {
        Particle* p = &ps->particles[i];
        if (p->life > 0.0f) {
            vec3 deltaPosition;
            glm_vec3_scale(p->velocity, deltaTime, deltaPosition);
            glm_vec3_add(p->position, deltaPosition, p->position);

            vec4 decrement = {0.0f, deltaTime * 0.25f, deltaTime * 0.5f, deltaTime * 0.125f};
            glm_vec4_sub(p->color, decrement, p->color);
            p->color[0] = fmaxf(p->color[0], 0.0f);
            p->color[1] = fmaxf(p->color[1], 0.0f);
            p->color[2] = fmaxf(p->color[2], 0.0f);
            p->color[3] = fmaxf(p->color[3], 0.0f);

            p->life -= deltaTime * 0.25f;
        } else {
            fillParticle(p);
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, ps->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Particle) * MAX_PARTICLES, ps->particles);
}

void renderParticles(ParticleSystem* ps) {
    glBindVertexArray(ps->VAO);
    glDrawArrays(GL_POINTS, 0, MAX_PARTICLES);
    glBindVertexArray(0);
}

void deleteParticleSystem(ParticleSystem* ps) {
    glDeleteVertexArrays(1, &ps->VAO);
    glDeleteBuffers(1, &ps->VBO);
}