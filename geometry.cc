#include "geometry.h"

Vector::Vector(int x, int y) {
    x_coordinate = x;
    y_coordinate = y;
}

int Vector::x() const {
    return x_coordinate;
}

int Vector::y() const {
    return y_coordinate;
}

Vector Vector::reflection() {
    return Vector(y_coordinate, x_coordinate);
}

bool Vector::operator==(const Vector &vec) const {
    return (x_coordinate == vec.x() && y_coordinate == vec.y());
}

Vector& Vector::operator+=(const Vector& vec) {
    x_coordinate += vec.x();
    y_coordinate += vec.y();
    return *this;
}

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
    static const Position orig(0, 0);
    return orig;
}

bool Position::operator==(const Position& pos) const {
    return (x_coordinate == pos.x() && y_coordinate == pos.y());
}

Position& Position::operator+=(const Vector& vec) {
    x_coordinate += vec.x();
    y_coordinate += vec.y();
    return *this;
}
