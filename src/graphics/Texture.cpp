#include "Texture.hpp"

#include "GL/glew.h"

Texture::Texture(unsigned int id, int width, int height, unsigned char* image_data) : id(id), width(width), height(height), image_data(image_data) {}

void Texture::flipImageVertically() {
    int row_size = width * 4;  // Размер одной строки изображения
    unsigned char* temp_row = new unsigned char[row_size];

    for (int y = 0; y < height / 2; ++y) {
        unsigned char* top_row = image_data + y * row_size;
        unsigned char* bottom_row = image_data + (height - 1 - y) * row_size;

        // Копируем верхнюю строку во временный буфер
        memcpy(temp_row, top_row, row_size);
        // Меняем строки местами
        memcpy(top_row, bottom_row, row_size);
        memcpy(bottom_row, temp_row, row_size);
    }

    free(temp_row);  // Освобождаем временный буфер
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, id);
}

Texture::~Texture() {
	free(image_data);
	glDeleteTextures(1, &id);
}
