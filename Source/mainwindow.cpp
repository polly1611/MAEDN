#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <gamemanager.h>
#include <QDebug>
#include <QRandomGenerator>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QPropertyAnimation>
#include <sstream>
#include <QParallelAnimationGroup>
#include <QColor>

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
       //Verindung zu den PushButtons/Spielfiguren
       connect(ui->A1, SIGNAL (clicked()),this, SLOT(A1Btn_clicked()));
       connect(ui->A2, SIGNAL (clicked()),this, SLOT(A2Btn_clicked()));
       connect(ui->A3, SIGNAL (clicked()),this, SLOT(A3Btn_clicked()));
       connect(ui->A4, SIGNAL (clicked()),this, SLOT(A4Btn_clicked()));
   } if (PlayerNo == 2){
       ui->textBox->setPlaceholderText("Du bist Spieler B");
       //Verindung zu den PushButtons/Spielfiguren
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

void MainWindow::move(int diceValue, QString BtnName)
{
    //VarButton variable wird mit dem gedrückten Button initialisiert, sodass die gewählte Figur zieht
    QPushButton* VarButton = this->findChild<QPushButton*>(BtnName);

    //wenn Figur noch im "Start-Haus" ist und bei Würfel 6 rausziehen soll
    if (VarButton->toolTip().isEmpty() && diceValue == 6)
    {
        QPropertyAnimation *animation = new QPropertyAnimation(VarButton, "geometry", this);
        animation->setDuration(1000);
        if(VarButton == ui->A1 || VarButton == ui->A2||VarButton == ui->A3||VarButton == ui->A4)
        {
            animation->setStartValue(QRect(VarButton->x(), VarButton->y(), 31, 31));
            animation->setEndValue(QRect(ui->field_1->x(), ui->field_1->y(), 40, 40));
                  /* animation->start();*/


            QColor startColor = VarButton->palette().button().color(); //Startfarbe ist die aktuelle Farbe des Buttons
            QColor endColor = Qt::red; //Endfarbe ist rot
            QPropertyAnimation *colorAnimation = new QPropertyAnimation(VarButton, "styleSheet", this);
            colorAnimation->setDuration(1000);
            colorAnimation->setStartValue(QString("background-color: %1").arg(startColor.name()));
            colorAnimation->setEndValue(QString("background-color: %1").arg(endColor.name()));

            QParallelAnimationGroup *group = new QParallelAnimationGroup(this);
            group->addAnimation(animation);
            group->addAnimation(colorAnimation);
            group->start();

            VarButton->setToolTip("in");      //markiert, das der Spieler nun im Spiel ist
            VarButton->setStatusTip("1");     //legt Feldposition der Figur im StatusTip ab; bei Spieler = field_1


        }
        else if(VarButton == ui->B1 ||VarButton == ui->B2||VarButton == ui->B3||VarButton == ui->B4)
        {
                   animation->setStartValue(QRect(VarButton->x(), VarButton->y(), 31, 31));
                   animation->setEndValue(QRect(ui->field_11->x(), ui->field_11->y(), 40, 40));
                   animation->start();
                   VarButton->setToolTip("in");      //markiert, das der Spieler nun im Spiel ist
                   VarButton->setStatusTip("11");    //Spieler B Start = field_11
        }
    }
   // alle möglichen Spielzüge für Spieler A
   else if(VarButton->toolTip() == "in" && (VarButton == ui->A1 || VarButton == ui->A2||VarButton == ui->A3||VarButton == ui->A4))
   {
        //aktuelle Position der Figur ermitteln aus dem StatusTip und addiert den Würfelwert für den aktuellen zug. Speichert ergebnis in int Ply
        QString PlayerPosition = VarButton->statusTip();
        int FieldID = PlayerPosition.toInt();
        qDebug()<<FieldID;
        int goTo = diceValue + FieldID;
        qDebug()<<goTo;

        if (goTo>40)
        {            
                    QPropertyAnimation *animation = new QPropertyAnimation(VarButton, "geometry", this);
                    animation->setDuration(1000);
                    animation->setStartValue(QRect(VarButton->x(), VarButton->y(), 40, 40));
                    if(VarButton == ui->A1)
                    {
                     animation->setEndValue(QRect(ui->finish_A4->x(), ui->finish_A4->y(), 31, 31));
                     VarButton->setStatusTip(""); //alte Position löschen, da Spieler im Ziel ist
                    }
                    if(VarButton == ui->A2)
                    {
                     animation->setEndValue(QRect(ui->finish_A3->x(), ui->finish_A3->y(), 31, 31));
                     VarButton->setStatusTip("");
                    }
                    if(VarButton == ui->A3)
                    {
                     animation->setEndValue(QRect(ui->finish_A2->x(), ui->finish_A2->y(), 31, 31));
                     VarButton->setStatusTip("");
                    }
                    if(VarButton == ui->A4)
                    {
                     animation->setEndValue(QRect(ui->finish_A1->x(), ui->finish_A1->y(), 31, 31));
                     VarButton->setStatusTip("");
                    }
                    animation->start();
        }
        else
        {
            //Umwandlung des Integers in einen QString um das nächste Feld zu finden
            std::string myString = "field_" + std::to_string(goTo);
            QString nextFieldName = QString::fromStdString(myString);
            //Umwandlung des Integers in einen String, um die Spielerposition zu aktualisieren
            QString nextFieldID = QString::number(goTo);            

            //neues Zielfeld finden
            QLabel* VarLable = this->findChild<QLabel*>(nextFieldName);
            int myX = VarLable->x(); // Koordinaten des Zielfeldes wegspeichern, nötig weil VarLabel direkt nicht funktioniert
            int myY = VarLable->y();
            QPropertyAnimation *animation = new QPropertyAnimation(VarButton, "geometry", this);
            animation->setStartValue(QRect(VarButton->x(), VarButton->y(), 31, 31));
            animation->setEndValue(QRect(myX, myY, 40, 40));
            animation->start();
            VarButton->setStatusTip(nextFieldID);     //aktualisiert die Spielerposition

            //Überprüfung, ob gegnerischen Figuren bereits auf diesem Feld steht. Falls ja -> muss dieser zurück in sein Starthaus
            if (ui->B1->statusTip() == nextFieldID)
            {
                //Spielfiguren aus dem Spiel nehmen
                QPropertyAnimation *animation = new QPropertyAnimation(ui->B1, "geometry", this);
                animation->setDuration(1000);
                animation->setStartValue(QRect(ui->B1->x(), ui->B1->y(), 40, 40));
                animation->setEndValue(QRect(ui->house_B1->x(), ui->house_B1->y(), 31, 31)); //geschlagene Figur wird zurück ins "Haus" animiert
                animation->start();
                ui->B1->setToolTip("");
                ui->B1->setStatusTip("");
                ui->B1->setEnabled(false);
            }
            if (ui->B2->statusTip() == nextFieldID)
            {
                QPropertyAnimation *animation = new QPropertyAnimation(ui->B2, "geometry", this);
                animation->setDuration(1000);
                animation->setStartValue(QRect(ui->B2->x(), ui->B2->y(), 40, 40));
                animation->setEndValue(QRect(ui->house_B2->x(), ui->house_B2->y(), 31, 31)); //geschlagene Figur wird zurück ins "Haus" animiert
                animation->start();
                ui->B2->setToolTip("");
                ui->B2->setStatusTip("");
                ui->B2->setEnabled(false);
            }
            if (ui->B3->statusTip() == nextFieldID)
            {
                QPropertyAnimation *animation = new QPropertyAnimation(ui->B3, "geometry", this);
                animation->setDuration(1000);
                animation->setStartValue(QRect(ui->B3->x(), ui->B3->y(), 40, 40));
                animation->setEndValue(QRect(ui->house_B3->x(), ui->house_B3->y(), 31, 31)); //geschlagene Figur wird zurück ins "Haus" animiert
                animation->start();
                ui->B3->setToolTip("");
                ui->B3->setStatusTip("");
                ui->B3->setEnabled(false);
            }
            if (ui->B4->statusTip() == nextFieldID)
            {
                QPropertyAnimation *animation = new QPropertyAnimation(ui->B4, "geometry", this);
                animation->setDuration(1000);
                animation->setStartValue(QRect(ui->B4->x(), ui->B4->y(), 40, 40));
                animation->setEndValue(QRect(ui->house_B4->x(), ui->house_B4->y(), 31, 31)); //geschlagene Figur wird zurück ins "Haus" animiert
                animation->start();
                ui->B4->setToolTip("");
                ui->B4->setStatusTip("");
                ui->B4->setEnabled(false);
            }
        }
   }
   // alle möglichen Spielzüge für Spieler B
   else if(VarButton->toolTip() == "in" && (VarButton == ui->B1 || VarButton == ui->B2||VarButton == ui->B3||VarButton == ui->B4))
   {
        //aktuelle Position der Figur ermitteln aus dem StatusTip und addiert den Würfelwert für den aktuellen zug. Speichert ergebnis in int Ply
        QString PlayerPosition = VarButton->statusTip();
        int FieldID = PlayerPosition.toInt();
        int goTo = (diceValue + FieldID) % 40; //hier Modulo verwendet, da max. 40 Felder


        if (goTo>10 && FieldID <11) //Definiert die Kriterien für den Einzug ins Ziel
        {
            QPropertyAnimation *animation = new QPropertyAnimation(VarButton, "geometry", this);
            animation->setDuration(1000);
            animation->setStartValue(QRect(VarButton->x(), VarButton->y(), 40, 40));
            if(VarButton == ui->B1)
            {
             animation->setEndValue(QRect(ui->finish_B4->x(), ui->finish_B4->y(), 31, 31));
             VarButton->setStatusTip(""); //alte Position löschen, da Spieler im Ziel ist
            }
            if(VarButton == ui->B2)
            {
             animation->setEndValue(QRect(ui->finish_B3->x(), ui->finish_B3->y(), 31, 31));
             VarButton->setStatusTip("");
            }
            if(VarButton == ui->B3)
            {
             animation->setEndValue(QRect(ui->finish_B2->x(), ui->finish_B2->y(), 31, 31));
             VarButton->setStatusTip("");
            }
            if(VarButton == ui->B4)
            {
             animation->setEndValue(QRect(ui->finish_B1->x(), ui->finish_B1->y(), 31, 31));
             VarButton->setStatusTip("");
            }
            animation->start();
        }
        else // Spielzug auf dem Feld
            {
            //Umwandlung des Integers in einen String um das nächste Feld zu finden
            std::string myString = "field_" + std::to_string(goTo);
            QString nextFieldName = QString::fromStdString(myString);
            //Umwandlung des Integers in einen String, um die Spielerposition zu aktualisieren
            QString nextFieldID = QString::number(goTo);
            qDebug()<<nextFieldName;

            //neues Zielfeld finden
            QLabel* VarLable = this->findChild<QLabel*>(nextFieldName);
            int myX = VarLable->x(); // Koordinaten des Zielfeldes wegspeichern, nötig weil die VarLabel direkt nicht funktioniert
            int myY = VarLable->y();
            QPropertyAnimation *animation = new QPropertyAnimation(VarButton, "geometry", this);
            animation->setStartValue(QRect(VarButton->x(), VarButton->y(), 31, 31));
            animation->setEndValue(QRect(myX, myY, 40, 40));
            animation->start();
            VarButton->setStatusTip(nextFieldID);     //aktualisiert die Spielerposition

            //Überprüfung, ob gegnerischen Figuren bereits auf diesem Feld steht. Falls ja -> muss dieser zurück in sein Starthaus
            if (ui->A1->statusTip() == nextFieldID)
            {
                QPropertyAnimation *animation = new QPropertyAnimation(ui->A1, "geometry", this);
                animation->setDuration(1000);
                animation->setStartValue(QRect(ui->A1->x(), ui->A1->y(), 40, 40));
                animation->setEndValue(QRect(ui->house_A1->x(), ui->house_A1->y(), 31, 31)); //geschlagene Figur wird zurück ins "Haus" animiert
                animation->start();
                ui->A1->setToolTip("");
                ui->A1->setStatusTip("");
                ui->A1->setEnabled(false);
            }
            if (ui->A2->statusTip() == nextFieldID)
            {
                QPropertyAnimation *animation = new QPropertyAnimation(ui->A2, "geometry", this);
                animation->setDuration(1000);
                animation->setStartValue(QRect(ui->A2->x(), ui->A2->y(), 40, 40));
                animation->setEndValue(QRect(ui->house_A2->x(), ui->house_A2->y(), 31, 31)); //geschlagene Figur wird zurück ins "Haus" animiert
                animation->start();
                ui->A2->setToolTip("");
                ui->A2->setStatusTip("");
                ui->A2->setEnabled(false);
            }
            if (ui->A3->statusTip() == nextFieldID)
            {
                QPropertyAnimation *animation = new QPropertyAnimation(ui->A3, "geometry", this);
                animation->setDuration(1000);
                animation->setStartValue(QRect(ui->A3->x(), ui->A3->y(), 40, 40));
                animation->setEndValue(QRect(ui->house_A3->x(), ui->house_A3->y(), 31, 31)); //geschlagene Figur wird zurück ins "Haus" animiert
                animation->start();
                ui->A3->setToolTip("");
                ui->A3->setStatusTip("");
                ui->A3->setEnabled(false);
            }
            if (ui->A4->statusTip() == nextFieldID)
            {
                QPropertyAnimation *animation = new QPropertyAnimation(ui->A4, "geometry", this);
                animation->setDuration(1000);
                animation->setStartValue(QRect(ui->A4->x(), ui->A4->y(), 40, 40));
                animation->setEndValue(QRect(ui->house_A4->x(), ui->house_A4->y(), 31, 31)); //geschlagene Figur wird zurück ins "Haus" animiert
                animation->start();
                ui->A4->setToolTip("");
                ui->A4->setStatusTip("");
                ui->A4->setEnabled(false);
            }
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
        gm->updateMove(diceValue, BtnName);
    }
}
void MainWindow::A3Btn_clicked()//Aufruf der Spielfigur + Überprüfung, dass nur der "richtige" Spieler diesen ansprechen darf

{
    if (PlayerNo == 1)
    {
        QString BtnName = "A3";
        gm->updateMove(diceValue, BtnName);
    }
}
void MainWindow::A4Btn_clicked()//Aufruf der Spielfigur + Überprüfung, dass nur der "richtige" Spieler diesen ansprechen darf

{
    if (PlayerNo == 1)
    {
        QString BtnName = "A4";      
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

