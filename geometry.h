#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <cstdint>
#include <cassert>

/*
 * Popraw proszę operatory do takich, jak je opisałem tu w pliku .h
 * (const, referencje - NIE używaj wskaźników!)
 * */
class Position;

class Vector {
public:
    Vector(long x, long y);
    explicit Vector(const Position&);
    [[nodiscard]] long x() const;
    [[nodiscard]] long y() const;
    [[nodiscard]] Vector reflection() const;
    Vector& operator+=(const Vector&);
private:
    long x_coordinate;
    long y_coordinate;
};

class Position {
public:
    Position(long x, long y);
    explicit Position(const Vector&);
    [[nodiscard]] long x() const;
    [[nodiscard]] long y() const;
    [[nodiscard]] Position reflection() const;
    static const Position& origin();
    Position& operator+=(const Vector&);
private:
    long x_coordinate;
    long y_coordinate;
};


class Rectangle {
public:
    Rectangle(long width, long height, Position pos);
    Rectangle(long width, long height);
    [[nodiscard]] long width() const;
    [[nodiscard]] long height() const;
    [[nodiscard]] const Position & pos() const;
    [[nodiscard]] Rectangle reflection() const;
    Rectangle& operator+=(const Vector& vec);
    [[nodiscard]] int64_t area() const;
private:
    Position left_bottom_corner;
    long w;
    long h;
};

class Rectangles {
public:
    Rectangles() = default;
    Rectangles(std::initializer_list<Rectangle>);
    Rectangles(const Rectangles&) = default;
    Rectangles(Rectangles&&) noexcept = default;
    ~Rectangles() = default;
    Rectangles& operator=(const Rectangles&) = default;
    Rectangles& operator=(Rectangles&&) noexcept = default;
    const Rectangle& operator[](long i) const;
    Rectangle& operator[](long i);
    Rectangles& operator+=(const Vector& vec);
    [[nodiscard]] size_t size() const;
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

Rectangles operator+(Rectangles&& rects, const Vector& vec);

Rectangles operator+(const Vector& vec, const Rectangles& rects);

Rectangles operator+(const Vector& vec, Rectangles&& rects);

#endif // GEOMETRY_H