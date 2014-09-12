#include "scene.h"
#include <cmath>
#include <QGraphicsView>
#include "blockrelay.h"

#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QHBoxLayout>
int Scene::scene_width=15000;
int Scene::scene_height=15000;

Scene::Scene(QObject* parent): QGraphicsScene(parent)
{
    MainElement::InitConstans();
    this->setSceneRect(0,0,scene_width,scene_height);

    nElement=0;
    drawContactLine=0;
    beginContact=NULL;
    endContact=NULL;
    question = new QDialog;

}


void Scene::SetDrawContactLine(int a)
{
    drawContactLine=a;
    if(drawContactLine==2)
    {
        beginContact->SetChecked(false);
        endContact->SetChecked(false);

        if(beginContact->GetNeighbour()==NULL && endContact->GetNeighbour()==NULL && beginContact!=endContact && dynamic_cast<MainElement*>(beginContact->parentItem())!=dynamic_cast<MainElement*>(endContact->parentItem()))
        {
        beginContact->SetNeighbour(endContact);
        endContact->SetNeighbour(beginContact);
        }


        beginContact=NULL;
        endContact=NULL;
        drawContactLine=0;
    }


}

void Scene::DeleteConnectionLine()
{
    for(int i=0;i<arrElement.size();i++)
    {
        QVector <Contacts*> tempContacts = arrElement[i]->GetArrContacts();
        for(int j=0;j<tempContacts.size();j++)
        {
            if( tempContacts[j]->GetNeighbour()!=NULL && tempContacts[j]->GetIsChecked() )
            {

                    if(arrElement[i]->CreateDialog())
                    {

                        tempContacts[j]->SetChecked(false);
                        tempContacts[j]->setIsDrawedConnection(false);
                        tempContacts[j]->GetNeighbour()->SetChecked(false);
                        tempContacts[j]->GetNeighbour()->setIsDrawedConnection(false);
                        tempContacts[j]->GetNeighbour()->SetNeighbour(NULL);
                        tempContacts[j]->SetNeighbour(NULL);
                        update(this->sceneRect());

                    }
                    else
                    {
                        tempContacts[j]->SetChecked(false);
                        tempContacts[j]->GetNeighbour()->SetChecked(false);
                        update(this->sceneRect());

                    }


            }
        }


    }

}



bool Scene::ChangeDifferentParametrs(QString s)
{
    int parametr=0;
    if(!s.compare("Задайте радиус контакта"))
    {
        parametr = MainElement::getRad();
    }

    if(!s.compare("Задайте толщину линий элементов"))
    {
        parametr=MainElement::getWidthLinesElements();
    }

    if(!s.compare("Задайте толщину линий контактов"))
    {
        parametr=MainElement::getWidthLinesContacts();
    }

    QPushButton okButton,cancelButton;

    okButton.setText(tr("OK"));
    cancelButton.setText(tr("Cancel"));

    QVBoxLayout layout;



     question->setLayout(&layout);


         QHBoxLayout layoutText1;
         QLabel text1;
         text1.setText(s);
         QTextEdit parametrText;
         parametrText.setMaximumHeight(30);
         parametrText.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
         parametrText.setText(QString::number(parametr));
         layoutText1.addWidget(&text1);
         layoutText1.addWidget(&parametrText);


     layout.addLayout(&layoutText1);
     layout.addWidget(&okButton);
     layout.addWidget(&cancelButton);

     question->setLayout(&layout);

     QObject::connect(&okButton, SIGNAL(clicked()), question, SLOT(accept()));
     QObject::connect(&cancelButton, SIGNAL(clicked()), question, SLOT(reject()));
     question->setVisible(true);
     question->show();
     question->exec();

     if(question->result() == QDialog::Accepted)
     {
         parametr=parametrText.toPlainText().toInt();

         if(parametr!=0)
         {
            if(!s.compare("Задайте радиус контакта"))
            {
                MainElement::setRad(parametr);
                for(int i=0;i<arrElement.size();i++)
                {
                        arrElement[i]->ReDrawContact();

                }
            }

            if(!s.compare("Задайте толщину линий элементов") && parametr!=0)
            {
                MainElement::setWidthLinesElements(parametr);
            }

            if(!s.compare("Задайте толщину линий контактов") && parametr!=0)
            {
                MainElement::setWidthLinesContacts(parametr);
            }

         }

         return true;
     }

     if(question->result() == QDialog::Rejected)
     {
          return false;
     }
}
QVector<MainElement *> Scene::getArrElement() const
{
    return arrElement;
}

void Scene::setArrElement(const QVector<MainElement *> &value)
{
    arrElement = value;
}


