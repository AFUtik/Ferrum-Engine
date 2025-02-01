#include "Guillotine.hpp"

bool GuillotinePacker::pack(Rectangle& tile) {
    auto bestIt = freeRectangles.end();
    for (auto it = freeRectangles.begin(); it != freeRectangles.end(); ++it) {
        if (it->canFit(tile.width, tile.height)) {
            if (bestIt == freeRectangles.end() || it->width * it->height < bestIt->width * bestIt->height) {
                bestIt = it;
            }
        }
    }
    if (bestIt == freeRectangles.end()) return false; 

    Rectangle usedRect(bestIt->x, bestIt->y, tile.width, tile.height);
    tile.x = usedRect.x;
    tile.y = usedRect.y;

    splitRectangle(*bestIt, usedRect);
    freeRectangles.erase(bestIt);
    return true;
}

void GuillotinePacker::splitRectangle(const Rectangle& freeRect, const Rectangle& usedRect) {
    // area to the right //
    if (freeRect.width > usedRect.width) {
        freeRectangles.push_back(Rectangle(
            freeRect.x + usedRect.width,
            freeRect.y,
            freeRect.width - usedRect.width,
            freeRect.height
        ));
    }
    
    // area at the bottom //
    if (freeRect.height > usedRect.height) {
        freeRectangles.push_back(Rectangle(
            freeRect.x,
            freeRect.y + usedRect.height,
            usedRect.width,
            freeRect.height - usedRect.height
        ));
    }
}