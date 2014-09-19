#include "mainelement.h"
#include <QApplication>
#include <cmath>
#include <QGraphicsScene>
#include <scene.h>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QPen>
#include <blockrelay.h>
#include <relayrelay.h>
#include <relaycontact.h>
#include <QErrorMessage>
#include <QGraphicsView>

int MainElement::STEP_GRID=0;
int MainElement::rad=0;
bool MainElement::isSelectRelayMode=false;
int MainElement::widthLinesElements=2;
int MainElement::widthLinesContacts=1;
RelayContact* MainElement::relayContactSelected=NULL;



MainElement::MainElement(QGraphicsObject* parent) : QGraphicsObject(parent)
{
    isMirrorGorizontal=false;
    isMirrorVertical=false;
    idElement=0;

    setAcceptDrops(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    question = new QDialog;

    isSelectRelayMode=false;
    relayContactSelected=NULL;


}

MainElement::MainElement(int idElement, int posX, int posY, bool isMirrorGorizontal, bool isMirrorVertical, int sizeX, int sizeY, int nContactsLeft,int nContactsDown,int nContactsRight,int nContactsUp,QString name, QGraphicsObject* parent): QGraphicsObject(parent)
{
    MainElement::idElement=idElement;
    MainElement::isMirrorGorizontal=isMirrorGorizontal;
    MainElement::isMirrorVertical=isMirrorVertical;
    MainElement::sizeX=sizeX;
    MainElement::sizeY=sizeY;
    MainElement::nContactsLeft=nContactsLeft;
    MainElement::nContactsRight=nContactsRight;
    MainElement::nContactsDown=nContactsDown;
    MainElement::nContactsUp=nContactsUp;
    MainElement::nameElement=name;
    this->setPos(posX, posY);

    setAcceptDrops(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    question = new QDialog;

    isSelectRelayMode=false;
    relayContactSelected=NULL;
    nContacts = nContactsDown + nContactsUp + nContactsLeft + nContactsRight;
}




void MainElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setRenderHint(QPainter::Antialiasing);

    QPen pen = painter->pen();
    pen.setWidth(widthLinesElements);
    painter->setPen(pen);



}

void MainElement::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);

    QVector<MainElement*> a = dynamic_cast<Scene*>(this->scene())->getArrElement();

    bool fl = true;
    while(fl)
    {
        fl=false;
    for(int i=0;i<a.size();i++)
    {
        if(a[i]->pos()==this->pos() && a[i]!=this)
        {
            this->moveBy(STEP_GRID, STEP_GRID);
            fl=true;

        }
    }
    }


    a.clear();

}

void MainElement::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(isSelectRelayMode && event->button() == Qt::LeftButton)
    {

        if(dynamic_cast<RelayRelay*>(this)!=NULL)
        {
            if(CreateDialog("Привязать контакт реле к реле?"))
            {
                relayContactSelected->setAssociatedRelay(dynamic_cast<RelayRelay*>(this));
                relayContactSelected->setNameElement(this->getNameElement());
                relayContactSelected->setIsLinked(true);

            }

        }
        else
        {
            QErrorMessage mess(this->scene()->views().last()->cornerWidget());
            mess.showMessage("Выбранный элемент не является реле, будет выполнен сброс команды.");

            mess.exec();

        }

        relayContactSelected->setIsProcessLinked(false);
        relayContactSelected=NULL;
        isSelectRelayMode=false;

        dynamic_cast<Scene*>(this->scene())->update();
    }

    QGraphicsItem::mousePressEvent(event);

}

bool MainElement::CreateDialog(QString s)
{
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

     QObject::connect(&okButton, SIGNAL(clicked()), question, SLOT(accept()));
     QObject::connect(&cancelButton, SIGNAL(clicked()), question, SLOT(reject()));
     question->setVisible(true);
     question->show();
     question->exec();

     if(question->result() == QDialog::Accepted)
         return true;

     if(question->result() == QDialog::Rejected)
         return false;

}



void MainElement::InitConstans()
{
    STEP_GRID = 30;
    rad = STEP_GRID*0.2;
}

int MainElement::getSizeX() const
{
    return sizeX;
}

void MainElement::setSizeX(int value)
{
    sizeX = value;
}
int MainElement::getRad()
{
    return rad;
}

void MainElement::setRad(int value)
{
    rad = value;
}
int MainElement::getSizeY() const
{
    return sizeY;
}

