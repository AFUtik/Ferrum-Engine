#include "TextureHandler.hpp"

#include <iostream>
#include "Texture.hpp"

#include <stdlib.h>
#include <stdio.h>
#include "png.h"

int _png_load(const char* file, int* width, int* height, png_byte **image_data) {
    FILE* f;
    int is_png, bit_depth, color_type, row_bytes;
    png_infop info_ptr, end_info;
    png_uint_32 t_width, t_height;
    png_byte header[8];
    png_bytepp row_pointers;
    png_structp png_ptr;
    //GLuint texture;
    //int alpha;

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
            //alpha = GL_RGBA;
            break;
        case PNG_COLOR_TYPE_RGB:
            //alpha = GL_RGB;
            break;
        default:
            std::cerr << "Color type not supported!" << std::endl;
            png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
            return 0;
    }

    //glGenTextures(1, &texture);
    //glBindTexture(GL_TEXTURE_2D_ARRAY, texture);
    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //glTexImage2D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, t_width, t_height, 0, alpha, GL_UNSIGNED_BYTE, (GLvoid*)*image_data);
    //
    //glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    free(row_pointers);
    fclose(f);

    //return texture;
    return 1;
}

int _png_save(const char* file, int width, int height, png_byte *image_data) {
    FILE* fp = fopen(file, "wb");
    if (!fp) {
        perror("Failed to open the file.");
        return 0;
    }

    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        fclose(fp);
        return 0;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_write_struct(&png, nullptr);
        fclose(fp);
        return 0;
    }

    if (setjmp(png_jmpbuf(png))) {
        png_destroy_write_struct(&png, &info);
        fclose(fp);
        return 0;
    }

    png_init_io(png, fp);

    png_set_IHDR(
        png,
        info,
        width,
        height,
        8,  
        PNG_COLOR_TYPE_RGBA,  
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );

    png_write_info(png, info);

    png_bytep* rowPointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
    for (unsigned int y = 0; y < height; ++y) {
        rowPointers[y] = image_data + (height - 1 - y) * width * 4; // RGBA
    }
    png_write_image(png, rowPointers);
    png_write_end(png, nullptr);

    free(rowPointers);
    png_destroy_write_struct(&png, &info);
    fclose(fp);

    return 1;
}

Texture* load_texture_png(std::string filename) {
    int width, height;
    png_byte *image_data;
    unsigned int success = _png_load(filename.c_str(), &width, &height, &image_data);
    if (success == 0) {
        std::cerr << "Could not load texture " << filename << std::endl;
        return nullptr;
    }
    return new Texture(success, width, height, image_data);
}

bool save_texture_png(std::string filename, Texture* texture) {
    int width, height;
    png_byte *image_data;
    unsigned int success = _png_save(filename.c_str(), texture->width, texture->height, texture->image_data);
    if (success == 0) {
        std::cerr << "Could not load texture " << filename << std::endl;
        return false;
    }
    return true;
}