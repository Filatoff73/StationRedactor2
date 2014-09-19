#include "relayrelay.h"
#include <QInputDialog>
#include <QWidget>
#include <QGraphicsView>
#include "scene.h"
#include "relaycontact.h"


RelayRelay::RelayRelay(QGraphicsObject* parent) : MainElement(parent)
{

    nameElement = "";
    typeElement = TYPE_RELAY_RELAY;

     nContactsLeft=1;
     nContactsRight=1;
     nContactsUp=0;
     nContactsDown=0;

     nContacts = nContactsDown + nContactsUp + nContactsLeft + nContactsRight;

     sizeX=3;
     sizeY=2;

     SetContact();

     delay=0;
     isVoltage=false;

}

RelayRelay::RelayRelay(int idElement, int posX, int posY, bool isMirrorGorizontal, bool isMirrorVertical, int sizeX, int sizeY, int nContactsLeft,int nContactsDown,int nContactsRight,int nContactsUp, QString name, QGraphicsObject* parent):
     MainElement( idElement,  posX,  posY,  isMirrorGorizontal,  isMirrorVertical,  sizeX,  sizeY,  nContactsLeft, nContactsDown, nContactsRight, nContactsUp,  name, parent)
{
    typeElement = TYPE_RELAY_RELAY;
    SetContact();

    delay=0;
    isVoltage=false;
}




RelayRelay::~RelayRelay()
{

}

void RelayRelay::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = QRect(0,0, STEP_GRID * sizeX, STEP_GRID * sizeY);

    painter->drawText(0,-STEP_GRID/2.0,nameElement);

    QString ret = isVoltage ? "on" : "off";
    painter->drawText(rect, Qt::AlignHCenter | Qt::AlignTop,
                      ret);
    painter->drawText(rect, Qt::AlignHCenter | Qt::AlignBottom,
                      QString::number(delay));


    MainElement::paint(painter, option, widget);

    QPen pen = painter->pen();
    if(!isVoltage)
        pen.setColor(Qt::red);
    else
        pen.setColor(Qt::green);
    painter->setPen(pen);

    painter->drawRect(rect);



}

void RelayRelay::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{


    QMenu myMenu;
    myMenu.addAction("Под током/обесточено");
    myMenu.addAction("Изменить задержку");
    myMenu.addAction("Переименовать элемент");
    myMenu.addAction("Удалить элемент");

    QAction* selectedItem = myMenu.exec(event->screenPos());
    if (selectedItem)
    {
        QString txt = selectedItem->text();

        if(!txt.compare("Под током/обесточено"))
        {
            isVoltage = !isVoltage;

            dynamic_cast<Scene*>(this->scene())->update();
        }

        if(!txt.compare("Изменить задержку"))
        {
            bool ok;
            QString text = QInputDialog::getText(this->scene()->views().last()->cornerWidget(), tr(""),
                                              tr("Задержка (мсек):"), QLineEdit::Normal,
                                              QString::number(delay), &ok);
            if (ok && !text.isEmpty())
            {
                bool ok;
                text.toInt(&ok);
                if(ok)
                    delay = text.toInt();
            }
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











bool RelayRelay::getIsVoltage() const
{
    return isVoltage;
}

void RelayRelay::setIsVoltage(bool value)
{
    isVoltage = value;
}
int RelayRelay::getDelay() const
{
    return delay;
}

void RelayRelay::setDelay(int value)
{
    delay = value;
}

void RelayRelay::SaveToXml(QXmlStreamWriter &writer)
{
    writer.writeStartElement("Element");
    SaveBaseElementParametrs(writer);//атрибуты

    writer.writeStartElement("Parametrs");

    writer.writeAttribute("isVoltage", QString::number(isVoltage));
    writer.writeAttribute("delay", QString::number(delay));

    writer.writeEndElement();//parametrs

    writer.writeStartElement("Contacts");

    for(int i=0;i<arrContacts.size();i++)
    {
        arrContacts[i]->WriteToXmlContacts(writer);
    }

    writer.writeEndElement();//contacts


    writer.writeEndElement();//element
}





