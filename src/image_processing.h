 #ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <string>
#include <unordered_map>

using Params = std::unordered_map<std::string, std::string>;

void invert_colors(unsigned char* img, int width, int height, int channels); //инверсия (негатив)
void grayscale(unsigned char* img, int width, int height, int channels); //чб
void brightness(unsigned char* img, int width, int height, int channels, int value); //яркость
void contrast(unsigned char* img, int width, int height, int channels, float factor); //контраст
void rotate(unsigned char** img, int* width, int* height, int channels, int angle); //пооврот по часовой стрелке
void flip(unsigned char* img, int width, int height, int channels, const std::string& direction); //отражение (горизонтальное или вертикальное)

void apply_filter(const std::string& filter_name, const Params& params, unsigned char** img, int* width, int* height, int channels);

#endif // IMAGE_PROCESSING_H
