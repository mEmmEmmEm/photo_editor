#include "image_processing.h"
#include <cstring>
#include <cmath>
#include <iostream>

using namespace std;

void invert_colors(unsigned char* img, int width, int height, int channels) {
    int size = width * height * channels;
    for (int i = 0; i < size; i++) {
        img[i] = 255 - img[i];
    }
}

void grayscale(unsigned char* img, int width, int height, int channels) {
    if (channels < 3) return;

    for (int i = 0; i < width * height; i++) {
        int idx = i * channels;
        unsigned char r = img[idx];
        unsigned char g = img[idx + 1];
        unsigned char b = img[idx + 2];
        unsigned char gray = static_cast<unsigned char>(0.299 * r + 0.587 * g + 0.114 * b);
        img[idx] = img[idx + 1] = img[idx + 2] = gray;
    }
}

void brightness(unsigned char* img, int width, int height, int channels, int value) {
    int size = width * height * channels;
    for (int i = 0; i < size; i++) {
        int v = img[i] + value;
        if (v < 0) v = 0;
        if (v > 255) v = 255;
        img[i] = static_cast<unsigned char>(v);
    }
}

void contrast(unsigned char* img, int width, int height, int channels, float factor) {
    // Формула контраста: newColor = (color - 128)*factor + 128
    int size = width * height * channels;
    for (int i = 0; i < size; i++) {
        int v = static_cast<int>((img[i] - 128) * factor + 128);
        if (v < 0) v = 0;
        if (v > 255) v = 255;
        img[i] = static_cast<unsigned char>(v);
    }
}

void rotate(unsigned char** img, int* width, int* height, int channels, int angle) {
    if (angle != 90 && angle != 180 && angle != 270) {
        cerr << "Unsupported rotation angle: " << angle << endl;
        return;
    }

    int w = *width;
    int h = *height;
    int new_w = (angle == 180) ? w : h;
    int new_h = (angle == 180) ? h : w;
    unsigned char* rotated = new unsigned char[new_w * new_h * channels];

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            for (int c = 0; c < channels; c++) {
                int src_idx = (y * w + x) * channels + c;
                int dst_idx;

                switch (angle) {
                    case 90:
                        dst_idx = ((x) * new_w + (new_w - y - 1)) * channels + c;
                        break;
                    case 180:
                        dst_idx = ((new_h - y - 1) * new_w + (new_w - x - 1)) * channels + c;
                        break;
                    case 270:
                        dst_idx = ((new_h - x - 1) * new_w + y) * channels + c;
                        break;
                    default:
                        dst_idx = src_idx; 
                        break;
                }

                rotated[dst_idx] = (*img)[src_idx];
            }
        }
    }

    delete[] *img;
    *img = rotated;
    *width = new_w;
    *height = new_h;
}

void flip(unsigned char* img, int width, int height, int channels, const string& direction) {
    if (direction != "horizontal" && direction != "vertical") {
        cerr << "Unsupported flip direction: " << direction << endl;
        return;
    }

    unsigned char* temp = new unsigned char[width * height * channels];
    memcpy(temp, img, width * height * channels);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int src_idx = (y * width + x) * channels;
            int dst_x = (direction == "horizontal") ? (width - x - 1) : x;
            int dst_y = (direction == "vertical") ? (height - y - 1) : y;
            int dst_idx = (dst_y * width + dst_x) * channels;

            for (int c = 0; c < channels; c++) {
                img[dst_idx + c] = temp[src_idx + c];
            }
        }
    }

    delete[] temp;
}

void apply_filter(const std::string& filter_name, const Params& params,
                  unsigned char** img, int* width, int* height, int channels) {
    if (filter_name == "invert") {
        invert_colors(*img, *width, *height, channels);
    } else if (filter_name == "grayscale") {
        grayscale(*img, *width, *height, channels);
    } else if (filter_name == "brightness") {
        int val = 0;
        if (params.count("value")) {
            val = stoi(params.at("value"));
        }
        brightness(*img, *width, *height, channels, val);
    } else if (filter_name == "contrast") {
        float val = 1.0f;
        if (params.count("value")) {
            val = stof(params.at("value"));
        }
        contrast(*img, *width, *height, channels, val);
    } else if (filter_name == "rotate") {
        int angle = 0;
        if (params.count("angle")) {
            angle = stoi(params.at("angle"));
        }
        rotate(img, width, height, channels, angle);
    } else if (filter_name == "flip") {
        string dir = "horizontal";
        if (params.count("direction")) {
            dir = params.at("direction");
        }
        flip(*img, *width, *height, channels, dir);
    } else {
        cerr << "Unknown filter: " << filter_name << endl;
    }
}
