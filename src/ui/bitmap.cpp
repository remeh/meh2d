#include <cstdio>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>

#include "ui/bitmap.h"
#include "core/color.h"

using namespace std;

namespace meh {

Bitmap::Bitmap(int w, int h, bool videoMemory) {
    al_set_new_bitmap_flags(videoMemory ? ALLEGRO_VIDEO_BITMAP : ALLEGRO_MEMORY_BITMAP);
    aBitmap = al_create_bitmap(w,h);
    clip.set(0,0,w,h);
    // Clears the content of the Bitmap which can have some
    // junk data with some video drivers
    clear(Color(0.0f,0.0f,0.0f,0.0f));
}

Bitmap::Bitmap(string file, bool videoMemory) {
    al_set_new_bitmap_flags(videoMemory ? ALLEGRO_VIDEO_BITMAP : ALLEGRO_MEMORY_BITMAP);
    aBitmap = nullptr;
    aBitmap = al_load_bitmap(file.c_str());
    if (!aBitmap) {
        printf("Error: file %s doesn't exists.\n",file.c_str());
    }
}

Bitmap::~Bitmap() {
    if (aBitmap != nullptr) {
        al_destroy_bitmap(aBitmap);
    }
}

void Bitmap::bind() {
    if (aBitmap) {
        al_set_target_bitmap(aBitmap);
        al_set_clipping_rectangle(clip.position().x(),clip.position().y(), clip.width(), clip.height());
    }
}

void Bitmap::clear(Color c) {
    if (aBitmap) {
        ALLEGRO_BITMAP* backbuffer = al_get_target_bitmap();
        bind(); 
        al_clear_to_color(c.color());
        al_set_target_bitmap(backbuffer);
    }
}

bool Bitmap::save(string filename) {
    if (aBitmap) {
        return al_save_bitmap(filename.c_str(),aBitmap);
    }
    return false;
}

} // namespace meh
