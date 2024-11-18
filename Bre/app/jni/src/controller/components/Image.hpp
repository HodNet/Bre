//
// Created by Jonathan on 14/11/2024.
//

#ifndef BRE_IMAGE_HPP
#define BRE_IMAGE_HPP

#include "../../controller/components/Rectangle.hpp"
#include "../../res/images.hpp"

class Image : public Rectangle {

private:
    const char* filename = images::not_found;
    const float src_width = 0;
    const float src_height = 0;

public:
    Image() = default;
    Image(const Image& i) = default;
    Image(const float x, const float y, const float w, const float h, const char* file_name, const float file_width, const float file_height) :
        Rectangle(x, y, w, h), filename(file_name), src_width(file_width), src_height(file_height) {}

    const char* getFilename() const {
        return filename;
    }

    float getSrcWidth() const {
        return src_width;
    }

    float getSrcHeight() const {
        return src_height;
    }
};

#endif //BRE_IMAGE_HPP
