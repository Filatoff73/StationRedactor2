#include "chainpoint.h"
#include "scene.h"

ChainPoint::ChainPoint(QGraphicsObject* parent) : MainElement(parent)
{
    nameElement = "";

     nContactsLeft=1;
     nContactsRight=1;
     nContactsUp=1;
     nContactsDown=1;

     nContacts = nContactsDown + nContactsUp + nContactsLeft + nContactsRight;

     sizeX=1;
     sizeY=1;

     SetContact();
}

void ChainPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    MainElement::paint(painter, option, widget);

    painter->drawLine(0,sizeY*STEP_GRID/2.0, sizeX*STEP_GRID, sizeY*STEP_GRID/2.0);

    painter->drawLine(sizeX*STEP_GRID/2.0, 0 , sizeX*STEP_GRID/2.0, sizeY*STEP_GRID);


}

void ChainPoint::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu myMenu;
    myMenu.addAction("Удалить элемент");

    QAction* selectedItem = myMenu.exec(event->screenPos());
    if (selectedItem)
    {
        QString txt = selectedItem->text();

        if(!txt.compare("Удалить элемент"))
        {
            dynamic_cast<Scene*>(this->scene())->DeleteElement(this);
        }

    }
}