void MainElement::setSizeY(int value)
{
    sizeY = value;
}
int MainElement::getWidthLinesElements()
{
    return widthLinesElements;
}

void MainElement::setWidthLinesElements(int value)
{
    widthLinesElements = value;
}
int MainElement::getWidthLinesContacts()
{
    return widthLinesContacts;
}

void MainElement::setWidthLinesContacts(int value)
{
    widthLinesContacts = value;
}
int MainElement::getIdElement() const
{
    return idElement;
}

void MainElement::setIdElement(int value)
{
    idElement = value;
}
QString MainElement::getNameElement() const
{
    return nameElement;
}

void MainElement::setNameElement(const QString &value)
{
    nameElement = value;
}

void MainElement::SaveBaseElementParametrs(QXmlStreamWriter &writer)
{
    writer.writeAttribute("typeElement",  QString::number(typeElement));
    writer.writeAttribute("idElement", QString::number(idElement));

    writer.writeAttribute("posX", QString::number(this->pos().x()));
    writer.writeAttribute("posY", QString::number(this->pos().y()));
    writer.writeAttribute("isMirrorGorizontal", QString::number(isMirrorGorizontal));
    writer.writeAttribute("isMirrorVertical", QString::number(isMirrorVertical));

    writer.writeAttribute("sizeX", QString::number(sizeX));
    writer.writeAttribute("sizeY", QString::number(sizeY));

    writer.writeAttribute("nContactsLeft", QString::number(nContactsLeft));
    writer.writeAttribute("nContactsDown", QString::number(nContactsDown));
    writer.writeAttribute("nContactsRight", QString::number(nContactsRight));
    writer.writeAttribute("nContactsUp", QString::number(nContactsUp));
    writer.writeAttribute("name", nameElement);
}

Contacts *MainElement::findContactByNum(int num)
{
    for(int i=0;i<arrContacts.size();i++)
    {
        if(arrContacts[i]->getNum()==num)
            return arrContacts[i];
    }
    return NULL;
}



QRectF MainElement::boundingRect() const
{
    return QRectF(0, 0, sizeX*STEP_GRID, sizeY*STEP_GRID);
}


QVariant MainElement::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene())
    {
        QPointF newPos = value.toPointF();

        if(newPos.x()<0)
        {
            newPos.setX(0);
        }

        if(newPos.y()<0)
        {
            newPos.setY(0);
        }

        if(QApplication::mouseButtons() == Qt::LeftButton)
        {
            int gridSize = STEP_GRID;
            qreal xV = round(newPos.x()/gridSize)*gridSize;
            qreal yV = round(newPos.y()/gridSize)*gridSize;
            this->scene()->update(this->scene()->sceneRect());


            return QPointF(xV, yV);
        }
        else
            return newPos;
    }
    else
        return QGraphicsItem::itemChange(change, value);
}


void MainElement::SetContact()
{
    int k=0;
    for(int i=0;i<nContactsLeft;++i)
    {
            float interval = sizeY/(nContactsLeft+1.0);
            QPoint q;
            q.setX(0);
            q.setY(i*interval*STEP_GRID+interval*STEP_GRID);

            arrContacts.append(new Contacts(q.x()-rad/2.0, q.y()-rad/2.0, rad, rad));
            arrContacts.last()->SetOrientation(Left);
            arrContacts.last()->SetPositionContact(q);
            //arrContacts.last()->pen().setColor(arrContacts.last()->GetColorContact());
            arrContacts.last()->setParentItem(this);
            arrContacts.last()->setVisible(true);
            arrContacts.last()->setNum(k);
            k++;

    }


    for(int i=0;i<nContactsDown;++i)
    {
             float interval = (sizeX-1.0)/(nContactsDown+1.0);


            QPoint q;
            q.setX(i*interval*STEP_GRID+interval*STEP_GRID + 0.5*STEP_GRID);
            q.setY(sizeY*STEP_GRID);
            arrContacts.append(new Contacts(q.x()-rad/2.0, q.y()-rad/2.0, rad, rad));
            arrContacts.last()->SetOrientation(Bottom);
            arrContacts.last()->SetPositionContact(q);
            //arrContacts.last()->pen().setColor(arrContacts.last()->GetColorContact());
            arrContacts.last()->setParentItem(this);
            arrContacts.last()->setVisible(true);

            arrContacts.last()->setNum(k);
            k++;

    }

    for(int i=0;i<nContactsRight;++i)
    {
            float interval = sizeY/(nContactsRight+1.0);


            QPoint q;
            q.setX(sizeX*STEP_GRID);
            q.setY(i*interval*STEP_GRID+interval*STEP_GRID);
            arrContacts.append(new Contacts(q.x()-rad/2.0, q.y()-rad/2.0, rad, rad));
            arrContacts.last()->SetOrientation(Right);
            arrContacts.last()->SetPositionContact(q);
            //arrContacts.last()->pen().setColor(arrContacts.last()->GetColorContact());
            arrContacts.last()->setParentItem(this);
            arrContacts.last()->setVisible(true);

            arrContacts.last()->setNum(k);
            k++;



    }

    for(int i=0;i<nContactsUp;++i)
    {
             float interval = (sizeX-1.0)/(nContactsUp+1.0);


            QPoint q;
            q.setX(i*interval*STEP_GRID+interval*STEP_GRID + 0.5*STEP_GRID);
            q.setY(0);
            arrContacts.append(new Contacts(q.x()-rad/2.0, q.y()-rad/2.0, rad, rad));
            arrContacts.last()->SetOrientation(Top);
            arrContacts.last()->SetPositionContact(q);
            //arrContacts.last()->pen().setColor(arrContacts.last()->GetColorContact());
            arrContacts.last()->setParentItem(this);
            arrContacts.last()->setVisible(true);

            arrContacts.last()->setNum(k);
            k++;

    }




}

