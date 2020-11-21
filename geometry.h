#pragma ide diagnostic ignored "modernize-use-nodiscard"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <cstdint>

/*
 * Popraw proszę operatory do takich, jak je opisałem tu w pliku .h
 * (const, referencje - NIE używaj wskaźników!)
 * */
class Position;

class Vector {
public:
    Vector(int32_t x, int32_t y);
    explicit Vector(const Position&);
//    explicit Vector(Position&&);
    [[nodiscard]] int32_t x() const;
    [[nodiscard]] int32_t y() const;
    Vector reflection() const;
    Vector& operator+=(const Vector&);
private:
    int32_t x_coordinate;
    int32_t y_coordinate;
};

class Position {
public:
    Position(int32_t x, int32_t y);
    explicit Position(const Vector&);
//    explicit Position(Vector&&);
    [[nodiscard]] int32_t x() const;
    [[nodiscard]] int32_t y() const;
    Position reflection() const;
    static Position origin();
    Position& operator+=(const Vector&);
private:
    int32_t x_coordinate;
    int32_t y_coordinate;
};


class Rectangle {
public:
    Rectangle(int32_t width, int32_t height, Position pos);
    Rectangle(int32_t width, int32_t height);
    int32_t width() const;
    int32_t height() const;
    const Position & pos() const;
    Rectangle reflection() const;
    Rectangle& operator+=(const Vector& vec);
    int64_t area() const;
    friend Rectangle merge_horizontally(const Rectangle& rect1, const Rectangle& rect2);
    friend Rectangle merge_vertically(const Rectangle& rect1, const Rectangle& rect2);
private:
    Position left_bottom_corner;
    Position right_bottom_corner;
    Position left_top_corner;
    Position right_top_corner;
    Rectangle(Position left_bottom_corner, Position right_bottom_corner,
            Position left_top_corner, Position right_top_corner);
};

class Rectangles {
public:
    Rectangles();
    Rectangles(std::initializer_list<Rectangle>);
    Rectangles(const Rectangles&);
    Rectangles(Rectangles&&);
    Rectangles& operator=(const Rectangles&) = default;
    Rectangles& operator=(Rectangles&&) = default;
    Rectangle& operator[](int32_t i);
    const Rectangle& operator[](int32_t i) const;
    size_t size() const;
    Rectangles& operator+=(const Vector& vec);
    friend Rectangle merge_all(const Rectangles& rectangles);
private:
    std::vector<Rectangle> rectangles;
};


Rectangle merge_horizontally(const Rectangle& rect1, const Rectangle& rect2);

Rectangle merge_vertically(const Rectangle& rect1, const Rectangle& rect2);

Rectangle merge_all(const Rectangles& rectangles);

bool operator==(const Position& pos1, const Position& pos2);

bool operator==(const Vector& vec1, const Vector& vec2);

bool operator==(const Rectangle& rect1, const Rectangle& rect2);

bool operator==(const Rectangles& rects1, const Rectangles& rects2);

Position operator+(const Vector& vec, const Position& pos);

Position operator+(const Position& pos, const Vector& vec);

Vector operator+(const Vector& vec1, const Vector& vec2);

Rectangle operator+(const Rectangle& rect, const Vector& vec);

Rectangle operator+(const Vector& vec, const Rectangle& rect);

Rectangles operator+(const Rectangles& rects, const Vector& vec);

Rectangles operator+(const Vector& vec, const Rectangles& rects);

#endif