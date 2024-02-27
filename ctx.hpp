#pragma once

#include <stdint.h>
#include <functional>
#include <cmath>

#define swp(a, b)   \
    {               \
        auto t = a; \
        a = b;      \
        b = t;      \
    }

// ascii

#pragma once
inline uint64_t characters[] = {
    // https://github.com/dhepper/font8x8/blob/master/font8x8_basic.h
    0x0000000000000000, // U+0020 (space)
    0x183C3C1818001800, // U+0021 (!)
    0x3636000000000000, // U+0022 (")
    0x36367F367F363600, // U+0023 (#)
    0x0C3E031E301F0C00, // U+0024 ($)
    0x006333180C666300, // U+0025 (%)
    0x1C361C6E3B336E00, // U+0026 (&)
    0x0606030000000000, // U+0027 (')
    0x180C0606060C1800, // U+0028 (()
    0x060C1818180C0600, // U+0029 ())
    0x00663CFF3C660000, // U+002A (*)
    0x000C0C3F0C0C0000, // U+002B (+)
    0x00000000000C0C06, // U+002C (,)
    0x0000003F00000000, // U+002D (-)
    0x00000000000C0C00, // U+002E (.)
    0x6030180C06030100, // U+002F (/)
    0x3E63737B6F673E00, // U+0030 (0)
    0x0C0E0C0C0C0C3F00, // U+0031 (1)
    0x1E33301C06333F00, // U+0032 (2)
    0x1E33301C30331E00, // U+0033 (3)
    0x383C36337F307800, // U+0034 (4)
    0x3F031F3030331E00, // U+0035 (5)
    0x1C06031F33331E00, // U+0036 (6)
    0x3F3330180C0C0C00, // U+0037 (7)
    0x1E33331E33331E00, // U+0038 (8)
    0x1E33333E30180E00, // U+0039 (9)
    0x000C0C00000C0C00, // U+003A (:)
    0x000C0C00000C0C06, // U+003B (;)
    0x180C0603060C1800, // U+003C (<)
    0x00003F00003F0000, // U+003D (=)
    0x060C1830180C0600, // U+003E (>)
    0x1E3330180C000C00, // U+003F (?)
    0x3E637B7B7B031E00, // U+0040 (@)
    0x0C1E33333F333300, // U+0041 (A)
    0x3F66663E66663F00, // U+0042 (B)
    0x3C66030303663C00, // U+0043 (C)
    0x1F36666666361F00, // U+0044 (D)
    0x7F46161E16467F00, // U+0045 (E)
    0x7F46161E16060F00, // U+0046 (F)
    0x3C66030373667C00, // U+0047 (G)
    0x3333333F33333300, // U+0048 (H)
    0x1E0C0C0C0C0C1E00, // U+0049 (I)
    0x7830303033331E00, // U+004A (J)
    0x6766361E36666700, // U+004B (K)
    0x0F06060646667F00, // U+004C (L)
    0x63777F7F6B636300, // U+004D (M)
    0x63676F7B73636300, // U+004E (N)
    0x1C36636363361C00, // U+004F (O)
    0x3F66663E06060F00, // U+0050 (P)
    0x1E3333333B1E3800, // U+0051 (Q)
    0x3F66663E36666700, // U+0052 (R)
    0x1E33070E38331E00, // U+0053 (S)
    0x3F2D0C0C0C0C1E00, // U+0054 (T)
    0x3333333333333F00, // U+0055 (U)
    0x33333333331E0C00, // U+0056 (V)
    0x6363636B7F776300, // U+0057 (W)
    0x6363361C1C366300, // U+0058 (X)
    0x3333331E0C0C1E00, // U+0059 (Y)
    0x7F6331184C667F00, // U+005A (Z)
    0x1E06060606061E00, // U+005B ([)
    0x03060C1830604000, // U+005C (\)
    0x1E18181818181E00, // U+005D (])
    0x081C366300000000, // U+005E (^)
    0x00000000000000FF, // U+005F (_)
    0x0C0C180000000000, // U+0060 (`)
    0x00001E303E336E00, // U+0061 (a)
    0x0706063E66663B00, // U+0062 (b)
    0x00001E3303331E00, // U+0063 (c)
    0x3830303e33336E00, // U+0064 (d)
    0x00001E333f031E00, // U+0065 (e)
    0x1C36060f06060F00, // U+0066 (f)
    0x00006E33333E301F, // U+0067 (g)
    0x0706366E66666700, // U+0068 (h)
    0x0C000E0C0C0C1E00, // U+0069 (i)
    0x300030303033331E, // U+006A (j)
    0x070666361E366700, // U+006B (k)
    0x0E0C0C0C0C0C1E00, // U+006C (l)
    0x0000337F7F6B6300, // U+006D (m)
    0x00001F3333333300, // U+006E (n)
    0x00001E3333331E00, // U+006F (o)
    0x00003B66663E060F, // U+0070 (p)
    0x00006E33333E3078, // U+0071 (q)
    0x00003B6E66060F00, // U+0072 (r)
    0x00003E031E301F00, // U+0073 (s)
    0x080C3E0C0C2C1800, // U+0074 (t)
    0x0000333333336E00, // U+0075 (u)
    0x00003333331E0C00, // U+0076 (v)
    0x0000636B7F7F3600, // U+0077 (w)
    0x000063361C366300, // U+0078 (x)
    0x00003333333E301F, // U+0079 (y)
    0x00003F190C263F00, // U+007A (z)
    0x380C0C070C0C3800, // U+007B ({)
    0x1818180018181800, // U+007C (|)
    0x070C0C380C0C0700, // U+007D (})
    0x6E3B000000000000, // U+007E (~)
    0x0000000000000000  // U+007F
};

