#ifndef CHAINBUTTON_H
#define CHAINBUTTON_H
#include "mainelement.h"

class ChainButton : public MainElement
{
public:
    ChainButton(QGraphicsObject* parent=0);
    ChainButton(int idElement, int posX, int posY, bool isMirrorGorizontal, bool isMirrorVertical, int sizeX, int sizeY, int nContactsLeft,int nContactsDown,int nContactsRight,int nContactsUp,QString name, QGraphicsObject* parent=0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
     void SaveToXml(QXmlStreamWriter& writer);
     void ReDrawContact();
};

#endif // CHAINBUTTON_H
