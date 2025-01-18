#include "Texture_loader.hpp"

#include <iostream>
#include "GL/glew.h"
#include "png.h"
#include "Texture.hpp"


int _png_load(const char* file, int* width, int* height, png_byte **image_data) {
    FILE* f;
    int is_png, bit_depth, color_type, row_bytes;
    png_infop info_ptr, end_info;
    png_uint_32 t_width, t_height;
    png_byte header[8];
    png_bytepp row_pointers;
    png_structp png_ptr;
    GLuint texture;
    int alpha;

    if (!(f = fopen(file, "rb"))) {
        std::cerr << "File could not be opened: " << file << std::endl;
        return 0;
    }

    fread(header, 1, 8, f);
    is_png = ~png_sig_cmp(header, 0, 8);
    if (!is_png) {
        std::cerr << "Not a PNG file: " << file << std::endl;
        fclose(f);
        return 0;
    }

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        std::cerr << "Failed to create PNG read struct" << std::endl;
        fclose(f);
        return 0;
    }

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        std::cerr << "Failed to create PNG info struct" << std::endl;
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        fclose(f);
        return 0;
    }

    end_info = png_create_info_struct(png_ptr);
    if (!end_info) {
        std::cerr << "Failed to create PNG end info struct" << std::endl;
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(f);
        return 0;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        std::cerr << "Error during PNG reading" << std::endl;
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(f);
        return 0;
    }

    png_init_io(png_ptr, f);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    png_get_IHDR(png_ptr, info_ptr, &t_width, &t_height, &bit_depth, &color_type, NULL, NULL, NULL);
    *width = t_width;
    *height = t_height;

    png_read_update_info(png_ptr, info_ptr);
    row_bytes = png_get_rowbytes(png_ptr, info_ptr);

    *image_data = (png_byte*)malloc(row_bytes * t_height * sizeof(png_byte));
    if (!*image_data) {
        std::cerr << "Failed to allocate memory for image data" << std::endl;
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(f);
        return 0;
    }

    row_pointers = (png_bytepp)malloc(t_height * sizeof(png_bytep));
    if (!row_pointers) {
        std::cerr << "Failed to allocate memory for row pointers" << std::endl;
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        free(*image_data);
        fclose(f);
        return 0;
    }

    for (unsigned int i = 0; i < t_height; ++i) {
        row_pointers[t_height - 1 - i] = *image_data + i * row_bytes;
    }

    png_read_image(png_ptr, row_pointers);

    switch (png_get_color_type(png_ptr, info_ptr)) {
        case PNG_COLOR_TYPE_RGBA:
            alpha = GL_RGBA;
            break;
        case PNG_COLOR_TYPE_RGB:
            alpha = GL_RGB;
            break;
        default:
            std::cerr << "Color type not supported!" << std::endl;
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            return 0;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t_width, t_height, 0, alpha, GL_UNSIGNED_BYTE, (GLvoid*)*image_data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    free(row_pointers);
    fclose(f);

    return texture;
}

Texture* load_texture(std::string filename) {
    int width, height;
    png_byte *image_data;
    GLuint texture = _png_load(filename.c_str(), &width, &height, &image_data);
    if (texture == 0) {
        std::cerr << "Could not load texture " << filename << std::endl;
        return nullptr;
    }
    return new Texture(texture, width, height, image_data);
}