namespace dsl
{
    struct color
    {
        uint8_t b;
        uint8_t g;
        uint8_t r; // hands off compiler UwU
        uint8_t a;
    };

    static const color nullColor = {0};

    inline constexpr color argb(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        return {b, g, r, a};
    };
    inline constexpr color rgb(uint8_t r, uint8_t g, uint8_t b) { return argb(r, g, b, 255); };

    class ctx
    {
        const uint32_t height;
        const uint32_t width;
        color *img;
        constexpr bool isInside(uint32_t x, uint32_t y); // not safety checks
    public:
        ctx(int width, int height);
        ctx(int width, int height, color *img);
        ctx(ctx &cp);
        ~ctx();
        // get data
        color *getData();

        uint32_t getHeight();
        uint32_t getWidth();
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
        void drawLineLeftRight(int32_t x, int32_t y, int32_t l, color c);
        void drawLineUpDown(int32_t x, int32_t y, int32_t l, color c);
        // other ctx
        void drawCtx(int32_t x, int32_t y, ctx &context, uint8_t scale = 1);
        // triangle
        void drawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, color c);
        void fillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, color c);
        // symbols
        // sprites
        // letters
        void drawLetter(char ch, int32_t x, int32_t y, color c, int32_t scale = 1);
        void print(const char *text, int32_t x, int32_t y, color c, uint32_t scale = 1);
        void print(int32_t number, int32_t x, int32_t y, color c, uint32_t scale = 1);

    private:
        // helpfull
        void mirrorDrawPoint(int32_t x, int32_t y, uint32_t ox, uint32_t oy, color c);
    };
}

// ctx

inline constexpr bool dsl::ctx::isInside(uint32_t x, uint32_t y)
{
    return (x < width && y < height);
}

inline dsl::ctx::ctx(int width, int height) : height(height), width(width)
{
    img = new color[height * width];
    fill(nullColor);
}

inline dsl::ctx::ctx(ctx &cp) : height(cp.height), width(cp.width)
{
    img = new color[height * width];
    for (int32_t i = 0; i < width * height; i++)
    {
        img[i] = cp.img[i];
    }
}

inline dsl::ctx::~ctx()
{
    delete[] img;
}

inline dsl::color *dsl::ctx::getData()
{
    return img;
}

inline uint32_t dsl::ctx::getHeight()
{
    return height;
}

inline uint32_t dsl::ctx::getWidth()
{
    return width;
}

inline void dsl::ctx::fillRect(int32_t x, int32_t y, uint32_t w, uint32_t h, color c)
{
    x = std::max(0, x);
    y = std::max(0, y);
    w = std::min(width, w);
    h = std::min(height, h);

    for (int32_t ix = 0; ix < (int32_t)w; ix++)
    {
        for (int32_t iy = 0; iy < (int32_t)h; iy++)
        {
            img[(x + ix) + width * (y + iy)] = c; // to -optimize?
        }
    }
};

inline void dsl::ctx::drawRect(int32_t x, int32_t y, uint32_t w, uint32_t h, color c) // to-optimize
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

