#ifndef SETTING_H
#define SETTING_H

#include <QMainWindow>

namespace Ui {
class setting;
}

class setting : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit setting(QWidget *parent = 0);
    ~setting();
    
private slots:
    void on_databaseButton_clicked();

    void on_yesButton_clicked();

    void on_indexButton_clicked();

    void on_noButton_clicked();

    void on_outpathButton_clicked();
private:
    Ui::setting *ui;
};

#endif // SETTING_H
