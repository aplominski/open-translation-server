#ifndef OPEN_TRANSLATION_SERVER_LIBRARY_H
#define OPEN_TRANSLATION_SERVER_LIBRARY_H

#include <iostream>
#include <locale>
#include <vector>
#include <unordered_map>

class Translation {
public:
    Translation(std::string defaultLanguage, bool throwing = false);
    void addLanguage(std::string language,std::string prefix);
    void addPhrase(std::string phrase_key, std::string translated_phase,std::string language);
    std::string getByKey(std::string key);

    void stdcoutByKey(std::string key, bool withEndl = true);
    void stdcerrByKey(std::string key, bool withEndl = true);
    void stdclogByKey(std::string key, bool withEndl = true);

    void changeLanguage(std::string perfix);
    std::vector<std::string> avalibleLanguages;
private:
    bool throwing;
    struct TranslationLanguage {
        std::string name;
        std::string prefix;
        std::unordered_map<std::string, std::string> translations;

    };

    std::string preferredLanguage;
    std::string defaultLanguage;
    std::unordered_map<std::string,TranslationLanguage> languages;
};

#endif //OPEN_TRANSLATION_SERVER_LIBRARY_H