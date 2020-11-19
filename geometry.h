#ifndef GEOMETRY_H
#define GEOMETRY_H

class Vector {
public:
    Vector(int x, int y);
    [[nodiscard]] int x() const;
    [[nodiscard]] int y() const;
    Vector reflection();
    bool operator==(const Vector&) const;
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
    int width();
    int height();
    const Position& pos();
    Rectangle reflection();
private:
    Position left_bottom_corner;
    Position right_bottom_corner;
    Position left_top_corner;
    Position right_top_corner;

};

class Rectangles {
public:
    Rectangles({Rectangle});
};

Rectangle merge_horizontally(Rectangle& rect1, Rectangle& rect2);

Rectangle merge_vertically(Rectangle& rect1, Rectangle& rect2);

Rectangle merge_all(Rectangles rectangles);

#endif