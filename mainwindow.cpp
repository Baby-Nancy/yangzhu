#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolBar>
#include <query_pig.h>
#include <fstream>
#include <qDebug>

using namespace std;

struct A_Pig{
    int sty_id;
    int pig_name;//o-黑猪,1-小花猪，2-大花白猪
    int day;
    float weight;
    float weight_unit;
};

struct PigSty{
    int Sty_id;
    int flag;//当前猪圈猪的种类，flag-0表示全是黑猪
    int PigNum;//当前猪圈里猪的数量
    A_Pig Pig[10];
    float income;
    PigSty *next;
};

PigSty * CreatPigStyList(int num){
    PigSty *head=NULL;
    PigSty *s1;//s1指向新建结点
    PigSty *s2;//s2指向尾结点
    qsrand((unsigned int)time(NULL));//产生随机数种子
    //qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0;i<num;i++)
    {
        s1=new PigSty;
        s1->Sty_id=i;
        s1->PigNum=10;//猪圈里猪的数量

        //初始化猪圈里的猪的信息
        s1->flag=qrand()%2;//决定猪圈是否全是黑猪
        for(int j=0;j<10;j++)
        {
            if(s1->flag==0)s1->Pig[j].pig_name=0;//都是黑猪
            else s1->Pig[j].pig_name=qrand()%2+1;//没有黑猪

            s1->Pig[j].sty_id=i;
            s1->Pig[j].day=0;
            s1->Pig[j].weight=20+(float)qrand()/(float)(RAND_MAX/(30));
            s1->Pig[j].weight_unit=1.0*qrand()/RAND_MAX*(1.2-0);
            //s1->Pig[j].weight=(qrand()%30+20)+qrand()/double(RAND_MAX);
        }

        s1->income=0;
        s1->next=NULL;
        if(head==NULL)head=s1;
        else  s2->next=s1;
        s2=s1;
    }
    return head;
}

PigSty * creatlist(){
    PigSty *head=NULL;
    PigSty *s1;//s1指向新建结点
    PigSty *s2;//s2指向尾结点

    PigSty x[100];
    PigSty *y=x;
    ifstream ifs;
    ifs.open("D:\\Qtproject\\yangzhu\\pigsty.txt",ios::in|ios::binary);
    for(int k=0;k<100;k++)
    {
        ifs.read((char *)y,sizeof(x[0]));
        y++;
    }
    ifs.close();

    for(int i=0;i<100;i++)
    {
        s1=new PigSty;
        s1->Sty_id=i;
        s1->PigNum=x[i].PigNum;//猪圈里猪的数量
        s1->flag=x[i].flag;
        s1->income=x[i].income;

        //从文件里读猪的数据放到链表里
        for(int j=0;j<10;j++)
        {
            s1->Pig[j].sty_id=i;
            s1->Pig[j].pig_name=x[i].Pig[j].pig_name;
            s1->Pig[j].day=x[i].Pig[j].day;
            s1->Pig[j].weight=x[i].Pig[j].weight;
            s1->Pig[j].weight_unit=x[i].Pig[j].weight_unit;
            //s1->Pig[j].weight=(qrand()%30+20)+qrand()/double(RAND_MAX);
        }

        s1->next=NULL;
        if(head==NULL)head=s1;
        else  s2->next=s1;
        s2=s1;
    }
    return head;
}

