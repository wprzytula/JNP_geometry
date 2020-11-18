#include <iostream>
#include "geometry.h"

#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
using namespace std;

Vector::Vector(int x, int y) {
    x_coordinate = x;
    y_coordinate = y;
}

int Vector::x() const {
    return x_coordinate;
}

int Vector::y() {
    return y_coordinate;
}

Vector Vector::reflection() {
    return Vector(y_coordinate, x_coordinate);
}

Vector &Vector::operator+=(const Vector &) {
    return <#initializer#>;
}

bool Vector::operator==(Vector vec) {
    return (x_coordinate == vec.x() && y_coordinate == vec.y());
}

Vector *Vector::operator+=(Vector vec) {
    x_coordinate += vec.x();
    y_coordinate += vec.y();
    return this;
}

Position const Position::orig = Position(0, 0); // to zbędne, lepiej zrób to
                                                   // jako stałą statyczną
                                                   // w metodzie origin()

Position::Position(int x, int y) {
    x_coordinate = x;
    y_coordinate = y;
}

int Position::x() const {
    return x_coordinate;
}

int Position::y() const {
    return y_coordinate;
}

Position Position::reflection() {
    return Position(y_coordinate, x_coordinate);
}

Position Position::origin() {
    return orig;
}

Position &Position::operator+=(const Vector &) {
    return <#initializer#>;
}

bool operator==(const Position& pos1, const Position& pos2) {
    return pos1.x() == pos2.x() && pos1.y() == pos2.y();
}

/*
bool Position::operator==(Position pos) {
    return (x_coordinate == pos.x() && y_coordinate == pos.y());
}
*/

Position *Position::operator+=(Vector vec) {
    x_coordinate += vec.x();
    y_coordinate += vec.y();
    return this;
}



Rectangle::Rectangle(int width, int height, Position pos) : left_bottom_corner(pos),
left_top_corner({pos.x(), pos.y() + height}),
right_bottom_corner({pos.x() + width, pos.y()}),
right_top_corner({pos.x() + width, pos.y() + height}) {}

Rectangle::Rectangle(int width, int height) :
    Rectangle(width, height, {0, 0}) {}


int Rectangle::width() const {
    return right_bottom_corner.x() - left_bottom_corner.x();
}

int Rectangle::height() const {
    return left_top_corner.y() - left_bottom_corner.y();
}

const Position & Rectangle::pos() const {
    return left_bottom_corner;
}

#pragma ide diagnostic ignored "ArgumentSelectionDefects"
Rectangle Rectangle::reflection() {
    return Rectangle{{right_top_corner.y(), right_bottom_corner.x()},
                     {left_top_corner.y(), left_top_corner.x()},
                     {right_bottom_corner.y(), right_bottom_corner.x()},
                     {left_bottom_corner.y(), left_bottom_corner.x()}};
}

Rectangle::Rectangle(Position left_bottom_corner, Position right_bottom_corner,
                     Position left_top_corner, Position right_top_corner) :
                     left_bottom_corner(left_bottom_corner),
                     right_bottom_corner(right_bottom_corner),
                     left_top_corner(left_top_corner),
                     right_top_corner(right_top_corner) {}

Rectangle& Rectangle::operator+=(const Vector& vec) {
    left_bottom_corner += vec;
    left_top_corner += vec;
    right_bottom_corner += vec;
    right_top_corner += vec;
    return *this;
}

long Rectangle::area() {
    return width() * height();
}

Rectangles::Rectangles(std::initializer_list<Rectangle> initializer_list) :
    rectangles(initializer_list) {}

size_t Rectangles::size() const {
    return rectangles.size();
}

Rectangles::Rectangles() = default;

Rectangle& Rectangles::operator[](int i) {
    return rectangles[i];
}

const Rectangle& Rectangles::operator[](int i) const {
    return const_cast<Rectangle &>(rectangles[i]);
}

Rectangles& Rectangles::operator+=(const Vector& vec) {
    for (auto it = rectangles.begin(); it < rectangles.end(); ++it) {
        *it += vec;
    }
    return *this;
}

bool horizontal_merge_possible(const Rectangle& rect1, const Rectangle& rect2) {
    return (rect1.width() == rect2.width() && rect1.pos().x() == rect2.pos().x() &&
            rect1.pos().y() + rect1.height() == rect1.pos().y());
}

bool vertical_merge_possible(const Rectangle& rect1, const Rectangle& rect2) {
    return (rect1.height() == rect2.height() && rect1.pos().y() == rect2.pos().y() &&
            rect1.pos().x() + rect1.width() == rect1.pos().x());
}

Rectangle merge_horizontally(const Rectangle& rect1, const Rectangle& rect2) {
    if (!horizontal_merge_possible(rect1, rect2)) {
        // TODO - throw exception?
    }
    return {rect1.left_bottom_corner, rect1.right_bottom_corner,
            rect2.left_top_corner, rect2.right_top_corner};
}

Rectangle merge_vertically(const Rectangle& rect1, const Rectangle& rect2) {
    if (!vertical_merge_possible(rect1, rect2)) {
        // TODO - throw exception?
    }
    return {rect1.left_bottom_corner, rect2.right_bottom_corner,
            rect1.left_top_corner, rect2.right_top_corner};
}

Rectangle merge_all(const Rectangles& rectangles) {

}

Rectangle merge_all(Rectangles&& rectangles) {

}

bool operator==(const Rectangle& rec1, const Rectangle& rec2) {
    return rec1.pos() == rec2.pos() &&
           rec1.width() == rec2.width() && rec2.height() == rec2.height();
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

//TODO!
Position operator+(const Vector& vec, const Position& pos) {

}

Position operator+(const Position& pos, const Vector& vec) {

}

Vector operator+(const Vector& vec1, const Vector& vec2) {

}

Rectangle operator+(const Rectangle& rect, const Vector& vec) {
    return {rect.width(), rect.height(),
            {rect.pos().x() + vec.x(), rect.pos().y()}};
}
// TODO: which one? Below or above?
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
    Rectangles new_rects(rects);
    new_rects += vec;
    return new_rects;
}

Rectangles operator+(const Vector& vec, const Rectangles& rects) {
    return rects + vec;
}