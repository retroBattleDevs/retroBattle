#include "headers/textures/AsciiTexture.h"

AsciiTexture::AsciiTexture(int w, int h) : width(w), height(h), grid(h, std::string(w, ' ')) {
    //hello there
}

void AsciiTexture::fillRow(int index, const std::string& content){
    if (index >= 0 && index < height) {
        grid[index] = content.substr(0, width);

        if (grid[index].length() < width) {
            grid[index].append(width - grid[index].length(), ' ');
        }
    }
}

void AsciiTexture::printTexture(int y, int x) const{
    int startY = y - (height / 2);
    int startX = x - (width / 2);

    for (int i = 0; i < height; ++i) {
        mvprintw(startY + i, startX, "%s", grid[i].c_str());
    }
}
