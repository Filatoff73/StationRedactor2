#ifndef VIEW_H
#define VIEW_H
#include <QGraphicsView>
#include <QObject>
#include <QMouseEvent>
#include <QWheelEvent>

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(QGraphicsView* parent=0);

    void wheelEvent(QWheelEvent* event);

};

#endif // VIEW_H
