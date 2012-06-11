#include <allegro5/allegro.h>
#include <iostream>
#include <string>

#include "core/fileconfig.h"

using namespace std;

namespace meh {

FileConfig::FileConfig(string filePath) {
    aConfig = nullptr;
    aConfig = al_load_config_file(filePath.c_str());

    if (aConfig == NULL) {
        aConfig = al_create_config();
    } else {
        read();
    }
}

FileConfig::~FileConfig() {
    if (aConfig != nullptr) {
        al_destroy_config(aConfig);
        aConfig = nullptr;
    }
}

void FileConfig::read() {
    ALLEGRO_CONFIG_SECTION* itSection;
    ALLEGRO_CONFIG_ENTRY* itEntry;

    const char* section = al_get_first_config_section(aConfig,&itSection);
    string sSection(section);
    const char* entry = al_get_first_config_entry(aConfig,section, &itEntry);
    while (section != NULL && entry != NULL) {
        map<string, string> val;
        string value(al_get_config_value(aConfig,section,entry));
        val[entry] = value;

        while (const char* nextEntry = al_get_next_config_entry(&itEntry)) {
            string sNextEntry(nextEntry);
            string nextValue(al_get_config_value(aConfig,section,nextEntry));
            val[sNextEntry] = nextValue;
        }
        mapValues[sSection] = val;

        // Next section
        section = al_get_next_config_section(&itSection);
        if (section != NULL) {
            sSection = section;
            entry = al_get_first_config_entry(aConfig,section,&itEntry);
        }
        mapValues[sSection] = val;
    }
}

}
