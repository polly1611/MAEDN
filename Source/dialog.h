#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
# include <mainwindow.h>

namespace Ui { class Dialog;}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    MainWindow *w;

public slots:
    void startBtn_clicked();
    void endBtn_clicked();
};

#endif // DIALOG_H
