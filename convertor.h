#ifndef CONVERTOR_H
#define CONVERTOR_H
#include <QPixmap>
#include <QString>

int encodeColor(QRgb);
float encodeLen(int);
double delta(QRgb,QRgb);
int deflate(QRgb);
QRgb inflate(int);

class Convertor
{
public:
    void convert(QPixmap pixmap,QString pathSave);
};

#endif // CONVERTOR_H
