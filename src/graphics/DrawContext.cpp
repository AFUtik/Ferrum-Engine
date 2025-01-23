#include "DrawContext.hpp"

DrawContext::DrawContext() {

}

#include "DrawContext.hpp"

DrawContext::~DrawContext() {
    delete chunk_renderer;
    delete entity_renderer;
}