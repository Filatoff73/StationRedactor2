#include "chainbutton.h"
#include "scene.h"

ChainButton::ChainButton(QGraphicsObject* parent) : MainElement(parent)
{
    nameElement = "";
    typeElement = TYPE_CHAIN_BUTTON;

     nContactsLeft=1;
     nContactsRight=1;
     nContactsUp=0;
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
}

ChainButton::ChainButton(int idElement, int posX, int posY, bool isMirrorGorizontal, bool isMirrorVertical, int sizeX, int sizeY, int nContactsLeft,int nContactsDown,int nContactsRight,int nContactsUp, QString name, QGraphicsObject* parent):
     MainElement( idElement,  posX,  posY,  isMirrorGorizontal,  isMirrorVertical,  sizeX,  sizeY,  nContactsLeft, nContactsDown, nContactsRight, nContactsUp,  name, parent)
{
    typeElement = TYPE_CHAIN_BUTTON;

    for(int i=0;i<nContacts;i++)
    {
        arrContacts.append(new Contacts(0,0,0,0));
        arrContacts.last()->setParentItem(this);
        arrContacts.last()->setVisible(true);
    }

    this->ReDrawContact();
}

void ChainButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->drawText(0,-STEP_GRID/2.0,nameElement);
    MainElement::paint(painter, option, widget);

    painter->drawLine(0,sizeY*STEP_GRID/2.0, sizeX*STEP_GRID, sizeY*STEP_GRID/2.0);

    painter->drawLine(sizeX*STEP_GRID/2.0, sizeY*STEP_GRID/2.0 , sizeX*STEP_GRID/2.0, 0);

    painter->drawLine(sizeX*STEP_GRID/3.0, 0 , sizeX*STEP_GRID/3.0*2.0, 0);


}

void ChainButton::ReDrawContact()
{

    arrContacts[0]->setRect(0-rad/2.0, STEP_GRID*sizeY/2.0-rad/2.0, rad, rad);
    arrContacts[0]->SetOrientation(Left);
    arrContacts[0]->SetPositionContact(QPoint(0,STEP_GRID*sizeY/2.0));
    arrContacts[0]->setNum(0);

    arrContacts[1]->setRect(sizeX*STEP_GRID-rad/2.0, STEP_GRID*sizeY-rad/2.0, rad, rad);
    arrContacts[1]->SetOrientation(Right);
    arrContacts[1]->SetPositionContact(QPoint(sizeX*STEP_GRID,STEP_GRID*sizeY));
    arrContacts[1]->setNum(1);

}

void ChainButton::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu myMenu;
    myMenu.addAction("Переименовать элемент");
    myMenu.addAction("Удалить элемент");

    QAction* selectedItem = myMenu.exec(event->screenPos());
    if (selectedItem)
    {
        QString txt = selectedItem->text();

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

void ChainButton::SaveToXml(QXmlStreamWriter &writer)
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
