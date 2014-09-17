#include "contacts.h"
#include "scene.h"
#include <cmath>


Contacts::Contacts(int x, int y, int w, int h, QGraphicsItem* parent) : QGraphicsEllipseItem(x,y,w,h,parent)
{
    idContact=0;
    num=0;
    labelContact = "0";
    colorContact=Qt::black;
    isChecked=false;
    isDrawedConnection=false;
    nameContact = "";

    neighbourContact=NULL;



    //чтобы не перекрывались линии
    setZValue(10);

}


void Contacts::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{

 if (mouseEvent->buttons() == Qt::LeftButton)
     {
        //если у контакта нет соседей
        if( neighbourContact==NULL )
        {
            if(!isChecked)
                SetChecked(true);
            else
                SetChecked(false);


            int a=dynamic_cast<Scene*>(this->scene())->GetDrawContactLine();
            a++;
            if(a==1) //Начало отрисовки контакта
                dynamic_cast<Scene*>(this->scene())->SetBeginDrawContact(this);
            if(a==2) //Есть возможность отрисовки контакта
               {
                    dynamic_cast<Scene*>(this->scene())->SetEndDrawContact(this);
               }

            dynamic_cast<Scene*>(this->scene())->SetDrawContactLine(a);
        }

        else //если есть соседи, выделить контакт
            if(neighbourContact!=NULL && neighbourContact->GetNeighbour()!=NULL )
            {
                if(!isChecked || !neighbourContact->GetIsChecked())
                {
                    this->SetChecked(true);
                    neighbourContact->SetChecked(true);
                }
                else
                    {
                        neighbourContact->SetChecked(false);
                        this->SetChecked(false);

                    }
            }


        this->scene()->update(this->scene()->sceneRect());
 }
}

void Contacts::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
painter->setRenderHint(QPainter::Antialiasing);



    switch (contactOrientation) {
    case Bottom:
        painter->drawText(positionContact.x(),positionContact.y()-MainElement::getRad()/2.0,nameContact);
        break;
    case Top:
        painter->drawText(positionContact.x(),positionContact.y()+MainElement::getRad()*2,nameContact);
        break;
    case Left:
        painter->drawText(positionContact.x()+MainElement::getRad()*1.5,positionContact.y()+MainElement::getRad(),nameContact);
        break;
    case Right:
        painter->drawText(positionContact.x()-MainElement::getRad()*2.2,positionContact.y()+MainElement::getRad()/2.0,nameContact);
        break;
    default:
        break;
    }


    QBrush br(Qt::SolidPattern);
    QPen pen = this->pen();
    pen.setWidth(MainElement::getWidthLinesContacts());
    painter->setPen(pen);
    br.setColor(pen.color());
    painter->setBrush(br);



    painter->drawEllipse(this->rect());


}



void Contacts::SetPositionContact(QPoint a)
{
    positionContact=a;   
}
bool Contacts::getIsDrawedConnection() const
{
    return isDrawedConnection;
}

void Contacts::setIsDrawedConnection(bool value)
{
    isDrawedConnection = value;
}
int Contacts::getNum() const
{
    return num;
}

void Contacts::setNum(int value)
{
    num = value;
}




