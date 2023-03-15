#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QMainWindow>
#include <mainwindow.h>
//#include <gamemanager.h>

namespace Ui { class StartWindow; }

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
     StartWindow(QWidget *parent = nullptr);
    ~StartWindow();
     StartWindow (MainWindow *mw);
     void setGameManager(GameManager *gm);

private:
    Ui::StartWindow *ui;
    MainWindow *mw;
    GameManager *gm;

public slots:
    void startBtn_clicked();
    void endBtn_clicked();
};

#endif // STARTWINDOW_H
