#include <iostream>
#include "geometry.h"

using namespace std;

Vector::Vector(int x, int y) {
    x_coordinate = x;
    y_coordinate = y;
}

int Vector::x() {
    return x_coordinate;
}

int Vector::y() {
    return y_coordinate;
}

Vector Vector::reflection() {
    return Vector(y_coordinate, x_coordinate);
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

int Position::x() {
    return x_coordinate;
}

int Position::y() {
    return y_coordinate;
}

Position Position::reflection() {
    return Position(y_coordinate, x_coordinate);
}

Position Position::origin() {
    return orig;
}

bool Position::operator==(Position pos) {
    return (x_coordinate == pos.x() && y_coordinate == pos.y());
}

Position *Position::operator+=(Vector vec) {
    x_coordinate += vec.x();
    y_coordinate += vec.y();
    return this;
}
