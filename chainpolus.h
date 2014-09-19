#ifndef CHAINPOLUS_H
#define CHAINPOLUS_H
#include "mainelement.h"

class ChainPolus : public MainElement
{
public:
    ChainPolus(QGraphicsObject* parent=0);
    ChainPolus(int idElement, int posX, int posY, bool isMirrorGorizontal, bool isMirrorVertical, int sizeX, int sizeY, int nContactsLeft,int nContactsDown,int nContactsRight,int nContactsUp,QString name, QGraphicsObject* parent=0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void SaveToXml(QXmlStreamWriter& writer);
};

#endif // CHAINPOLUS_H
