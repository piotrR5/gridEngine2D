#include "parser.hpp"



void Config::parseConfig(string filename){
    fstream file;
    file.open(filename);
    string line;

    unordered_map<string,any>config;

    while(getline(file, line)){
        string key;
        char foo;
        string val;
        stringstream ss;
        ss<<line;
        ss>>key>>foo>>val;


        if(val.find(".")!=string::npos){
            any foo=make_any<double>(stod(val));
            config.emplace(key, foo);
        }else if(val[0]>='0' && val[0]<='9'){
            any foo=make_any<int>(stoi(val));
            config.emplace(key, foo);
        }else if(val=="true" || val=="false"){
            any foo=make_any<bool>((val=="true" ? 1 : 0));
            config.emplace(key, foo);
        }else if(val[0]=='{'){
            while(val.find('{')!=string::npos){
                val.erase(val.begin()+val.find('{'));
            }
            while(val.find('}')!=string::npos){
                val.erase(val.begin()+val.find('}'));
            }
            while(val.find(',')!=string::npos){
                val[val.find(',')]=' ';
            }
            uint8_t r,g,b,a;
            string sr="",sg="",sb="",sa="";
            size_t i;

            for(i=0;i<val.size();i++){
                if(val[i]==' ')break;
                sr+=val[i];
            }
            i++;
            for(;i<val.size();i++){
                if(val[i]==' ')break;
                sg+=val[i];
            }
            i++;
            for(;i<val.size();i++){
                if(val[i]==' ')break;
                sb+=val[i];
            }
            i++;
            for(;i<val.size();i++){
                if(val[i]==' ')break;
                sa+=val[i];
            }

            r=stoi(sr);
            g=stoi(sg);
            b=stoi(sb);
            a=stoi(sa);
            
            RGBA temp={r,g,b,a};
            any foo=make_any<RGBA>(temp);
            config.emplace(key, foo);
        }else{
            val.erase(0,1);
            val.erase(val.size()-1, val.size());
            any foo=make_any<string>(val);
            config.emplace(key, foo);
        }

        cout<<"[ config: ] "<<key<<" = "<<val<<" <- "<<config[key].type().name()<<"\n";
    }
    this->config=config;
}

void Config::saveConfig(string filename){
    std::ofstream file;
    file.open(filename);

    for(auto& [a,b]:config){

        file<<a<<" = ";

        if(b.type()==typeid(int)){
            file<<any_cast<int>(b);
        }else if(b.type()==typeid(double)){
            file<<any_cast<double>(b);
        }else if(b.type()==typeid(string)){
            string foo=any_cast<string>(b);
            foo="\""+foo;
            foo+="\"";
            file<<foo;
        }else if(b.type()==typeid(bool)){
            file<<any_cast<bool>(b);
        }else if(b.type()==typeid(RGBA)){
            RGBA foo=any_cast<RGBA>(b);
            file<<"{"<<(int)foo.r<<","<<(int)foo.g<<","<<(int)foo.b<<","<<(int)foo.a<<"}";
        }
        file<<"\n";
    }

    file.close();
}

any& Config::operator[](string key){
    if(config.find(key)==config.end()){
        l=make_any<int>(-1);
        return l;
    }
    return config[key];
}


