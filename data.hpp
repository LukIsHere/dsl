/*

*/

#pragma once
#include "stdint.h"
// maybe one day i will be
// able to do it without
// using stl but i can't rn
#include <fstream>
#include <iostream>
#include <string>

namespace dsl
{
    class dataArray
    {
    private:
        uint8_t *data;
        uint32_t size;

    public:
        uint8_t *getData();
        uint32_t getSize();
        dataArray();
        dataArray(std::string filename);
        dataArray(uint8_t *data, uint32_t size);
        dataArray(dataArray &data);
        ~dataArray();
        void save(std::string filename);
        void reSize(uint32_t size);
        void push(uint8_t value);
        bool getBit(uint32_t place, uint8_t bit);
        uint8_t &operator[](uint32_t place);
    };

    uint8_t staticDSize(uint32_t value); // 0101101
    // like string view but kinda diffrent
    class PbView
    {
    private:
        uint32_t place = 0;
        uint8_t bit = 0;
        uint8_t nowValue = 0;
        uint8_t *data;

    public:
        PbView(dataArray &data);
        PbView(uint8_t *data);
        // takes the pointer to start of the array
        void reset();
        bool readBit();
        uint32_t readDynamic();
        uint32_t readStatic(uint8_t size);
        // advanced
        template <typename T>
        T readCast();
    };
    // writes data
    class PbWriter
    {
    private:
        uint8_t current;
        uint8_t bit;
        dataArray data;

    public:
        PbWriter();
        void clear();
        void writeBit(bool value);
        void writeDynamic(uint32_t value);
        void writeStatic(uint32_t value, uint8_t size);
        // advanced
        template <typename T>
        // do not cast class/struct that contains pointers
        void writeCast(T data);
        dataArray exportData();
    };
}

uint8_t *dsl::dataArray::getData()
{
    return data;
};
uint32_t dsl::dataArray::getSize()
{
    return size;
};
dsl::dataArray::dataArray()
{
    this->size = 0;
    this->data = nullptr;
}
dsl::dataArray::dataArray(std::string filename)
{
    std::ifstream infile(filename, std::ios::binary);
    if(!infile.is_open()){
        throw std::runtime_error("Failed to open file: " + filename);
    }
    infile.seekg(0, infile.end);
    size_t file_size = infile.tellg();
    infile.seekg(0, infile.beg);
    data = new uint8_t[file_size];
    infile.read(reinterpret_cast<char *>(data), file_size);
    infile.close();
};
dsl::dataArray::dataArray(uint8_t *data, uint32_t size)
{
    this->size = size;
    if (this->size == 0)
        this->data = nullptr;
    else
    {
        this->data = new uint8_t[size];
        for (uint32_t i = 0; i < size; i++)
        {
            this->data[i] = data[i];
        }
    }
};
dsl::dataArray::dataArray(dataArray &data)
{
    this->size = data.size;
    if (this->size == 0)
        this->data = nullptr;
    else
    {
        this->data = new uint8_t[this->size];
        for (uint32_t i = 0; i < this->size; i++)
        {
            this->data[i] = data.data[i];
        }
    }
};
dsl::dataArray::~dataArray()
{
    if (this->data == 0 || this->data == nullptr)
        return;
    else
    {
        delete[] this->data;
    }
};
void dsl::dataArray::save(std::string filename)
{
    std::ofstream outfile(filename, std::ios::binary);
    if(!outfile.is_open()){
        throw std::runtime_error("Failed to write file: " + filename);
    }
    outfile.write(reinterpret_cast<char *>(this->data), size);
    outfile.flush();
    outfile.close();
};
void dsl::dataArray::reSize(uint32_t size)
{
    if (this->size == size)
        return;

    if (size == 0)
    {
        if (this->data == nullptr)
            return;

        delete[] this->data;
        this->data = nullptr;

        return;
    }
    uint8_t *newData = new uint8_t[size];
    for (uint32_t i = 0; i < size; i++)
    {
        if (this->size > i)
            newData[i] = this->data[i];
        else
            newData[i] = 0;
    }
    delete[] this->data;
    this->data = newData;
    this->size = size;
};
void dsl::dataArray::push(uint8_t value)
{
    reSize(this->size + 1);
    data[this->size - 1] = value;
};
bool dsl::dataArray::getBit(uint32_t place, uint8_t bit)
{
    if (place >= this->size)
        return false;
    return bool((this->data[place] >> (bit & 0b00000111)) & 0b00000001);
};
uint8_t &dsl::dataArray::operator[](uint32_t place)
{
    if (place >= this->size)
        throw "you are trying to access value that is not inside this dataArray";
    return this->data[place];
};

