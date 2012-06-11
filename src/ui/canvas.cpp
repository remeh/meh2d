#include <string>
#include <cstdio>
#include <allegro5/allegro.h>

#include "core/system.h"
#include "ui/view.h"
#include "ui/canvas.h"

namespace meh {

Canvas::Canvas(int w, int h, CanvasMode mode) :
    v(nullptr),
    fpsTimer(16.0),
    eventQueue(nullptr) {
    switch (mode) {
        case CANVAS_OPENGL:
            al_set_new_display_flags(ALLEGRO_OPENGL);
            break;
        case CANVAS_DIRECT3D:
#ifdef ALLEGRO_DIRECT3D
            al_set_new_display_flags(ALLEGRO_DIRECT3D);
#else
            // XXX should I use ALLEGRO_DIRECT3D_INTERNAL here ?
            printf("DIRECT3D not supported on this system.\n");
#endif
            break;
        default:
            break;
    }
    aCanvas = al_create_display(w,h);

    clip.set(0,0,w,h);
    
    eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_display_event_source(aCanvas));
    al_register_event_source(eventQueue, al_get_timer_event_source(fpsTimer.timer()));

    fpsTimer.start();
}

Canvas::~Canvas() {
    fpsTimer.stop();
    if (aCanvas) {
        al_destroy_display(aCanvas);
    }
    if (v) {
        delete v;
    }
    if (eventQueue) {
        al_destroy_event_queue(eventQueue);
    }
}

Vector2d<int> Canvas::position() const {
    int x;
    int y;
    al_get_window_position(aCanvas,&x,&y);
    return Vector2d<int>(x,y);
}

void Canvas::setPosition(int x, int y) {
    Vector2d<int> p(x,y);
    setPosition(p);
}

void Canvas::setPosition(Vector2d<int>& p) {
    al_set_window_position(aCanvas,p.x(),p.y());
}

void Canvas::flip() {
    al_flip_display();
}

void Canvas::bind() {
    al_set_target_backbuffer(aCanvas);
    al_set_clipping_rectangle(clip.position().x(),clip.position().y(),clip.width(),clip.height());
}

void Canvas::setTitle(string title) {
    al_set_window_title(aCanvas,title.c_str());    
}

void Canvas::draw() {
    bind();
    al_clear_to_color(al_map_rgb(0,0,0));
    if (v) {
       v->draw();
    }
}

bool Canvas::refresh() {
    al_wait_for_event(eventQueue,&event);
    if (event.type == ALLEGRO_EVENT_TIMER && al_is_event_queue_empty(eventQueue)) {
        draw();
        return true;
    }
    return false;
}

} // namespace meh
