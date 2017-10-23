#ifndef CONVERTOR_H
#define CONVERTOR_H
#include <QPixmap>
#include <QString>

struct Color {
    uint8_t r, g, b;
};

struct Pair_Color {
    Color bcolor, fcolor;
    int count;
};

struct Len {
    float x, y;
};

int encodeColor(QRgb);
float encodeLen(int);
double delta(QRgb,QRgb);
int deflate(QRgb);
QRgb inflate(int);

class Convertor
{
public:
    void convert(QPixmap pixmap);
};

#endif // CONVERTOR_H
