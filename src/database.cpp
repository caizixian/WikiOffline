#include "database.h"
#include "ui_database.h"
#include <QtGui>
#include <iostream>
using namespace std;
string stemp;
QString s2q(const string &s);
string q2s(const QString &s);
article indexion;
database::database(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::database)
{
    ui->setupUi(this);
}
database::~database()
{
    delete ui;
}
void database::on_pushButton_clicked()
{
    QString databasepath = QFileDialog::getOpenFileName(this,"选择一个维基百科数据库",QDir::currentPath(),"Wikipedia Database(*.xml)");
    ui->lineEdit->setText(databasepath);
}
void database::on_pushButton_2_clicked()
{
    QString indexpath = QFileDialog::getSaveFileName(this, "生成索引的位置",QDir::currentPath(), "Wikipedia Offline Reader Index(*.db)");
    ui->lineEdit_2->setText(indexpath);
}
void database::on_pushButton_3_clicked()//关键的生成索引环节
{
    cin.clear();
    freopen(q2s(ui->lineEdit->text()).c_str(),"r",stdin);//读取数据库路径
    freopen(q2s(ui->lineEdit_2->text()).c_str(),"w",stdout);//读取索引路径

    //progress、tail用于进度条
    long long tail;
    fseeko64(fr,0,2);
    tail=ftello64(fr);
    int progress;

    int flag=0,num=1;
    fseeko64(fr,0,ios_base::beg);
    std::ios::sync_with_stdio(false);
    string s;

    while(getline(cin,s))
    {
        if(s.size()>=25&&flag==1)//防止溢出
        {
            if(s.substr(0,20)=="    <redirect title=")//重定向的标志
            {  indexion.direction=s.substr(21,s.size()-25);
                indexion.begin=0;
                cout<<indexion.title<<endl<<"RD"<<endl<<indexion.direction<<endl;//用RD作为索引中重定向的标志
                flag=0;
                num++;
            }
            else
            {
                indexion.direction="";
            }
        }

        if(s.size()>=21&&flag==1)
            if(s.substr(0,21)=="      <text xml:space")//记录正文位置
            {

                indexion.begin=ftello64(fr);
                flag=0;
                num++;
                cout<<indexion.title<<endl<<indexion.begin<<endl;
            }


        if(flag==0&&s.size()>=11)//找到标题后flag做标记
            if(s.substr(0,11)=="    <title>")
            {
                indexion.title=s.substr(11,s.size()-19);
                num++;
                flag=1;
            }



        progress=(100*float(ftello64(fr)/float(tail)));
        ui->progressBar->setValue(progress);
    }
}
