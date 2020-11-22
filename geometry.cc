#ifdef NDEBUG
const bool debug = false;
#else
const bool debug = true;
#endif // NDEBUG

/* TODO sensownosc makra */
#define safe_assert(expression) \
    do { \
        if (debug) { \
            assert(expression); \
        } else { \
            if (!(expression)) \
                exit(1); \
        } \
    } while (false)

#include <cassert>
#include <cstdlib>
#include "geometry.h"


Vector::Vector(long x, long y)
    : x_coordinate(x)
    , y_coordinate(y) {}

Vector::Vector(const Position& pos)
    : x_coordinate(pos.x())
    , y_coordinate(pos.y()) {}

long Vector::x() const {
    return x_coordinate;
}

long Vector::y() const {
    return y_coordinate;
}

Vector Vector::reflection() const {
    return Vector(y_coordinate, x_coordinate);
}

Vector& Vector::operator+=(const Vector& vec) {
    x_coordinate += vec.x();
    y_coordinate += vec.y();
    return *this;
}

Position::Position(long x, long y)
    : x_coordinate(x)
    , y_coordinate(y) {}

Position::Position(const Vector& vec)
    : x_coordinate(vec.x())
    , y_coordinate(vec.y()) {}

long Position::x() const {
    return x_coordinate;
}

long Position::y() const {
    return y_coordinate;
}

Position Position::reflection() const {
    return Position(y_coordinate, x_coordinate);
}

const Position& Position::origin() {
    static const Position orig(0, 0);
    return orig;
}

Position& Position::operator+=(const Vector& vec) {
    x_coordinate += vec.x();
    y_coordinate += vec.y();
    return *this;
}

Rectangle::Rectangle(long width, long height, Position pos)
    : w(width)
    , h(height)
    , left_bottom_corner(pos)
    /* TODO czy nie robic wciecia tutaj */
    {safe_assert(width > 0 && height > 0);}

Rectangle::Rectangle(long width, long height) :
    Rectangle(width, height, {0, 0})
    {safe_assert(width > 0 && height > 0);}

long Rectangle::width() const {
    return w;
}

long Rectangle::height() const {
    return h;
}

const Position& Rectangle::pos() const {
    return left_bottom_corner;
}

long Rectangle::area() const {
    return width() * height();
}

Rectangle Rectangle::reflection() const{
    return Rectangle{h, w, left_bottom_corner.reflection()};
}

Rectangle& Rectangle::operator+=(const Vector& vec) {
    left_bottom_corner += vec;
    return *this;
}

Rectangles::Rectangles(std::initializer_list<Rectangle> initializer_list)
    : rectangles(initializer_list) {}

size_t Rectangles::size() const {
    return rectangles.size();
}

const Rectangle& Rectangles::operator[](long i) const {
    safe_assert(i >= 0 && i < size());
    return rectangles[i];
}

Rectangle& Rectangles::operator[](long i) {
    safe_assert(i >= 0 && i < size());
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
    safe_assert(horizontal_merge_possible(rect1, rect2));
    return {rect1.width(), rect1.height() + rect2.height(),
            rect1.pos()};
}

Rectangle merge_vertically(const Rectangle& rect1, const Rectangle& rect2) {
    safe_assert(vertical_merge_possible(rect1, rect2));
    return {rect1.width() + rect2.width(), rect1.height(), rect1.pos()};
}

Rectangle merge_all(const Rectangles& rects) {
    Rectangle result = rects.rectangles[0];
    for (auto it = rects.rectangles.begin() + 1,
            end = rects.rectangles.end(); it < end; ++it) {
        safe_assert(horizontal_merge_possible(result, *it) ||
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
    for (size_t i = 0; i < rects1.size(); ++i) {
        if (!(rects1[i] == rects2[i]))
            return false;
    }
    return true;
}

Position operator+(const Vector& vec, const Position& pos) {
    return pos + vec;
}

Position operator+(const Position& pos, const Vector& vec) {
    return {pos.x() + vec.x(), pos.y() + vec.y()};
}

Vector operator+(const Vector& vec1, const Vector& vec2) {
    return {vec1.x() + vec2.x(), vec1.y() + vec2.y()};
}

Rectangle operator+(const Rectangle& rect, const Vector& vec) {
    return {rect.width(), rect.height(), rect.pos() + vec};
}

Rectangle operator+(const Vector& vec, const Rectangle& rect) {
    return rect + vec;
}

Rectangles operator+(const Rectangles& rects, const Vector& vec) {
    Rectangles new_rects(rects);
    new_rects += vec;
    return new_rects;
}

Rectangles operator+(Rectangles&& rects, const Vector& vec) {
    Rectangles new_rects(std::move(rects));
    new_rects += vec;
    return new_rects;
}

Rectangles operator+(const Vector& vec, const Rectangles& rects) {
    return rects + vec;
}

Rectangles operator+(const Vector& vec, Rectangles&& rects) {
    return std::move(rects) + vec;
}