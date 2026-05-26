#pragma once
#ifndef ASCIITEXTURE_H
#define ASCIITEXTURE_H

#include <iostream>
#include <vector>
#include <string>
#include "external_libraries/PDCurses/curses.h"

class AsciiTexture {
private:
    int width;
    int height;
    std::vector<std::string> grid;

public:
    AsciiTexture(int w, int h);
    void fillRow(int index, const std::string& content);
    void printTexture(int y,int x) const;
};

#endif