bool Scene::ChangeSiezeBlocks(QString s)
{

    int X=BlockRelay::getSiezeBlockX(), Y=BlockRelay::getSiezeBlockY();
    QPushButton okButton,cancelButton;

    okButton.setText(tr("OK"));
    cancelButton.setText(tr("Cancel"));

    QHBoxLayout layout;

    layout.addWidget(&cancelButton);
    layout.addWidget(&okButton);

    QLabel text;

    text.setText(s);
    layout.setDirection(QBoxLayout::BottomToTop);
    layout.addWidget(&text);

     question->setLayout(&layout);


         QHBoxLayout layoutText1;
         QLabel text1;
         text1.setText("Размер по Ох");
         QTextEdit siezeX;
         siezeX.setMaximumHeight(30);
         siezeX.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
         siezeX.setText(QString::number(X));
         layoutText1.addWidget(&text1);
         layoutText1.addWidget(&siezeX);

         QHBoxLayout layoutText2;
         QLabel text2;
         text2.setText("Размер по Оy");
         QTextEdit siezeY;
         siezeY.setMaximumHeight(30);
         siezeY.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
         siezeY.setText(QString::number(Y));
         layoutText2.addWidget(&text2);
         layoutText2.addWidget(&siezeY);

     layout.addLayout(&layoutText1);
     layout.addLayout(&layoutText2);
     question->setLayout(&layout);

     QObject::connect(&okButton, SIGNAL(clicked()), question, SLOT(accept()));
     QObject::connect(&cancelButton, SIGNAL(clicked()), question, SLOT(reject()));
     question->setVisible(true);
     question->show();
     question->exec();

     if(question->result() == QDialog::Accepted)
     {
         X=siezeX.toPlainText().toInt();
         Y=siezeY.toPlainText().toInt();

         if(X!=0 && Y!=0)
         {
         BlockRelay::setSiezeBlockX(X);
         BlockRelay::setSiezeBlockY(Y);

         for(int i=0;i<arrElement.size();i++)
         {
             if(dynamic_cast<BlockRelay*>(arrElement[i])!=NULL)
             {
                 arrElement[i]->setSizeX(X);
                 arrElement[i]->setSizeY(Y);
                 arrElement[i]->ReDrawContact();
             }
         }
         }

         return true;
     }

     if(question->result() == QDialog::Rejected)
     {
          return false;
     }


}


void Scene::drawBackground(QPainter *painter, const QRectF &rect)
{

    const int gridSize = MainElement::GetStepGrid();

    const int realLeft = static_cast<int>(std::floor(rect.left()));
    const int realRight = static_cast<int>(std::ceil(rect.right()));
    const int realTop = static_cast<int>(std::floor(rect.top()));
    const int realBottom = static_cast<int>(std::ceil(rect.bottom()));

    // Draw grid.
    const int firstLeftGridLine = realLeft - (realLeft % gridSize);
    const int firstTopGridLine = realTop - (realTop % gridSize);

    QVarLengthArray<QLine, 100> lines;

    for (qreal x = firstLeftGridLine; x <= realRight; x += gridSize)
        lines.append(QLine(x, realTop, x, realBottom));
    for (qreal y = firstTopGridLine; y <= realBottom; y += gridSize)
        lines.append(QLine(realLeft, y, realRight, y));

    //painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(QColor(220, 220, 220), 0.0));
    painter->drawLines(lines.data(), lines.size());

    // Draw axes.
    painter->setPen(QPen(Qt::lightGray, 0.0));
    painter->drawLine(0, realTop, 0, realBottom);
    painter->drawLine(realLeft, 0, realRight, 0);


    DrawContactsLine(painter, rect);
}

