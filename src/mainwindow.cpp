#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <iostream>
#include <string>
#include <Qstring>
#include "about.h"
#include "database.h"
#include "help.h"
#include "setting.h"
#include <fstream>
FILE *fr=stdin;//文件指针*fr
article pages[20000000],result[10000];//pages为读取的条目索引，result为搜索结果
long long pagecount;//记录条目总数
long long stoi(std::string s)//字符串转成数值
{
    long long interger=0;
    for(unsigned i=0;i<=s.size()-1;i++)
    {
        interger=interger*10+int(s[i]-'0');
    }
    return interger;
}

QString s2q(const std::string &s)//string转换为QString
{
    return QString(QString::fromLocal8Bit(s.c_str()));
}
std::string q2s(const QString &s)//QString转换为string
{
    return std::string((const char *)s.toLocal8Bit());
}
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    //程序运行时读取配置文件
    QSettings *setting = new QSettings ("config.ini",QSettings ::IniFormat);
    QString indexpath;
    indexpath=setting->value("General/Index","Default Value").toString();
    QString database;
    database=setting->value("General/Database","Default Value").toString();
    QString outpath;
    outpath=setting->value("General/Outpath","Default Value").toString();
    //读取索引
    if(database!="Default Value"&&indexpath!="Default Value")
    {
        cin.clear();

        long long i=1;
        freopen(q2s(indexpath).c_str(),"r",stdin);

        std::ios::sync_with_stdio(false);//加快cin的速度
        std::string a;
        while(getline(cin,pages[i].title))
        {
            getline(cin,a);
            if(a=="RD")//重定向的标记
            {
                getline(cin,a);
                pages[i].direction=a;//设置重定向
            }
            else
                pages[i].begin=stoi(a);//设置被索引条目的位置
            i++;
        }

        pagecount=i;
    }
    else
        QMessageBox::information(NULL, "首次使用", "请设置维基百科数据库及其索引", QMessageBox::Yes );
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_5_triggered()
{
    about *aboutwindow=new about(this);
    aboutwindow->show();
}

void MainWindow::on_action_3_triggered()
{
    setting *settingwindow=new setting(this);
    settingwindow->show();
}

void MainWindow::on_searchButton_clicked()
{

    QString keyword=ui->lineEdit->text();//在搜索框中输入关键词
    std::string finder=q2s(keyword);
    long long num=1,t;
    ui->resultList->clear();

    for(long long j=1;j<=pagecount&&num<1000;j++)//开始搜索，最多不超过1000个结果
    {
        t=pages[j].title.find(finder);
        if(t>=0&&t<=255)
        {
            result[num].begin=pages[j].begin;
            result[num].title=pages[j].title;
            result[num].direction=pages[j].direction;
            ui->resultList->addItem(s2q(result[num].title));//把搜索结果放入result数组并显示在列表上
            num++;
        }

    }
}


void MainWindow::on_action_2_triggered()
{
    help *helpwindow=new help(this);
    helpwindow->show();
}

void MainWindow::on_action_triggered()
{
    database *datawindow=new database(this);
    datawindow->show();
}

void MainWindow::on_readButton_clicked()
{


    long long number=ui->resultList->currentRow()+1;
    if (number<=0)//如未选择条目则不读取
    return ;

    QString database;//打开数据库文件
    QSettings *setting = new QSettings ("config.ini",QSettings ::IniFormat);
    database=setting->value("General/Database","Default Value").toString();
    QString outpath;
    outpath=setting->value("General/Outpath","Default Value").toString();
    freopen(q2s(database).c_str(),"r",stdin);

    cin.clear();
    if(result[number].direction!="") //判断是否重定向
        for(long long j=1;j<=pagecount;j++)
        {
            if(pages[j].title==result[number].direction)//将定向结果转到重定向条目上
            {
                result[number].begin=pages[j].begin;
                break;
            }
        }
    fseeko64(fr,result[number].begin-2000,0);//ftello64输出文件指针存在误差，需要从2000字节前搜索

    freopen((q2s(outpath)).c_str(),"w",stdout);

    //输出正常条目及重定位后条目
    string tempstr;
    int flag=0;//flag为判断读取状况的标记
    while(flag!=3)
    {

        getline(cin,tempstr);

        if(flag==0)//即为未找到条目
            if(tempstr.size()>11)//防止溢出
            {    if(tempstr.substr(0,11)=="    <title>")
                {
                    if(result[number].direction==tempstr.substr(11,tempstr.size()-19)||result[number].title==tempstr.substr(11,tempstr.size()-19))
                        flag=1;
                }

            }

        if(flag==1)//即为找到条目，未找到正文
            if(tempstr.size()>=21)
            { if(tempstr.find("<text xml:space")>0&&tempstr.find("<text xml:space")<tempstr.size())
                {
                    flag=2;
                }
            }

        if(flag==2)//找到正文未找到结尾
        {
            cout<<tempstr<<endl;
            if(tempstr.find("</text>")>0&&tempstr.find("</text>")<tempstr.size())
            {
                flag=3;//全部完成

            }
        }
    }

    string command="start "+q2s(outpath);
    system(command.c_str());//打开维基条目
}
