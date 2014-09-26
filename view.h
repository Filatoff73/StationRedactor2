#ifndef VIEW_H
#define VIEW_H
#include <QGraphicsView>
#include <QObject>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QAbstractScrollArea>
#include <QKeyEvent>

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(QGraphicsView* parent=0);

    void wheelEvent(QWheelEvent* event);

    void contextMenuEvent (QContextMenuEvent * event);

    void keyPressEvent(QKeyEvent *event);

    void InitViewVariable();

private:
    double stepSlider;

};

#endif // VIEW_H
