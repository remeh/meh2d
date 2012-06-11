#include <cstdio>
#include "ui/particlesmanager.h"
#include "ui/particle.h"
#include "ui/view.h"

namespace meh {

ParticlesManager::ParticlesManager(View* view) :
    v(view) {
    if (!v) {
        // TODO log
        printf("ERR: the view can't be null when creating the ParticlesManager\n");
    } else {
        if (!v->getBitmap("meh_particles")) {
            // XXX Relative URI ...
            v->resourcesManager().loadBitmap("meh_particles","./res/particles.bmp");
        }
    }
    ptcles.clear();
}

ParticlesManager::~ParticlesManager() {
    for (auto it = ptcles.begin(); it != ptcles.end(); it++) {
        delete *it;
    }
}

void ParticlesManager::tick() {
    for (auto it = ptcles.begin(); it != ptcles.end(); it++) {
        (*it)->tick();
    }
    checkForDeadParticles();
}

void ParticlesManager::checkForDeadParticles() {
    for (auto it = ptcles.begin(); it != ptcles.end();) {
        Particle* particle = *it;
        if (!particle->alive()) {
            v->remDrawable(particle->sprite());
            delete particle->sprite();
            delete particle;
            it = ptcles.erase(it);
        } else {
            it++;
        }
    }
}

void ParticlesManager::addParticle(Vector2d<float> position, double ttl, float angle, float velocity, float slowdown, Color color) {
    if (ptcles.size() < 25000) {
        Particle* p = new Particle(position,ttl,angle,velocity,slowdown,color,*this);
        ptcles.push_back(p);
    }
}

}
