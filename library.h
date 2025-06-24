#ifndef OPEN_TRANSLATION_SERVER_LIBRARY_H
#define OPEN_TRANSLATION_SERVER_LIBRARY_H

#ifdef __cplusplus
#include <iostream>
#include <locale>
#include <vector>
#include <unordered_map>
#endif

#ifdef __cplusplus
class Translation {
public:
    Translation(std::string defaultLanguage, bool throwing = false);
    void addLanguage(std::string language,std::string prefix);
    void addPhrase(std::string phrase_key, std::string translated_phase,std::string language);
    std::string getByKey(std::string key);

    void stdcoutByKey(std::string key, bool withEndl = true);
    void stdcerrByKey(std::string key, bool withEndl = true);
    void stdclogByKey(std::string key, bool withEndl = true);

    void changeLanguage(std::string prefix);
    std::vector<std::string> availableLanguages;
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
#endif //__cplusplus

//C-API
typedef struct {
    void* ptr;
}Translation_handle;

void translation_creation(Translation_handle* handle, const char* defaultLanguage);
void translation_addLanguage(Translation_handle* handle, const char* language, const char* prefix);
void translation_addPhrase(Translation_handle* handle, const char* phrase_key,  const char* translated_phase, const char* language);
const char* translation_getByKey(Translation_handle* handle, const char* key);

void translation_stdcoutByKey_narg(Translation_handle* handle, const char* key);
void translation_stdcerrByKey_narg(Translation_handle* handle, const char* key);
void translation_stdclogByKey_narg(Translation_handle* handle, const char* key);

void translation_stdcoutByKey_arg(Translation_handle* handle, const char* key, bool endl);
void translation_stdcerrByKey_arg(Translation_handle* handle, const char* key, bool endl);
void translation_stdclogByKey_arg(Translation_handle* handle, const char* key, bool endl);

#define _GET_OVERRIDE(_1, _2, NAME, ...) NAME
#define translation_stdcoutByKey(...) _GET_OVERRIDE(__VA_ARGS__, translation_stdcoutByKey_arg, translation_stdcoutByKey_narg)(__VA_ARGS__)
#define translation_stdcerrByKey(...) _GET_OVERRIDE(__VA_ARGS__, translation_stdcerrByKey_arg, translation_stdcerrByKey_narg)(__VA_ARGS__)

void translation_changeLanguage(Translation_handle* handle, const char* prefix);
const char **translation_availableLanguages(Translation_handle *handle, size_t &outSize);

#endif //OPEN_TRANSLATION_SERVER_LIBRARY_H