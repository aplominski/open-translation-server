#ifndef OPEN_TRANSLATION_SERVER_LIBRARY_H
#define OPEN_TRANSLATION_SERVER_LIBRARY_H

#include <iostream>
#include <locale>
#include <vector>
#include <unordered_map>

struct TranslationLanguage {
    std::string name;
    std::string prefix;
    std::unordered_map<std::string, std::string> translations;

};

class Translation {
public:
    Translation(std::string defaultLanguage);
    void addLanguage(TranslationLanguage language);
    std::string preferredLanguage;
    std::string defaultLanguage;
    std::string getByKey(std::string key);

    void stdcoutByKey(std::string key, bool withEndl = true);
    void stdcerrByKey(std::string key, bool withEndl = true);
    void stdclogByKey(std::string key, bool withEndl = true);

    void changeLanguage(std::string perfix);
    std::vector<std::string> avalibleLanguages;
private:
    std::unordered_map<std::string,TranslationLanguage> languages;
};

#endif //OPEN_TRANSLATION_SERVER_LIBRARY_H