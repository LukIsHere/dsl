/*
a great pice of code part of
dsl diffrent standard library
(wip as i write it so no links)

coded and delivered by L team
code by luk the oop programmer
debbugged by zoz the glaceon
(not really since he is just
pokemon in the game but we
can treat him as a rubber
duck right?)

it may break everything it touches
or something i dont know why
some people state that in their
comment thingies but yes

also no touch touch credits
without premission but if
you want you can modify code
itself so yes i hope it's
helpfull my guy and you
will be able to make great
things with it
*/
#pragma once
#include<stdio.h>
#include <string.h>
#include <stdint.h>
#include <string>
#include <functional>
#include <iostream>

namespace dsl {
    class string_refference{
            char** data;
            uint32_t* size;
        public:
            string_refference(char** data, uint32_t* size){
                this->data = data;
                this->size = size;
            };
            string_refference(const string_refference& other){
                throw "no";
            };
            void operator=(const char* text){
                delete *data;
                *data = new char[strlen(text) + 1];
                strcpy(*data, text);
                *size = strlen(text);
            }
            void operator=(char* text){
                delete *data;
                *data = new char[strlen(text) + 1];
                strcpy(*data, text);
                *size = strlen(text);
            }
            void operator=(const string_refference& other){
                delete *data;
                *data = strcpy(new char[*other.size + 1], *other.data);
                *size = *other.size;
            }
            void operator=(const std::string& other){
                delete *data;
                *data = new char[other.size() + 1];
                strcpy(*data, other.c_str());
                *size = other.size();
            }
            char* c_str(){
                return *data;
            }
            std::string to_string(){
                return std::string(*data);
            }
            char& operator[](uint32_t index){
                return (*data)[index];
            }
    };
    class json{
        private:
            enum json_type : unsigned char{null,bol,num,str,obj,arr} type;
            struct json_pair{
                char* key;
                uint32_t size;
                json* value;  
            };
            union json_data{
                struct {
                    bool boolean;    
                } bol;
                struct{
                    int64_t number;
                } num;
                struct{
                    char* string;
                    uint32_t size;
                } str;
                struct{
                    json_pair* data;
                    uint32_t size;
                } obj;
                struct{
                    json** data;
                    uint32_t size;
                } arr;
            } data;
            void copy(const json& other){
                goNull();//clears all pointers if there are any
                setType(other.type);
                switch(type){
                    case bol:
                        data.bol.boolean = other.data.bol.boolean;
                        break;
                    case num:
                        data.num.number = other.data.num.number;
                        break;
                    case str:
                        data.str.string = new char[strlen(other.data.str.string) + 1];
                        data.str.size = strlen(other.data.str.string);
                        strcpy(data.str.string, other.data.str.string);
                        break;
                    case obj:
                        data.obj.data = new json_pair[other.data.obj.size];
                        data.obj.size = other.data.obj.size;
                        for(uint32_t i = 0; i<other.data.obj.size; i++){
                            data.obj.data[i].key = new char[strlen(other.data.obj.data[i].key) + 1];
                            data.obj.data[i].size = strlen(other.data.obj.data[i].key);
                            strcpy(data.obj.data[i].key, other.data.obj.data[i].key);
                            data.obj.data[i].value = new json(*other.data.obj.data[i].value);
                        }
                        break;
                    case arr:
                        data.arr.data = new json*[other.data.arr.size];
                        data.arr.size = other.data.arr.size;
                        for(uint32_t i = 0; i<other.data.arr.size; i++){
                            data.arr.data[i] = new json(*other.data.arr.data[i]);
                        }
                        break;
                }
            }
            void parseObject(const char* text,uint64_t& place){
                place++;//{
                setType(obj);
                if(text[place]=='}'){
                    place++;//}
                    return;
                }
                uint64_t size = 1;
                uint64_t tempPlace = 0;
                uint64_t cb = 1;
                while(true){
                    if(text[tempPlace+place]=='{')cb++;
                    if(text[tempPlace+place]=='}')cb--;
                    if(text[tempPlace+place]==',')size++;
                    if(cb==0)break;
                    tempPlace++;
                }
                tempPlace = 0;
                data.obj.data = new json_pair[size];
                data.obj.size = size;
                //"token":{}
                for(uint64_t i = 0; i<size; i++){
                    place++;//"
                    uint64_t keyl = 0;
                    while(true){
                        if(text[tempPlace+place]=='"')break;
                        tempPlace++;
                        keyl++;
                    }
                    data.obj.data[i].key = new char[keyl+1];
                    data.obj.data[i].size = keyl;
                    for(uint64_t j = 0; j<keyl; j++){
                        data.obj.data[i].key[j] = text[place];
                        place++;
                    }
                    data.obj.data[i].key[keyl] = '\0';
                    place++;//:
                    if(text[place]==':')place++;
                    data.obj.data[i].value = new json(text,place);
                    tempPlace = 0;
                    place++;
                }
                place++;//}
                return;
            }
            void parseArray(const char* text,uint64_t& place){
                place++;//[
                setType(arr);
                if(text[place]==']'){
                    place++;//]
                    return;
                }
                uint64_t size = 1;
                uint64_t tempPlace = 0;
                uint64_t cb = 1;
                while(true){
                    if(text[tempPlace+place]=='[')cb++;
                    if(text[tempPlace+place]==']')cb--;
                    if(text[tempPlace+place]==',')size++;
                    if(cb==0)break;
                    tempPlace++;
                }
                tempPlace = 0;
                data.arr.data = new json*[size];
                data.arr.size = size;
                for (uint64_t i = 0; i < size; i++)
                {
                    data.arr.data[i] = new json(text,place);
                    place++;//, or ]
                }
                return;
                
            }
            void parseString(const char* text,uint64_t& place){
                place++;//"
                setType(str);
                uint64_t tempPlace = 0;
                while (text[tempPlace+place] != '"')
                {
                    tempPlace++;
                }
                data.str.size = tempPlace;
                data.str.string = new char[tempPlace+1];
                for(uint64_t i = 0; i<tempPlace; i++){
                    data.str.string[i] = text[place];
                    place++;
                }
                data.str.string[tempPlace] = '\0';
                if(text[place]=='"')place++;
                return;
                
            }
            void parseNumber(const char* text,uint64_t& place){
                bool negative = false;
                if(text[place]=='-'){
                    negative = true;
                    place++;//-
                }
                uint64_t tempNum = 0;
                while (true)
                {
                    if(text[place]>='0' && text[place]<='9'){
                        tempNum = tempNum*10 + (text[place]-'0');
                        place++;
                    }else break;
                }
                tempNum = negative ? -tempNum : tempNum;
                getNumber() = tempNum;
                return;
                
            }
            void parse(const char* text,bool iKnowWhatImDoing){
                goNull();
                char* analize;
                if(!iKnowWhatImDoing){
                    analize = new char[strlen(text)+1];
                    uint64_t org = 0;
                    uint64_t prep = 0;
                    uint64_t len = strlen(text);
                    for(uint64_t i = 0; i<len; i++){
                        if(text[i]==' '||text[i]=='\n'){
                            org++;
                        }else{
                            analize[prep] = text[org];
                            prep++;
                            org++;
                        }
                    }
                    analize[prep] = '\0';
                }else analize = (char*)text;
                uint64_t place = 0;
                this->parse(analize,place);
            }
            void parse(const char* text,uint64_t& place){
                goNull();
                switch(text[place]){
                    case '{':
                        //object
                        parseObject(text,place);
                        return;
                        break;
                    case '[':
                        //array
                        parseArray(text,place);
                        return;
                        break;
                    case 'n':
                        //null
                        place+=4;
                        return;
                        break;
                    case 't':
                        //bool
                        getBoolean() = true;
                        place+=4;
                        return;
                        break;
                    case 'f':
                        //bool
                        getBoolean() = false;
                        place+=5;
                        break;
                    case '"':
                        //string
                        parseString(text,place);
                        return;
                        break;
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                    case '-':
                        parseNumber(text,place);
                        return;
                        break;
                }
            } 
        public:
            json_type getType(){
                return type;
            }
            void resize(uint32_t newSize){
                switch(type){
                    case bol:
                        return;
                        break;
                    case num:
                        return;
                        break;
                    case str:
                        return;
                        break;
                    case obj:{
                        uint32_t sizeNow = data.obj.size;
                        if(sizeNow<newSize){
                            json_pair* newData = new json_pair[newSize];
                            for(uint32_t i = 0; i<newSize; i++){
                                if(i<sizeNow)newData[i] = data.obj.data[i];
                                else{
                                    newData[i].key = nullptr;
                                    newData[i].value = new json();
                                    newData[i].size = 0;
                                }
                            }
                            delete [] data.obj.data;
                            data.obj.data = newData;
                            data.obj.size = newSize;
                        }else if(sizeNow>newSize){
                            json_pair* newData = new json_pair[newSize];
                            for(uint32_t i = 0; i<sizeNow; i++){
                                if(i<newSize)newData[i] = data.obj.data[i];
                                else{
                                    delete [] newData[i].key;
                                    delete newData[i].value;
                                }                                
                            }
                            delete [] data.obj.data;
                            data.obj.data = newData;
                            data.obj.size = newSize;
                        }
                        break;}
                    case arr:{
                        uint32_t sizeNow = data.arr.size;
                        if(sizeNow<newSize){
                            json** newData = new json*[newSize];
                            for(uint32_t i = 0; i<newSize; i++){
                                if(i<sizeNow)newData[i] = data.arr.data[i];
                                else{
                                    newData[i] = new json();
                                }
                            }
                            delete [] data.arr.data;
                            data.arr.data = newData;
                            data.arr.size = newSize;
                        }else if(sizeNow>newSize){
                            json** newData = new json*[newSize];
                            for(uint32_t i = 0; i<sizeNow; i++){
                                if(i<newSize)newData[i] = data.arr.data[i];
                                else{
                                    delete newData[i];
                                }
                            }
                            delete [] data.arr.data;
                            data.arr.data = newData;
                            data.arr.size = newSize;
                        }
                        break;}
                }
            }
            uint32_t size(){
                switch(type){
                    case bol:
                        return 1;
                    case num:
                        return 1;
                    case str:
                        return data.str.size;
                    case obj:
                        return data.obj.size;
                    case arr:
                        return data.arr.size;
                }
                return 0;
            }
            void goNull(){
                if(type==null)return;
                switch(type){
                    case bol:
                        type = null;
                        break;
                    case num:
                        type = null;
                        break;
                    case str:
                        delete data.str.string;
                        data.str.string = nullptr;
                        data.str.size = 0;
                        type = null;
                        break;
                    case obj:
                        for(uint32_t i = 0; i<data.obj.size; i++){
                            delete data.obj.data[i].key;
                            delete data.obj.data[i].value;
                        }
                        delete [] data.obj.data;
                        data.obj.data = nullptr;
                        data.obj.size = 0;
                        type = null;
                        break;
                    case arr:
                        for(uint32_t i = 0; i<data.arr.size; i++){
                            delete data.arr.data[i];
                        }
                        delete [] data.arr.data;
                        data.arr.data = nullptr;
                        data.arr.size = 0;
                        type = null;
                        break;
                }
            }
            void setType(json_type newType){
                if(type==newType){
                    return;
                }
                goNull();
                switch(newType){
                    case bol:
                        type = newType;
                        data.bol.boolean = false;
                        break;
                    case num:
                        type = newType;
                        data.num.number = 0;
                        break;
                    case str:
                        data.str.string = nullptr;
                        data.str.size = 0;
                        type = newType;
                        break;
                    case obj:
                        data.obj.data = nullptr;
                        data.obj.size = 0;
                        type = newType;
                        break;
                    case arr:
                        data.arr.data = nullptr;
                        data.arr.size = 0;
                        type = newType;
                        break;
                    default:
                        goNull();
                }
            }
            json(){
                goNull();
            };
            json(const json& other){
                copy(other);
            }
            json(std::string json){
                parse(json.c_str(),false);
            };
            json(const char* text,bool iKnowWahtImDoing = false){
                parse(text,iKnowWahtImDoing);
            };
            json(char* text,bool iKnowWahtImDoing = false){
                parse(text,iKnowWahtImDoing);
            };
            json(const char* text,uint64_t& place){
                parse(text,place);
            }
            int64_t& getNumber(){
                setType(json_type::num);
                return data.num.number;
            }
            string_refference getString(){
                setType(json_type::str);
                return string_refference(&data.str.string, &data.str.size);
            }
            bool& getBoolean(){
                setType(json_type::bol);
                return data.bol.boolean;
            }
            json& operator[](const char* key){
                setType(json_type::obj);
                for(uint32_t i = 0; i<data.obj.size; i++){
                    if(strcmp(data.obj.data[i].key, key)==0){
                        return *data.obj.data[i].value;
                    }
                }
                resize(size()+1);
                data.obj.data[size()-1].key = new char[strlen(key)+1];
                strcpy(data.obj.data[size()-1].key, key);
                data.obj.data[size()-1].size = strlen(key);
                data.obj.data[size()-1].value = new json();
                return *data.obj.data[size()-1].value;
            }
            json& operator[](const std::string& key){
                return operator[](key.c_str());
            }
            json& operator[](int index){
                return operator[](uint32_t(index));
            }
            json& operator[](uint32_t index){
                setType(json_type::arr);
                if(data.arr.size<=index){
                    resize(index+1);
                }
                return *data.arr.data[index];
            }
            json& operator=(const json& other){
                return *this;
            }
            void operator=(const char* text){
                setType(json_type::str);
                delete data.str.string;
                data.str.string = new char[strlen(text)+1];
                strcpy(data.str.string, text);
                data.str.size = strlen(text);
            }
            void operator=(const std::string& text){
                operator=(text.c_str());
            }
            void operator=(int64_t number){
                setType(json_type::num);
                data.num.number = number;
            }
            void operator=(bool boolean){
                setType(json_type::bol);
                data.bol.boolean = boolean;
            }
            void operator=(int number){
                setType(json_type::num);
                data.num.number = number;
            }
            bool objectExists(const char* key){
                setType(json_type::obj);
                for(uint32_t i = 0; i<data.obj.size; i++){
                    if(strcmp(data.obj.data[i].key, key)==0){
                        return true;
                    }
                }
                return false;
            }
            void objectErease(const char* key){
                if(!objectExists(key))return;
                json_pair* temp = new json_pair[data.obj.size-1];
                uint64_t si = 0;
                for(uint32_t i = 0; i<data.obj.size; i++){
                    if(strcmp(data.obj.data[i].key, key)==0){
                        temp[si].key = data.obj.data[i].key;
                        temp[si].value = data.obj.data[i].value;
                        temp[si].size = data.obj.data[i].size;
                        si++;
                    }else{
                        delete [] data.obj.data[i].key;
                        delete data.obj.data[i].value;
                    }
                }
                delete [] data.obj.data;
                data.obj.data = temp;
                data.obj.size--;
            }
            void arrayForEach(std::function<void(json&)> func){
                setType(json_type::arr);
                for(uint32_t i = 0; i<data.arr.size; i++){
                    func(*data.arr.data[i]);
                }
            }
            void objectForEach(std::function<void(char*,json&)> func){
                setType(json_type::obj);
                for(uint32_t i = 0; i<data.obj.size; i++){
                    func(data.obj.data[i].key, *data.obj.data[i].value);
                }
            }
            void arrayPush(json& value){
                setType(json_type::arr);
                resize(size()+1);
                data.arr.data[size()-1] = new json(value);
            }
            void arrayPop(){
                setType(json_type::arr);
                if(size()==0)return;
                resize(size()-1);
            }
            uint64_t raw_Size() const{
                switch(type){
                    case bol:
                        if(data.bol.boolean){
                            return 4;//true
                        }else{
                            return 5;//true
                        }
                        return 0;
                    case num:
                        return std::to_string(data.num.number).size();//1234
                    case str:
                        return data.str.size+2;//""
                    case obj:{
                        uint32_t size = 2;//{}
                        for(uint64_t i = 0; i<data.obj.size; i++){
                            size += data.obj.data[i].size;
                            size += data.obj.data[i].value->raw_Size();
                            size += 3;//"":
                        }
                        return size;
                        break;}
                    case arr:{
                        uint64_t size = 2;//[]
                        for(uint64_t i = 0; i<data.arr.size; i++){
                            size += data.arr.data[i]->raw_Size();
                            size += 1;//,
                        }
                        return size;
                        break;}
                }
                return 4;
            }
            std::string raw() const {
                uint64_t psize = raw_Size();
                char* buffer = new char[raw_Size()+1];
                uint64_t laclace = 0;
                raw(buffer,laclace);
                buffer[laclace] = '\0';
                std::string result = buffer;
                delete [] buffer;
                return result;
            }
            void raw(char* buffer,uint64_t& place) const {
                switch(type){
                    case bol:
                        if(data.bol.boolean){
                            buffer[place] = 't';
                            place++;
                            buffer[place] = 'r';
                            place++;
                            buffer[place] = 'u';
                            place++;
                            buffer[place] = 'e';
                            place++;
                        }else{
                            buffer[place] = 'f';
                            place++;
                            buffer[place] = 'a';
                            place++;
                            buffer[place] = 'l';
                            place++;
                            buffer[place] = 's';
                            place++;
                            buffer[place] = 'e';
                            place++;
                        }
                        break;
                    case num:{
                        auto numb = std::to_string(data.num.number);
                        for(uint8_t i = 0; i<numb.size(); i++){
                            buffer[place] = numb[i];
                            place++;
                        }
                        break;}
                    case str:
                        buffer[place] = '"';
                        place++;
                        for(uint64_t i = 0; i<strlen(data.str.string); i++){
                            buffer[place] = data.str.string[i];
                            place++;
                        }
                        buffer[place] = '"';
                        place++;
                        break;
                    case obj:{
                        buffer[place] = '{';
                        place++;
                        bool first = true;
                        for(uint64_t i = 0; i<data.obj.size; i++){
                            if(!first){
                                buffer[place] = ',';
                                place++;
                            }else first = false;
                            buffer[place] = '"';
                            place++;
                            for(uint64_t j = 0; j<strlen(data.obj.data[i].key); j++){
                                buffer[place] = data.obj.data[i].key[j];
                                place++;
                            }
                            buffer[place] = '"';
                            place++;
                            buffer[place] = ':';
                            place++;
                            data.obj.data[i].value->raw(buffer,place);
                        }
                        buffer[place] = '}';
                        place++;
                        break;}
                    case arr:{
                        buffer[place] = '[';
                        place++;
                        bool first = true;
                        for(uint64_t i = 0; i<data.arr.size; i++){
                            if(!first){
                                buffer[place] = ',';
                                place++;
                            }else first = false;
                            data.arr.data[i]->raw(buffer,place);
                        }
                        buffer[place] = ']';
                        place++;
                        break;}
                    default:
                        buffer[place] = 'n';
                        place++;
                        buffer[place] = 'u';
                        place++;
                        buffer[place] = 'l';
                        place++;
                        buffer[place] = 'l';
                        place++;

            }

        };
    };
    std::ostream & operator << (std::ostream &out, const json &c)
    {
        out << c.raw();
        return out;
    }
}