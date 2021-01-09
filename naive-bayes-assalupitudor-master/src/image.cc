// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/image.h>


namespace bayes {

    Image::Image() = default;

    //operator over loading
    istream& operator>>(istream& is, Image& image) {
        char c;
        for (size_t row = 0; row < kImageSize; ++row) {
            for (size_t col = 0; col < kImageSize; ++col) {
                if (is.get(c)) {
                    if (c == ' ') {
                        image.pixels_[row][col] = 0;
                    } else {
                        image.pixels_[row][col] = 1;
                    }
                }
            }
        }
        return is;
    }

    //returns pixel at specified location
    int Image::GetPixel(int row, int col) {
        return pixels_[row][col];
    }

}  // namespace bayes