void Sold_outPig(PigSty *head){
    PigSty *s1=head;
    //每30天后猪的体重和饲养天数变化
    for(int i=0;s1!=NULL;i++){
        for(int j=0;j<s1->PigNum;j++){
            if(s1->Pig[j].pig_name!=-1){
                    s1->Pig[j].day+=30;
                    s1->Pig[j].weight+=s1->Pig[j].weight_unit*30;
            }
        }
        s1=s1->next;
    }

    s1=head;
    ofstream ofs;
    for(int i=0;s1!=NULL;i++){
        int pignum=0;
        for(int j=0;j<s1->PigNum;j++){
            if(s1->Pig[j].day>=360||s1->Pig[j].weight>=150){
                //猪的品种不同，卖出的价格也不同
                switch(s1->Pig[j].pig_name){
                    case 0:{s1->income=s1->income+15*s1->Pig[j].weight;break;}
                    case 1:{s1->income=s1->income+7*s1->Pig[j].weight;break;}
                    case 2:{s1->income=s1->income+6*s1->Pig[j].weight;break;}
                }
                //记录卖出的猪的信息
                A_Pig p=s1->Pig[j];
                ofs.open("D:\\Qtproject\\yangzhu\\sell.txt",ios::out|ios::binary|ios::app);
                ofs.write((const char *)&p,sizeof(p));
                ofs.close();

                //对猪圈中卖出的猪的位置的信息进行重置
                s1->Pig[j].pig_name=-1;
                s1->Pig[j].day=0;
                s1->Pig[j].weight=0;
                s1->Pig[j].weight_unit=0;
                pignum++;//卖出猪的数量
            }
        }
        s1->PigNum=s1->PigNum-pignum;//当前猪圈猪的数量发生变化
        //*sum+=pignum;//此次卖猪总共卖出的猪的数量发生变化
        if(!s1->PigNum){  //如果这个猪圈的猪卖完了，重新考虑这个猪圈放黑猪还是其它两种猪
            s1->flag=rand()%2;//重新考虑当前猪圈应该放什么品种的猪
        }
        s1=s1->next;
    }
    return ;
}

void Buy_inPig(PigSty *head){
    PigSty *s1=head;
    qsrand((unsigned int)time(NULL));
    //买进sum只猪，对这些猪的信息进行初始化
    for(int i=0;s1!=NULL;i++){
        for(int j=0;s1->PigNum<10;j++){
            if(s1->Pig[j].pig_name==-1){
                if(s1->PigNum!=0&&s1->flag==0)s1->Pig[j].pig_name=0;
                if(s1->PigNum!=0&&s1->flag==1)s1->Pig[j].pig_name=rand()%2+1;
                if(s1->PigNum==0){         //猪卖完了，要重新考虑猪圈中放的是黑猪还是其它猪
                    //括号里的操作已经重新确定当前猪圈应该放什么类型的猪了
                    if((s1->flag=rand()%2))s1->Pig[j].pig_name=rand()%2+1;//flag==1,放小花猪和大花白猪
                    else s1->Pig[j].pig_name=0;  //flag==0，全放黑猪
                }
                s1->Pig[j].weight=20+(float)qrand()/(float)(RAND_MAX/(30));
                        //(rand()%31+20)+rand()/double(RAND_MAX);
                s1->Pig[j].weight_unit=1.0*qrand()/RAND_MAX*(1.2-0);
                        //1.0*rand()/RAND_MAX*(1.2-0);
                s1->PigNum++;

                //记录买进的猪的信息
                A_Pig p=s1->Pig[j];
                ofstream ofs;
                ofs.open("D:\\Qtproject\\yangzhu\\buy.txt",ios::out|ios::binary|ios::app);
                ofs.write((const char *)&p,sizeof(p));
                ofs.close();
            }
        }
        s1=s1->next;
    }
}

void tab(PigSty *x){
    //从文件中读数据
    //从文件中读取当前猪圈的信息
    //PigSty x[100];
    ifstream ifs;
    ifs.open("D:\\Qtproject\\yangzhu\\pigsty.txt",ios::in|ios::binary);
    for(int k=0;k<100;k++)
    {
        ifs.read((char *)x,sizeof(x[0]));
        x++;
    }
    ifs.close();
}

