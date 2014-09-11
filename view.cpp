#include "view.h"
#include "mainelement.h"
#include <QScrollBar>

View::View(QGraphicsView* parent) : QGraphicsView(parent)
{
    this->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    this->horizontalScrollBar()->setValue(1);
    this->verticalScrollBar()->setValue(1);

}

void View::wheelEvent(QWheelEvent* event)
{
    if(event->delta()>0)
    {
        scale(SCALE, SCALE);
        this->horizontalScrollBar()->setValue(1);
        this->verticalScrollBar()->setValue(1);
    }

    if(event->delta()<0)
    {
        scale(1/SCALE, 1/SCALE);
        this->horizontalScrollBar()->setValue(1);
        this->verticalScrollBar()->setValue(1);
    }
}
