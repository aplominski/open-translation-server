#include "library.h"

#include <iostream>
#include <locale>
#include <string.h>
#include <vector>
#include <unordered_map>

Translation::Translation(std::string defaultLanguage_, bool throwing ) {
    std::locale loc;
    std::string lang = loc.name();
    std::string language_code = lang.substr(0, 2);

    this->preferredLanguage = language_code;
    this->defaultLanguage = defaultLanguage_;
    this->throwing = throwing;
}

void Translation::addLanguage(std::string language_name,std::string prefix){
    for (const auto& pair : this->languages) {
        if (pair.second.prefix == prefix && this->throwing) {throw std::invalid_argument("Key already exists");}
    }
    TranslationLanguage language;
    language.name = language_name;
    language.prefix = prefix;
    this->availableLanguages.push_back(language.prefix);
    this->languages[language.prefix] = language;
}

std::string Translation::getByKey(std::string key) {
    for (std::string language : this->availableLanguages) {
        if (language == this->preferredLanguage) {
            TranslationLanguage selected = this->languages[this->preferredLanguage];
            return selected.translations[key];
        }
        else {
            TranslationLanguage selected = this->languages[this->defaultLanguage];
            return selected.translations[key];
        }
    }
    return "";
}
void Translation::addPhrase(std::string phrase_key, std::string translated_phrase, std::string language) {
    for (auto& pair : this->languages) {
        if (pair.second.name == language) {
            pair.second.translations[phrase_key] = translated_phrase;
            break;
        }
    }
}


void Translation::stdcoutByKey(std::string key,bool withEndl) {
    for (std::string language : this->availableLanguages) {
        if (language == this->preferredLanguage) {
            TranslationLanguage selected = this->languages[this->preferredLanguage];
            if (withEndl) std::cout << selected.translations[key] << std::endl;
            else std::cout << selected.translations[key];
        }
        else {
            TranslationLanguage selected = this->languages[this->defaultLanguage];
            if (withEndl) std::cout << selected.translations[key] << std::endl;
            else std::cout << selected.translations[key];
        }
    }
}

void Translation::stdcerrByKey(std::string key,bool withEndl) {
    for (std::string language : this->availableLanguages) {
        if (language == this->preferredLanguage) {
            TranslationLanguage selected = this->languages[this->preferredLanguage];
            if (withEndl) std::cerr << selected.translations[key] << std::endl;
            else std::cerr << selected.translations[key];
        }
        else {
            TranslationLanguage selected = this->languages[this->defaultLanguage];
            if (withEndl) std::cerr << selected.translations[key] << std::endl;
            else std::cerr << selected.translations[key];
        }
    }
}

void Translation::stdclogByKey(std::string key,bool withEndl) {
    for (std::string language : this->availableLanguages) {
        if (language == this->preferredLanguage) {
            TranslationLanguage selected = this->languages[this->preferredLanguage];
            if (withEndl) std::clog << selected.translations[key] << std::endl;
            else std::clog << selected.translations[key];
        }
        else {
            TranslationLanguage selected = this->languages[this->defaultLanguage];
            if (withEndl) std::clog << selected.translations[key] << std::endl;
            else std::clog << selected.translations[key];
        }
    }
}

void Translation::changeLanguage(std::string perfix) {
    this->preferredLanguage = perfix;
}

Translation_handle* translation_creation(const char* defaultLanguage) {
    Translation_handle* handle = new Translation_handle;
    handle->ptr = new Translation(std::string(defaultLanguage), false);
    return handle;
}
void translation_addLanguage(Translation_handle* handle, const char* language, const char* prefix) {
    if (handle && handle->ptr) {
        static_cast<Translation*>(handle->ptr)->addLanguage(std::string(language), std::string(prefix));
    }
}
void translation_addPhrase(Translation_handle* handle, const char* phrase_key,  const char* translated_phase, const char* language) {
    if (handle && handle->ptr) {
        static_cast<Translation*>(handle->ptr)->addPhrase(std::string(phrase_key), std::string(translated_phase), std::string(language));
    }
}
const char* translation_getByKey(Translation_handle* handle, const char* key) {
    if (handle && handle->ptr) {
        static_cast<Translation*>(handle->ptr)->getByKey(std::string(key));
    }
}

void stdcoutByKey_narg(Translation_handle* handle, const char* key) {
    if (handle && handle->ptr) {
        static_cast<Translation*>(handle->ptr)->stdcoutByKey(key, true);
    }
}
void stdcerrByKey_narg(Translation_handle* handle, const char* key) {
    if (handle && handle->ptr) {
        static_cast<Translation*>(handle->ptr)->stdcerrByKey(key, true);
    }
}
void stdclogByKey_narg(Translation_handle* handle, const char* key){
    if (handle && handle->ptr) {
        static_cast<Translation*>(handle->ptr)->stdclogByKey(key, true);
    }
}

void stdcoutByKey_arg(Translation_handle* handle, const char* key, bool endl) {
    if (handle && handle->ptr) {
        static_cast<Translation*>(handle->ptr)->stdcoutByKey(key, endl);
    }
}
void stdcerrByKey_arg(Translation_handle* handle, const char* key, bool endl) {
    if (handle && handle->ptr) {
        static_cast<Translation*>(handle->ptr)->stdcerrByKey(key, endl);
    }
}
void stdclogByKey_arg(Translation_handle* handle, const char* key, bool endl) {
    if (handle && handle->ptr) {
        static_cast<Translation*>(handle->ptr)->stdclogByKey(key, endl);
    }
}

void translation_changeLanguage(Translation_handle* handle, const char* prefix) {
    if (handle && handle->ptr) {
        static_cast<Translation*>(handle->ptr)->changeLanguage(std::string(prefix));
    }
}

const char **translation_availableLanguages(Translation_handle *handle, size_t &outSize) {
    if (handle && handle->ptr) {
        outSize = static_cast<Translation*>(handle->ptr)->availableLanguages.size();
        const char** arr = (const char**)malloc(sizeof(char*) * outSize);
        for (size_t i = 0; i < outSize; ++i) {
            arr[i] = strdup(static_cast<Translation*>(handle->ptr)->availableLanguages[i].c_str());
        }
        return arr;
    }
}