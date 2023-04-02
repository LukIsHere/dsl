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
#include <string>
#include <stdint.h>

namespace dsl {
    class parser{
        private:
            uint32_t place = 0;
            std::string text;
        public:
            parser(std::string text){
                this->text = text;
            };
            std::string getWord(){
                if(place >= text.size()){
                    return "";
                }
                std::string word = "";
                while(text.at(place) != ' '){
                    word += text.at(place);
                    place++;
                    if(place == text.size())break;
                }
                place++;
                return word;
            };
            int getNumber(){
                int out = 0;
                try{
                    out = std::stoi(getWord());
                }catch(...){}

                return out;
            };
            char getChar(){
                if(place >= text.size()){
                    return '\0';
                }
                place+=2;
                return text.at(place-2);
            };
    };
}