#include "blockrelay.h"
#include <QMimeData>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "scene.h"
#include <QPen>


int BlockRelay::SiezeBlockX=3;
int BlockRelay::SiezeBlockY=3;

BlockRelay::BlockRelay(QGraphicsObject* parent) : MainElement(parent)
{
    nameElement = "BlockRelay";
    idElement=1;

     nContactsLeft=2;
     nContactsRight=3;
     nContactsUp=4;
     nContactsDown=5;

     nContacts = nContactsDown + nContactsUp + nContactsLeft + nContactsRight;

     sizeX=SiezeBlockX;
     sizeY=SiezeBlockY;

     SetContact();

}


void BlockRelay::contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
{
    QMenu myMenu;
    myMenu.addAction("Отразить по вертикали");
    myMenu.addAction("Отразить по горизонтали");
    myMenu.addAction("Удалить элемент");

    QAction* selectedItem = myMenu.exec(event->screenPos());
    if (selectedItem)
    {
        QString txt = selectedItem->text();

        if(!txt.compare("Отразить по вертикали"))
        {
            isMirrorVertical=!isMirrorVertical;
            int temp;
            temp = nContactsLeft;
            nContactsLeft=nContactsRight;
            nContactsRight=temp;
            ReDrawContact();
        }

        if(!txt.compare("Отразить по горизонтали"))
        {
            isMirrorGorizontal=!isMirrorGorizontal;
            int temp;
            temp = nContactsUp;
            nContactsUp=nContactsDown;
            nContactsDown=temp;
            ReDrawContact();

        }

        if(!txt.compare("Удалить элемент"))
        {
            dynamic_cast<Scene*>(this->scene())->DeleteElement(this);
        }

    }

}
int BlockRelay::getSiezeBlockX()
{
    return SiezeBlockX;
}

void BlockRelay::setSiezeBlockX(int value)
{
    SiezeBlockX = value;
}
int BlockRelay::getSiezeBlockY()
{
    return SiezeBlockY;
}

void BlockRelay::setSiezeBlockY(int value)
{
    SiezeBlockY = value;
}




void BlockRelay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    MainElement::paint(painter, option, widget);


    painter->save();
    painter->translate(sizeX*STEP_GRID/2,STEP_GRID*sizeY/2);
    if(isMirrorGorizontal)
    {
        QTransform t = painter->worldTransform();
        t.rotate(180, Qt::XAxis);
        painter->setTransform(t);

    }
    if(isMirrorVertical)
    {
        QTransform t = painter->worldTransform();
        t.rotate(180, Qt::YAxis);
        painter->setTransform(t);

    }

    painter->translate(-sizeX*STEP_GRID/2.0,-STEP_GRID*sizeY/2.0);


    DrawBlock(painter);

     //Возврат к исходной системе координат
     painter->restore();
}


void BlockRelay::DrawBlock(QPainter* painter)
{
    painter->drawRect(1, 1, (sizeX)*STEP_GRID-2, (sizeY)*STEP_GRID-2 );

    //QFont font = &GetFont();
   // painter->setFont(GetFont());

    //painter->drawText(this->size().height()/2, this->size().width()/2, nameBlock);

   // SetContact();

}
