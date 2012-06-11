#include <cstdio>
#include "ui/view.h"
#include "ui/sprite.h"
#include "ui/drawable.h"
#include "ui/drawableline.h"
#include "ui/particlesmanager.h"

namespace meh {

View::View(View* parent) :
    prnt(parent), // this line is needed because the ParticlesManager use the pointer of the
                  // parent view by calling view->getBitmap() 
    pm(this) {
    this->prnt = nullptr;
    this->ch = nullptr;
    setParent(parent);    
    setChild(nullptr);
    lastUsedBitmapId.clear();
}

View::~View() {
    if (prnt)
        prnt->setChild(nullptr);
    for (auto it = listDrawables.begin(); it != listDrawables.end(); it++) {
        Drawable* d = *it;
        // TODO specific primitives type
        if (d->getType() == Drawable::SPRITE) {
            delete dynamic_cast<Sprite*>(d);
        } else {
            delete d;
        }

        *it = nullptr;
    }
    if (ch)
        delete ch;
}

Drawable* View::addDrawable(Drawable* drawable) {
    if (drawable)
        listDrawables.push_back(drawable);
    return drawable;
}

Sprite* View::addSprite(Vector2d<float> position, Vector2d<float> size, string bitmapId, Rect<float> texCoord) {
    Sprite* s = new Sprite(position, size, *this, bitmapId, texCoord);
    return s;
}

bool View::remDrawable(Drawable* drawable) {
    // It could be weird that I use a deque instead of a list
    // which has a remove(object) method, which would be more 
    // convenient to use here. But actually the deque manages
    // better size modifications and based on the idea that 
    // you'll more often delete the oldest items whom are on
    // the top of the deque, it doesn't need to fully parse the
    // deque , it shouldn't be a problem.
    for (auto it = listDrawables.begin(); it != listDrawables.end(); it++) {
        if (drawable == *it) {
            listDrawables.erase(it);
            return true;
        }
    }
    return false;
}

Sprite* View::addSprite(Sprite* sprite) {
    if (sprite) {
        listDrawables.push_back(sprite);
    }
    return sprite;
}

void View::draw() {
    for (auto it = listDrawables.begin(); it != listDrawables.end(); it++) {
        Drawable* drawable = *it;
        // Do not display an invisible drawable
        if (!drawable->visible())
            continue;

        Sprite* sprite = nullptr;
        if (drawable->getType() == Drawable::SPRITE) {
            sprite = dynamic_cast<Sprite*>(drawable);
        }

        // If the held bitmap isn't the same that the one
        // which will be used for the next draw, do not
        // hold it anymore
        if (sprite && lastUsedBitmapId != sprite->bitmapId()) {
            if (al_is_bitmap_drawing_held()) {
                al_hold_bitmap_drawing(false);
            }
        }

        // Draw it
        drawable->draw();

        if (sprite && !al_is_bitmap_drawing_held()) {
            lastUsedBitmapId = sprite->bitmapId();
            al_hold_bitmap_drawing(true);
        }
    }
    if (al_is_bitmap_drawing_held()) {
        al_hold_bitmap_drawing(false);
        lastUsedBitmapId.clear();
    }
    if (ch) {
        ch->draw();
    }
}

void View::setParent(View* parent) {
    this->prnt = parent;

    if (parent) {
        if (parent->child()) // TODO use a debug instead of a printf
            printf("ERR: The parent view already had a child %p\n",parent->child());
        else
            parent->setChild(this);
    }
}

void View::setChild(View* child) {
    this->ch = child;
    if (ch && ch->parent() != this) {
        ch->setParent(this);
    }
}

Bitmap* View::getBitmap(string uniqueId) {
    Bitmap* bitmap = rm.getBitmap(uniqueId);
    if (!bitmap && prnt) {
        bitmap = prnt->resourcesManager().getBitmap(uniqueId);
    }
    return bitmap;
}

Sample* View::getSample(string uniqueId) {
    Sample* sample = rm.getSample(uniqueId);
    if (!sample && prnt) {
        sample = prnt->resourcesManager().getSample(uniqueId);
    }
    return sample;
}

Font* View::getFont(string uniqueId) {
    Font* font = rm.getFont(uniqueId);
    if (!font && prnt) {
        font = prnt->resourcesManager().getFont(uniqueId);
    }
    return font;
}

void View::tick() {
    // Tick the ParticlesManager
    pm.tick();
    // Tick every sprites
    for (auto it = listDrawables.begin(); it != listDrawables.end(); it++) {
        (*it)->tick();
    }
    // Tick the sub-view(s)
    if (ch) {
        ch->tick();
    }
}

} // namespace meh
