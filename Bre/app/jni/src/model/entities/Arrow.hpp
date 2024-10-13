//
// Created by Jonathan on 29/09/2024.
//

#ifndef BRE_ARROW_HPP
#define BRE_ARROW_HPP

#include "../../controller/components/Point2D.hpp"
#include "../../controller/components/Vector2D.hpp"

#include <stdexcept>

class Arrow {
    Point2D* center = nullptr;
    Vector2D* vector = nullptr;

public:
    Arrow() = default;

    void setCenter(int initial_input_x, int initial_input_y) {
        center = new Point2D(initial_input_x, initial_input_y);
    }

    void setVector(int final_input_x, int final_input_y) {
        if (center == nullptr)
            return;
        vector = new Vector2D((final_input_x - center->x)/2, (final_input_y - center->y)/2);
    }

    Point2D* getCenter() const {
        return center;
    }

    Vector2D* getVector() const {
        return vector;
    }

    Point2D getTip() const {
        if(center == nullptr || vector == nullptr)
            throw std::runtime_error("NullPointerException calling getTip() in Arrow.hpp: Arrow center or vector not initialized.");
        return Point2D(center->x + vector->x, center->y + vector->y);
    }

    Vector2D getDirection() const {
        if(vector == nullptr)
            throw std::runtime_error("NullPointerException calling getDirection() in Arrow.hpp: Arrow vector not initialized.");
        return Vector2D(vector->getNormalizedVector());
    }

    ~Arrow() {
        delete center;
        delete vector;
    }
};


#endif //BRE_ARROW_HPP
