// Copyright 2020 [Your Name]. All rights reserved.

#include <bayes/classifier.h>
#include <bayes/model.h>

#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <vector>


namespace bayes {

    Model::Model() = default;

    void Model::train(const string& tr_images_filename,
                      const string& tr_labels_filename) {
        tr_labels = Classifier::ParseLabels(tr_labels_filename);
        std::cout << "finished parsing training labels" << std::endl;

        tr_images = Classifier::ParseImages(tr_images_filename);
        std::cout << "finished parsing training images" << std::endl;
        priors.resize(kNumClasses);
        for (size_t i = 0; i < tr_images.size(); ++i) {
            size_t label = tr_labels[i];
            priors[label]++;
            Image image = tr_images[i];
            for (size_t row = 0; row < kImageSize; ++row) {
                for (size_t col = 0; col < kImageSize; ++col) {
                    ++conditional_probs[row][col][label][image.GetPixel(row, col)];
                }
            }
        }
        // convert from simple counts to probabilities
        for (size_t label = 0; label < kNumClasses; ++label) {
            priors[label] /= tr_images.size();
            for (size_t row = 0; row < kImageSize; ++row) {
                for (size_t col = 0; col < kImageSize; ++col) {
                    for (size_t shade = 0; shade < kNumShades; ++shade) {
                        conditional_probs[row][col][label][shade] =
                                (conditional_probs[row][col][label][shade] + k_smoothing) /
                                (2 * k_smoothing + priors[label]);
                    }
                }
            }
        }
    }


    double Model::GetPrior(int label) {
        return priors[label];
    }

    double Model::GetConditionalProb(int row, int col, int label, int shade) {
        return conditional_probs[row][col][label][shade];
    }

    //operator overloading to return conditional probability
    ostream& operator<<(ostream& os, Model& model) {
        for (size_t label = 0; label < 10; label++) {
            os << std::to_string(model.priors[label]) + " ";
        }
        for (size_t label = 0; label < kNumClasses; label++) {
            os << "\n";
            for (size_t row = 0; row < kImageSize; row++) {
                for (size_t col = 0; col < kImageSize; col++) {
                    for (size_t shade = 0; shade < kNumShades; shade++) {
                        os << std::to_string(model.conditional_probs[row][col][label][shade]) + " ";
                    }
                }
            }
        }
        return os;
    }

    //operator overloading to return input stream 
    istream& operator>>(istream& is, Model& model) {
        string value;
        for (size_t label = 0; label < kNumClasses; label++) {
            if (getline(is, value, ' ')) {
                model.priors.push_back(std::stod(value));
            }
        }
        for (size_t label = 0; label < kNumClasses; label++) {
            for (size_t row = 0; row < kImageSize; row++) {
                for (size_t col = 0; col < kImageSize; col++) {
                    for (size_t shade = 0; shade < kNumShades; shade++) {
                        if (getline(is, value, ' ')){
                            model.conditional_probs[row][col][label][shade] = std::stod(value);
                        }
                    }
                }
            }
        }
        return is;
    }


}  // namespace bayes