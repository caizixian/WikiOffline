#ifndef DATABASE_H
#define DATABASE_H

#include <QMainWindow>

namespace Ui {
class database;
}

class database : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit database(QWidget *parent = 0);
    ~database();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::database *ui;
};
extern FILE *fr;
struct article
{
    std::string title,direction;
    long long begin;
};

#endif // DATABASE_H
