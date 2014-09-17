#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <mainelement.h>
#include "contacts.h"
#include <QMouseEvent>
#include <QGraphicsSceneEvent>
#include <QVector>
#include <QGraphicsLineItem>
#include <QDialog>


class Scene : public QGraphicsScene
{
public:
   explicit Scene(QObject* parent=0);
    ~Scene();

    void drawBackground(QPainter *painter, const QRectF &rect);

    void DrawContactsLine(QPainter *painter, const QRectF &rect);

    static void SetSceneSieze(int width, int height)
    {
        scene_width = width;
        scene_height = height;
    }

    void AddBlock();

    void AddPoint();

    void AddPolus();

    void AddRelayContact();

    void AddRelay();

    void DeleteElement(MainElement* element);

    int GetDrawContactLine()
    {
        return drawContactLine;
    }

    void SetDrawContactLine(int a);

    void SetBeginDrawContact(Contacts* a1)
    {
        beginContact=a1;
    }

    void SetEndDrawContact(Contacts* a1)
    {
        endContact=a1;
    }

    void DeleteConnectionLine();
    bool ChangeSiezeBlocks(QString s);
    bool ChangeDifferentParametrs(QString s);
    QString SetStringParamElementDialog(QString s);


    QVector<MainElement *> getArrElement() const;
    void setArrElement(const QVector<MainElement *> &value);

private:
    static int scene_width;
    static int scene_height;
    int nElement;

    int drawContactLine;
    Contacts* beginContact;
    Contacts* endContact;
    QDialog* question;


    QVector <MainElement*> arrElement;

};

#endif // SCENE_H
