#ifndef BLOCKRELAY_H
#define BLOCKRELAY_H

#include "mainelement.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneContextMenuEvent>

class BlockRelay : public MainElement
{
public:
    BlockRelay(QGraphicsObject* parent=0);
    BlockRelay(int idElement, int posX, int posY, bool isMirrorGorizontal, bool isMirrorVertical, int sizeX, int sizeY, int nContactsLeft,int nContactsDown,int nContactsRight,int nContactsUp,QString name, QGraphicsObject* parent=0);


    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void DrawBlock(QPainter* painter);

    void contextMenuEvent( QGraphicsSceneContextMenuEvent * event );

    void SaveToXml(QXmlStreamWriter& writer);



};

#endif // BLOCKRELAY_H
