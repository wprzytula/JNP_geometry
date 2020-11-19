#pragma ide diagnostic ignored "modernize-use-nodiscard"
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>

/*
 * Popraw proszę operatory do takich, jak je opisałem tu w pliku .h
 * (const, referencje - NIE używaj wskaźników!)
 * */

class Vector {
public:
    Vector(int x, int y);
    [[nodiscard]] int x() const;
    [[nodiscard]] int y() const;
    Vector reflection();
    Vector& operator+=(const Vector&);
private:
    int x_coordinate;
    int y_coordinate;
};

class Position {
public:
    Position(int x, int y);
    [[nodiscard]] int x() const;
    [[nodiscard]] int y() const;
    Position reflection();
    static Position origin();
    bool operator==(const Position&) const;
    Position& operator+=(const Vector&);
private:
    int x_coordinate;
    int y_coordinate;
};


class Rectangle {
public:
    Rectangle(int width, int height, Position pos);
    Rectangle(int width, int height);
    int width() const;
    int height() const;
    const Position & pos() const;
    Rectangle reflection();
    Rectangle& operator+=(const Vector& vec);
    long area();
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
    Rectangle& operator[](int i);
    const Rectangle& operator[](int i) const;
    size_t size() const;
    Rectangles& operator+=(const Vector& vec);
    friend Rectangle merge_all(const Rectangles& rectangles);
    friend Rectangle merge_all(Rectangles&& rectangles);
private:
    std::vector<Rectangle> rectangles;
};


Rectangle merge_horizontally(Rectangle& rect1, Rectangle& rect2);

Rectangle merge_vertically(Rectangle& rect1, Rectangle& rect2);

Rectangle merge_all(Rectangles& rectangles);

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