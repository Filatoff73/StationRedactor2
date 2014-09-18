#include "chainpolus.h"
#include <QPen>
#include "scene.h"

ChainPolus::ChainPolus(QGraphicsObject* parent) : MainElement(parent)
{
     nameElement = "";
     nContactsLeft=1;
     nContactsRight=0;
     nContactsUp=0;
     nContactsDown=0;

     nContacts = nContactsDown + nContactsUp + nContactsLeft + nContactsRight;

     sizeX=2;
     sizeY=2;

     SetContact();

}

void ChainPolus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->drawText(0,STEP_GRID/2.0, nameElement);
    MainElement::paint(painter, option, widget);



    if(nContactsLeft==1)
    {
        painter->drawLine(0, sizeY/2.0*STEP_GRID, sizeX/2.0*STEP_GRID, sizeY/2.0*STEP_GRID);
    }

    if(nContactsRight==1)
    {
        painter->drawLine(sizeX/2.0*STEP_GRID, sizeY/2.0*STEP_GRID, sizeX*STEP_GRID, sizeY/2.0*STEP_GRID);
    }

    if(nContactsUp==1)
    {
        painter->drawLine(sizeX/2.0*STEP_GRID, 0, sizeX/2.0*STEP_GRID, sizeY/2.0*STEP_GRID);
    }

    if(nContactsDown==1)
    {
        painter->drawLine(sizeX/2.0*STEP_GRID, sizeY/2.0*STEP_GRID, sizeX/2.0*STEP_GRID, sizeY*STEP_GRID);
    }

    QPen pen = painter->pen();
    pen.setStyle(Qt::DotLine);
    painter->setPen(pen);

    if(nContactsLeft==1)
    {
        painter->drawLine(sizeX/2.0*STEP_GRID, sizeY/2.0*STEP_GRID, sizeX*STEP_GRID, sizeY/2.0*STEP_GRID);
    }

    if(nContactsRight==1)
    {
        painter->drawLine(0, sizeY/2.0*STEP_GRID, sizeX/2.0*STEP_GRID, sizeY/2.0*STEP_GRID);
    }

    if(nContactsUp==1)
    {
        painter->drawLine(sizeX/2.0*STEP_GRID, sizeY/2.0*STEP_GRID, sizeX/2.0*STEP_GRID, sizeY*STEP_GRID);
    }

    if(nContactsDown==1)
    {
        painter->drawLine(sizeX/2.0*STEP_GRID, 0, sizeX/2.0*STEP_GRID, sizeY/2.0*STEP_GRID);
    }

}

void ChainPolus::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu myMenu;
    myMenu.addAction("Влево");
    myMenu.addAction("Вправо");
    myMenu.addAction("Вверх");
    myMenu.addAction("Вниз");
    myMenu.addAction("Переименовать элемент");
    myMenu.addAction("Удалить элемент");

    QAction* selectedItem = myMenu.exec(event->screenPos());
    if (selectedItem)
    {
        QString txt = selectedItem->text();

        if(!txt.compare("Влево"))
        {
            nContactsLeft=1;
            nContactsDown=0;
            nContactsRight=0;
            nContactsUp=0;
            ReDrawContact();
            dynamic_cast<Scene*>(this->scene())->update();
        }

        if(!txt.compare("Вправо"))
        {
            nContactsLeft=0;
            nContactsDown=0;
            nContactsRight=1;
            nContactsUp=0;
            ReDrawContact();
            dynamic_cast<Scene*>(this->scene())->update();

        }

        if(!txt.compare("Вверх"))
        {
            nContactsLeft=0;
            nContactsDown=0;
            nContactsRight=0;
            nContactsUp=1;
            ReDrawContact();
            dynamic_cast<Scene*>(this->scene())->update();

        }

        if(!txt.compare("Вниз"))
        {
            nContactsLeft=0;
            nContactsDown=1;
            nContactsRight=0;
            nContactsUp=0;
            ReDrawContact();
            dynamic_cast<Scene*>(this->scene())->update();

        }

        if(!txt.compare("Переименовать элемент"))
        {
            nameElement = dynamic_cast<Scene*>(this->scene())->SetStringParamElementDialog(nameElement);
            dynamic_cast<Scene*>(this->scene())->update();

        }

        if(!txt.compare("Удалить элемент"))
        {
            dynamic_cast<Scene*>(this->scene())->DeleteElement(this);
        }


    }
}
