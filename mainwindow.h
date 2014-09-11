#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scene.h"
#include "view.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Scene* scene;
    View* view;

private slots:
    void AddBlockButton();
    void DeleteConnection();
    void WidthLines();
    void WidthLinesContacts();
    void SiezeBlocks();
    void RadContacts();
};

#endif // MAINWINDOW_H
