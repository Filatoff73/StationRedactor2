#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QScrollBar>


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




    connect(ui->addBlock, SIGNAL(clicked()), this, SLOT(AddBlockButton()));
    connect(ui->deleteConnection, SIGNAL(clicked()), this, SLOT(DeleteConnection()));
    connect(ui->widthLines, SIGNAL(clicked()), this, SLOT(WidthLines()));
    connect(ui->siezeBlocks, SIGNAL(clicked()), this, SLOT(SiezeBlocks()));
    connect(ui->rContact, SIGNAL(clicked()), this, SLOT(RadContacts()));
    connect(ui->widthLineContatcts, SIGNAL(clicked()), this, SLOT(WidthLinesContacts()));
}


void MainWindow::AddBlockButton()
{
    scene->AddBlock();
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

void MainWindow::SiezeBlocks()
{
    scene->ChangeSiezeBlocks("Задать размер блока");
}

void MainWindow::RadContacts()
{
    scene->ChangeDifferentParametrs("Задайте радиус контакта");
}




MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete view;
}
