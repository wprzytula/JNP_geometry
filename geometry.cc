#include <cassert>
#include "geometry.h"

Position::Position(const Vector& vec)
    : x_coord(vec.x()), y_coord(vec.y()) {}

const Position& Position::origin() {
    static const Position orig(0, 0);
    return orig;
}

Position& Position::operator+=(const Vector& vec) {
    x_coord += vec.x();
    y_coord += vec.y();
    return *this;
}

Vector& Vector::operator+=(const Vector& vec) {
    x_coord += vec.x();
    y_coord += vec.y();
    return *this;
}

Rectangle::Rectangle(Rectangle::coord_t width, Rectangle::coord_t height, Position pos)
    : w(width), h(height), left_bottom_corner(pos) {
    assert(width > 0 && height > 0);
}

Rectangle::Rectangle(Rectangle::coord_t width, Rectangle::coord_t height) :
    Rectangle(width, height, {0, 0}) {
    assert(width > 0 && height > 0);
}

Rectangle& Rectangle::operator+=(const Vector& vec) {
    left_bottom_corner += vec;
    return *this;
}

const Rectangle& Rectangles::operator[](std::vector<Rectangle>::size_type i) const {
    assert(i >= 0 && i < size());
    return rectangles[i];
}

Rectangle& Rectangles::operator[](std::vector<Rectangle>::size_type i) {
    assert(i >= 0 && i < size());
    return rectangles[i];
}

Rectangles& Rectangles::operator+=(const Vector& vec) {
    for (auto it = rectangles.begin(); it < rectangles.end(); ++it) {
        *it += vec;
    }
    return *this;
}

bool horizontal_merge_possible(const Rectangle& rect1, const Rectangle& rect2) {
    return (rect1.width() == rect2.width() && rect1.pos().x() == rect2.pos().x() &&
            rect1.pos().y() + rect1.height() == rect2.pos().y());
}

bool vertical_merge_possible(const Rectangle& rect1, const Rectangle& rect2) {
    return (rect1.height() == rect2.height() && rect1.pos().y() == rect2.pos().y() &&
            rect1.pos().x() + rect1.width() == rect2.pos().x());
}

Rectangle merge_horizontally(const Rectangle& rect1, const Rectangle& rect2) {
    assert(horizontal_merge_possible(rect1, rect2));
    return {rect1.width(), rect1.height() + rect2.height(),
            rect1.pos()};
}

Rectangle merge_vertically(const Rectangle& rect1, const Rectangle& rect2) {
    assert(vertical_merge_possible(rect1, rect2));
    return {rect1.width() + rect2.width(), rect1.height(), rect1.pos()};
}

Rectangle merge_all(const Rectangles& rects) {
    Rectangle result = rects.rectangles[0];
    for (auto it = rects.rectangles.begin() + 1,
            end = rects.rectangles.end(); it < end; ++it) {
        assert(horizontal_merge_possible(result, *it) ||
               vertical_merge_possible(result, *it));
        if (horizontal_merge_possible(result, *it)) {
            result = merge_horizontally(result, *it);
        } else {
            /* Vertical merge possible */
            result = merge_vertically(result, *it);
        }
    }
    return result;
}

bool operator==(const Position& pos1, const Position& pos2) {
    return pos1.x() == pos2.x() && pos1.y() == pos2.y();
}

bool operator==(const Vector& vec1, const Vector& vec2) {
    return vec1.x() == vec2.x() && vec1.y() == vec2.y();
}

bool operator==(const Rectangle& rec1, const Rectangle& rec2) {
    return rec1.pos() == rec2.pos() &&
           rec1.width() == rec2.width() && rec1.height() == rec2.height();
}

bool operator==(const Rectangles& rects1, const Rectangles& rects2) {
    if (rects1.size() != rects2.size())
        return false;
    for (std::vector<Rectangle>::size_type i = 0; i < rects1.size(); ++i) {
        if (!(rects1[i] == rects2[i]))
            return false;
    }
    return true;
}
