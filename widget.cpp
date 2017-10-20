#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    _noImageMessage = "Use doble click to load picture";
    _backgroundColor = Qt::white;
    connect(this,SIGNAL(pixmapChanged()),SLOT(repaint()));
    ui->setupUi(this);
}

int rgbToHex(QRgb color){
    int red = qRed(color);
    int green =qGreen(color);
    int blue = qBlue(color);
    return red*65536+green*256+blue;
}

Widget::~Widget()
{
    delete ui;
}
void Widget::setPixmap(QPixmap pixmap)
{
    _originalImage = pixmap;
    emit pixmapChanged();
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() !=Qt::LeftButton)
        return;
    QString filename = QFileDialog::getOpenFileName(this,tr("Open image"),QDir::homePath(),tr("Image Files (*.png *.jpg *.bmp)"));
    if(filename.isEmpty())
        return;
    setPixmap(QPixmap(filename));
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();
    painter.setBrush(_backgroundColor);
    painter.drawRect(rect());
    painter.restore();
    if(_originalImage.isNull()){
        painter.drawText(rect(),Qt::AlignCenter,_noImageMessage);
    }
    else{
        QRect imageRect = rect();
        painter.drawPixmap(imageRect,_originalImage);
    }
}


void Widget::on_pushButton_clicked()
{
    QImage img = _originalImage.toImage();
    QMessageBox *mes = new QMessageBox;
    if(!_originalImage.isNull()){
        QRgb rgb = img.pixel(159,99);
        int r = qRed(rgb);
        int g = qGreen(rgb);
        int b = qBlue(rgb);
        int hex = rgbToHex(rgb);
        QString HEX = QString::number(hex);
        QString R = QString::number(r);
        QString G = QString::number(g);
        QString B = QString::number(b);
        QString str ="R: "+R+" G: "+G+" B: "+B+" Hex: "+HEX;
        mes->setText(str);
        mes->show();
    }
}