// helper function

// tells you how much bytes you need for a number
uint8_t dsl::staticDSize(uint32_t value)
{
    if (value < 2)
        return 1;
    else
    {
        uint32_t candidate = 2;
        uint32_t possible = 4;
        while (true)
        {
            if (value < possible)
                return candidate;
            candidate++;
            possible <<= 1;
        }
    }
}

// PbView

dsl::PbView::PbView(dataArray &data) : data(data.getData())
{
    reset();
};
dsl::PbView::PbView(uint8_t *data) : data(data)
{
    reset();
};
void dsl::PbView::reset()
{
    place = 0;
    bit = 0b10000000;
    nowValue = data[place];
};
// reads one bit
bool dsl::PbView::readBit()
{
    if (bit == 0)
    {
        place++;
        nowValue = data[place];
        bit = 0b10000000;
    }
    bool out = nowValue & (bit);
    bit >>= 1;
    return out;
};
// reads data like 11110 where 110 is 3 and 0 is 1
uint32_t dsl::PbView::readDynamic()
{
    uint32_t out = 1;
    while (readBit())
    {
        // increment until get 0 bit
        out++;
    }
    return out;
};
// reads data like 10110 where 101(3) is 5 and 0(1) is 1
uint32_t dsl::PbView::readStatic(uint8_t size)
{
    uint32_t out = 0;
    for (uint8_t i = 0; i < size; i++)
    {
        out <<= 1;
        out |= (uint32_t)readBit();
    }
    return out;
};

template <typename T>
T dsl::PbView::readCast()
{
    T out;
    uint32_t size = sizeof(T);
    uint8_t *outPTR = (uint8_t *)(&out);
    for (uint32_t i = 0; i < size; i++)
    {
        outPTR[i] = readStatic(8);
    }
    return out;
};

// PbWriter
dsl::PbWriter::PbWriter()
{
    clear();
};
// clears everyting
void dsl::PbWriter::clear()
{
    data.reSize(0);
    current = 0;
    bit = 0b10000000;
};
// writes exactly one bit
void dsl::PbWriter::writeBit(bool value)
{
    if (bit == 0)
    {
        bit = 0b10000000;
        data.push(current);
        current = 0;
    }
    if (value)
        current |= bit;
    bit >>= 1;
};
// writes value like 1111111110 where 1 is 0 and 4 is 1110
void dsl::PbWriter::writeDynamic(uint32_t value)
{
    for (uint32_t i = 0; i < value - 1; i++)
    {
        writeBit(true);
    }
    if (value != 0)
        writeBit(false);
};
// wites value like 101001 where 3(4) is 100 and 3(5) is 101
void dsl::PbWriter::writeStatic(uint32_t value, uint8_t size)
{
    for (uint8_t i = 0; i < size; i++)
    {
        writeBit((value >> (size - (1 + i))) & 1);
    }
};

template <typename T>
void dsl::PbWriter::writeCast(T data)
{
    T value = data;
    uint8_t *valuePTR = (uint8_t *)(&value);
    uint32_t size = sizeof(T);
    for (uint32_t i = 0; i < size; i++)
    {
        writeStatic(valuePTR[i], 8);
    }
};

// gives you data you've written
dsl::dataArray dsl::PbWriter::exportData()
{
    dataArray out = data;
    if (bit != 0b10000000)
        out.push(current);
    return out;
};