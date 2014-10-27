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

void View::contextMenuEvent (QContextMenuEvent * event)
{
    QGraphicsView::contextMenuEvent(event);

    if(event->isAccepted())
        return;

    QPoint pos = event->pos();


    QPoint globalPos = event->globalPos();

    QMenu myMenu;
    myMenu.addAction("Добавить блок из файла");
    myMenu.addAction("Добавить тестовый блок");
    myMenu.addAction("Добавить кнопку");
    myMenu.addAction("Добавить полюс");
    myMenu.addAction("Добавить точку");
    myMenu.addAction("Добавить контакт реле");
    myMenu.addAction("Добавить внешний контакт");
    myMenu.addAction("Добавить вторую обмотку");

    QAction* selectedItem = myMenu.exec(globalPos);
    if (selectedItem)
    {
        QString txt = selectedItem->text();


        if(!txt.compare("Добавить блок из файла"))
        {
            dynamic_cast<Scene*>(this->scene())->AddFileBlock(pos);
            update();
        }

        if(!txt.compare("Добавить тестовый блок"))
        {
            dynamic_cast<Scene*>(this->scene())->AddTestBlock(pos);
            update();
        }

        if(!txt.compare("Добавить вторую обмотку"))
        {
            dynamic_cast<Scene*>(this->scene())->AddSecondContactRelay(pos);
            update();
        }

        if(!txt.compare("Добавить кнопку"))
        {
            dynamic_cast<Scene*>(this->scene())->AddChainButton(pos);
            update();
        }

        if(!txt.compare("Добавить полюс"))
        {
            dynamic_cast<Scene*>(this->scene())->AddPolus(pos);

            update();
        }

        if(!txt.compare("Добавить точку"))
        {
            dynamic_cast<Scene*>(this->scene())->AddPoint(pos);
            update();
        }

        if(!txt.compare("Добавить контакт реле"))
        {
            dynamic_cast<Scene*>(this->scene())->AddRelay(pos);
            update();
        }

        if(!txt.compare("Добавить внешний контакт"))
        {
            dynamic_cast<Scene*>(this->scene())->AddRelayContact(pos);
            update();
        }



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
