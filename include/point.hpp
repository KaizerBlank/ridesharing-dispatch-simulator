#ifndef POINT_H
#define POINT_H

class Point {
    private:
    double x;
    double y;

    public:
    // Construtor de Point, inicializa um ponto com coordenadas cartesianas (x, y).
    Point(double px = 0.0, double py = 0.0);

    // Getters
    double getX() const;
    double getY() const;

};

#endif