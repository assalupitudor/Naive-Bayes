// Copyright (c) 2020 [Your Name]. All rights reserved.

#ifndef BAYES_MODEL_H_
#define BAYES_MODEL_H_

#include "image.h"
#include <nlohmann/json.hpp>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::ostream;

namespace bayes {

// 0-9 inclusive.
    constexpr size_t kNumClasses = 10;
// Shaded or not shaded.
    constexpr size_t kNumShades = 2;
// Laplace smoothing constant
    const double k_smoothing = 1;

/**
 * Represents a Naive Bayes classification model for determining the
 * likelihood that an individual pixel for an individual class is
 * white or black.
 */
    class Model {
    private:
        vector<Image> tr_images;
        vector<int> tr_labels;
        vector<double> priors;
        double conditional_probs[kImageSize][kImageSize][kNumClasses][kNumShades]{};

    public:
        Model();
        void train(const string& tr_images_filename, const string& tr_labels_filename);
        double GetPrior(int label);
        double GetConditionalProb(int row, int col, int label, int shade);
        friend ostream& operator<<(ostream& os, Model& model);
        friend istream& operator>>(istream& is, Model& model);
    };

}  // namespace bayes


#endif  // BAYES_MODEL_H_