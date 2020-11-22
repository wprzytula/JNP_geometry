#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>

/* TODO czy konstruktorow w klasach wystarczy i czy sa dobre */
/* TODO czy wszystkie slowka const sa dobrze podstawiane */
/* TODO wybor long jako typu */

/* TODO czy samo class Position czy wszytkie klasy zadeklarowac tutaj */
class Position;

class Vector {
public:
    Vector(long x, long y);
    explicit Vector(const Position& pos);
    /* TODO czy dawac nodiscard */
    [[nodiscard]] long x() const;
    [[nodiscard]] long y() const;
    [[nodiscard]] Vector reflection() const;
    Vector& operator+=(const Vector& vec);
private:
    long x_coordinate;
    long y_coordinate;
};

class Position {
public:
    Position(long x, long y);
    explicit Position(const Vector& vec);
    [[nodiscard]] long x() const;
    [[nodiscard]] long y() const;
    [[nodiscard]] Position reflection() const;
    static const Position& origin();
    Position& operator+=(const Vector& vec);
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
    [[nodiscard]] const Position& pos() const;
    [[nodiscard]] long area() const;
    [[nodiscard]] Rectangle reflection() const;
    Rectangle& operator+=(const Vector& vec);
private:
    Position left_bottom_corner;
    long w;
    long h;
};

class Rectangles {
public:
    Rectangles() = default;
    Rectangles(std::initializer_list<Rectangle> rects);
    Rectangles(const Rectangles& rects) = default;
    Rectangles(Rectangles&& rects) noexcept = default;
    /* TODO czy desktruktor ma byc */
    ~Rectangles() = default;
    [[nodiscard]] size_t size() const;
    Rectangles& operator=(const Rectangles& rects) = default;
    Rectangles& operator=(Rectangles&& rects) noexcept = default;
    const Rectangle& operator[](long i) const;
    Rectangle& operator[](long i);
    Rectangles& operator+=(const Vector& vec);
    /* TODO czy friend jest akceptowalny i czy podwojna deklaracja merge_all */
    friend Rectangle merge_all(const Rectangles& rects);
private:
    std::vector<Rectangle> rectangles;
};


Rectangle merge_horizontally(const Rectangle& rect1, const Rectangle& rect2);

Rectangle merge_vertically(const Rectangle& rect1, const Rectangle& rect2);

/* TODO czy merge_all jest efektywnie zaimplementowany */
Rectangle merge_all(const Rectangles& rects);

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