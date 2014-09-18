#ifndef CHAINPOLUS_H
#define CHAINPOLUS_H
#include "mainelement.h"

class ChainPolus : public MainElement
{
public:
    ChainPolus(QGraphicsObject* parent=0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
};

#endif // CHAINPOLUS_H
