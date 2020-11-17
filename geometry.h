#ifndef GEOMETRY_H
#define GEOMETRY_H

class Vector {
private:
    int x_coordinate;
    int y_coordinate;
public:
    Vector(int x, int y);

    int x();

    int y();

    Vector reflection();

    bool operator==(Vector vec);

    Vector *operator+=(Vector vec);
};

class Position {
private:
    static Position const orig;
    int x_coordinate;
    int y_coordinate;
public:
    Position(int x, int y);

    int x();

    int y();

    Position reflection();

    static Position origin();

    bool operator==(Position pos);

    Position *operator+=(Vector vec);
};

#endif