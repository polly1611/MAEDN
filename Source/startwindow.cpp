#include "startwindow.h"
#include "ui_startwindow.h"
#include "gamemanager.h"



StartWindow::StartWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    //Verbindung der zu dem Start Button um das Spiel zu starten und Ende Button um das Fenster zu schließen
    connect(ui->startBtn, SIGNAL(clicked()), this, SLOT(startBtn_clicked()));
    connect(ui->endBtn, SIGNAL(clicked()), this, SLOT(endBtn_clicked()));
}

StartWindow::~StartWindow()
{
    delete ui;
}
void StartWindow::startBtn_clicked()
{
    //Übergabe des Namens an den GameManager und schließen des Anmeldefensters
    QString name = ui->name->text();
    gm->sendName(name);
    this->close();
}

void StartWindow::endBtn_clicked()
{
    mw->close();
    this->close();
}

void StartWindow::setGameManager(GameManager *gm)
{
    //Verbindung zum GameManager aufbauen;
    this ->gm = gm;
}

