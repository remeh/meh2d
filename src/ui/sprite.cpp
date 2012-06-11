#include <cstdio>
#include "core/system.h"
#include "core/vector2d.h"
#include "ui/bitmap.h"
#include "ui/drawable.h"
#include "ui/sprite.h"
#include "ui/spriteanimation.h"
#include "ui/view.h"

namespace meh {

Sprite::Sprite(Vector2d<float> position, Vector2d<float> size, View& view, string bitmapId, Rect<float> texCoord) :
    bitmap(bitmapId),
    pos(position),
    s(size),
    view(view),
    currAnimation(nullptr),
    animHasChangedSinceLastRotation(true),
    texCoord(texCoord),
    strted(true),
    rotCenter(0.0f,0.0f),
    rotAngle(0.0f),
    bmp(nullptr),
    tColor(1.0f,1.0f,1.0f,1.0f),
    isTinted(false) {
    view.addSprite(this);
    show();
    anims.clear();
    type = Drawable::SPRITE;
}

Sprite::~Sprite() {
    for (auto it = anims.begin(); it != anims.end(); it++) {
        delete it->second;
    }
    if (bmp) {
        al_destroy_bitmap(bmp);
        bmp = nullptr;
    }
    anims.clear();
}

void Sprite::draw() {
    // Retrieves the Bitmap from the View's ResourceManager
    Bitmap* b = view.getBitmap(bitmap);
    Rect<float>* texCoords = nullptr;
    if (anims.size() == 0 || !currAnimation) {
        texCoords = &texCoord;
    } else {
        texCoords = &(currAnimation->getCurrentTexCoords());
    }
    // Size of this frame
    if (b) {
        if (rotAngle == 0.0f && !isTinted) {
            al_draw_scaled_bitmap(b->bitmap(),
            texCoords->position().x(), texCoords->position().y(),
            texCoords->width(), texCoords->height(),
            pos.x(), pos.y(),
            s.x(), s.y(),
            0);
        } else {
            // To rotate the bitmap, we should do it in a temporary bitmap
            if (animHasChangedSinceLastRotation) {
                if (bmp) {
                    al_destroy_bitmap(bmp);
                    bmp = nullptr;
                }
                bmp = al_create_sub_bitmap(b->bitmap(),texCoords->position().x(),texCoords->position().y(),texCoords->width(),texCoords->height());
                animHasChangedSinceLastRotation = false;
            }
            al_draw_tinted_scaled_rotated_bitmap(bmp,
                tColor.color(),
                rotCenter.x()/(s.x()/texCoords->width()),rotCenter.y()/(s.y()/texCoords->height()),
                pos.x(),pos.y(),
                s.x()/texCoords->width(),s.y()/texCoords->height(),
                rotAngle,
                0);
        }
    } else {
        printf("ERR: Sprite::draw() -> unknown Bitmap uniqueId : %s\n",bitmap.c_str());
    }
}

void Sprite::addAnimation(string name, unsigned int nbFrames, const unsigned int* durations, const Rect<float>* texCoords) {
    anims[name] = new SpriteAnimation(name, nbFrames,durations,texCoords);
}

void Sprite::setAnimation(string animation) {
    if (!anims[animation]) {
        // TODO log
        printf("ERR: Unknown animation %s\n",animation.c_str());
        return;
    }
    currAnimation = anims[animation];
    // This call ensure that the current frame is still
    // an acceptable number for the new animation
    currAnimation->setCurrentFrame(currAnimation->currentFrame());
}

void Sprite::tick() {
    if (strted && anims.size() != 0 && currAnimation) {
        if (currAnimation->tick()) {
            animHasChangedSinceLastRotation = true;
        }
    }
}

void Sprite::startAnimation() {
    strted = true;
}

void Sprite::stopAnimation() {
    strted = false;
}

} // namespace meh
