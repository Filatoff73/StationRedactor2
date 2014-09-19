#include "blockrelay.h"
#include <QMimeData>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "scene.h"
#include "view.h"
#include <QPen>
#include <QInputDialog>


BlockRelay::BlockRelay(QGraphicsObject* parent) : MainElement(parent)
{
    nameElement = "BlockRelay";
    typeElement = TYPE_BLOCK_RELAY;

     nContactsLeft=2;
     nContactsRight=3;
     nContactsUp=4;
     nContactsDown=5;

     nContacts = nContactsDown + nContactsUp + nContactsLeft + nContactsRight;

     sizeX=4;
     sizeY=6;

     SetContact();

}


BlockRelay::BlockRelay(int idElement, int posX, int posY, bool isMirrorGorizontal, bool isMirrorVertical, int sizeX, int sizeY, int nContactsLeft,int nContactsDown,int nContactsRight,int nContactsUp, QString name, QGraphicsObject* parent):
     MainElement( idElement,  posX,  posY,  isMirrorGorizontal,  isMirrorVertical,  sizeX,  sizeY,  nContactsLeft, nContactsDown, nContactsRight, nContactsUp,  name, parent)
{
    typeElement = TYPE_BLOCK_RELAY;
    SetContact();
}

void BlockRelay::contextMenuEvent( QGraphicsSceneContextMenuEvent * event )
{
    QMenu myMenu;
    myMenu.addAction("Отразить по вертикали");
    myMenu.addAction("Отразить по горизонтали");
    myMenu.addAction("Изменить размер по Ох");
    myMenu.addAction("Изменить размер по Оу");
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
            dynamic_cast<Scene*>(this->scene())->update();
        }

        if(!txt.compare("Отразить по горизонтали"))
        {
            isMirrorGorizontal=!isMirrorGorizontal;
            int temp;
            temp = nContactsUp;
            nContactsUp=nContactsDown;
            nContactsDown=temp;
            ReDrawContact();
            dynamic_cast<Scene*>(this->scene())->update();

        }

        if(!txt.compare("Изменить размер по Ох"))
        {
            bool ok;
            QString text = QInputDialog::getText(this->scene()->views().last()->cornerWidget(), tr(""),
                                              tr("Размер по Ox"), QLineEdit::Normal,
                                              QString::number(sizeX), &ok);

            if (ok && !text.isEmpty() )
            {
                bool ok1;
                text.toInt(&ok1);
                if(ok1)
                {
                    sizeX = text.toInt();
                }
            }
            ReDrawContact();
            dynamic_cast<Scene*>(this->scene())->update();

        }

        if(!txt.compare("Изменить размер по Оу"))
        {
            bool ok;
            QString text = QInputDialog::getText(this->scene()->views().last()->cornerWidget(), tr(""),
                                              tr("Размер по Oу"), QLineEdit::Normal,
                                              QString::number(sizeY), &ok);

            if (ok && !text.isEmpty() )
            {
                bool ok1;
                text.toInt(&ok1);
                if(ok1)
                {
                    sizeY = text.toInt();
                }
            }
            ReDrawContact();
            dynamic_cast<Scene*>(this->scene())->update();

        }

        if(!txt.compare("Удалить элемент"))
        {
            dynamic_cast<Scene*>(this->scene())->DeleteElement(this);
        }


    }

}

void BlockRelay::SaveToXml(QXmlStreamWriter &writer)
{
    writer.writeStartElement("Element");
    SaveBaseElementParametrs(writer);//атрибуты
    writer.writeStartElement("Contacts");

    for(int i=0;i<arrContacts.size();i++)
    {
        arrContacts[i]->WriteToXmlContacts(writer);
    }

    writer.writeEndElement();//contacts


    writer.writeEndElement();//element
}





void BlockRelay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->drawText(sizeX/2.0*STEP_GRID - nameElement.length()*sizeX/2.0, sizeY/2.0*STEP_GRID, nameElement);
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


}