inline void dsl::ctx::fill(color c)
{
    for (uint32_t i = 0; (int32_t)i < (int32_t)height * (int32_t)width; i++)
    {
        img[i] = c;
    }
};

inline void dsl::ctx::drawPoint(int32_t x, int32_t y, color c)
{
    if (x >= width || x < 0 || y >= height || y < 0)
        return;
    img[x + width * y] = c;
};

inline void dsl::ctx::drawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, color c)
{
    int32_t dx = x2 - x1;
    int32_t dy = y2 - y1;
    if (abs(dx) < abs(dy))
    {
        if (x1 > x2)
        {
            swp(x1, x2);
            swp(y1, y2);
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
            swp(x1, x2);
            swp(y1, y2);
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

inline void dsl::ctx::drawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, color c)
{
    drawLine(x1, y1, x2, y2, c);
    drawLine(x2, y2, x3, y3, c);
    drawLine(x3, y3, x1, y1, c);
};

inline void dsl::ctx::drawCircle(int32_t x, int32_t y, uint32_t radius, color c)
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

inline void dsl::ctx::mirrorDrawPoint(int32_t x, int32_t y, uint32_t ox, uint32_t oy, color c)
{
    drawPoint(x + ox, y + oy, c);
    drawPoint(x + ox, y - oy, c);
    drawPoint(x - ox, y - oy, c);
    drawPoint(x - ox, y + oy, c);
}

inline void dsl::ctx::fillCircle(int32_t x, int32_t y, uint32_t radius, color c)
{
    drawPoint(x, y, c);

    float len = 0;
    for (int32_t i = 1; i < radius; i++)
    {
        len = sqrt((float(radius) * float(radius)) - (float(i) * float(i)));
        for (int32_t j = 1; j < len; j++)
        {
            if (i == j)
                break;

            mirrorDrawPoint(x, y, i, j, c);
            mirrorDrawPoint(x, y, j, i, c);
        }
        if (i == len)
            break;
    }

    float skos = sqrt((float(radius) * float(radius)) / 2);

    for (int32_t i = 1; i < skos; i++)
    { // skos
        mirrorDrawPoint(x, y, i, i, c);
    }

    for (int32_t i = 1; i < radius; i++)
    { // pion/poziom
        drawPoint(x + i, y, c);
        drawPoint(x - i, y, c);
        drawPoint(x, y + i, c);
        drawPoint(x, y - i, c);
    }
};

inline void dsl::ctx::drawLineLeftRight(int32_t x, int32_t y, int32_t l, color c)
{
    for (uint32_t i = 0; i < l; i++)
    {
        drawPoint(x + i, y, c);
    }
}

inline void dsl::ctx::drawLineUpDown(int32_t x, int32_t y, int32_t l, color c)
{
    for (uint32_t i = 0; i < l; i++)
    {
        drawPoint(x, y + i, c);
    }
}

inline void dsl::ctx::fillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, color c)
{

    if (y1 > y2)
    {
        swp(x1, x2);
        swp(y1, y2);
    }
    if (y2 > y3)
    {
        swp(x2, x3);
        swp(y2, y3);
    }
    if (y1 > y2)
    {
        swp(x1, x2);
        swp(y1, y2);
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

inline void dsl::ctx::drawLetter(char ch, int32_t x, int32_t y, color c, int32_t scale)
{
    uint8_t id = (uint8_t)ch - ' ';

    uint64_t p = 1;
    const uint64_t chr = characters[id];

    for (uint8_t i = 0; i < 8; i++)
    {
        for (uint8_t j = 0; j < 8; j++)
        {
            if (chr & p)
                fillRect(x + j * scale, y + (7 - i) /*nie chcialo mi się obracać każdy znak w tablicy*/ * scale, scale, scale, c);
            p <<= 1;
        }
    }
};

inline void dsl::ctx::drawCtx(int32_t x, int32_t y, ctx &context, uint8_t scale)
{
    for (int32_t ix = 0; ix < context.width; ix++)
    {
        for (int32_t iy = 0; iy < context.height; iy++)
        {
            fillRect(x + ix * scale, y + iy * scale, scale, scale, context.img[ix + context.width * iy]);
        }
    }
}

inline void dsl::ctx::print(const char *text, int32_t x, int32_t y, color c, uint32_t scale)
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
            drawLetter(text[place], x + 8 * place * scale, y + line * scale * 8, c, scale);
        place++;
    }
};

inline void dsl::ctx::print(int32_t number, int32_t x, int32_t y, color c, uint32_t scale)
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