#ifndef MAINELEMENT_H
#define MAINELEMENT_H
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QPainter>
#include <QDebug>
#include <QDrag>
#include <QDialog>
#include <QGraphicsSceneDragDropEvent>
#include <contacts.h>
#include <QContextMenuEvent>
#include <QMenu>
#include <QAction>
#include <QObject>
#define SCALE 1.1

class MainElement : public QGraphicsObject
{

public:
    MainElement(QGraphicsObject* parent=0);
    virtual ~MainElement();

    QRectF boundingRect() const ;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void SetContact();

    void ReDrawContact();

    QVector<Contacts*>& GetArrContacts()
    {
        return arrContacts;
    }

    bool CreateDialog(void);

    static void InitConstans();

    static int GetStepGrid()
    {
        return STEP_GRID;
    }



    int getSizeX() const;
    void setSizeX(int value);

    static int getRad();
    static void setRad(int value);

    int getSizeY() const;
    void setSizeY(int value);


    static int getWidthLinesElements();
    static void setWidthLinesElements(int value);

    static int getWidthLinesContacts();
    static void setWidthLinesContacts(int value);

protected:
    static int STEP_GRID;
    static int rad;
    static int widthLinesElements;
    static int widthLinesContacts;

    ///ДЛЯ ЭЛЕМЕНТОВ
    int sizeX, sizeY;//размеры (в клетках) элеиента

    int nContactsLeft;
    int nContactsRight;
    int nContactsUp;
    int nContactsDown;
    int nContacts;

    bool isMirrorGorizontal;
    bool isMirrorVertical;

    QString nameElement;
    int idElement;

    QVector<Contacts*> arrContacts;        
    QDialog* question;




};

#endif // MAINELEMENT_H
