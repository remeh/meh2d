#include <cmath>

#include "ui/particle.h"
#include "ui/sprite.h"
#include "core/vector2d.h"
#include "core/system.h"

namespace meh {

Particle::Particle(Vector2d<float> position, double ttl, float angle, float velocity, float slowdown, Color color, ParticlesManager& particulesManager) :
    pos(position),
    ttl(ttl),
    ang((angle*ALLEGRO_PI)/180.0),
    velo(velocity),
    live(true),
    sd(slowdown),
    deathTick(System::currentTime()+ttl),
    pm(particulesManager) {
    Vector2d<float> size(16,16);
    Rect<float> texCoor(0,0,16,16);
    spr = new Sprite(position,size,pm.view(),"meh_particles", texCoor);
    spr->setTintColor(color);
}

void Particle::tick() {
    if (!live) 
        return;
    
    if (System::currentTime() > deathTick) {
        live = false;
        return;
    }

    // It is alive, so move the particle
    pos.setXY(pos.x() + cos(ang)*velo,
              pos.y() + sin(ang)*velo);
    velo -= sd;
    if (velo < 0.0) {
        velo = 0.0;
    }
    spr->setPosition(pos.x(),pos.y());
}

}
