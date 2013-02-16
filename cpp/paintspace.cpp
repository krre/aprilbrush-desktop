#include "paintspace.h"
#include "qmlwindow.h"

PaintSpace::PaintSpace(QQuickItem *parent) :
    QQuickPaintedItem(parent)
{
    // Default black transparency color
    pixmapColor.setRgba(qRgba(0, 0, 0, 0));
    count = 0;
}

void PaintSpace::paint(QPainter *painter)
{

    if (pixmap.isNull())
    {
        QRectF rect = boundingRect();
        pixmap = QPixmap(rect.width(), rect.height());
        pixmap.fill(pixmapColor);
        pixmapPtr = &pixmap;
    }

    painter->drawPixmap(0, 0, pixmap);
    //qDebug() << "update" << count++;
}

QPixmap *PaintSpace::pixmapPtr = NULL;

