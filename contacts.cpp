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
    nameContact = "1-11";

    neighbourContact=NULL;

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
        painter->drawText(positionContact.x(),positionContact.y()-6,nameContact);
        break;
    case Top:
        painter->drawText(positionContact.x(),positionContact.y()+MainElement::getRad()*2.2,nameContact);
        break;
    case Left:
        painter->drawText(positionContact.x()+MainElement::getRad()*1.5,positionContact.y()+MainElement::getRad(),nameContact);
        break;
    case Right:
        painter->drawText(positionContact.x()-28,positionContact.y()+12,nameContact);
        break;
    default:
        break;
    }


    QPen pen = this->pen();
    pen.setWidth(MainElement::getWidthLinesContacts());
    painter->setPen(pen);

    painter->drawEllipse(this->rect());

    /*if(neighbourContact!=NULL && neighbourContact->GetNeighbour()!=NULL && !isDrawedConnection)
    {

    int xpos1 = positionContact.x();//+ mapToScene(parentItem()->pos()).x();
    int ypos1 = positionContact.y();//+ mapToScene(parentItem()->pos()).y();

    int xpos2 = neighbourContact->GetPositionContact().x()+ mapToScene(neighbourContact->parentItem()->pos()).x() - mapToScene(parentItem()->pos()).x();
    int ypos2 = neighbourContact->GetPositionContact().y()+ mapToScene(neighbourContact->parentItem()->pos()).y() - mapToScene(parentItem()->pos()).y();


    int rightDefaultX = (dynamic_cast<MainElement*>(this->parentItem())->getSizeX()+0.5)*MainElement::GetStepGrid();
    int leftDefaultX  = (0-0.5)*MainElement::GetStepGrid();
     int upDefaultY  = (0-0.5)*MainElement::GetStepGrid();
     int downDefaultY  = (dynamic_cast<MainElement*>(this->parentItem())->getSizeY()+0.5)*MainElement::GetStepGrid();

     int upLine1=ypos1-MainElement::GetStepGrid()/2.0;
     int downLine1=ypos1+MainElement::GetStepGrid()/2.0;
     int leftLine1=xpos1-MainElement::GetStepGrid()/2.0;
     int rightLine1=xpos1+MainElement::GetStepGrid()/2.0;

     int upLine2=ypos2-MainElement::GetStepGrid()/2.0;
     int downLine2=ypos2+MainElement::GetStepGrid()/2.0;
     int leftLine2=xpos2-MainElement::GetStepGrid()/2.0;
     int rightLine2=xpos2+MainElement::GetStepGrid()/2.0;


    qDebug()<<"xpos1="<<xpos1<<endl;
    qDebug()<<"ypos1="<<ypos1<<endl;
    qDebug()<<"xpos2="<<xpos2<<endl;
    qDebug()<<"ypos2="<<ypos2<<endl;

    if((contactOrientation==Right && neighbourContact->Getorientation()==Left) )
    {
    if(xpos1<xpos2)
    {
        painter->drawLine(xpos1, ypos1, rightLine1, ypos1);
        painter->drawLine(rightLine1, ypos1, rightLine1, ypos2 );
        painter->drawLine(rightLine1, ypos2, xpos2, ypos2 );
    }

    if(xpos1>=xpos2)
    {
    painter->drawLine(xpos1, ypos1, rightLine1, ypos1);
    painter->drawLine(rightLine1, ypos1, rightLine1, downDefaultY );
    painter->drawLine(rightLine1, downDefaultY, leftLine2, downDefaultY );

    painter->drawLine(leftLine2, downDefaultY, leftLine2, ypos2 );
    painter->drawLine(leftLine2, ypos2, xpos2, ypos2 );

    }
    }

    if((contactOrientation==Left && neighbourContact->Getorientation()==Right) )
    {
        if(xpos1<=xpos2)
        {
            painter->drawLine(xpos1, ypos1, leftLine1, ypos1);
            painter->drawLine(leftLine1, ypos1, leftLine1, downDefaultY );
            painter->drawLine(leftLine1, downDefaultY, rightLine2, downDefaultY );

            painter->drawLine(rightLine2, downDefaultY, rightLine2, ypos2 );
            painter->drawLine(rightLine2, ypos2, xpos2, ypos2 );


        }

        if(xpos1>xpos2)
        {
            painter->drawLine(xpos1, ypos1, leftLine1, ypos1);
            painter->drawLine(leftLine1, ypos1, leftLine1, ypos2 );
            painter->drawLine(leftLine1, ypos2, xpos2, ypos2 );
        }
    }

    if((contactOrientation==Left && neighbourContact->Getorientation()==Left))
    {
    if(xpos1<=xpos2)
    {
    painter->drawLine(xpos1, ypos1, leftLine1, ypos1);
    painter->drawLine(leftLine1, ypos1, leftLine1, ypos2 );
    painter->drawLine(leftLine1, ypos2, xpos2, ypos2 );
    }

    if(xpos1>xpos2)
    {
        painter->drawLine(xpos2, ypos2, leftLine2, ypos2);
        painter->drawLine(leftLine2, ypos2, leftLine2, ypos1 );
        painter->drawLine(leftLine2, ypos1, xpos1, ypos1 );

    }
    }

    if((contactOrientation==Right && neighbourContact->Getorientation()==Right))
    {
    if(xpos1<=xpos2)
    {
        painter->drawLine(xpos2, ypos2, rightLine2, ypos2);
        painter->drawLine(rightLine2, ypos2, rightLine2, ypos1 );
        painter->drawLine(rightLine2, ypos1, xpos1, ypos1 );

    }

    if(xpos1>xpos2)
    {
        painter->drawLine(xpos1, ypos1, rightLine1, ypos1);
        painter->drawLine(rightLine1, ypos1, rightLine1, ypos2 );
        painter->drawLine(rightLine1, ypos2, xpos2, ypos2 );

    }
    }

    if((contactOrientation==Top && neighbourContact->Getorientation()==Top))
    {
    if(ypos1<=ypos2)
    {
        painter->drawLine(xpos1, ypos1, xpos1 , upLine1);
        painter->drawLine(xpos1 , upLine1, xpos2, upLine1 );
        painter->drawLine(xpos2, upLine1, xpos2, ypos2 );
    }

    if(ypos1>ypos2)
    {
        painter->drawLine(xpos2, ypos2, xpos2 , upLine2);
        painter->drawLine(xpos2 , upLine2, xpos1, upLine2 );
        painter->drawLine(xpos1, upLine2, xpos1, ypos1 );
    }
    }

    if((contactOrientation==Bottom && neighbourContact->Getorientation()==Bottom))
    {
    if(ypos1<=ypos2)
    {
        painter->drawLine(xpos2, ypos2, xpos2 , downLine2);
        painter->drawLine(xpos2 , downLine2, xpos1, downLine2 );
        painter->drawLine(xpos1, downLine2, xpos1, ypos1 );


    }

    if(ypos1>ypos2)
    {
        painter->drawLine(xpos1, ypos1, xpos1 , downLine1);
        painter->drawLine(xpos1 , downLine1, xpos2, downLine1 );
        painter->drawLine(xpos2, downLine1, xpos2, ypos2 );
    }
    }

    if((contactOrientation==Bottom && neighbourContact->Getorientation()==Top))
    {
    if(ypos1<ypos2)
    {
        painter->drawLine(xpos1, ypos1, xpos1, downLine1);
        painter->drawLine(xpos1, downLine1, xpos2, downLine1 );

        painter->drawLine(xpos2, downLine1, xpos2, ypos2 );


    }

    if(ypos1>=ypos2)
    {
        painter->drawLine(xpos1, ypos1, xpos1, downLine1 );
        painter->drawLine(xpos1, downLine1, rightDefaultX ,ypos1 + 0.5*MainElement::GetStepGrid() );

        painter->drawLine(rightDefaultX ,downLine1 ,rightDefaultX , upLine2 );
        painter->drawLine(rightDefaultX , upLine2, xpos2, upLine2 );
        painter->drawLine(xpos2, upLine2 ,xpos2,ypos2);
    }
    }

    if((contactOrientation==Top && neighbourContact->Getorientation()==Bottom))
    {
    if(ypos1<ypos2)
    {


        painter->drawLine(xpos1, ypos1, xpos1, upLine1 );
        painter->drawLine(xpos1, upLine1, rightDefaultX ,upLine1 );

        painter->drawLine(rightDefaultX ,upLine1 ,rightDefaultX , downLine2 );
        painter->drawLine(rightDefaultX , downLine2, xpos2, downLine2);
        painter->drawLine(xpos2, downLine2 ,xpos2,ypos2);


    }

    if(ypos1>=ypos2)
    {
        painter->drawLine(xpos1, ypos1, xpos1, upLine1);
        painter->drawLine(xpos1, upLine1, xpos2, upLine1);

        painter->drawLine(xpos2, upLine1, xpos2, ypos2 );
    }
    }

    if((contactOrientation==Top && neighbourContact->Getorientation()==Left))
    {
        painter->drawLine(xpos1,ypos1, xpos1, upLine1);
        painter->drawLine(xpos1, upLine1, leftLine2, upLine1 );
        painter->drawLine(leftLine2, upLine1  , leftLine2, ypos2 );
        painter->drawLine(leftLine2, ypos2  , xpos2, ypos2 );

    }

    if((contactOrientation==Left && neighbourContact->Getorientation()==Top))
    {
        painter->drawLine(xpos1,ypos1, leftLine1, ypos1);
        painter->drawLine(leftLine1, ypos1, leftLine1, upLine2 );
        painter->drawLine(leftLine1, upLine2 , xpos2, upLine2 );
        painter->drawLine(xpos2, upLine2 , xpos2, ypos2 );

    }

    if((contactOrientation==Top && neighbourContact->Getorientation()==Right))
    {
        painter->drawLine(xpos1,ypos1, xpos1, upLine1);
        painter->drawLine(xpos1, upLine1, rightLine2, upLine1 );
        painter->drawLine(rightLine2, upLine1  , rightLine2, ypos2 );
        painter->drawLine(rightLine2, ypos2  , xpos2, ypos2 );

    }

    if((contactOrientation==Right && neighbourContact->Getorientation()==Top))
    {
        painter->drawLine(xpos1,ypos1, rightLine1, ypos1);
        painter->drawLine(rightLine1, ypos1, rightLine1, upLine2 );
        painter->drawLine(rightLine1, upLine2 , xpos2, upLine2 );
        painter->drawLine(xpos2, upLine2 , xpos2, ypos2 );

    }

    if((contactOrientation==Bottom && neighbourContact->Getorientation()==Left))
    {
        painter->drawLine(xpos1,ypos1, xpos1, downLine1);
        painter->drawLine(xpos1, downLine1, leftLine2, downLine1 );
        painter->drawLine(leftLine2, downLine1  , leftLine2, ypos2 );
        painter->drawLine(leftLine2, ypos2  , xpos2, ypos2 );

    }

    if((contactOrientation==Left && neighbourContact->Getorientation()==Bottom))
    {
        painter->drawLine(xpos1,ypos1, leftLine1, ypos1);
        painter->drawLine(leftLine1, ypos1, leftLine1, downLine2 );
        painter->drawLine(leftLine1, downLine2 , xpos2, downLine2 );
        painter->drawLine(xpos2, downLine2 , xpos2, ypos2 );

    }

    if((contactOrientation==Bottom && neighbourContact->Getorientation()==Right))
    {
        painter->drawLine(xpos1,ypos1, xpos1, downLine1);
        painter->drawLine(xpos1, downLine1, rightLine2, downLine1 );
        painter->drawLine(rightLine2, downLine1  , rightLine2, ypos2 );
        painter->drawLine(rightLine2, ypos2  , xpos2, ypos2 );

    }

    if((contactOrientation==Right && neighbourContact->Getorientation()==Bottom))
    {
        painter->drawLine(xpos1,ypos1, rightLine1, ypos1);
        painter->drawLine(rightLine1, ypos1, rightLine1, downLine2 );
        painter->drawLine(rightLine1, downLine2 , xpos2, downLine2 );
        painter->drawLine(xpos2, downLine2 , xpos2, ypos2 );

    }



    neighbourContact->setIsDrawedConnection(true);

    }*/


}
bool Contacts::getIsDrawedConnection() const
{
    return isDrawedConnection;
}

void Contacts::setIsDrawedConnection(bool value)
{
    isDrawedConnection = value;
}



