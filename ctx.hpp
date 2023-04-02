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
#include <stdint.h>
#include <functional>
#include <cmath>
#include <iostream> //can be removed

#include "data.hpp" //inny nagłówek dsl

// ascii

#pragma once
inline bool characters[][5][5] = {
    {{false, false, false, false, false}, // spacja
     {false, false, false, false, false},
     {false, false, false, false, false},
     {false, false, false, false, false},
     {false, false, false, false, false}},

    {{false, false, true, false, false}, //!
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, false, false, false},
     {false, false, true, false, false}},

    {{false, true, false, true, false}, //"
     {false, false, false, false, false},
     {false, false, false, false, false},
     {false, false, false, false, false},
     {false, false, false, false, false}},

    {{false, true, false, true, false}, // #
     {true, true, true, true, true},
     {false, true, false, true, false},
     {true, true, true, true, true},
     {false, true, false, true, false}},

    {{false, true, true, true, false}, //$
     {true, false, true, false, false},
     {false, true, true, true, false},
     {false, false, true, false, true},
     {false, true, true, true, false}},

    {{true, false, false, false, true}, //%
     {false, true, false, false, false},
     {false, false, true, false, false},
     {false, false, false, true, false},
     {true, false, false, false, true}},

    {{false, false, true, false, false}, //&
     {false, true, false, true, false},
     {false, false, true, false, false},
     {false, true, false, true, false},
     {false, false, true, false, true}},

    {{false, false, true, false, false}, //'
     {false, false, false, false, false},
     {false, false, false, false, false},
     {false, false, false, false, false},
     {false, false, false, false, false}},

    {{false, false, true, false, false}, //(
     {false, true, false, false, false},
     {false, true, false, false, false},
     {false, true, false, false, false},
     {false, false, true, false, false}},

    {{false, false, true, false, false}, //)
     {false, false, false, true, false},
     {false, false, false, true, false},
     {false, false, false, true, false},
     {false, false, true, false, false}},

    {{false, false, true, false, false}, //*
     {false, true, true, true, false},
     {false, false, true, false, false},
     {false, false, false, false, false},
     {false, false, false, false, false}},

    {{false, false, false, false, false}, //+
     {false, false, true, false, false},
     {false, true, true, true, false},
     {false, false, true, false, false},
     {false, false, false, false, false}},

    {{false, false, false, false, false}, //,
     {false, false, false, false, false},
     {false, false, false, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false}},

    {{false, false, false, false, false}, //-
     {false, false, false, false, false},
     {false, true, true, true, false},
     {false, false, false, false, false},
     {false, false, false, false, false}},

    {{false, false, false, false, false}, //.
     {false, false, false, false, false},
     {false, false, false, false, false},
     {false, false, false, false, false},
     {false, false, true, false, false}},

    {{false, false, false, true, false}, ///
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, true, false, false, false}},

    {{false, false, true, false, false}, // 0
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, false, true, false, false}},

    {{false, false, true, false, false}, // 1
     {false, true, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false}},

    {{false, false, true, false, false}, // 2
     {false, true, false, true, false},
     {false, false, false, true, false},
     {false, false, true, false, false},
     {false, true, true, true, false}},

    {{false, true, true, false, false}, // 3
     {false, false, false, true, false},
     {false, true, true, false, false},
     {false, false, false, true, false},
     {false, true, true, false, false}},

    {{false, false, false, true, false}, // 4
     {false, false, true, true, false},
     {false, true, false, true, false},
     {false, true, true, true, false},
     {false, false, false, true, false}},

    {{false, true, true, true, false}, // 5
     {false, false, false, true, false},
     {false, false, true, false, false},
     {false, true, false, false, false},
     {false, false, true, true, false}},

    {{false, false, true, true, false}, // 6
     {false, true, false, false, false},
     {false, true, true, false, false},
     {false, true, false, true, false},
     {false, false, true, false, false}},

    {{false, true, true, true, false}, // 7
     {false, false, false, true, false},
     {false, false, false, true, false},
     {false, false, true, false, false},
     {false, false, true, false, false}},

    {{false, false, true, false, false}, // 8
     {false, true, false, true, false},
     {false, false, true, false, false},
     {false, true, false, true, false},
     {false, false, true, false, false}},

    {{false, false, true, false, false}, // 9
     {false, true, false, true, false},
     {false, false, true, true, false},
     {false, false, false, true, false},
     {false, true, true, false, false}},

    {{false, false, false, false, false}, //:
     {false, false, true, false, false},
     {false, false, false, false, false},
     {false, false, true, false, false},
     {false, false, false, false, false}},

    {{false, false, false, false, false}, //;
     {false, false, true, false, false},
     {false, false, false, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false}},

    {{false, false, false, true, false}, //<
     {false, false, true, false, false},
     {false, true, false, false, false},
     {false, false, true, false, false},
     {false, false, false, true, false}},

    {{false, false, false, false, false}, //=
     {false, true, true, true, false},
     {false, false, false, false, false},
     {false, true, true, true, false},
     {false, false, false, false, false}},

    {{false, false, false, true, false}, //>
     {false, false, true, false, false},
     {false, true, false, false, false},
     {false, false, true, false, false},
     {false, false, false, true, false}},

    {{false, true, true, false, false}, //?
     {false, false, false, true, false},
     {false, false, true, false, false},
     {false, false, false, false, false},
     {false, false, true, false, false}},

    {{false, false, true, false, false}, //@
     {false, true, false, true, false},
     {false, true, true, true, false},
     {false, true, false, false, false},
     {false, false, true, false, false}},

    {{false, false, true, false, false}, // a
     {false, true, false, true, false},
     {false, true, true, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false}},

    {{false, true, true, false, false}, // b
     {false, true, false, true, false},
     {false, true, true, false, false},
     {false, true, false, true, false},
     {false, true, true, false, false}},

    {{false, false, true, true, false}, // c
     {false, true, false, false, false},
     {false, true, false, false, false},
     {false, true, false, false, false},
     {false, false, true, true, false}},

    {{false, true, true, false, false}, // d
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, true, false, false}},

    {{false, true, true, true, false}, // e
     {false, true, false, false, false},
     {false, true, true, false, false},
     {false, true, false, false, false},
     {false, true, true, true, false}},

    {{false, true, true, true, false}, // f
     {false, true, false, false, false},
     {false, true, true, false, false},
     {false, true, false, false, false},
     {false, true, false, false, false}},

    {{false, false, true, true, false}, // g
     {false, true, false, false, false},
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, false, true, false, false}},

    {{false, true, false, true, false}, // h
     {false, true, false, true, false},
     {false, true, true, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false}},

    {{false, false, true, false, false}, // i
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false}},

    {{false, false, true, false, false}, // j
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, true, false, false, false}},

    {{false, true, false, true, false}, // k
     {false, true, false, true, false},
     {false, true, true, false, false},
     {false, true, false, true, false},
     {false, true, false, true, false}},

    {{false, false, true, false, false}, // l
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, true, false}},

    {{false, true, false, true, false}, // m
     {false, true, true, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false}},

    {{false, true, false, true, false}, // n
     {false, true, true, true, false},
     {false, true, true, true, false},
     {false, true, true, true, false},
     {false, true, false, true, false}},

    {{false, false, true, false, false}, // o
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, false, true, false, false}},

    {{false, true, true, false, false}, // p
     {false, true, false, true, false},
     {false, true, true, false, false},
     {false, true, false, false, false},
     {false, true, false, false, false}},

    {{false, false, true, false, false}, // q
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, false, true, true, false}},

    {{false, true, true, false, false}, // r
     {false, true, false, true, false},
     {false, true, true, false, false},
     {false, true, false, true, false},
     {false, true, false, true, false}},

    {{false, false, true, true, false}, // s
     {false, true, false, false, false},
     {false, false, true, false, false},
     {false, false, false, true, false},
     {false, true, true, false, false}},

    {{false, true, true, true, false}, // t
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false}},

    {{false, true, false, true, false}, // u
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, true, true, false}},

    {{false, true, false, true, false}, // v
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, false, true, false, false}},

    {{false, true, false, true, false}, // w
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, true, true, false},
     {false, true, false, true, false}},

    {{false, true, false, true, false}, // x
     {false, true, false, true, false},
     {false, false, true, false, false},
     {false, true, false, true, false},
     {false, true, false, true, false}},

    {{false, true, false, true, false}, // y
     {false, true, false, true, false},
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false}},

    {{false, true, true, true, false}, // z
     {false, false, false, true, false},
     {false, false, true, false, false},
     {false, true, false, false, false},
     {false, true, true, true, false}},

    {{false, true, true, false, false}, //[
     {false, true, false, false, false},
     {false, true, false, false, false},
     {false, true, false, false, false},
     {false, true, true, false, false}},

    {{false, true, false, false, false}, //\-
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, false, true, false}},

    {{false, false, true, true, false}, //]
     {false, false, false, true, false},
     {false, false, false, true, false},
     {false, false, false, true, false},
     {false, false, true, true, false}},

    {{false, false, true, false, false}, //^
     {false, true, false, true, false},
     {false, false, false, false, false},
     {false, false, false, false, false},
     {false, false, false, false, false}},

    {{false, false, false, false, false}, //_
     {false, false, false, false, false},
     {false, false, false, false, false},
     {false, false, false, false, false},
     {false, true, true, true, false}},

    {{false, true, false, false, false}, //`
     {false, false, true, false, false},
     {false, false, false, false, false},
     {false, false, false, false, false},
     {false, false, false, false, false}},

    // repeat for small letters

    {{false, false, true, false, false}, // a
     {false, true, false, true, false},
     {false, true, true, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false}},

    {{false, true, true, false, false}, // b
     {false, true, false, true, false},
     {false, true, true, false, false},
     {false, true, false, true, false},
     {false, true, true, false, false}},

    {{false, false, true, true, false}, // c
     {false, true, false, false, false},
     {false, true, false, false, false},
     {false, true, false, false, false},
     {false, false, true, true, false}},

    {{false, true, true, false, false}, // d
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, true, false, false}},

    {{false, true, true, true, false}, // e
     {false, true, false, false, false},
     {false, true, true, false, false},
     {false, true, false, false, false},
     {false, true, true, true, false}},

    {{false, true, true, true, false}, // f
     {false, true, false, false, false},
     {false, true, true, false, false},
     {false, true, false, false, false},
     {false, true, false, false, false}},

    {{false, false, true, true, false}, // g
     {false, true, false, false, false},
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, false, true, false, false}},

    {{false, true, false, true, false}, // h
     {false, true, false, true, false},
     {false, true, true, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false}},

    {{false, false, true, false, false}, // i
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false}},

    {{false, false, true, false, false}, // j
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, true, false, false, false}},

    {{false, true, false, true, false}, // k
     {false, true, false, true, false},
     {false, true, true, false, false},
     {false, true, false, true, false},
     {false, true, false, true, false}},

    {{false, false, true, false, false}, // l
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, true, false}},

    {{false, true, false, true, false}, // m
     {false, true, true, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false}},

    {{false, true, false, true, false}, // n
     {false, true, true, true, false},
     {false, true, true, true, false},
     {false, true, true, true, false},
     {false, true, false, true, false}},

    {{false, false, true, false, false}, // o
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, false, true, false, false}},

    {{false, true, true, false, false}, // p
     {false, true, false, true, false},
     {false, true, true, false, false},
     {false, true, false, false, false},
     {false, true, false, false, false}},

    {{false, false, true, false, false}, // q
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, false, true, true, false}},

    {{false, true, true, false, false}, // r
     {false, true, false, true, false},
     {false, true, true, false, false},
     {false, true, false, true, false},
     {false, true, false, true, false}},

    {{false, false, true, true, false}, // s
     {false, true, false, false, false},
     {false, false, true, false, false},
     {false, false, false, true, false},
     {false, true, true, false, false}},

    {{false, true, true, true, false}, // t
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false}},

    {{false, true, false, true, false}, // u
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, true, true, false}},

    {{false, true, false, true, false}, // v
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, false, true, false, false}},

    {{false, true, false, true, false}, // w
     {false, true, false, true, false},
     {false, true, false, true, false},
     {false, true, true, true, false},
     {false, true, false, true, false}},

    {{false, true, false, true, false}, // x
     {false, true, false, true, false},
     {false, false, true, false, false},
     {false, true, false, true, false},
     {false, true, false, true, false}},

    {{false, true, false, true, false}, // y
     {false, true, false, true, false},
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false}},

    {{false, true, true, true, false}, // z
     {false, false, false, true, false},
     {false, false, true, false, false},
     {false, true, false, false, false},
     {false, true, true, true, false}},

    {{false, false, true, false, false}, //{
     {false, true, false, false, false},
     {false, false, true, false, false},
     {false, true, false, false, false},
     {false, false, true, false, false}},

    {{false, false, false, false, false}, //|
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, true, false, false},
     {false, false, false, false, false}},

    {{false, false, true, false, false}, //}
     {false, false, false, true, false},
     {false, false, true, false, false},
     {false, false, false, true, false},
     {false, false, true, false, false}},

    {{false, true, false, true, false}, //~
     {false, false, true, false, true},
     {false, false, false, false, false},
     {false, false, false, false, false},
     {false, false, false, false, false}},
};

