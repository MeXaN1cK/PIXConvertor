#include "convertor.h"
#include <QString>
#include <QPixmap>
#include <QFileDialog>
#include <QImage>
#include <QRgb>
#include <map>
#include <vector>
#include <utility>

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

const int reds=6;
const int greens=8;
const int blues=5;
const float greys[16] = {
    0.05859375, 0.1171875, 0.17578125, 0.234375, 0.29296875, 0.3515625, 0.41015625, 0.46875,
    0.52734375, 0.5859375, 0.64453125, 0.703125, 0.76171875, 0.8203125, 0.87890625, 0.9375
};

bool compare_color(Color c1, Color c2){
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b;
}

void Convertor::convert(QPixmap pixmap) {
    QImage img = pixmap.toImage();

    int imageWidth = img.width();
    int imageHeight = img.height();
    
    Color basicColors[160][100];
    for(int i=0; i < imageWidth; i++){
        for(int j=0; j < imageHeight; j++){
            QRgb rgb = img.pixel(i,j);
            basicColors[i][j].r = qRed(rgb);
            basicColors[i][j].g = qGreen(rgb);
            basicColors[i][j].b = qBlue(rgb);
        }
    }
    
    Pair_Color max_pair;
    std::vector<Pair_Color> pair_statistics;
    for(int i = 0; i < imageWidth; i++){
        for(int j = 0; j < imageHeight / 2;j += 2){
            Color bcolor = basicColors[i][j];
            Color fcolor = basicColors[i][j + 1];
            bool push = true;
            for(int q = 0; q < pair_statistics.size(); q++){
                Pair_Color pair = pair_statistics[q];
                if(compare_color(pair.bcolor, bcolor) && compare_color(pair.fcolor, fcolor)){
                    pair.count++;
                    push = false;
                    if(pair.count > max_pair.count){
                        max_pair = pair;
                    }
                }
            }
            if(push){
                Pair_Color pair = {bcolor, fcolor, 1};
                pair_statistics.push_back(pair);
            }
        }
    }
}

void encodeColor(QRgb rgb, Color &colRGB) {
    int r = qRed(rgb) * 255;
    int g = qGreen(rgb) * 255;
    int b = qBlue(rgb) * 255;
    colRGB.r = r;
    colRGB.g = g;
    colRGB.b = b;
}

void encodeLen(int len, Len &llen) {
    llen.x = len / 256;
    llen.y = len % 256;
}

double delta(QRgb a, QRgb b) {
  int dr = qRed(a) - qRed(b);
  int dg = qGreen(a) - qGreen(b);
  int db = qBlue(a) - qBlue(b);
  return 0.2126 * dr * dr + 0.7152 * dg * dg + 0.0722 * db * db;
}

int deflate(QRgb rgb) {
 int idxR = qRed(rgb) * 255 * (reds - 1) / 0xFF + 0.5;
 int idxG = qGreen(rgb) * 255 * (greens - 1.0) / 0xFF + 0.5;
 int idxB = qBlue(rgb) * 255 * (blues - 1.0) / 0xFF + 0.5;
 int compressed = 16 + idxR * greens * blues + idxG * blues + idxB;
 
 for(int i=0; i < 16; i++){
     if(delta(inflate(i), rgb) < delta(inflate(compressed), rgb))
         compressed = i;
 }
    
 return compressed;
}

QRgb inflate(int value) {
    if(value < 16){
        return greys[value];
    } else {
        int index = value - 16;
        float idxB = index % blues;
        float idxG = (index / blues) % greens;
        float idxR = (index / blues / greens) % reds;
        int r = (idxR * 0xFF / (reds - 1) + 0.5);
        int g = (idxG * 0xFF / (greens - 1) + 0.5);
        int b = (idxB * 0xFF / (blues - 1) + 0.5);
        QRgb rgb = qRgb(r, g, b);
        return rgb;
    }
}
