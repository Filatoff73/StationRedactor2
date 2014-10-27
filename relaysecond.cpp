#include "relaysecond.h"
#include "relayrelay.h"
#include "scene.h"
#include "relaycontact.h"
#include <QErrorMessage>
#include <QGraphicsView>

RelaySecond::RelaySecond(QGraphicsObject* parent) : MainElement(parent)
{
    nameElement = "ВТОРОЙ КОНТАКТ";
    typeElement = TYPE_RELAY_SECOND;

     nContactsLeft=1;
     nContactsRight=1;
     nContactsUp=0;
     nContactsDown=0;

     nContacts = nContactsDown + nContactsUp + nContactsLeft + nContactsRight;

     sizeX=3;
     sizeY=2;

     SetContact();
     isLinked=false;
     isProcessLinked=false;
     associatedRelay=NULL;

}

RelaySecond::RelaySecond(int idElement, int posX, int posY, bool isMirrorGorizontal, bool isMirrorVertical, int sizeX, int sizeY, int nContactsLeft,int nContactsDown,int nContactsRight,int nContactsUp, QString name, QGraphicsObject* parent):
     MainElement( idElement,  posX,  posY,  isMirrorGorizontal,  isMirrorVertical,  sizeX,  sizeY,  nContactsLeft, nContactsDown, nContactsRight, nContactsUp,  name, parent)
{
    typeElement = TYPE_RELAY_SECOND;
    SetContact();

    isLinked=false;
    isProcessLinked=false;
    associatedRelay=NULL;
}


void RelaySecond::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(isLinked && associatedRelay!=NULL)
    {
        nameElement = associatedRelay->getNameElement();
    }

    painter->drawText(0,-STEP_GRID/2.0,nameElement);
    MainElement::paint(painter, option, widget);

    QPen pen = painter->pen();

    pen.setColor(Qt::red);
    if(!isLinked)
        painter->setPen(pen);

    pen.setColor(Qt::blue);
    if(isProcessLinked)
        painter->setPen(pen);



     QRectF rect = QRect(0,0, STEP_GRID * sizeX, STEP_GRID * sizeY);
     painter->drawRect(rect);


}

void RelaySecond::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu myMenu;
    myMenu.addAction("Привязать к реле");
    myMenu.addAction("Сброс привязки");
    myMenu.addAction("Переименовать элемент");
    myMenu.addAction("Удалить элемент");

    QAction* selectedItem = myMenu.exec(event->screenPos());
    if (selectedItem)
    {
        QString txt = selectedItem->text();


        if(!txt.compare("Привязать к реле"))
        {
            isSelectRelayMode=true;
            relayContactSelected=this;
            isProcessLinked=true;
            update();
        }

        if(!txt.compare("Сброс привязки"))
        {
            isSelectRelayMode=false;
            relayContactSelected=NULL;
            RemoveAssociatedRelay();
            dynamic_cast<Scene*>(this->scene())->update();
        }

        if(!txt.compare("Переименовать элемент"))
        {
            if(!isLinked)
            {
                nameElement = dynamic_cast<Scene*>(this->scene())->SetStringParamElementDialog(nameElement);
                dynamic_cast<Scene*>(this->scene())->update();
            }
            else
            {
                QErrorMessage mess(this->scene()->views().last()->cornerWidget());
                mess.showMessage("Нельзя переименовать связанный с реле контакт");
                mess.exec();
            }

        }

        if(!txt.compare("Удалить элемент"))
        {
            dynamic_cast<Scene*>(this->scene())->DeleteElement(this);
        }


    }

}



void RelaySecond::RemoveAssociatedRelay()
{
    isProcessLinked=false;
    if(isLinked)
    {
        isLinked=false;
        associatedRelay=NULL;
        nameElement="ВТОРОЙ КОНТАКТ";

    }
}
RelayRelay *RelaySecond::getAssociatedRelay() const
{
    return associatedRelay;
}

void RelaySecond::setAssociatedRelay(RelayRelay *value)
{
    associatedRelay = value;
}
bool RelaySecond::getIsLinked() const
{
    return isLinked;
}

void RelaySecond::setIsLinked(bool value)
{
    isLinked = value;
}
bool RelaySecond::getIsProcessLinked() const
{
    return isProcessLinked;
}

void RelaySecond::setIsProcessLinked(bool value)
{
    isProcessLinked = value;
}

void RelaySecond::SaveToXml(QXmlStreamWriter &writer)
{

    writer.writeStartElement("Element");
    SaveBaseElementParametrs(writer);//атрибуты

    writer.writeStartElement("Parametrs");

    writer.writeAttribute("isLinked", QString::number(isLinked));
    writer.writeAttribute("isProcessLinked", QString::number(isProcessLinked));
    if(associatedRelay!=NULL)
    {
        writer.writeAttribute("associatedRelay", QString::number(associatedRelay->getIdElement()));
    }
    else
    {
         writer.writeAttribute("associatedRelay", "");
    }

    writer.writeEndElement();//parametrs


    writer.writeStartElement("Contacts");

    for(int i=0;i<arrContacts.size();i++)
    {
        arrContacts[i]->WriteToXmlContacts(writer);
    }

    writer.writeEndElement();//contacts


    writer.writeEndElement();//element
}
