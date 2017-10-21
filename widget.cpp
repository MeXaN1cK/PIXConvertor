#include "widget.h"
#include "ui_widget.h"
#include "convertor.h"

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
    Convertor *convertor = new Convertor();
    if(!_originalImage.isNull()){
        convertor->convert(_originalImage);

    }
}
