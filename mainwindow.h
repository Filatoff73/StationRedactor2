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

    void save();
    void saveAs();
    void open();
    void openStation();
    void generateStationCode();

private:
    Ui::MainWindow *ui;
    Scene* scene;
    View* view;
    QString saveDir;

private slots:
    void AddTestBlockButton();
    void AddFileBlockButton();
    void AddPointButton();
    void AddPolus();
    void AddButton();
    void AddSecondContactRelay();
    void AddRelay();
    void AddRelayContact();
    void DeleteConnection();
    void WidthLines();
    void WidthLinesContacts();
    //void SiezeBlocks();
    void RadContacts();
    void GreedButton();


    void MenuBarFunc(QAction *act);

};

#endif // MAINWINDOW_H
