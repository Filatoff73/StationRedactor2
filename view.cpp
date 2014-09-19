#include "view.h"
#include "mainelement.h"
#include <QScrollBar>
#include <scene.h>
#include <mainelement.h>
#include <QSizePolicy>


View::View(QGraphicsView* parent) : QGraphicsView(parent)
{
    this->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    this->horizontalScrollBar()->setValue(1);
    this->verticalScrollBar()->setValue(1);


    InitViewVariable();
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);



}

void View::wheelEvent(QWheelEvent* event)
{
    if(event->delta()>0)
    {
        scale(SCALE, SCALE);

        stepSlider*=SCALE;
        //this->horizontalScrollBar()->setValue(1);
        //this->verticalScrollBar()->setValue(1);
    }

    if(event->delta()<0)
    {
        scale(1/SCALE, 1/SCALE);

        if(stepSlider>1)
        {
            stepSlider*=1/SCALE;
        }
        //this->horizontalScrollBar()->setValue(1);
        //this->verticalScrollBar()->setValue(1);
    }
}


void View::keyPressEvent(QKeyEvent *event)
{

    if(event->key()==Qt::Key_Left)
    {
        this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value()-stepSlider);
    }

    if(event->key()==Qt::Key_Right)
    {
        this->horizontalScrollBar()->setValue(this->horizontalScrollBar()->value()+stepSlider);
    }

    if(event->key()==Qt::Key_Up)
    {
        this->verticalScrollBar()->setValue(this->verticalScrollBar()->value()-stepSlider);
    }

    if(event->key()==Qt::Key_Down)
    {
        this->verticalScrollBar()->setValue(this->verticalScrollBar()->value()+stepSlider);
    }


}

void View::InitViewVariable()
{
        stepSlider = MainElement::GetStepGrid()/2.0;
}
