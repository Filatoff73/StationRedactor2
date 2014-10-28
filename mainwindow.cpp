#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollBar>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new Scene();
    view = new View();

    view->setScene(scene);

    view->horizontalScrollBar()->setValue(1);
    view->verticalScrollBar()->setValue(1);

    view->show();

    //ui->centralWidget->layout()->addWidget(view);

    ui->sceneLayout->addWidget(view);

    this->setGeometry(110,110,900,900);

    this->setWindowTitle("POLIVID Station Redactor");


    connect(ui->addTestBlock, SIGNAL(clicked()), this, SLOT(AddTestBlockButton()));
    connect(ui->addFileBlock, SIGNAL(clicked()), this, SLOT(AddFileBlockButton()));
    connect(ui->addPoint, SIGNAL(clicked()), this, SLOT(AddPointButton()));
    connect(ui->addSecondContactRelay, SIGNAL(clicked()), this, SLOT(AddSecondContactRelay()));
    connect(ui->addPolus, SIGNAL(clicked()), this, SLOT(AddPolus()));
    connect(ui->addRelay, SIGNAL(clicked()), this, SLOT(AddRelay()));
    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(AddButton()));
    connect(ui->addContactRelay, SIGNAL(clicked()), this, SLOT(AddRelayContact()));
    connect(ui->deleteConnection, SIGNAL(clicked()), this, SLOT(DeleteConnection()));
    connect(ui->widthLines, SIGNAL(clicked()), this, SLOT(WidthLines()));
   // connect(ui->siezeBlocks, SIGNAL(clicked()), this, SLOT(SiezeBlocks()));
    connect(ui->rContact, SIGNAL(clicked()), this, SLOT(RadContacts()));
    connect(ui->widthLineContatcts, SIGNAL(clicked()), this, SLOT(WidthLinesContacts()));
    connect(ui->greedButton, SIGNAL(clicked()), this, SLOT(GreedButton()));

    this->connect(ui->menuBar, SIGNAL(triggered(QAction*)), this, SLOT(MenuBarFunc(QAction*)) );

    saveDir = "";
}


void MainWindow::AddTestBlockButton()
{
    scene->AddTestBlock();
}

void MainWindow::AddFileBlockButton()
{
    scene->AddFileBlock();
}

void MainWindow::AddPointButton()
{
    scene->AddPoint();
}

void MainWindow::AddPolus()
{
    scene->AddPolus();
}

void MainWindow::AddButton()
{
    scene->AddChainButton();
}

void MainWindow::AddSecondContactRelay()
{
    scene->AddSecondContactRelay();
}

void MainWindow::AddRelay()
{
    scene->AddRelay();
}

void MainWindow::AddRelayContact()
{
    scene->AddRelayContact();
}

void MainWindow::DeleteConnection()
{

    scene->DeleteConnectionLine();
}

void MainWindow::WidthLines()
{
    scene->ChangeDifferentParametrs("Задайте толщину линий элементов");
}

void MainWindow::WidthLinesContacts()
{
    scene->ChangeDifferentParametrs("Задайте толщину линий контактов");
}

/*void MainWindow::SiezeBlocks()
{
    scene->ChangeSiezeBlocks("Задать размер блока");
}*/

void MainWindow::RadContacts()
{
    scene->ChangeDifferentParametrs("Задайте радиус контакта");
}

void MainWindow::GreedButton()
{
    scene->ChangeDifferentParametrs("Задайте шаг сетки");
}


void MainWindow::save()
{
    if(!saveDir.compare(""))
        return;

    QFile f(saveDir);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    scene->saveFile(f);
    f.close();
}

void MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
             tr("Сохранить бмрц станции"), saveDir, "*.station");

    if(!fileName.compare(""))
        return;


    if(fileName.mid(fileName.size() - 8).compare(".station"))
        fileName += ".station";

    QDir dir(fileName);
    saveDir = dir.absolutePath();

    QFile f(saveDir);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    scene->saveFile(f);
    f.close();
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
             tr("Открыть бмрц станции"), saveDir, "*.station");

    if(!fileName.compare(""))
        return;

    QDir dir(fileName);
    saveDir = dir.absolutePath();

    QFile f(saveDir);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
             return;

    scene->openFile(f);
    f.close();

    view->InitViewVariable();
}

void MainWindow::openStation()
{
    QString fileName = QFileDialog::getOpenFileName(this,
             tr("Открыть станцию"), saveDir, "*.xml");


    if(!fileName.compare(""))
        return;

    QDir dir(fileName);
    saveDir = dir.absolutePath();

    QFile f(saveDir);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text))
             return;
    /////////////////////////////////

    saveDir.clear();

    fileName = QFileDialog::getSaveFileName(this,
             tr("Сохранить бмрц станции"), saveDir, "*.station");

    if(!fileName.compare(""))
        return;


    if(fileName.mid(fileName.size() - 8).compare(".station"))
        fileName += ".station";

    dir.setPath(fileName);
    saveDir = dir.absolutePath();

    QFile f2(saveDir);
    if (!f2.open(QIODevice::WriteOnly | QIODevice::Text))
             return;

    /////////////////////////////////////

    scene->generateStation(f,f2);
    f.close();
    f2.close();

    if (!f2.open(QIODevice::ReadOnly | QIODevice::Text))
             return;

    scene->openFile(f2);
    view->InitViewVariable();

    f2.close();


}





void MainWindow::MenuBarFunc(QAction *act)
{
    if (act)
    {
        QString txt = act->text();

        if(!txt.compare("Открыть"))
        {
            open();
        }

        if(!txt.compare("Сохранить"))
        {
            if(!saveDir.compare(""))
                saveAs();
            else
                save();
        }

        if(!txt.compare("Сохранить как"))
        {
            saveAs();
        }

        if(!txt.compare("Сгенерировать БМРЦ станции"))
        {
            openStation();
        }


        if(!txt.compare("О программе"))
        {
           QMessageBox::about(this, "О программе", "Редактор БМРЦ станции\n\nВсе права принадлежат ООО\"ПОЛИВИД\"\n\nТехподдержка: filatov.work@yandex.ru");
        }

        if(!txt.compare("Выход"))
        {
           this->close();
        }
    }
}




MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete view;
}
