#include <map>
#include <string>

#include "core/resourcesmanager.h"
#include "core/sample.h"
#include "ui/bitmap.h"

using namespace std;

namespace meh {

ResourcesManager::ResourcesManager() {
    mapBitmaps.clear();
    mapSamples.clear();
    mapFonts.clear();
}

ResourcesManager::~ResourcesManager() {
    for (auto v = mapBitmaps.begin(); mapBitmaps.end() != v; v++) {
        if (v->second) {
            delete v->second;
        }
    }
    mapBitmaps.clear();
    for (auto v = mapSamples.begin(); mapSamples.end() != v; v++) {
        if (v->second) {
            delete v->second;
        }
    }
    mapSamples.clear();
    mapFonts.clear();
    for (auto v = mapFonts.begin(); mapFonts.end() != v; v++) {
        if (v->second) {
            delete v->second;
        }
    }
    mapFonts.clear();
}

Bitmap* ResourcesManager::loadBitmap(string uniqueId, string file, bool videoMemory) {
    if (mapBitmaps.count(uniqueId) == 1) {
        printf("WARN: the uniqueId '%s' for bitmaps was already used, the old instance of the resource is deleted.",uniqueId.c_str());
        this->delBitmap(uniqueId);
    }
    Bitmap* b = new Bitmap(file,videoMemory);
    if (b->bitmap()) {
        mapBitmaps[uniqueId] = b;
        return b;
    }
    return nullptr;
}

Bitmap* ResourcesManager::addBitmap(string uniqueId, Bitmap* bitmap) {
    if (bitmap == nullptr)
        return nullptr;
    if (mapBitmaps.count(uniqueId) == 1) {
        printf("WARN: the uniqueId '%s' for bitmaps was already used, the old instance of the resource is deleted.",uniqueId.c_str());
        this->delBitmap(uniqueId);
    }
    mapBitmaps[uniqueId] = bitmap;
    return bitmap;
}

Bitmap* ResourcesManager::getBitmap(string uniqueId) {
    if (mapBitmaps.count(uniqueId) == 1) {
        return mapBitmaps[uniqueId];
    }
    return nullptr;
}

bool ResourcesManager::delBitmap(string uniqueId) {
    auto it = mapBitmaps.find(uniqueId);
    if (it != mapBitmaps.end()) {
        delete it->second;
        mapBitmaps.erase(it);
        return true;
    }
    return false;
}

Bitmap* ResourcesManager::remBitmap(string uniqueId) {
    auto it = mapBitmaps.find(uniqueId);
    if (it != mapBitmaps.end()) {
        Bitmap* ret = it->second;
        mapBitmaps.erase(it);
        return ret;
    }
    return nullptr;
}

Sample* ResourcesManager::loadSample(string uniqueId, string file) {
    if (mapSamples.count(uniqueId) == 1) {
        printf("WARN: the uniqueId '%s' for samples was already used, the old instance of the resource is deleted.",uniqueId.c_str());
        this->delSample(uniqueId);
    }
    Sample* s = new Sample(file);
    if (s->sample()) {
        mapSamples[uniqueId] = s;
        return s;
    }
    return nullptr;
}

Sample* ResourcesManager::addSample(string uniqueId, Sample* sample) {
    if (sample == nullptr)
        return nullptr;
    if (mapSamples.count(uniqueId) == 1) {
        printf("WARN: the uniqueId '%s' for samples was already used, the old instance of the resource is deleted.",uniqueId.c_str());
        this->delSample(uniqueId);
    }
    mapSamples[uniqueId] = sample;
    return sample;
}

Sample* ResourcesManager::getSample(string uniqueId) {
    if (mapSamples.count(uniqueId) == 1) {
        return mapSamples[uniqueId];
    }
    return nullptr;
}

bool ResourcesManager::delSample(string uniqueId) {
    auto it = mapSamples.find(uniqueId);
    if (it != mapSamples.end()) {
        delete it->second;
        mapSamples.erase(it);
        return true;
    }
    return false;
}

Sample* ResourcesManager::remSample(string uniqueId) {
    auto it = mapSamples.find(uniqueId);
    if (it != mapSamples.end()) {
        Sample* ret = it->second;
        mapSamples.erase(it);
        return ret;
    }
    return nullptr;
}

Font* ResourcesManager::loadFont(string uniqueId, string file, int ptSize) {
    if (mapFonts.count(uniqueId) == 1) {
        printf("WARN: the uniqueId '%s' for fonts was already used, the old instance of the resource is deleted.",uniqueId.c_str());
        this->delFont(uniqueId);
    }
    Font* f = new Font(file,ptSize);
    if (f->font()) {
        mapFonts[uniqueId] = f;
        return f;
    }
    return nullptr;
}

Font* ResourcesManager::addFont(string uniqueId, Font* font) {
    if (font == nullptr)
        return nullptr;
    if (mapFonts.count(uniqueId) == 1) {
        printf("WARN: the uniqueId '%s' for fonts was already used, the old instance of the resource is deleted.",uniqueId.c_str());
        this->delFont(uniqueId);
    }
    mapFonts[uniqueId] = font;
    return font;
}

Font* ResourcesManager::getFont(string uniqueId) {
    if (mapFonts.count(uniqueId) == 1) {
        return mapFonts[uniqueId];
    }
    return nullptr;
}

bool ResourcesManager::delFont(string uniqueId) {
    auto it = mapFonts.find(uniqueId);
    if (it != mapFonts.end()) {
        delete it->second;
        mapFonts.erase(it);
        return true;
    }
    return false;
}

Font* ResourcesManager::remFont(string uniqueId) {
    auto it = mapFonts.find(uniqueId);
    if (it != mapFonts.end()) {
        Font* ret = it->second;
        mapFonts.erase(it);
        return ret;
    }
    return nullptr;
}

}
