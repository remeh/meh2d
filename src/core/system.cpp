#include <cstdio>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <cstdlib>
#include <ctime>

#include "core/system.h"

namespace meh {

bool System::initializated = false;

void System::init() {
    // TODO proper logging
    if (!al_init()) {
        printf("ERR: Unable to init Allegro 5.\n");
    }

    printf("init system image addon...\n");
    if (!al_init_image_addon()) {
        printf("ERR: Unable to init the Allegro 5 image addon.\n");
    } 

    printf("init system keyboard...\n");
    if (!al_install_keyboard()) {
        printf("ERR: Unable to init the keyboard driver.\n");
    }

    printf("init system mouse...\n");
    if (!al_install_mouse()) {
        printf("ERR: Unable to init the mouse driver.\n");
    }

    printf("init system audio...\n");
    if (!al_install_audio()) {
        printf("ERR: Unable to init Allegro 5 audio system.\n");
    }

    printf("init system acodec...\n");
    if (!al_init_acodec_addon()) {
        printf("ERR: Unable to init Allegro 5 audio codec addon.\n");
    }

    printf("init system samples...\n");
    if (!al_reserve_samples(16)) {
        printf("ERR: Unable to reserve samples for sound system.\n");
    }   

    printf("init primitives addon...\n");
    if (!al_init_primitives_addon()) {
        printf("ERR: Unable to init Allegro 5 primitives addon.\n");
    }

    printf("init font addon...\n");
    al_init_font_addon();

    printf("init ttf addon...\n");
    if (!al_init_ttf_addon()) {
        printf("ERR: Unable to init Allegro 5 TTF addon.\n");
    }

    srand(time(NULL));

    System::initializated = true;
}

bool System::isInitializated() {
    return initializated;
}

int System::rnd(int min, int max) {
    return (rand()%(max-min))+min;
}

int System::rnd(int max) {
    return rand()%max;
}

double System::currentTime() {
    return al_get_time()*1000;
}

void System::sleep(unsigned int ms) {
    al_rest(static_cast<double>(ms)/1000);
}

}
