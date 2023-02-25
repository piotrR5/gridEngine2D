#include <map>
#include <any>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include <complex>
#include <functional>
#include <unordered_map>

#ifndef __PARSER

#define __PARSER

using std::cout;
using std::map;
using std::unordered_map;
using std::fstream;
using std::any;
using std::string;
using std::stringstream;
using std::make_any;
using std::any_cast;

struct Config{
    any l;

    any& operator[](string key);

    

    unordered_map<string,any>config;

    void parseConfig(string filename);

    void saveConfig(string filename);

    template<typename T>
    T at(string key){
        if(config.find(key)==config.end()){
            return T();
        }
        return any_cast<T>(config[key]);
    }

};




#endif

