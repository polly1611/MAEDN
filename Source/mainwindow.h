#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <pitch.h>

namespace Ui { class MainWindow;}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent=nullptr);
    ~MainWindow();

private:

    Ui::MainWindow *ui;

 public slots:
    void quit();

};

#endif // MAINWINDOW_H
