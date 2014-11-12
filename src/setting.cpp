#include "setting.h"
#include "ui_setting.h"
#include <QtGui>
#include <Windows.h>
setting::setting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::setting)
{
    ui->setupUi(this);
    QSettings *setting = new QSettings ("config.ini",QSettings ::IniFormat);
    ui->database->setText(setting->value("General/Database","Default Value").toString());
    ui->index->setText(setting->value("General/Index","Default Value").toString());
}

setting::~setting()
{
    delete ui;
}
QString s2q(const std::string &s);
std::string q2s(const QString &s);
void setting::on_databaseButton_clicked()
{

    QString filepath = QFileDialog::getOpenFileName(this,"选择一个维基百科数据库",QDir::currentPath(),"维基百科数据库文件(*.xml)");
    ui->database->setText(filepath);
}
void setting::on_outpathButton_clicked()
{

    QString outpath = QFileDialog::getSaveFileName(this, "输出文件",QDir::currentPath(), "文本格式(*.txt)");
    ui->outpath->setText(outpath);
}
void restart()
{
    qApp->quit();
    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
}
void setting::on_yesButton_clicked()
{
    QSettings *setting = new QSettings ("config.ini",QSettings ::IniFormat);
    setting->setValue("General/Database",ui->database->text());
    setting->setValue("General/Index",ui->index->text());
    setting->setValue("General/Outpath",ui->outpath->text());

}

void setting::on_indexButton_clicked()
{
    QString filepath = QFileDialog::getOpenFileName(this,"与数据库相对应的索引文件",QDir::currentPath(),"维基离线索引(*.db)");
    ui->index->setText(filepath);
}


void setting::on_noButton_clicked()
{
    restart();
}
