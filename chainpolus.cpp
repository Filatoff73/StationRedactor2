#include "chainpolus.h"
#include <QPen>
#include "scene.h"

ChainPolus::ChainPolus(QGraphicsObject* parent) : MainElement(parent)
{
     nameElement = "";
     typeElement = TYPE_CHAIN_POLUS;
     nContactsLeft=1;
     nContactsRight=0;
     nContactsUp=0;
     nContactsDown=0;

     nContacts = nContactsDown + nContactsUp + nContactsLeft + nContactsRight;

     sizeX=2;
     sizeY=2;
     isPlus=true;

     SetContact();

}

ChainPolus::ChainPolus(int idElement, int posX, int posY, bool isMirrorGorizontal, bool isMirrorVertical, int sizeX, int sizeY, int nContactsLeft,int nContactsDown,int nContactsRight,int nContactsUp, QString name, QGraphicsObject* parent):
     MainElement( idElement,  posX,  posY,  isMirrorGorizontal,  isMirrorVertical,  sizeX,  sizeY,  nContactsLeft, nContactsDown, nContactsRight, nContactsUp,  name, parent)
{
    typeElement = TYPE_CHAIN_POLUS;
    isPlus=false;
        SetContact();
}

void ChainPolus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    painter->drawText(0,STEP_GRID/2.0, nameElement);

    QPen penPol = painter->pen();
    int r=5;

    if(isPlus)
    {
        penPol.setColor(Qt::green);
        painter->setPen(penPol);
        painter->drawEllipse(sizeX/1.5*STEP_GRID + r, STEP_GRID/2.0 - 2*r, 2*r, 2*r);
        painter->drawLine(sizeX/1.5*STEP_GRID + r, STEP_GRID/2.0 - r, sizeX/1.5*STEP_GRID + 3*r, STEP_GRID/2.0 - r );
        painter->drawLine(sizeX/1.5*STEP_GRID + 2*r, STEP_GRID/2.0 - 2*r, sizeX/1.5*STEP_GRID + 2*r, STEP_GRID/2.0);
       // painter->drawText(sizeX/1.5*STEP_GRID,STEP_GRID/2.0, "+");
    }

    if(!isPlus)
    {
        penPol.setColor(Qt::red);
        painter->setPen(penPol);
        painter->drawEllipse(sizeX/1.5*STEP_GRID + r, STEP_GRID/2.0 - 2*r, 2*r, 2*r);
        painter->drawLine(sizeX/1.5*STEP_GRID + r, STEP_GRID/2.0 - r, sizeX/1.5*STEP_GRID + 3*r, STEP_GRID/2.0 - r );
    }

    painter->restore();
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
    myMenu.addAction("Изменить полярность");
    myMenu.addAction("Удалить элемент");

    QAction* selectedItem = myMenu.exec(event->screenPos());
    if (selectedItem)
    {
        QString txt = selectedItem->text();

        if(!txt.compare("Изменить полярность"))
        {
            isPlus=!isPlus;
            dynamic_cast<Scene*>(this->scene())->update();
        }

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

void ChainPolus::SaveToXml(QXmlStreamWriter &writer)
{
    writer.writeStartElement("Element");
    SaveBaseElementParametrs(writer);//атрибуты

    writer.writeStartElement("Parametrs");

    writer.writeAttribute("isPlus", QString::number(isPlus));

    writer.writeEndElement();//parametrs

    writer.writeStartElement("Contacts");

    for(int i=0;i<arrContacts.size();i++)
    {
        arrContacts[i]->WriteToXmlContacts(writer);
    }

    writer.writeEndElement();//contacts


    writer.writeEndElement();//element
}
bool ChainPolus::getIsPlus() const
{
    return isPlus;
}

void ChainPolus::setIsPlus(bool value)
{
    isPlus = value;
}