void write(PigSty *s)
{
    PigSty p;
    ofstream ofs;
    ofs.open("D:\\Qtproject\\yangzhu\\pigsty.txt",ios::out|ios::binary);
    while(s!=NULL){
        ofs.write((const char *)s,sizeof(p));
        s=s->next;
    }
    ofs.close();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(2);

    connect(ui->actionnew,&QAction::triggered,[=](){
        PigSty *head1=CreatPigStyList(100);
        PigSty *sp=head1;
        //把整个猪场的信息存入文件中
        write(sp);
        ofstream ofs;
        ofs.open("D:\\Qtproject\\yangzhu\\sell.txt",ios::trunc|ios::binary);
        ofs.close();
        ofstream ofs1;
        ofs1.open("D:\\Qtproject\\yangzhu\\buy.txt",ios::trunc|ios::binary);
        ofs1.close();
    });

    //点击功能键“卖出的猪的信息”
    connect(ui->actionsell,&QAction::triggered,this,[=](){
        //ui->stackedWidget->setCurrentIndex(4);//
        ui->tableWidget_2->setColumnCount(3);//
        ui->tableWidget_2->setRowCount(100);
        ui->tableWidget_2->setHorizontalHeaderLabels(QStringList()<<"猪的种类"<<"猪的体重"<<"卖出价格");//
        A_Pig p;
        int a=0;
        ifstream ifs;
        ifs.open("D:\\Qtproject\\yangzhu\\sell.txt",ios::in|ios::binary);
//        while(!ifs){
//            qDebug()<<"文件打开失败";
//        }
//        while(ifs.eof()){
//            qDebug()<<"文件已到达末尾";
//        }
        while(!ifs.eof())
        {
            ifs.read((char *)&p,sizeof(p));
            int j=0;
            switch(p.pig_name)
            {
            case 0:{ui->tableWidget_2->setItem(a,j,new QTableWidgetItem("黑猪"));break;}
            case 1:{ui->tableWidget_2->setItem(a,j,new QTableWidgetItem("小花猪"));break;}
            case 2:{ui->tableWidget_2->setItem(a,j,new QTableWidgetItem("大白花猪"));break;}
            }
            ui->tableWidget_2->setItem(a,++j,new QTableWidgetItem(QString::number(p.weight)));
            switch(p.pig_name)
            {
            case 0:{ui->tableWidget_2->setItem(a,++j,new QTableWidgetItem(QString::number(p.weight*15)));break;}
            case 1:{ui->tableWidget_2->setItem(a,++j,new QTableWidgetItem(QString::number(p.weight*7)));break;}
            case 2:{ui->tableWidget_2->setItem(a,++j,new QTableWidgetItem(QString::number(p.weight*6)));break;}
            }
            if(ifs.eof()){
                break;
            }
            a++;
        }
        ifs.close();
        ui->stackedWidget->setCurrentIndex(4);//
    });

    //点击功能键“买进的猪的信息”
    connect(ui->actionbuy,&QAction::triggered,this,[=](){
        //ui->stackedWidget->setCurrentIndex(4);//
        ui->tableWidget_3->setColumnCount(2);//
        ui->tableWidget_3->setRowCount(100);
        ui->tableWidget_3->setHorizontalHeaderLabels(QStringList()<<"猪的种类"<<"猪的体重");//
        A_Pig p;
        int a=0;
        ifstream ifs;
        ifs.open("D:\\Qtproject\\yangzhu\\buy.txt",ios::in|ios::binary);
//        while(!ifs){
//            qDebug()<<"文件打开失败";
//        }
//        while(ifs.eof()){
//            qDebug()<<"文件已到达末尾";
//        }
        while(!ifs.eof())
        {
            ifs.read((char *)&p,sizeof(p));
            int j=0;
            switch(p.pig_name)
            {
            case 0:{ui->tableWidget_3->setItem(a,j,new QTableWidgetItem("黑猪"));break;}
            case 1:{ui->tableWidget_3->setItem(a,j,new QTableWidgetItem("小花猪"));break;}
            case 2:{ui->tableWidget_3->setItem(a,j,new QTableWidgetItem("大白花猪"));break;}
            }
            ui->tableWidget_3->setItem(a,++j,new QTableWidgetItem(QString::number(p.weight)));
            if(ifs.eof()){
                break;
            }
            a++;
        }
        ifs.close();
        ui->stackedWidget->setCurrentIndex(5);//
    });

//    //点击“不同种类猪的信息”
//    connect(ui->actionblack,&QAction::triggered,[=](){
//        PigSty x[100];
//        PigSty *y=x;
//        ifstream ifs;
//        ifs.open("D:\\Qtproject\\yangzhu\\pigsty.txt",ios::in|ios::binary);
//        for(int i=0;i<100;i++){
//            ifs.read((char *)y,sizeof(x[0]));
//            y++;
//        }
//        ifs.close();
//        int sum=0;
//        int a=0;
//        ui->tableWidget_4->setRowCount(1000);
//        ui->tableWidget_4->setColumnCount(2);
//        ui->tableWidget_4->setHorizontalHeaderLabels(QStringList()<<"体重"<<"饲养天数");
//        for(int i=0;i<100;i++){
//            for(int j=0;j<10;j++){
//                while(x[i].Pig[j].pig_name==0){
//                    sum++;
//                    ui->tableWidget_4->setItem(a,0,new QTableWidgetItem(QString::number(x[i].Pig[j].weight)));
//                    ui->tableWidget_4->setItem(a,1,new QTableWidgetItem(QString::number(x[i].Pig[j].day)));
//                    a++;
//                }
//            }
//        }
//        ui->stackedWidget->setCurrentIndex(6);
//    });

    //点击功能键“猪圈信息”
    connect(ui->actionquery_pigsty,&QAction::triggered,[=](){
        ui->stackedWidget->setCurrentIndex(3);
        connect(ui->btn_yes2,&QPushButton::clicked,[=](){
            int id=ui->lineEdit_pigstyid->text().toInt();
            ifstream ifs;
            PigSty p;
            ifs.open("D:\\Qtproject\\yangzhu\\pigsty.txt",ios::in|ios::binary);
            for(int i=0;i<=id;i++){
                ifs.read((char *)&p,sizeof(p));
            }
            switch(p.flag)
            {
            case 0:{ui->lineEdit->setText("黑猪");break;}
            case 1:{ui->lineEdit->setText("小花猪和大白花猪");break;}
            }
            ui->lineEdit_2->setText(QString::number(p.PigNum));
            ifs.close();
            connect(ui->btn_find,&QPushButton::clicked,[=](){
                ui->lineEdit->clear();
                ui->lineEdit_2->clear();
                ui->lineEdit_pigstyid->clear();
            });
        });
    });
    connect(ui->btn_back3,&QPushButton::clicked,[=](){
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_pigstyid->clear();
        ui->stackedWidget->setCurrentIndex(2);
    });

    //点击功能键“猪的信息”，调用mainwindow的成员函数，弹出窗口
    connect(ui->actionquery_pig,&QAction::triggered,this,&MainWindow::Query_Pig);

    //点击功能键“猪场信息”，调用mainwindow的成员函数，弹出窗口dialog_1
    connect(ui->actionquery_pigtab,&QAction::triggered,this,[=](){
        ui->stackedWidget->setCurrentIndex(0);

        //跳转到猪圈的表格
        connect(ui->tab_btnPigsty,&QPushButton::clicked,[=](){
            ui->stackedWidget->setCurrentIndex(0);
        });
        //跳转到猪的表格
        connect(ui->tab_btnPig,&QPushButton::clicked,[=](){
            ui->stackedWidget->setCurrentIndex(1);
        });


        //回到主页面
        connect(ui->btn_back,&QPushButton::clicked,[=](){
            ui->stackedWidget->setCurrentIndex(2);
        });

        //回到主页面
        connect(ui->btn_back2,&QPushButton::clicked,[=](){
            ui->stackedWidget->setCurrentIndex(2);
        });

        ui->tableWidget->setColumnCount(4);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"猪圈编号"<<"猪的种类"<<"猪的数量"<<"猪圈收入");
        ui->tableWidget->setColumnWidth(1,200);
        ui->tableWidget->setRowCount(100);

        ui->tableWidget_pig->setColumnCount(5);
        ui->tableWidget_pig->setHorizontalHeaderLabels(QStringList()<<"猪圈编号"<<"猪的种类"<<"饲养天数"<<"体重"<<"体重增长：kg/d");
        ui->tableWidget_pig->setRowCount(1000);

        PigSty x[100];
        tab(x);
        for(int i=0;i<100;i++)
        {
            //将读取到的信息插入猪圈的表格
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(x[i].Sty_id)));
            switch(x[i].flag)
            {
            case 0:{ui->tableWidget->setItem(i,1,new QTableWidgetItem("黑猪"));break;}
            case 1:{ui->tableWidget->setItem(i,1,new QTableWidgetItem("小花猪和大白花猪"));break;}
            }
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(x[i].PigNum)));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(x[i].income)));
            //将读取到的信息插入猪的表格
            //"猪圈编号"<<"猪的种类"<<"饲养天数"<<"体重"<<"体重增长：kg/d"
            for(int j=0;j<10;j++)
            {
                ui->tableWidget_pig->setItem(j+i*10,0,new QTableWidgetItem(QString::number(i)));
                switch(x[i].Pig[j].pig_name)
                {
                case -1:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("已卖出"));break;}
                case 0:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("黑猪"));break;}
                case 1:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("小花猪"));break;}
                case 2:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("大白花猪"));break;}
                }
                ui->tableWidget_pig->setItem(j+i*10,2,new QTableWidgetItem(QString::number(x[i].Pig[j].day)));
                ui->tableWidget_pig->setItem(j+i*10,3,new QTableWidgetItem(QString::number(x[i].Pig[j].weight)));
                ui->tableWidget_pig->setItem(j+i*10,4,new QTableWidgetItem(QString::number(x[i].Pig[j].weight_unit)));
            }
        }

        connect(ui->btn_sell,&QPushButton::clicked,[=]()
        {
            //创建一个链表，把文件里的信息写入链表
            PigSty *head=creatlist();
            Sold_outPig(head);
            PigSty *s1=head;
    //        PigSty p;
    //        ofstream ofs1;
    //        ofs1.open("D:\\Qtproject\\yangzhu\\pigsty.txt",ios::trunc|ios::out|ios::binary);
    //        while(s1!=NULL){
    //            ofs1.write((const char *)s1,sizeof(p));
    //            s1=s1->next;
    //        }
    //        ofs1.close();
            write(s1);
        });
        connect(ui->btn_buy,&QPushButton::clicked,[=]()
        {
            PigSty *head2=creatlist();
            Buy_inPig(head2);
            PigSty *s2=head2;
            write(s2);
        });
        connect(ui->btn_new,&QPushButton::clicked,[=]()
        {
            //清空表格内容
            ui->tableWidget->clearContents();
            ui->tableWidget_pig->clearContents();

            //重新把文件内容插入两个表格
            PigSty y[100];
            tab(y);
            for(int i=0;i<100;i++)
            {
                //将读取到的信息插入猪圈的表格
                ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(y[i].Sty_id)));
                switch(y[i].flag)
                {
                case 0:{ui->tableWidget->setItem(i,1,new QTableWidgetItem("黑猪"));break;}
                case 1:{ui->tableWidget->setItem(i,1,new QTableWidgetItem("小花猪和大白花猪"));break;}
                }
                ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(y[i].PigNum)));
                ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(y[i].income)));
                //将读取到的信息插入猪的表格
                //"猪圈编号"<<"猪的种类"<<"饲养天数"<<"体重"<<"体重增长：kg/d"
                for(int j=0;j<10;j++)
                {
                    ui->tableWidget_pig->setItem(j+i*10,0,new QTableWidgetItem(QString::number(i)));
                    switch(y[i].Pig[j].pig_name)
                    {
                    case -1:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("已卖出"));break;}
                    case 0:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("黑猪"));break;}
                    case 1:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("小花猪"));break;}
                    case 2:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("大白花猪"));break;}
                    }
                    ui->tableWidget_pig->setItem(j+i*10,2,new QTableWidgetItem(QString::number(y[i].Pig[j].day)));
                    ui->tableWidget_pig->setItem(j+i*10,3,new QTableWidgetItem(QString::number(y[i].Pig[j].weight)));
                    ui->tableWidget_pig->setItem(j+i*10,4,new QTableWidgetItem(QString::number(y[i].Pig[j].weight_unit)));
                }
            }
        });

    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::Query_Pigtab(){
//    Dialog_1 dlg1;
//    dlg1.exec();
//}

void MainWindow::Query_Pig(){
    query_pig dlg2;
    dlg2.exec();
}
