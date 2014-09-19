#include "scene.h"
#include <cmath>
#include <QGraphicsView>
#include "blockrelay.h"
#include "chainpoint.h"
#include "chainpolus.h"
#include "relayrelay.h"
#include "relaycontact.h"
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QMessageBox>
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

    if(!s.compare("Задайте шаг сетки"))
    {
        parametr=MainElement::GetStepGrid();
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

            if(!s.compare("Задайте шаг сетки") && parametr!=0)
            {
                MainElement::SetStepGrid(parametr);
                for(int i=0; i<arrElement.size();i++)
                {
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

QString Scene::SetStringParamElementDialog(QString s)
{
    QPushButton okButton;

    okButton.setText(tr("OK"));

    QVBoxLayout layout;



     question->setLayout(&layout);


         QHBoxLayout layoutText1;
         QLabel text1;
         text1.setText("Введите имя элемента");
         QTextEdit parametrText;
         parametrText.setMaximumHeight(30);
         parametrText.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
         parametrText.setText(s);
         layoutText1.addWidget(&text1);
         layoutText1.addWidget(&parametrText);


     layout.addLayout(&layoutText1);
     layout.addWidget(&okButton);

     question->setLayout(&layout);

     QObject::connect(&okButton, SIGNAL(clicked()), question, SLOT(accept()));
     question->setVisible(true);
     question->show();
     question->exec();

     if(question->result() == QDialog::Accepted)
     {
         return parametrText.toPlainText();
     }

     return "";



}

QVector<MainElement *> Scene::getArrElement() const
{
    return arrElement;
}

void Scene::setArrElement(const QVector<MainElement *> &value)
{
    arrElement = value;
}

void Scene::openFile(QFile &file)
{
    qDebug()<<"open";

    for(int i=0;i<arrElement.size();i++)
    {
        delete arrElement[i];
    }
    arrElement.clear();

    firstReading(file);

    file.seek(0);

    //if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    //{
    //         return;
   // }
    secondReading(file);

}

void Scene::setStationParametrs(QXmlStreamAttributes &attrib)
{
    if(attrib.hasAttribute("STEP_GRID"))
    {
        MainElement::SetStepGrid(attrib.value("STEP_GRID").toInt());
    }
    if(attrib.hasAttribute("RadContact"))
    {
        MainElement::setRad(attrib.value("RadContact").toInt());
    }

    if(attrib.hasAttribute("widthLinesElements"))
    {
        MainElement::setWidthLinesElements(attrib.value("widthLinesElements").toInt());
    }

    if(attrib.hasAttribute("widthLinesContacts"))
    {
        MainElement::setWidthLinesContacts(attrib.value("widthLinesContacts").toInt());
    }
}

void Scene::setElementParametrs(QXmlStreamAttributes &attrib)
{
    int typeElement=0, idElement=0, posX=0, posY=0, sizeX=0, sizeY=0, nContactsLeft=0, nContactsDown=0, nContactsRight=0, nContactsUp=0;
    bool isMirrorGorizontal=false, isMirrorVertical=false;
    QString name="";

    if(attrib.hasAttribute("typeElement"))
    {
        typeElement = attrib.value("typeElement").toInt();
    }

    if(attrib.hasAttribute("idElement"))
    {
        idElement = attrib.value("idElement").toInt();
    }

    if(attrib.hasAttribute("posX"))
    {
        posX = attrib.value("posX").toInt();
    }

    if(attrib.hasAttribute("posY"))
    {
        posY = attrib.value("posY").toInt();
    }

    if(attrib.hasAttribute("isMirrorGorizontal"))
    {
        if(attrib.value("isMirrorGorizontal").toInt()==1)
            isMirrorGorizontal=true;
        else
            isMirrorGorizontal=false;

    }

    if(attrib.hasAttribute("isMirrorVertical"))
    {
        if(attrib.value("isMirrorVertical").toInt()==1)
            isMirrorVertical=true;
        else
            isMirrorVertical=false;
    }

    if(attrib.hasAttribute("sizeX"))
    {
        sizeX = attrib.value("sizeX").toInt();
    }

    if(attrib.hasAttribute("sizeY"))
    {
        sizeY = attrib.value("sizeY").toInt();
    }

    if(attrib.hasAttribute("nContactsLeft"))
    {
        nContactsLeft = attrib.value("nContactsLeft").toInt();
    }

    if(attrib.hasAttribute("nContactsDown"))
    {
        nContactsDown = attrib.value("nContactsDown").toInt();
    }

    if(attrib.hasAttribute("nContactsRight"))
    {
        nContactsRight = attrib.value("nContactsRight").toInt();
    }

    if(attrib.hasAttribute("nContactsUp"))
    {
        nContactsUp = attrib.value("nContactsUp").toInt();
    }

    if(attrib.hasAttribute("name"))
    {
        name = attrib.value("name").toString();
    }

    switch (typeElement)
    {
    case 5:
        arrElement.append(new BlockRelay(idElement, posX, posY, isMirrorGorizontal, isMirrorVertical, sizeX, sizeY, nContactsLeft, nContactsDown, nContactsRight, nContactsUp,name));
        arrElement.last()->setVisible(true);
        this->addItem(arrElement.last());
        break;
    case 4:
        arrElement.append(new ChainPolus(idElement, posX, posY, isMirrorGorizontal, isMirrorVertical, sizeX, sizeY, nContactsLeft, nContactsDown, nContactsRight, nContactsUp,name));
        arrElement.last()->setVisible(true);
        this->addItem(arrElement.last());
        break;
    case 3:
        arrElement.append(new RelayContact(idElement, posX, posY, isMirrorGorizontal, isMirrorVertical, sizeX, sizeY, nContactsLeft, nContactsDown, nContactsRight, nContactsUp,name));
        arrElement.last()->setVisible(true);
        this->addItem(arrElement.last());
        break;
    case 1:
        arrElement.append(new RelayRelay(idElement, posX, posY, isMirrorGorizontal, isMirrorVertical, sizeX, sizeY, nContactsLeft, nContactsDown, nContactsRight, nContactsUp,name));
        arrElement.last()->setVisible(true);
        this->addItem(arrElement.last());
        break;
    case 0:
        arrElement.append(new ChainPoint(idElement, posX, posY, isMirrorGorizontal, isMirrorVertical, sizeX, sizeY, nContactsLeft, nContactsDown, nContactsRight, nContactsUp,name));
        arrElement.last()->setVisible(true);
        this->addItem(arrElement.last());
        break;

    default:
        break;
    }
}

void Scene::readOneElement(QXmlStreamReader &reader)
{
    QXmlStreamAttributes attrib = reader.attributes();

    int id=0;

    if(attrib.hasAttribute("idElement"))
    {
        id=attrib.value("idElement").toInt();
    }

       MainElement* element = findElementById(id);

       if(!element)
           return;

        while( !reader.hasError() &&  !(reader.isEndElement() && reader.name() == "Element") )
        {
             QXmlStreamReader::TokenType token = reader.readNext();

             if(token == QXmlStreamReader::StartElement)
             {
                 if(reader.name() == "Contact")
                 {
                     QXmlStreamAttributes attribContacts = reader.attributes();
                     int num = attribContacts.value("num").toInt();
                     Contacts* contactElement = element->findContactByNum(num);
                     contactElement->setNameContact( attribContacts.value("nameContact").toString());

                     if(attribContacts.hasAttribute("NeighbourBlock") && attribContacts.hasAttribute("NeighbourContact"))
                     {
                     if(attribContacts.value("NeighbourBlock").toString()!= "" && attribContacts.value("NeighbourContact").toString()!="")
                     {
                         int idNeigbourBlock = attribContacts.value("NeighbourBlock").toInt();
                         int numNeighbourContact = attribContacts.value("NeighbourContact").toInt();
                         contactElement->SetNeighbour(findElementById(idNeigbourBlock)->findContactByNum(numNeighbourContact));
                     }
                     }

                 }

                 if(reader.name() == "Parametrs")
                 {
                     QXmlStreamAttributes attribParametrs = reader.attributes();

                     if(attribParametrs.hasAttribute("isVoltage"))
                     {
                         if(attribParametrs.value("isVoltage").toInt()==1)
                         {
                            dynamic_cast<RelayRelay*>(element)->setIsVoltage(true);
                         }
                         else
                         {
                             dynamic_cast<RelayRelay*>(element)->setIsVoltage(false);
                         }
                     }

                     if(attribParametrs.hasAttribute("delay"))
                     {
                            dynamic_cast<RelayRelay*>(element)->setDelay(attribParametrs.value("delay").toInt());
                     }

                     if(attribParametrs.hasAttribute("isLinked"))
                     {
                         if(attribParametrs.value("isLinked").toInt()==1)
                         {
                            dynamic_cast<RelayContact*>(element)->setIsLinked(true);
                         }
                         else
                         {
                             dynamic_cast<RelayContact*>(element)->setIsLinked(false);
                         }
                     }

                     if(attribParametrs.hasAttribute("associatedRelay") && attribParametrs.value("associatedRelay").toString()!="")
                     {
                            dynamic_cast<RelayContact*>(element)->setAssociatedRelay(dynamic_cast<RelayRelay*>(findElementById(attribParametrs.value("associatedRelay").toInt())));
                     }


                 }


             }

        }




}

void Scene::firstReading(QFile &file)
{
    QXmlStreamReader reader(file.readAll());

    while(!reader.atEnd() && !reader.hasError())
    {
        QXmlStreamReader::TokenType token = reader.readNext();

        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }

        if(token == QXmlStreamReader::StartElement)
        {
            if(reader.name() == "Station")
            {
                QXmlStreamAttributes attrib = reader.attributes();
                setStationParametrs(attrib);
            }

            if(reader.name() == "Element")
            {
                QXmlStreamAttributes attrib = reader.attributes();
                setElementParametrs(attrib);
            }


        }


    }



    if(reader.hasError())
    {
        QMessageBox::critical(this->views().first()->cornerWidget(),
                              "GeneratorOut::parseXML",
                              reader.errorString(),
                              QMessageBox::Ok);
    }

    reader.clear();
    this->update();
}

void Scene::secondReading(QFile &file)
{

    QXmlStreamReader reader(file.readAll());

    while(!reader.atEnd() && !reader.hasError())
    {
        QXmlStreamReader::TokenType token = reader.readNext();

        if(token == QXmlStreamReader::StartDocument)
        {
            continue;
        }


        if(token == QXmlStreamReader::StartElement)
        {

            if(reader.name() == "Element")
            {
                readOneElement(reader);

            }

        }
    }



    if(reader.hasError())
    {
        QMessageBox::critical(this->views().first()->cornerWidget(),
                              "GeneratorOut::parseXML",
                              reader.errorString(),
                              QMessageBox::Ok);
    }

    reader.clear();
    this->update();


}





void Scene::saveFile(QFile &file)
{
    qDebug()<<"save";

    for(int i=0;i<arrElement.size();i++)
    {
        arrElement[i]->setIdElement(i);
    }

    QXmlStreamWriter writer(&file);

    writer.setAutoFormatting(true);
    writer.writeStartDocument("1.0");

    if(arrElement.size()==0)
        return;



    writer.writeStartElement("Station");
    writer.writeAttribute("STEP_GRID", QString::number(MainElement::GetStepGrid()));
    writer.writeAttribute("RadContact", QString::number(MainElement::getRad()));
    writer.writeAttribute("widthLinesElements", QString::number(MainElement::getWidthLinesElements()));
    writer.writeAttribute("widthLinesContacts", QString::number(MainElement::getWidthLinesContacts()));

    writer.writeStartElement("Elements");
    for(int i=0;i<arrElement.size();i++)
    {
        arrElement[i]->SaveToXml(writer);
    }
    writer.writeEndElement();//Elements

    writer.writeEndElement();//Station
    writer.writeEndDocument();


}

MainElement* Scene::findElementById(int id)
{
    for(int i=0;i<arrElement.size();i++)
    {
        if(arrElement[i]->getIdElement()==id)
            return arrElement[i];
    }

    return NULL;
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

void Scene::AddTestBlock()
{
    arrElement.append(new BlockRelay());
    arrElement.last()->setVisible(true);
    this->addItem(arrElement.last());
    arrElement.last()->moveBy(MainElement::GetStepGrid(),MainElement::GetStepGrid());

    bool fl = true;
    while(fl)
    {
        fl=false;
    for(int i=0;i<arrElement.size()-1;i++)
    {
        if(arrElement[i]->pos()==arrElement.last()->pos())
        {
            arrElement.last()->moveBy(dynamic_cast<MainElement*>(arrElement[i])->getSizeX()*MainElement::GetStepGrid()+MainElement::GetStepGrid(), 0);
            fl=true;

        }
    }
    }

    nElement++;

}

void Scene::AddFileBlock()
{
    QString saveDir;

    QString fileName = QFileDialog::getOpenFileName(this->views().last()->cornerWidget(),
             tr("Открыть блок"), "C:/", "*.block");

    if(!fileName.compare(""))
        return;

    QDir dir(fileName);
    saveDir = dir.absolutePath();

    QFile f(saveDir);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
             return;


    QXmlStreamReader reader(f.readAll());
    QString name = "";
    int nContactsLeft=0, nContactsDown=0, ncOntactsRight=0, nContactsUp=0;

    while(!reader.atEnd() && !reader.hasError())
    {
        QXmlStreamReader::TokenType token = reader.readNext();

        if(token == QXmlStreamReader::StartElement)
        {

            if(reader.name() == "Block")
            {
                QXmlStreamAttributes attrib = reader.attributes();
                name = attrib.value("name").toString();

            }
            if(reader.name() == "Contacts")
            {
                QXmlStreamAttributes attrib = reader.attributes();
                nContactsLeft = attrib.value("left").toInt();
                nContactsDown = attrib.value("down").toInt();
                ncOntactsRight = attrib.value("right").toInt();
                nContactsUp = attrib.value("up").toInt();

                int sizeX = std::max(nContactsUp, nContactsDown)/2.0 + 2;
                int sizeY= std::max(nContactsLeft, ncOntactsRight)/2.0 + 2;

                if(sizeX<4)
                    sizeX=4;
                if(sizeY<4)
                    sizeY=4;

                arrElement.append(new BlockRelay(0,0,0,false,false,sizeX,sizeY, nContactsLeft, nContactsDown, ncOntactsRight, nContactsUp, name));
                arrElement.last()->setVisible(true);
                this->addItem(arrElement.last());
                arrElement.last()->moveBy(MainElement::GetStepGrid(),MainElement::GetStepGrid());

                bool fl = true;
                while(fl)
                {
                    fl=false;
                for(int i=0;i<arrElement.size()-1;i++)
                {
                    if(arrElement[i]->pos()==arrElement.last()->pos())
                    {
                        arrElement.last()->moveBy(dynamic_cast<MainElement*>(arrElement[i])->getSizeX()*MainElement::GetStepGrid()+MainElement::GetStepGrid(), 0);
                        fl=true;

                    }
                }
                }
                nElement++;

                ReadContactsFileBlock(reader, arrElement.last());


            }

        }
    }

    if(reader.hasError())
    {
        QMessageBox::critical(this->views().first()->cornerWidget(),
                              "GeneratorOut::parseXML",
                              reader.errorString(),
                              QMessageBox::Ok);
    }

    reader.clear();
    this->update();


    f.close();

}

void Scene::ReadContactsFileBlock(QXmlStreamReader &reader, MainElement *element)
{

               if(!element)
                   return;

                while( !reader.hasError() &&  !(reader.isEndElement() && reader.name() == "Contacts") )
                {

                  QXmlStreamReader::TokenType token = reader.readNext();

                   if(token == QXmlStreamReader::StartElement)
                     {
                         if(reader.name() == "Contact")
                         {
                             QXmlStreamAttributes attribContacts = reader.attributes();
                             int num = attribContacts.value("num").toInt();
                             Contacts* contactElement = element->findContactByNum(num);
                             contactElement->setNameContact( attribContacts.value("name").toString());


                         }
                    }
                }
}

void Scene::AddPoint()
{
    arrElement.append(new ChainPoint());
    arrElement.last()->setVisible(true);
    this->addItem(arrElement.last());
    arrElement.last()->moveBy(MainElement::GetStepGrid(),MainElement::GetStepGrid());

    bool fl = true;
    while(fl)
    {
        fl=false;
    for(int i=0;i<arrElement.size()-1;i++)
    {
        if(arrElement[i]->pos()==arrElement.last()->pos())
        {
            arrElement.last()->moveBy(dynamic_cast<MainElement*>(arrElement[i])->getSizeX()*MainElement::GetStepGrid()+MainElement::GetStepGrid(), 0);
            fl=true;

        }
    }
    }




    nElement++;
}

void Scene::AddPolus()
{
    arrElement.append(new ChainPolus());
    arrElement.last()->setVisible(true);
    this->addItem(arrElement.last());
    arrElement.last()->moveBy(MainElement::GetStepGrid(),MainElement::GetStepGrid());

    bool fl = true;
    while(fl)
    {
        fl=false;
    for(int i=0;i<arrElement.size()-1;i++)
    {
        if(arrElement[i]->pos()==arrElement.last()->pos())
        {
            arrElement.last()->moveBy(dynamic_cast<MainElement*>(arrElement[i])->getSizeX()*MainElement::GetStepGrid()+MainElement::GetStepGrid(), 0);
            fl=true;

        }
    }
    }


arrElement.last()->setNameElement(SetStringParamElementDialog(arrElement.last()->getNameElement()));


    nElement++;
}

void Scene::AddRelayContact()
{
    arrElement.append(new RelayContact());
    arrElement.last()->setVisible(true);
    this->addItem(arrElement.last());

    arrElement.last()->moveBy(MainElement::GetStepGrid(),MainElement::GetStepGrid());

    bool fl = true;
    while(fl)
    {
        fl=false;
    for(int i=0;i<arrElement.size()-1;i++)
    {
        if(arrElement[i]->pos()==arrElement.last()->pos())
        {
            arrElement.last()->moveBy(dynamic_cast<MainElement*>(arrElement[i])->getSizeX()*MainElement::GetStepGrid()+MainElement::GetStepGrid(), 0);
            fl=true;

        }
    }
    }

arrElement.last()->setNameElement(SetStringParamElementDialog(arrElement.last()->getNameElement()));

    nElement++;
}

void Scene::AddRelay()
{
    arrElement.append(new RelayRelay());
    arrElement.last()->setVisible(true);
    this->addItem(arrElement.last());
    arrElement.last()->moveBy(MainElement::GetStepGrid(),MainElement::GetStepGrid());

    bool fl = true;
    while(fl)
    {
        fl=false;
    for(int i=0;i<arrElement.size()-1;i++)
    {
        if(arrElement[i]->pos()==arrElement.last()->pos())
        {
            arrElement.last()->moveBy(dynamic_cast<MainElement*>(arrElement[i])->getSizeX()*MainElement::GetStepGrid()+MainElement::GetStepGrid(), 0);
            fl=true;

        }
    }
    }

arrElement.last()->setNameElement(SetStringParamElementDialog(arrElement.last()->getNameElement()));


    nElement++;

}


void Scene::DeleteElement(MainElement* element)
{

    if(dynamic_cast<RelayRelay*>(element)!=NULL )
    {
        for(int i1=0;i1<arrElement.size();i1++)
        {
            if(dynamic_cast<RelayContact*>(arrElement[i1])!=NULL && dynamic_cast<RelayContact*>(arrElement[i1])->getAssociatedRelay()==element)
            {
                dynamic_cast<RelayContact*>(arrElement[i1])->RemoveAssociatedRelay();
            }
        }
    }

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

