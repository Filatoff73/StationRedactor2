#ifndef CONTACTS_H
#define CONTACTS_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <qxmlstream.h>

enum Orientation
{
   Left,
   Bottom,
   Right,
   Top
};

class Contacts : public QGraphicsEllipseItem
{
public:
    Contacts(int x, int y, int w, int h, QGraphicsItem* parent=0);

    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

   // QRectF boundingRect() const ;

    void SetPositionContact(QPoint a);

     QPoint GetPositionContact()
    {
        return positionContact;
    }

    void SetNeighbour(Contacts* neighbour)
    {
        neighbourContact = neighbour;
    }

    Contacts* GetNeighbour()
    {
        return neighbourContact;
    }

    int GetNumContact()
    {
        return num;
    }

    int GetIdContact()
    {
        return idContact;
    }

    void SetIdContact(int a)
    {
        idContact=a;
    }

    QColor& GetColorContact()
    {
        return colorContact;
    }

    void SetColorContact(QColor a)
    {
        colorContact=a;
    }

    void SetChecked(bool a)
    {
        if(a==true)
        {
            isChecked=true;
            colorContact = Qt::red;
            QPen pen = this->pen();
            pen.setColor(colorContact);
            this->setPen(pen);
        }
        if(a==false)
        {
            isChecked=false;
            colorContact = Qt::black;
            QPen pen = this->pen();
            pen.setColor(colorContact);
            this->setPen(pen);
        }
    }

    bool GetIsChecked()
    {
        return isChecked;
    }

    void SetOrientation(Orientation a)
    {
        contactOrientation=a;
    }

    Orientation Getorientation()
    {
        return contactOrientation;
    }





    bool getIsDrawedConnection() const;
    void setIsDrawedConnection(bool value);

    int getNum() const;
    void setNum(int value);

    void WriteToXmlContacts(QXmlStreamWriter &writer);

    QString getNameContact() const;
    void setNameContact(const QString &value);


private:

    int idContact;
    int num;
    QString nameContact;
    QPoint positionContact;
    QColor colorContact;
    bool isChecked;
    Contacts* neighbourContact;
    Orientation contactOrientation;
    bool isDrawedConnection;

};

#endif // CONTACTS_H
