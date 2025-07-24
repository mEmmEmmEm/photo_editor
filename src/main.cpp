#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"
#include <iostream>
#include <vector>
#include <string>
#include "image_processing.h"
#include "filter_parser.h"

using namespace std;

int main(int argc, char* argv[]){
    if(argc < 4){
        cout << "Using: ./Debug/PhotoEditor input.jpg output.jpg filter:param=value, .." << endl;
        return 1;
    }
    const char* input_path = argv[1];
    const char* output_path = argv[2];
    int width, height, channels;
    unsigned char* img = stbi_load(input_path, &width, &height, &channels, 0);
    if(!img){
        cerr << "Error input" << endl;
        return 1;
    }

    unsigned char** img_ptr = &img;
    int* width_ptr = &width;
    int* height_ptr = &height;
    int w = width;
    int h = height;

    for(int i = 3; i < argc; i++){
        string filter_name;
        Params params;
        parse_filter_arg(argv[i], filter_name, params);
        apply_filter(filter_name, params, img_ptr, width_ptr, height_ptr, channels);
    }

    if(!stbi_write_jpg(output_path, width, height, channels, img, 100)){
        cerr << "Error saved" << endl;
        stbi_image_free(img);
        return 1;
    }

    stbi_image_free(img);
    return 0;

}