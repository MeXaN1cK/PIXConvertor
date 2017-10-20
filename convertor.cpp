#include "convertor.h"
#include <QPixmap>
#include <QString>
#include <QFileDialog>
#include <QImage>
#include <QRgb>

struct Color
{
    uint8_t r,g,b;
};

const int reds=6;
const int greens=8;
const int blues=5;
const float greys[16]={
0.05859375, 0.1171875, 0.17578125, 0.234375, 0.29296875, 0.3515625, 0.41015625, 0.46875,
0.52734375, 0.5859375, 0.64453125, 0.703125, 0.76171875, 0.8203125, 0.87890625, 0.9375
};

void Convertor::convert(QPixmap pixmap, QString pathSave)
{
    QImage img = pixmap.toImage();

    int imageWight = img.width();
    int imageHeight = img.height();
    Color basicColors[imageWight][imageHeight];
    for(int i=0;i < imageWight;i++){
        for(int j=0;j < imageHeight;j++){
            QRgb rgb = img.pixel(i,j);
            basicColors[i][j].r = qRed(rgb);
            basicColors[i][j].g = qGreen(rgb);
            basicColors[i][j].b = qBlue(rgb);
        }
    }
}

int encodeColor(QRgb rgb){
    int r=qRed(rgb)*255;
    int g=qGreen(rgb)*255;
    int b=qBlue(rgb)*255;
    return r,g,b;
}
float encodeLen(int len){
    return len/256,len%256;
}

double delta(QRgb a,QRgb b){
  int dr=qRed(a)-qRed(b);
  int dg=qGreen(a)-qGreen(b);
  int db=qBlue(a)-qBlue(b);
  return 0.2126 * dr * dr + 0.7152 * dg * dg + 0.0722 * db * db;
}
