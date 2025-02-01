#include "library.h"

#include <iostream>
#include <locale>
#include <vector>
#include <unordered_map>

Translation::Translation(std::string defaultLanguage_) {
    std::locale loc;
    std::string lang = loc.name();
    std::string language_code = lang.substr(0, 2);

    this->preferredLanguage = language_code;
    this->defaultLanguage = defaultLanguage_;
}

void Translation::addLanguage(TranslationLanguage language) {
    this->avalibleLanguages.push_back(language.prefix);
    this->languages[language.prefix] = language;
}

std::string Translation::getByKey(std::string key) {
    for (std::string language : this->avalibleLanguages) {
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

void Translation::stdcoutByKey(std::string key,bool withEndl) {
    for (std::string language : this->avalibleLanguages) {
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
    for (std::string language : this->avalibleLanguages) {
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
    for (std::string language : this->avalibleLanguages) {
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





