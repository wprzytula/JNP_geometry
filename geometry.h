#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <cstdint>

class Vector;

class Position {
public:
    using coord_t = int32_t;
    Position() = delete;
    Position(coord_t x, coord_t y)
        : x_coord(x), y_coord(y) {}
    Position(const Position&) = default;
    Position(Position&&) = delete;
    explicit Position(const Vector& vec);
    [[nodiscard]] coord_t x() const {
        return x_coord;
    }
    [[nodiscard]] coord_t y() const {
        return y_coord;
    }
    [[nodiscard]] Position reflection() const;
    static const Position& origin();
    Position& operator+=(const Vector& vec);
private:
    coord_t x_coord;
    coord_t y_coord;
};

class Vector {
public:
    using coord_t = Position::coord_t;
    Vector() = delete;
    Vector(coord_t x, coord_t y)
        : x_coord(x), y_coord(y) {}
    Vector(const Vector&) = default;
    Vector(Vector&&) = delete;
    explicit Vector(const Position& pos)
        : x_coord(pos.x()), y_coord(pos.y()) {}
    [[nodiscard]] coord_t x() const {
        return x_coord;
    }
    [[nodiscard]] coord_t y() const {
        return y_coord;
    }
    [[nodiscard]] Vector reflection() const {
        return Vector(y_coord, x_coord);
    }
    Vector& operator+=(const Vector& vec);
private:
    coord_t x_coord;
    coord_t y_coord;
};

class Rectangle {
public:
    using coord_t = Vector::coord_t;
    Rectangle() = delete;
    Rectangle(coord_t width, coord_t height, Position pos);
    Rectangle(coord_t width, coord_t height);
    Rectangle(const Rectangle&) = default;
    Rectangle(Rectangle&&) = delete;
    [[nodiscard]] Rectangle::coord_t width() const {
        return w;
    }
    [[nodiscard]] coord_t height() const {
        return h;
    }
    [[nodiscard]] const Position& pos() const {
        return left_bottom_corner;
    }
    [[nodiscard]] coord_t area() const {
        return w * h;
    }
    [[nodiscard]] Rectangle reflection() const {
        return Rectangle{h, w, left_bottom_corner.reflection()};
    }
    Rectangle& operator+=(const Vector& vec);
private:
    Position left_bottom_corner;
    coord_t w;
    coord_t h;
};

class Rectangles {
public:
    using coord_t = Vector::coord_t;
    Rectangles() = default;
    Rectangles(std::initializer_list<Rectangle> initializer_list)
        : rectangles(initializer_list) {}
    Rectangles(const Rectangles& rects) = default;
    Rectangles(Rectangles&& rects) noexcept = default;
    [[nodiscard]] size_t size() const {
        return rectangles.size();
    }
    Rectangles& operator=(const Rectangles& rects) = default;
    Rectangles& operator=(Rectangles&& rects) noexcept = default;
    const Rectangle& operator[](std::vector<Rectangle>::size_type i) const;
    Rectangle& operator[](std::vector<Rectangle>::size_type i);
    Rectangles& operator+=(const Vector& vec);
    friend Rectangle merge_all(const Rectangles& rects);
private:
    std::vector<Rectangle> rectangles;
};


Rectangle merge_horizontally(const Rectangle& rect1, const Rectangle& rect2);

Rectangle merge_vertically(const Rectangle& rect1, const Rectangle& rect2);

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

Rectangles operator+(Rectangles rects, const Vector& vec);

Rectangles operator+(const Vector& vec, Rectangles rects);

#endif // GEOMETRY_H
