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
       connect(ui->A3, SIGNAL (clicked()),this, SLOT(A3Btn_clicked()));
       connect(ui->A4, SIGNAL (clicked()),this, SLOT(A4Btn_clicked()));
   } if (PlayerNo == 2){
       ui->textBox->setPlaceholderText("Du bist Spieler B");
       connect(ui->B1, SIGNAL (clicked()),this, SLOT(B1Btn_clicked()));
       connect(ui->B2, SIGNAL (clicked()),this, SLOT(B2Btn_clicked()));
       connect(ui->B3, SIGNAL (clicked()),this, SLOT(B3Btn_clicked()));
       connect(ui->B4, SIGNAL (clicked()),this, SLOT(B4Btn_clicked()));
   } if (PlayerNo == 3){
       ui->textBox->setPlaceholderText("Du bist Spieler C");
   } if (PlayerNo == 4){
       ui->textBox->setPlaceholderText("Du bist Spieler D");
   }
   connect(ui->diceBtn, SIGNAL(clicked()), this, SLOT(diceBtn_clicked()));
   //QLabel* field[40];
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

    // Erlaubt einen Spielzug mit den jeweiligen Spielfiguren
    if (diceValue == 6)
    {
        if (PlayerNo == 1)
        {
        ui->A1->setEnabled(true);
        ui->A2->setEnabled(true);
        ui->A3->setEnabled(true);
        ui->A4->setEnabled(true);
        }

        if (PlayerNo == 2)
        {
        ui->B1->setEnabled(true);
        ui->B2->setEnabled(true);
        ui->B3->setEnabled(true);
        ui->B4->setEnabled(true);
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
        if(ui->A3->toolTip().isEmpty())
        {
            ui->A3->setEnabled(false);
        }
        if(ui->A4->toolTip().isEmpty())
        {
            ui->A4->setEnabled(false);
        }
        if(ui->B1->toolTip().isEmpty())
        {
            ui->B1->setEnabled(false);
        }
        if(ui->B2->toolTip().isEmpty())
        {
            ui->B2->setEnabled(false);
        }
        if(ui->B3->toolTip().isEmpty())
        {
            ui->B3->setEnabled(false);
        }
        if(ui->B4->toolTip().isEmpty())
        {
            ui->B4->setEnabled(false);
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
                if(VarButton == ui->A1 || VarButton == ui->A2||VarButton == ui->A3||VarButton == ui->A4)
                    {
                        animation->setStartValue(QRect(VarButton->x(), VarButton->y(), 30, 30));
                        animation->setEndValue(QRect(ui->field_1->x(), ui->field_1->y(), 40, 40));
                        animation->start();
                        VarButton->setToolTip("in");
                        VarButton->setStatusTip("1");     //legt Feldposition der Figur im StatusTip ab; bei Spieler = field_1
                     }
                else if(VarButton == ui->B1 ||VarButton == ui->B2||VarButton == ui->B3||VarButton == ui->B4)
                     {
                        animation->setStartValue(QRect(VarButton->x(), VarButton->y(), 30, 30));
                        animation->setEndValue(QRect(ui->field_11->x(), ui->field_11->y(), 40, 40));
                        animation->start();
                        VarButton->setToolTip("in");
                        VarButton->setStatusTip("11");    //Spieler B Start = field_11
                     }
    }

   else if(VarButton->toolTip() == "in" && (VarButton == ui->A1 || VarButton == ui->A2||VarButton == ui->A3||VarButton == ui->A4))
   {
        //aktuelle Position der Figur ermitteln aus dem StatusTip und addiert den Würfelwert für den aktuellen zug. Speichert ergebnis in int Ply
        QString PlayerPosition = VarButton->statusTip();
        int FieldID = PlayerPosition.toInt();
        int goTo = diceValue + FieldID;

        if (goTo>40)
        {            
                    QPropertyAnimation *animation = new QPropertyAnimation(VarButton, "geometry", this);
                    animation->setDuration(1000);
                    animation->setStartValue(QRect(VarButton->x(), VarButton->y(), 40, 40));
                    if(VarButton == ui->A1)
                    {
                     animation->setEndValue(QRect(ui->finish_A4->x(), ui->finish_A4->y(), 30, 30));
                    }
                    if(VarButton == ui->A2)
                    {
                     animation->setEndValue(QRect(ui->finish_A3->x(), ui->finish_A3->y(), 30, 30));
                    }
                    if(VarButton == ui->A3)
                    {
                     animation->setEndValue(QRect(ui->finish_A2->x(), ui->finish_A2->y(), 30, 30));
                    }
                    if(VarButton == ui->A4)
                    {
                     animation->setEndValue(QRect(ui->finish_A1->x(), ui->finish_A1->y(), 30, 30));
                    }
                    animation->start();
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
void MainWindow::A3Btn_clicked()//Aufruf der Spielfigur + Überprüfung, dass nur der "richtige" Spieler diesen ansprechen darf

{
    if (PlayerNo == 1)
    {
        QString BtnName = "A3";
        //qDebug() << BtnName;
        gm->updateMove(diceValue, BtnName);
    }
}
void MainWindow::A4Btn_clicked()//Aufruf der Spielfigur + Überprüfung, dass nur der "richtige" Spieler diesen ansprechen darf

{
    if (PlayerNo == 1)
    {
        QString BtnName = "A4";
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
void MainWindow::B3Btn_clicked() //Aufruf der Spielfigur + Überprüfung, dass nur der "richtige" Spieler diesen ansprechen darf
{
    if (PlayerNo == 2)
    {
        QString BtnName = "B3";
        gm->updateMove(diceValue, BtnName);
    }
}
void MainWindow::B4Btn_clicked() //Aufruf der Spielfigur + Überprüfung, dass nur der "richtige" Spieler diesen ansprechen darf
{
    if (PlayerNo == 2)
    {
        QString BtnName = "B4";
        gm->updateMove(diceValue, BtnName);
    }
}
