#ifndef HELP_H
#define HELP_H

#include <QMainWindow>

namespace Ui {
class help;
}

class help : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit help(QWidget *parent = 0);
    ~help();
    
private:
    Ui::help *ui;
};

#endif // HELP_H
