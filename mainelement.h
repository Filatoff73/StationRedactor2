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
#include <QStringRef>

#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <qxmlstream.h>
#define SCALE 1.1

class RelayContact;
class MainElement : public QGraphicsObject
{

public:
    MainElement(QGraphicsObject* parent=0);

    MainElement(int idElement, int posX, int posY, bool isMirrorGorizontal, bool isMirrorVertical, int sizeX, int sizeY, int nContactsLeft,int nContactsDown,int nContactsRight,int nContactsUp, QString name, QGraphicsObject* parent=0);


    virtual ~MainElement();

    QRectF boundingRect() const ;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    void SetContact();

    virtual void ReDrawContact();

    QVector<Contacts*>& GetArrContacts()
    {
        return arrContacts;
    }

    bool CreateDialog(QString s="Удалить линию соединения?");

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

    static void SetStepGrid(int a)
    {
        if(a>1)
        STEP_GRID=a;
    }

    int getIdElement() const;
    void setIdElement(int value);

    QString getNameElement() const;
    void setNameElement(const QString &value);

    virtual void SaveToXml(QXmlStreamWriter& writer)=0;
    void SaveBaseElementParametrs(QXmlStreamWriter& writer);

    Contacts* findContactByNum(int num);

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
    int typeElement;

    QVector<Contacts*> arrContacts;        
    QDialog* question;

    static bool isSelectRelayMode;
    static RelayContact* relayContactSelected;



    const int TYPE_CHAIN_POINT = 0;
    const int TYPE_RELAY_RELAY = 1;
    const int TYPE_CHAIN_CONTACT = 2;
    const int TYPE_RELAY_CONTACT = 3;
    const int TYPE_CHAIN_POLUS = 4;
    const int TYPE_BLOCK_RELAY = 5;







};

#endif // MAINELEMENT_H
