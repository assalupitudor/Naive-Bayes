// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef BAYES_IMAGE_H_
#define BAYES_IMAGE_H_

#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>

using std::vector;
using std::istream;

namespace bayes {

    constexpr size_t kImageSize = 28;

    class Image {
    private:
        int pixels_[kImageSize][kImageSize];

    public:
        Image();
        int GetPixel(int row, int col);
        friend istream& operator>>(istream& is, Image& image);
    };

}  // namespace bayes

#endif  // BAYES_IMAGE_H_