void Scene::DrawContactsLine(QPainter *painter, const QRectF &rect)
{

    for(int i=0; i<arrElement.size();i++)
    {
        QVector<Contacts*> a = arrElement[i]->GetArrContacts();
        for(int j=0;j<a.size();j++)
        {

            Contacts* neighbourContact = a[j]->GetNeighbour();

            if(neighbourContact!=NULL && neighbourContact->GetNeighbour()!=NULL && !a[j]->getIsDrawedConnection())
                {

                QPen pen = a[j]->pen();
                pen.setWidth(MainElement::getWidthLinesContacts());
                painter->setPen(pen);

                int xpos1 = a[j]->GetPositionContact().x()+a[j]->parentItem()->pos().x();
                int ypos1 = a[j]->GetPositionContact().y()+a[j]->parentItem()->pos().y();

                int xpos2 = neighbourContact->GetPositionContact().x()+neighbourContact->parentItem()->pos().x();
                int ypos2 = neighbourContact->GetPositionContact().y()+neighbourContact->parentItem()->pos().y();


                int rightDefaultX = (dynamic_cast<MainElement*>(a[j]->parentItem())->getSizeX()+0.5)*MainElement::GetStepGrid() + a[j]->parentItem()->pos().x();
                 int downDefaultY  = (dynamic_cast<MainElement*>(a[j]->parentItem())->getSizeY()+0.5)*MainElement::GetStepGrid() + a[j]->parentItem()->pos().y();

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

                if((a[j]->Getorientation()==Right && neighbourContact->Getorientation()==Left) )
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

                if((a[j]->Getorientation()==Left && neighbourContact->Getorientation()==Right) )
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

                if((a[j]->Getorientation()==Left && neighbourContact->Getorientation()==Left))
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

                if((a[j]->Getorientation()==Right && neighbourContact->Getorientation()==Right))
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

                if((a[j]->Getorientation()==Top && neighbourContact->Getorientation()==Top))
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

                if((a[j]->Getorientation()==Bottom && neighbourContact->Getorientation()==Bottom))
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

                if((a[j]->Getorientation()==Bottom && neighbourContact->Getorientation()==Top))
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

                if((a[j]->Getorientation()==Top && neighbourContact->Getorientation()==Bottom))
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

                if((a[j]->Getorientation()==Top && neighbourContact->Getorientation()==Left))
                {
                    painter->drawLine(xpos1,ypos1, xpos1, upLine1);
                    painter->drawLine(xpos1, upLine1, leftLine2, upLine1 );
                    painter->drawLine(leftLine2, upLine1  , leftLine2, ypos2 );
                    painter->drawLine(leftLine2, ypos2  , xpos2, ypos2 );

                }

                if((a[j]->Getorientation()==Left && neighbourContact->Getorientation()==Top))
                {
                    painter->drawLine(xpos1,ypos1, leftLine1, ypos1);
                    painter->drawLine(leftLine1, ypos1, leftLine1, upLine2 );
                    painter->drawLine(leftLine1, upLine2 , xpos2, upLine2 );
                    painter->drawLine(xpos2, upLine2 , xpos2, ypos2 );

                }

                if((a[j]->Getorientation()==Top && neighbourContact->Getorientation()==Right))
                {
                    painter->drawLine(xpos1,ypos1, xpos1, upLine1);
                    painter->drawLine(xpos1, upLine1, rightLine2, upLine1 );
                    painter->drawLine(rightLine2, upLine1  , rightLine2, ypos2 );
                    painter->drawLine(rightLine2, ypos2  , xpos2, ypos2 );

                }

                if((a[j]->Getorientation()==Right && neighbourContact->Getorientation()==Top))
                {
                    painter->drawLine(xpos1,ypos1, rightLine1, ypos1);
                    painter->drawLine(rightLine1, ypos1, rightLine1, upLine2 );
                    painter->drawLine(rightLine1, upLine2 , xpos2, upLine2 );
                    painter->drawLine(xpos2, upLine2 , xpos2, ypos2 );

                }

                if((a[j]->Getorientation()==Bottom && neighbourContact->Getorientation()==Left))
                {
                    painter->drawLine(xpos1,ypos1, xpos1, downLine1);
                    painter->drawLine(xpos1, downLine1, leftLine2, downLine1 );
                    painter->drawLine(leftLine2, downLine1  , leftLine2, ypos2 );
                    painter->drawLine(leftLine2, ypos2  , xpos2, ypos2 );

                }

                if((a[j]->Getorientation()==Left && neighbourContact->Getorientation()==Bottom))
                {
                    painter->drawLine(xpos1,ypos1, leftLine1, ypos1);
                    painter->drawLine(leftLine1, ypos1, leftLine1, downLine2 );
                    painter->drawLine(leftLine1, downLine2 , xpos2, downLine2 );
                    painter->drawLine(xpos2, downLine2 , xpos2, ypos2 );

                }

                if((a[j]->Getorientation()==Bottom && neighbourContact->Getorientation()==Right))
                {
                    painter->drawLine(xpos1,ypos1, xpos1, downLine1);
                    painter->drawLine(xpos1, downLine1, rightLine2, downLine1 );
                    painter->drawLine(rightLine2, downLine1  , rightLine2, ypos2 );
                    painter->drawLine(rightLine2, ypos2  , xpos2, ypos2 );

                }

                if((a[j]->Getorientation()==Right && neighbourContact->Getorientation()==Bottom))
                {
                    painter->drawLine(xpos1,ypos1, rightLine1, ypos1);
                    painter->drawLine(rightLine1, ypos1, rightLine1, downLine2 );
                    painter->drawLine(rightLine1, downLine2 , xpos2, downLine2 );
                    painter->drawLine(xpos2, downLine2 , xpos2, ypos2 );

                }



                neighbourContact->setIsDrawedConnection(true);
        }
    }
}

}

void Scene::AddBlock()
{
    arrElement.append(new BlockRelay());
    arrElement.last()->setVisible(true);
    this->addItem(arrElement.last());

    bool fl = true;
    while(fl)
    {
        fl=false;
    for(int i=0;i<arrElement.size()-1;i++)
    {
        if(arrElement[i]->pos()==arrElement.last()->pos())
        {
            arrElement.last()->moveBy(dynamic_cast<MainElement*>(arrElement[i])->getSizeX()*MainElement::GetStepGrid(), 0);
            fl=true;

        }
    }
    }




    nElement++;

}


void Scene::DeleteElement(MainElement* element)
{
    for(int i=0;i<arrElement.size();i++)
    {
        if(arrElement[i]==element)
        {
            delete arrElement[i];
            arrElement.remove(i);
            nElement--;
            update(this->sceneRect());
        }
    }

}

Scene::~Scene()
{
    for(int i=0;i<arrElement.size();i++)
    {
        delete arrElement[i];
    }

    delete question;
}