// declaration
typedef std::function<void(int32_t, int32_t)> pointAction;

namespace dsl
{
    struct rgb
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
    struct argb
    {
        uint8_t a;
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
    class rgb565
    {
    public:
        uint16_t color;
        rgb565(uint16_t rgb) : color(rgb){};
        rgb565(uint32_t argb)
        {
            set((argb >> 16) & 0xFF, (argb >> 8) & 0xFF, argb & 0xFF);
        }
        rgb565(uint8_t r, uint8_t g, uint8_t b)
        {
            set(r, g, b);
        }
        rgb565(rgb c)
        {
            set(c.r, c.g, c.b);
        }
        rgb565(argb c)
        {
            set(c.r, c.g, c.b);
        }
        void set(uint8_t r, uint8_t g, uint8_t b)
        {
            color = 0;
            color |= r >> 3;
            color <<= 6;
            color |= g >> 2;
            color <<= 5;
            color |= b >> 3;
        }
        rgb get()
        {
            return rgb{uint8_t((color & 0x1F) << 3), uint8_t(((color >> 5) & 0x3F) << 2), uint8_t(((color >> 11) & 0x1F) << 3)};
        }
        uint16_t operator()()
        {
            return color;
        }
    };
    class argb8888
    {
    public:
        uint32_t color;
        argb8888(uint16_t rgb)
        {
            set(uint8_t((color & 0x1F) << 3), uint8_t(((color >> 5) & 0x3F) << 2), uint8_t(((color >> 11) & 0x1F) << 3));
        };
        argb8888(uint32_t argb) : color(argb){};
        argb8888(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        {
            set(r, g, b, a);
        }
        argb8888(rgb c)
        {
            set(c.r, c.g, c.b);
        }
        argb8888(argb c)
        {
            set(c.r, c.g, c.b, c.a);
        }
        void set(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
        {
            color = 0;
            color |= a;
            color <<= 8;
            color |= r;
            color <<= 8;
            color |= g;
            color <<= 8;
            color |= b;
        }
        argb get()
        {
            return argb{uint8_t((color >> 24) & 0xFF), uint8_t((color >> 16) & 0xFF), uint8_t((color >> 8) & 0xFF), uint8_t(color & 0xFF)};
        }
        uint32_t operator()()
        {
            return color;
        }
    };

    constexpr argb ARGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
    {
        return {a, r, g, b};
    }
    constexpr rgb RGB(uint8_t r, uint8_t g, uint8_t b)
    {
        return {r, g, b};
    }

    template <typename color>
    class ctxTemplate
    {
        int height;
        int width;

    public:
        // if you touch this you die
        color *img;
        ctxTemplate(int width, int height);
        ctxTemplate(ctxTemplate<color> &cp);
        ~ctxTemplate();
        // size manipilation
        // entier screen
        void fill(color c);
        // points
        void drawPoint(int32_t x, int32_t y, color c);
        // rectangles
        void fillRect(int32_t x, int32_t y, uint32_t w, uint32_t h, color c);
        void drawRect(int32_t x, int32_t y, uint32_t w, uint32_t h, color c);
        // circle
        void drawCircle(int32_t x, int32_t y, uint32_t radius, color c);
        void fillCircle(int32_t x, int32_t y, uint32_t radius, color c);
        // lines
        void drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, color c);
        void drawLineThick(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t scale, color c);
        void drawLineUpDown(int32_t x, int32_t y, int32_t l, color c);
        void drawLineLeftRight(int32_t x, int32_t y, int32_t l, color c);
        // other ctx
        void drawCtx(int32_t x, int32_t y, ctxTemplate<color> &context);
        // triangle
        void drawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, color c);
        void fillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, color c);
        // symbols
        void drawSymbol(int32_t x, int32_t y, dataArray &data, color c, uint32_t scale);
        // sprites
        void drawSprite(int32_t x, int32_t y, dataArray &data, uint32_t scale);
        // letters
        void drawLetter(char ch, int32_t x, int32_t y, color c, int32_t scale = 1);
        void print(const char *text, int32_t x, int32_t y, color c, uint32_t scale = 1);
        void print(int32_t number, int32_t x, int32_t y, color c, uint32_t scale = 1);