void MainElement::ReDrawContact()
{
    int k=0;

    for(int i=0;i<nContactsLeft;++i)
    {
            float interval = sizeY/(nContactsLeft+1.0);
            QPoint q;
            q.setX(0);
            q.setY(i*interval*STEP_GRID+interval*STEP_GRID);

            arrContacts[k]->setRect(q.x()-rad/2.0, q.y()-rad/2.0, rad, rad);
            arrContacts[k]->SetOrientation(Left);
            arrContacts[k]->SetPositionContact(q);
            arrContacts.last()->setNum(k);
            k++;

    }


    for(int i=0;i<nContactsDown;++i)
    {
             float interval = (sizeX-1.0)/(nContactsDown+1.0);


            QPoint q;
            q.setX(i*interval*STEP_GRID+interval*STEP_GRID + 0.5*STEP_GRID);
            q.setY(sizeY*STEP_GRID);
            arrContacts[k]->setRect(q.x()-rad/2.0, q.y()-rad/2.0, rad, rad);
            arrContacts[k]->SetOrientation(Bottom);
            arrContacts[k]->SetPositionContact(q);
            arrContacts.last()->setNum(k);
            k++;

    }

    for(int i=0;i<nContactsRight;++i)
    {
            float interval = sizeY/(nContactsRight+1.0);


            QPoint q;
            q.setX(sizeX*STEP_GRID);
            q.setY(i*interval*STEP_GRID+interval*STEP_GRID);
            arrContacts[k]->setRect(q.x()-rad/2.0, q.y()-rad/2.0, rad, rad);
            arrContacts[k]->SetOrientation(Right);
            arrContacts[k]->SetPositionContact(q);
            arrContacts.last()->setNum(k);
            k++;



    }

    for(int i=0;i<nContactsUp;++i)
    {
             float interval = (sizeX-1.0)/(nContactsUp+1.0);


            QPoint q;
            q.setX(i*interval*STEP_GRID+interval*STEP_GRID + 0.5*STEP_GRID);
            q.setY(0);
            arrContacts[k]->setRect(q.x()-rad/2.0, q.y()-rad/2.0, rad, rad);
            arrContacts[k]->SetOrientation(Top);
            arrContacts[k]->SetPositionContact(q);
            arrContacts.last()->setNum(k);
            k++;

    }



}




MainElement::~MainElement()
{
    for(int i=0;i<arrContacts.size();i++)
    {
        if(arrContacts[i]->GetNeighbour()!=NULL)
        {
            arrContacts[i]->SetChecked(false);
            arrContacts[i]->GetNeighbour()->SetChecked(false);

            arrContacts[i]->setIsDrawedConnection(false);
            arrContacts[i]->GetNeighbour()->setIsDrawedConnection(false);

            arrContacts[i]->GetNeighbour()->SetNeighbour(NULL);
            arrContacts[i]->SetNeighbour(NULL);

        }
    }



    for(int i=0;i<arrContacts.size();i++)
        delete arrContacts[i];

    delete question;
}
