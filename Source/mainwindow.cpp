#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <gamemanager.h>
#include <QDebug>
#include <QRandomGenerator>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QPropertyAnimation>

int MainWindow::playerCount=0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   playerCount++;
   PlayerNo = playerCount;
   if (PlayerNo == 1){
       ui->textBox->setPlaceholderText("Du bist Spieler A");
       connect(ui->A1, SIGNAL (clicked()),this, SLOT(A1Btn_clicked()));
       connect(ui->A2, SIGNAL (clicked()),this, SLOT(A2Btn_clicked()));
   } if (PlayerNo == 2){
       ui->textBox->setPlaceholderText("Du bist Spieler B");
       connect(ui->B1, SIGNAL (clicked()),this, SLOT(B1Btn_clicked()));
       connect(ui->B2, SIGNAL (clicked()),this, SLOT(B2Btn_clicked()));
   } if (PlayerNo == 3){
       ui->textBox->setPlaceholderText("Du bist Spieler C");
   } if (PlayerNo == 4){
       ui->textBox->setPlaceholderText("Du bist Spieler D");
   }
   connect(ui->diceBtn, SIGNAL(clicked()), this, SLOT(diceBtn_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setGameManager(GameManager *gm)
{
    //Verbindung zum GameManager aufbauen
    this->gm = gm;
}

void MainWindow::sendName(QString name){

    //Eintrag der Namen in die entsprechenden Spieler Zeilen
    if (ui->namePlyA->isEnabled() == true)
    {
        ui->namePlyA->setText(name);
        ui->namePlyA->setDisabled(true);
    }
    else if (ui->namePlyB->isEnabled() == true)
    {
        ui->namePlyB->setText(name);
        ui->namePlyB->setDisabled(true);
    }
}

void MainWindow::diceBtn_clicked()
{
    // Würfelzahlen mit Zufallsgenerator und Ausgabe
    diceValue = QRandomGenerator::global()->bounded(1,7);
    ui->diceOut->display(diceValue);

    if (diceValue == 6)
    {
        if (PlayerNo == 1)
        {
        ui->A1->setEnabled(true);
        ui->A2->setEnabled(true);}

        if (PlayerNo == 2)
        {
        ui->B1->setEnabled(true);
        ui->B2->setEnabled(true);
        }
    }else
    {
        if(ui->A1->toolTip().isEmpty())
        {
            ui->A1->setEnabled(false);
        }
        if(ui->A2->toolTip().isEmpty())
        {
            ui->A2->setEnabled(false);
        }
        if(ui->B1->toolTip().isEmpty())
        {
            ui->B1->setEnabled(false);
        }
        if(ui->B2->toolTip().isEmpty())
        {
            ui->B2->setEnabled(false);
        }
    }
}

void MainWindow::move(int diceValue, QString BtnName){

    //VarButton variable wird mit dem gedrückten Button initialisiert, sodass die gewählte Figur zieht
    QPushButton* VarButton = this->findChild<QPushButton*>(BtnName);


    if (VarButton->toolTip().isEmpty() && diceValue == 6) //wenn Figur noch im "Start-Haus" ist und bei Würfel 6 rausziehen soll
    {
                QPropertyAnimation *animation = new QPropertyAnimation(VarButton, "geometry", this);
                animation->setDuration(1000);
                if(VarButton == ui->A1 || VarButton == ui->A2)
                    {
                        animation->setStartValue(QRect(VarButton->x(), VarButton->y(), 30, 30));
                        animation->setEndValue(QRect(ui->field_1->x(), ui->field_1->y(), 40, 40));
                        animation->start();
                        VarButton->setToolTip("in");
                        VarButton->setStatusTip("1");     //Feldposition der Figur im StatusTip ab. Bei Spieler 1 (Rot): start = field_1
                     }
                else if(VarButton == ui->B1 ||VarButton == ui->B2)
                     {
                        animation->setStartValue(QRect(VarButton->x(), VarButton->y(), 30, 30));
                        animation->setEndValue(QRect(ui->field_11->x(), ui->field_11->y(), 40, 40));
                        animation->start();
                        VarButton->setToolTip("in");
                        VarButton->setStatusTip("11");    //blaue Spielsteine Start = field_11
                     }
    }

   else if(VarButton->toolTip() == "in" && (VarButton == ui->A1 || VarButton == ui->A2))
   {
        //aktuelle Position der Figur ermitteln aus dem StatusTip und addiert den Würfelwert für den aktuellen zug. Speichert ergebnis in int Ply
        QString PlayerPosition = VarButton->statusTip();
        int FieldID = PlayerPosition.toInt();
        int goTo = diceValue + FieldID;

        if (goTo<=40)
        {

        }
   }
}
void MainWindow::A1Btn_clicked() //Aufruf der Spielfigur + Überprüfung, dass nur der "richtige" Spieler diesen ansprechen darf
{
    if (PlayerNo == 1)
    {
        QString BtnName = "A1";
        //qDebug() << BtnName;
        gm->updateMove(diceValue, BtnName);
    }
}
void MainWindow::A2Btn_clicked()//Aufruf der Spielfigur + Überprüfung, dass nur der "richtige" Spieler diesen ansprechen darf

{
    if (PlayerNo == 1)
    {
        QString BtnName = "A2";
        //qDebug() << BtnName;
        gm->updateMove(diceValue, BtnName);
    }
}
void MainWindow::B1Btn_clicked() //Aufruf der Spielfigur + Überprüfung, dass nur der "richtige" Spieler diesen ansprechen darf
{
    if (PlayerNo == 2)
    {
        QString BtnName = "B1";
        gm->updateMove(diceValue, BtnName);
    }
}
void MainWindow::B2Btn_clicked()//Aufruf der Spielfigur + Überprüfung, dass nur der "richtige" Spieler diesen ansprechen darf
{
    if (PlayerNo == 2)
    {
        QString BtnName = "B2";
        gm->updateMove(diceValue, BtnName);
    }
}
