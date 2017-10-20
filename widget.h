#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QFileDialog>
#include <QImage>
#include <QRgb>
#include <QMessageBox>
#include <string>
#include <sstream>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QPixmap _originalImage;
    QString _noImageMessage;
    QColor _backgroundColor;
public:
    void setPixmap(QPixmap pixmap);
    QPixmap pixmap(){return _originalImage;}
signals:
    void pixmapChanged();
protected:
virtual void mouseDoubleClickEvent(QMouseEvent *event);
virtual void paintEvent(QPaintEvent *event);
private slots:
    void on_pushButton_clicked();
};

#endif // WIDGET_H
