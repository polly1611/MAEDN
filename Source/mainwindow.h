#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>


namespace Ui { class MainWindow;}

class GameManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent=nullptr);
    ~MainWindow();
    void setGameManager(GameManager *gm);
    void move(int diceValue, QString BtnName);
    void sendName(QString name);


static int playerCount;
private:

    Ui::MainWindow *ui;
    GameManager *gm;

 int PlayerNo;
 int diceValue;
 int goTo;
 QLabel Field[44];



signals:
 void clicked();
 void rolldice ();

public slots:
    void diceBtn_clicked();
    void A1Btn_clicked();
    void A2Btn_clicked();
    void B1Btn_clicked();
    void B2Btn_clicked();


};

#endif // MAINWINDOW_H
