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

    void AddTestBlock(QPoint pos = QPoint(MainElement::GetStepGrid(), MainElement::GetStepGrid()));

    void AddFileBlock(QPoint pos = QPoint(MainElement::GetStepGrid(), MainElement::GetStepGrid()));
    //Считать контакты нового блока из файла
    void ReadContactsFileBlock(QXmlStreamReader& reader, MainElement* elem);

    void AddPoint(QPoint pos = QPoint(MainElement::GetStepGrid(), MainElement::GetStepGrid()));

    void AddChainButton(QPoint pos = QPoint(MainElement::GetStepGrid(), MainElement::GetStepGrid()));

    void AddSecondContactRelay(QPoint pos = QPoint(MainElement::GetStepGrid(), MainElement::GetStepGrid()));

    void AddPolus(QPoint pos = QPoint(MainElement::GetStepGrid(), MainElement::GetStepGrid()));

    void AddRelayContact(QPoint pos = QPoint(MainElement::GetStepGrid(), MainElement::GetStepGrid()));

    void AddRelay(QPoint pos = QPoint(MainElement::GetStepGrid(), MainElement::GetStepGrid()));

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

    bool ChangeDifferentParametrs(QString s);
    QString SetStringParamElementDialog(QString s);


    QVector<MainElement *> getArrElement() const;
    void setArrElement(const QVector<MainElement *> &value);

    void openFile(QFile &f);
    //Открытие параметров станции из файла
    void setStationParametrs(QXmlStreamAttributes &attrib);
    //Создание елементов из файла, ввод начальных параметров с первого прохода
    void setElementParametrs(QXmlStreamAttributes &attrib);
    //Второй проход файла, расстановка контактов и доп параметров элементов
    void readOneElement(QXmlStreamReader& reader);
    void firstReading(QFile &f);
    void secondReading(QFile &f);
    void saveFile(QFile &f);
    MainElement* findElementById(int id);

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
