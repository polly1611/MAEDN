#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>


namespace Ui { class MainWindow;}

class GameManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    Ui::MainWindow *ui;
    GameManager *gm;

 int PlayerNo;
 int diceValue;
 int goTo; 

public:
static int playerCount;

    MainWindow(QWidget *parent=nullptr);
    ~MainWindow();
    void setGameManager(GameManager *gm);
    void move(int diceValue, QString BtnName);
    void sendName(QString name);
    void update(QString name, QString VarButton, int oldfieldID, int diceValue);

signals:
  void rolldice ();

public slots:
    void diceBtn_clicked();
    void A1Btn_clicked();
    void A2Btn_clicked();
    void A3Btn_clicked();
    void A4Btn_clicked();
    void B1Btn_clicked();
    void B2Btn_clicked();
    void B3Btn_clicked();
    void B4Btn_clicked();
};

#endif // MAINWINDOW_H