    private:
        // helpfull
        void drawTwistLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, pointAction function);
        void mirrorDrawPoint(int32_t x, int32_t y, uint32_t ox, uint32_t oy, color c);
    };
    typedef ctxTemplate<rgb565> ctx565;
    typedef ctxTemplate<argb8888> ctx8888;
}

// definition

#define swap_int(a, b) \
    {                  \
        int32_t t;     \
        t = a;         \
        a = b;         \
        b = t;         \
    }

template <typename color>
dsl::ctxTemplate<color>::ctxTemplate(int width, int height) : height(height), width(width)
{

    img = new color[height * width];
    for (int32_t i = 0; i < width * height; i++)
    {
        img[i] = 0;
    }
}
template <typename color>
dsl::ctxTemplate<color>::ctxTemplate(ctxTemplate &cp)
{
    height = cp.height;
    width = cp.width;
    img = new color[height * width];
    for (int32_t i = 0; i < width * height; i++)
    {
        img[i] = cp.img[i];
    }
}
template <typename color>
dsl::ctxTemplate<color>::~ctxTemplate()
{
    delete[] img;
}
template <typename color>
void dsl::ctxTemplate<color>::fillRect(int32_t x, int32_t y, uint32_t w, uint32_t h, color c)
{
    for (int32_t ix = 0; ix < w; ix++)
    {
        for (int32_t iy = 0; iy < h; iy++)
        {
            drawPoint(x + ix, y + iy, c); // maybe faster
        }
    }
};
template <typename color>
void dsl::ctxTemplate<color>::drawRect(int32_t x, int32_t y, uint32_t w, uint32_t h, color c)
{
    for (int32_t i = 0; i < w; i++)
    {
        drawPoint(x + i, y, c);
        drawPoint(x + i, y + h - 1, c);
    }
    for (int32_t i = 0; i < h; i++)
    {
        drawPoint(x, y + i, c);
        drawPoint(x + w - 1, y + i, c);
    }
};
template <typename color>
void dsl::ctxTemplate<color>::fill(color c)
{
    for (uint32_t i = 0; i < height * width; i++)
    {
        img[i] = c;
    }
};
template <typename color>
void dsl::ctxTemplate<color>::drawPoint(int32_t x, int32_t y, color c)
{
    if (x >= width || x < 0 || y >= height || y < 0)
        return;
    img[x + width * y] = c;
};
template <typename color>
void dsl::ctxTemplate<color>::drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, color c)
{
    int32_t dx = x2 - x1;
    int32_t dy = y2 - y1;
    if (abs(dx) < abs(dy))
    {
        if (x1 > x2)
        {
            swap_int(x1, x2);
            swap_int(y1, y2);
        }
        dx = x2 - x1;
        dy = y2 - y1;
        if (dy > 0)
        {
            for (int32_t i = 0; i < dy; i++)
            {
                float p = ((float)i / (float)dy) * (float)dx;
                drawPoint(x1 + p, y1 + i, c);
            }
        }
        else
        {
            dy = abs(dy);
            for (int32_t i = 0; i < dy; i++)
            {
                float p = ((float)i / (float)dy) * (float)dx;
                drawPoint(x1 + p, y1 - i, c);
            }
        }
    }
    else
    {
        if (y1 > y2)
        {
            swap_int(x1, x2);
            swap_int(y1, y2);
        }
        dx = x2 - x1;
        dy = y2 - y1;
        if (dx > 0)
        {
            for (int32_t i = 0; i < dx; i++)
            {
                float p = ((float)i / (float)dx) * (float)dy;
                drawPoint(x1 + i, y1 + p, c);
            }
        }
        else
        {
            dx = abs(dx);
            for (int32_t i = 0; i < dx; i++)
            {
                float p = ((float)i / (float)dx) * (float)dy;
                drawPoint(x1 - i, y1 + p, c);
            }
        }
    }
};
template <typename color>
void dsl::ctxTemplate<color>::drawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, color c)
{
    drawLine(x1, y1, x2, y2, c);
    drawLine(x2, y2, x3, y3, c);
    drawLine(x3, y3, x1, y1, c);
};
template <typename color>
void dsl::ctxTemplate<color>::drawTwistLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, pointAction function)
{
    int32_t dx = x2 - x1;
    int32_t dy = y2 - y1;
    if (abs(dx) < abs(dy))
    {
        if (x1 > x2)
        {
            swap_int(x1, x2);
            swap_int(y1, y2);
        }
        dx = x2 - x1;
        dy = y2 - y1;
        if (dy > 0)
        {
            for (int32_t i = 0; i < dy; i++)
            {
                float p = ((float)i / (float)dy) * (float)dx;
                function(*this, x1 + p, y1 + i);
            }
        }
        else
        {
            dy = abs(dy);
            for (int32_t i = 0; i < dy; i++)
            {
                float p = ((float)i / (float)dy) * (float)dx;
                function(*this, x1 + p, y1 + i);
            }
        }
    }
    else
    {
        if (y1 > y2)
        {
            swap_int(x1, x2);
            swap_int(y1, y2);
        }
        dx = x2 - x1;
        dy = y2 - y1;
        if (dx > 0)
        {
            for (int32_t i = 0; i < dx; i++)
            {
                float p = ((float)i / (float)dx) * (float)dy;
                function(*this, x1 + i, y1 + p);
            }
        }
        else
        {
            dx = abs(dx);
            for (int32_t i = 0; i < dx; i++)
            {
                float p = ((float)i / (float)dx) * (float)dy;
                function(*this, x1 + i, y1 + p);
            }
        }
    }
};
template <typename color>
void dsl::ctxTemplate<color>::drawCircle(int32_t x, int32_t y, uint32_t radius, color c)
{
    float len = 0;
    for (int32_t i = 0; i < radius; i++)
    {
        len = sqrt((float(radius) * float(radius)) - (float(i) * float(i)));
        mirrorDrawPoint(x, y, i, len, c);
        mirrorDrawPoint(x, y, len, i, c);
        if (i == len)
            return;
    }
};
template <typename color>
void dsl::ctxTemplate<color>::mirrorDrawPoint(int32_t x, int32_t y, uint32_t ox, uint32_t oy, color c)
{
    drawPoint(x + ox, y + oy, c);
    drawPoint(x + ox, y - oy, c);
    drawPoint(x - ox, y - oy, c);
    drawPoint(x - ox, y + oy, c);
}
template <typename color>
void dsl::ctxTemplate<color>::fillCircle(int32_t x, int32_t y, uint32_t radius, color c)
{
    float len = 0;
    for (int32_t i = 0; i < radius; i++)
    {
        len = sqrt((float(radius) * float(radius)) - (float(i) * float(i)));
        mirrorDrawPoint(x, y, i, len, c);
        mirrorDrawPoint(x, y, len, i, c);
        for (int32_t j = 0; j < len; j++)
        {
            mirrorDrawPoint(x, y, i, j, c);
            mirrorDrawPoint(x, y, j, i, c);
        }
        if (i == len)
            return;
    }
};
template <typename color>
void dsl::ctxTemplate<color>::drawLineThick(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t scale, color c)
{
    fillCircle(x1, y1, scale, c);
    fillCircle(x2, y2, scale, c);

    drawTwistLine(x1, y1, x2, y2, [&](int32_t x, int32_t y)
                  {
        this->drawLineLeftRight(x-scale,y,(scale<<1)+1,c);
        this->drawLineUpDown(x,y-scale,(scale<<1)+1,c);
        this->drawPoint(x,y,c); });
};
template <typename color>
void dsl::ctxTemplate<color>::drawLineLeftRight(int32_t x, int32_t y, int32_t l, color c)
{
    for (uint32_t i = 0; i < l; i++)
    {
        drawPoint(x + i, y, c);
    }
}
template <typename color>
void dsl::ctxTemplate<color>::drawLineUpDown(int32_t x, int32_t y, int32_t l, color c)
{
    for (uint32_t i = 0; i < l; i++)
    {
        drawPoint(x, y + i, c);
    }
}
template <typename color>
void dsl::ctxTemplate<color>::fillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, color c)
{

    if (y1 > y2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    if (y2 > y3)
    {
        std::swap(x2, x3);
        std::swap(y2, y3);
    }
    if (y1 > y2)
    {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }
    // 1<2<3
    float x1ToX2 = float(x2 - x1) / float(y2 - y1);
    float x2ToX3 = float(x3 - x2) / float(y3 - y2);
    float x1ToX3 = float(x3 - x1) / float(y3 - y1);

    bool x1tox2S = true;
    float currentLX = x1;
    float currentSX = x1;
    if (y1 == y2)
        currentSX = x2;

    for (int32_t currentY = y1; currentY <= y3; currentY++)
    {
        if (currentY == y2)
            x1tox2S = false;
        if (currentLX < currentSX)
            drawLineLeftRight(currentLX, currentY, currentSX - currentLX, c);
        else
            drawLineLeftRight(currentSX, currentY, currentLX - currentSX, c);
        if (x1tox2S)
            currentSX += x1ToX2;
        else
            currentSX += x2ToX3;
        currentLX += x1ToX3;
    }
};
template <typename color>
void dsl::ctxTemplate<color>::drawLetter(char ch, int32_t x, int32_t y, color c, int32_t scale)
{
    uint8_t id = (uint8_t)ch - ' ';
    for (uint8_t i = 0; i < 5; i++)
    {
        for (uint8_t j = 0; j < 5; j++)
        {
            if (characters[id][j][i])
                fillRect(x + i * scale, y + j * scale, scale, scale, c);
        }
    }
};
template <typename color>
void dsl::ctxTemplate<color>::drawCtx(int32_t x, int32_t y, ctxTemplate<color> &context)
{
    for (int32_t ix = 0; ix < context.width; ix++)
    {
        for (int32_t iy = 0; iy < context.height; iy++)
        {
            drawPoint(x + ix, y + iy, context.img[ix + context.width * iy]);
        }
    }
}
template <typename color>
void dsl::ctxTemplate<color>::print(const char *text, int32_t x, int32_t y, color c, uint32_t scale)
{
    uint32_t place = 0;
    uint32_t line = 0;
    while (text[place] != '\0')
    {

        if (text[place] == '\n')
        {
            line++;
            continue;
        }
        else
            drawLetter(text[place], x + 6 * place * scale, y + line * scale * 6, c, scale);
        place++;
    }
};
template <typename color>
void dsl::ctxTemplate<color>::print(int32_t number, int32_t x, int32_t y, color c, uint32_t scale)
{
    bool negative = false;
    if (number < 0)
    {
        negative = true;
        number = -number;
    }
    uint32_t numlenght = 0;
    int32_t temp = number;
    do
    {
        temp -= temp % 10;
        temp /= 10;
        numlenght++;
    } while (temp != 0);
    numlenght += negative;
    char *txt = new char[numlenght + 1];
    txt[numlenght] = '\0';

    if (negative)
    {
        txt[0] = '-';
    }
    uint32_t itnumlenght = numlenght - 1;
    while (number != 0)
    {
        txt[itnumlenght] = number % 10 + '0';
        number /= 10;
        itnumlenght--;
    }
    print(txt, x, y, c, scale);
    delete[] txt;
}

template <typename color>
void dsl::ctxTemplate<color>::drawSymbol(int32_t x, int32_t y, dataArray &data, color c, uint32_t scale)
{
    throw "not implemented yet"; // to-do
};

template <>
void dsl::ctxTemplate<dsl::rgb565>::drawSprite(int32_t x, int32_t y, dataArray &data, uint32_t scale)
{
    throw "not implemented yet"; // to-do
};

template <>
void dsl::ctxTemplate<dsl::argb8888>::drawSprite(int32_t x, int32_t y, dataArray &data, uint32_t scale)
{
    throw "not implemented yet"; // to-do
};

template <typename color>
void dsl::ctxTemplate<color>::drawSprite(int32_t x, int32_t y, dataArray &data, uint32_t scale)
{
    throw "only uint16_t/uint32_t is supportet unless you provide your own implementation";
};