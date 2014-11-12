#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_action_5_triggered();
    void on_action_3_triggered();

    void on_searchButton_clicked();

    void on_action_2_triggered();

    void on_action_triggered();

    void on_readButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
