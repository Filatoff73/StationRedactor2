#include "relaycontact.h"
#include "relayrelay.h"
#include "scene.h"
#include <QErrorMessage>
#include <QGraphicsView>

RelayContact::RelayContact(QGraphicsObject* parent) : MainElement(parent)
{
    nameElement = "КОНТАКТ";
    typeElement = TYPE_RELAY_CONTACT;

     nContactsLeft=2;
     nContactsRight=0;
     nContactsUp=1;
     nContactsDown=0;

     nContacts = nContactsDown + nContactsUp + nContactsLeft + nContactsRight;

     sizeX=3;
     sizeY=2;

     for(int i=0;i<nContacts;i++)
     {
         arrContacts.append(new Contacts(0,0,0,0));
         arrContacts.last()->setParentItem(this);
         arrContacts.last()->setVisible(true);
     }

     this->ReDrawContact();
     isLinked=false;
     isProcessLinked=false;
     associatedRelay=NULL;

}

RelayContact::RelayContact(int idElement, int posX, int posY, bool isMirrorGorizontal, bool isMirrorVertical, int sizeX, int sizeY, int nContactsLeft,int nContactsDown,int nContactsRight,int nContactsUp, QString name, QGraphicsObject* parent):
     MainElement( idElement,  posX,  posY,  isMirrorGorizontal,  isMirrorVertical,  sizeX,  sizeY,  nContactsLeft, nContactsDown, nContactsRight, nContactsUp,  name, parent)
{
    typeElement = TYPE_RELAY_CONTACT;
    for(int i=0;i<nContacts;i++)
    {
        arrContacts.append(new Contacts(0,0,0,0));
        arrContacts.last()->setParentItem(this);
        arrContacts.last()->setVisible(true);
    }

    this->ReDrawContact();
    isLinked=false;
    isProcessLinked=false;
    associatedRelay=NULL;
}


void RelayContact::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(isLinked && associatedRelay!=NULL)
    {
        nameElement = associatedRelay->getNameElement();
    }

    painter->drawText(0,-STEP_GRID/2.0,nameElement);
    MainElement::paint(painter, option, widget);

    QPen pen = painter->pen();
    pen.setColor(Qt::blue);
    if(isProcessLinked)
        painter->setPen(pen);



    if(!isLinked)
        painter->drawLine(arrContacts.last()->GetPositionContact().x(), arrContacts.last()->GetPositionContact().y(), arrContacts.first()->GetPositionContact().x(), STEP_GRID*sizeY/2.0);

  if(isLinked && associatedRelay!=NULL)
  {

      if(associatedRelay->getIsVoltage())
            painter->drawLine(arrContacts.last()->GetPositionContact(), arrContacts[1]->GetPositionContact());
      else
          painter->drawLine(arrContacts.last()->GetPositionContact(), arrContacts.first()->GetPositionContact());
  }

}

void RelayContact::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu myMenu;
    myMenu.addAction("Вверх");
    myMenu.addAction("Вниз");
    myMenu.addAction("Влево");
    myMenu.addAction("Вправо");
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

        if(!txt.compare("Вверх"))
        {
            nContactsUp=1;
            nContactsDown=0;
            ReDrawContact();
            dynamic_cast<Scene*>(this->scene())->update();
        }

        if(!txt.compare("Вниз"))
        {
            nContactsUp=0;
            nContactsDown=1;
            ReDrawContact();
            dynamic_cast<Scene*>(this->scene())->update();
        }

        if(!txt.compare("Влево"))
        {
            nContactsLeft=2;
            nContactsRight=0;
            ReDrawContact();
            dynamic_cast<Scene*>(this->scene())->update();
        }

        if(!txt.compare("Вправо"))
        {
            nContactsLeft=0;
            nContactsRight=2;
            ReDrawContact();
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

void RelayContact::ReDrawContact()
{

    if(nContactsLeft==2)
    {

        arrContacts[0]->setRect(0-rad/2.0, 0-rad/2.0, rad, rad);
        arrContacts[0]->SetOrientation(Left);
        arrContacts[0]->SetPositionContact(QPoint(0,0));
        arrContacts[0]->setNum(0);

        arrContacts[1]->setRect(0-rad/2.0, STEP_GRID*sizeY-rad/2.0, rad, rad);
        arrContacts[1]->SetOrientation(Left);
        arrContacts[1]->SetPositionContact(QPoint(0,STEP_GRID*sizeY));
        arrContacts[1]->setNum(1);

        if(nContactsDown==1)
        {
            arrContacts[2]->setRect(STEP_GRID*sizeX-rad/2.0, STEP_GRID*sizeY-rad/2.0, rad, rad);
            arrContacts[2]->SetOrientation(Right);
            arrContacts[2]->SetPositionContact(QPoint(STEP_GRID*sizeX,STEP_GRID*sizeY));
            arrContacts[2]->setNum(2);
        }

        if(nContactsUp==1)
        {
            arrContacts[2]->setRect(STEP_GRID*sizeX-rad/2.0, 0-rad/2.0, rad, rad);
            arrContacts[2]->SetOrientation(Right);
            arrContacts[2]->SetPositionContact(QPoint(STEP_GRID*sizeX,0));
            arrContacts[2]->setNum(2);
        }

    }

    if(nContactsRight==2)
    {

        arrContacts[0]->setRect(STEP_GRID*sizeX-rad/2.0, 0-rad/2.0, rad, rad);
        arrContacts[0]->SetOrientation(Right);
        arrContacts[0]->SetPositionContact(QPoint(STEP_GRID*sizeX,0));
        arrContacts[0]->setNum(0);

        arrContacts[1]->setRect(STEP_GRID*sizeX-rad/2.0, STEP_GRID*sizeY-rad/2.0, rad, rad);
        arrContacts[1]->SetOrientation(Right);
        arrContacts[1]->SetPositionContact(QPoint(STEP_GRID*sizeX,STEP_GRID*sizeY));
        arrContacts[1]->setNum(1);

        if(nContactsDown==1)
        {
            arrContacts[2]->setRect(0-rad/2.0, STEP_GRID*sizeY-rad/2.0, rad, rad);
            arrContacts[2]->SetOrientation(Left);
            arrContacts[2]->SetPositionContact(QPoint(0,STEP_GRID*sizeY));
            arrContacts[2]->setNum(2);
        }

        if(nContactsUp==1)
        {
            arrContacts[2]->setRect(0-rad/2.0, 0-rad/2.0, rad, rad);
            arrContacts[2]->SetOrientation(Left);
            arrContacts[2]->SetPositionContact(QPoint(0,0));
            arrContacts[2]->setNum(2);
        }

    }



}

void RelayContact::RemoveAssociatedRelay()
{
    isProcessLinked=false;
    if(isLinked)
    {
        isLinked=false;
        associatedRelay=NULL;
        nameElement="КОНТАКТ";

    }
}
RelayRelay *RelayContact::getAssociatedRelay() const
{
    return associatedRelay;
}

void RelayContact::setAssociatedRelay(RelayRelay *value)
{
    associatedRelay = value;
}
bool RelayContact::getIsLinked() const
{
    return isLinked;
}

void RelayContact::setIsLinked(bool value)
{
    isLinked = value;
}
bool RelayContact::getIsProcessLinked() const
{
    return isProcessLinked;
}

void RelayContact::setIsProcessLinked(bool value)
{
    isProcessLinked = value;
}

void RelayContact::SaveToXml(QXmlStreamWriter &writer)
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



