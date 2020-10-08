#include "dialog_1.h"
#include "ui_dialog_1.h"
#include <QDebug>
#include <QtGlobal>
#include <QTime>
#include <fstream>
#include <iostream>

using namespace std;

//PigSty * CreatPigStyList(int num){
//    PigSty *head=NULL;
//    PigSty *s1;//s1指向新建结点
//    PigSty *s2;//s2指向尾结点
//    qsrand((unsigned int)time(NULL));//产生随机数种子
//    //qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
//    for(int i=0;i<num;i++)
//    {
//        s1=new PigSty;
//        s1->Sty_id=i;
//        s1->PigNum=10;//猪圈里猪的数量

//        //初始化猪圈里的猪的信息
//        s1->flag=qrand()%2;//决定猪圈是否全是黑猪
//        for(int j=0;j<10;j++)
//        {
//            if(s1->flag==0)s1->Pig[j].pig_name=0;//都是黑猪
//            else s1->Pig[j].pig_name=qrand()%2+1;//没有黑猪

//            s1->Pig[j].day=0;
//            s1->Pig[j].weight=20+(float)qrand()/(float)(RAND_MAX/(30));
//            s1->Pig[j].weight_unit=1.0*qrand()/RAND_MAX*(1.2-0);
//            //s1->Pig[j].weight=(qrand()%30+20)+qrand()/double(RAND_MAX);
//        }

//        s1->income=0;
//        s1->next=NULL;
//        if(head==NULL)head=s1;
//        else  s2->next=s1;
//        s2=s1;
//    }
//    return head;
//}

//void Sold_outPig(PigSty *head){
//    PigSty *s1=head;
//    //每30天后猪的体重和饲养天数变化
//    for(int i=0;s1!=NULL;i++){
//        for(int j=0;j<s1->PigNum;j++){
//            if(s1->Pig[j].pig_name!=-1){
//                    s1->Pig[j].day+=30;
//                    s1->Pig[j].weight+=s1->Pig[j].weight_unit*30;
//            }
//        }
//        s1=s1->next;
//    }

//    s1=head;
//    for(int i=0;s1!=NULL;i++){
//        int pignum=0;
//        for(int j=0;j<s1->PigNum;j++){
//            if(s1->Pig[j].day>=360||s1->Pig[j].weight>=150){
//                //猪的品种不同，卖出的价格也不同
//                switch(s1->Pig[j].pig_name){
//                    case 0:{s1->income=s1->income+15*s1->Pig[j].weight;break;}
//                    case 1:{s1->income=s1->income+7*s1->Pig[j].weight;break;}
//                    case 2:{s1->income=s1->income+6*s1->Pig[j].weight;break;}
//                }
//                //对猪圈中卖出的猪的位置的信息进行重置
//                s1->Pig[j].pig_name=-1;
//                s1->Pig[j].day=0;
//                s1->Pig[j].weight=0;
//                s1->Pig[j].weight_unit=0;
//                pignum++;//卖出猪的数量
//            }
//        }
//        s1->PigNum=s1->PigNum-pignum;//当前猪圈猪的数量发生变化
//        //*sum+=pignum;//此次卖猪总共卖出的猪的数量发生变化
//        if(!s1->PigNum){  //如果这个猪圈的猪卖完了，重新考虑这个猪圈放黑猪还是其它两种猪
//            s1->flag=rand()%2;//重新考虑当前猪圈应该放什么品种的猪
//        }
//        s1=s1->next;
//    }
//    return ;
//}

//void Buy_inPig(PigSty *head){
//    PigSty *s1=head;
//    qsrand((unsigned int)time(NULL));
//    //买进sum只猪，对这些猪的信息进行初始化
//    for(int i=0;s1!=NULL;i++){
//        for(int j=0;s1->PigNum<10;j++){
//            if(s1->Pig[j].pig_name==-1){
//                if(s1->PigNum!=0&&s1->flag==0)s1->Pig[j].pig_name=0;
//                if(s1->PigNum!=0&&s1->flag==1)s1->Pig[j].pig_name=rand()%2+1;
//                if(s1->PigNum==0){         //猪卖完了，要重新考虑猪圈中放的是黑猪还是其它猪
//                    //括号里的操作已经重新确定当前猪圈应该放什么类型的猪了
//                    if((s1->flag=rand()%2))s1->Pig[j].pig_name=rand()%2+1;//flag==1,放小花猪和大花白猪
//                    else s1->Pig[j].pig_name=0;  //flag==0，全放黑猪
//                }
//                s1->Pig[j].weight=20+(float)qrand()/(float)(RAND_MAX/(30));
//                        //(rand()%31+20)+rand()/double(RAND_MAX);
//                s1->Pig[j].weight_unit=1.0*qrand()/RAND_MAX*(1.2-0);
//                        //1.0*rand()/RAND_MAX*(1.2-0);
//                s1->PigNum++;
//            }
//        }
//        s1=s1->next;
//    }
//}

//void tab(PigSty *x){
//    //从文件中读数据
//    //从文件中读取当前猪圈的信息
//    //PigSty x[100];
//    ifstream ifs;
//    ifs.open("D:\\Qtproject\\yangzhu\\pigsty.txt",ios::in|ios::binary);
//    for(int k=0;k<100;k++)
//    {
//        ifs.read((char *)x,sizeof(x[0]));
//        x++;
//    }
//    ifs.close();


//不要
//    //并将数据插入表格中
//    for(int i=0;i<100;i++)
//    {
//        //将读取到的信息插入猪圈的表格
//        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(x[i].Sty_id)));
//        switch(x[i].flag)
//        {
//        case 0:{ui->tableWidget->setItem(i,1,new QTableWidgetItem("黑猪"));break;}
//        case 1:{ui->tableWidget->setItem(i,1,new QTableWidgetItem("小花猪和大白花猪"));break;}
//        }
//        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(x[i].PigNum)));
//        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(x[i].income)));
//        //将读取到的信息插入猪的表格
//        //"猪圈编号"<<"猪的种类"<<"饲养天数"<<"体重"<<"体重增长：kg/d"
//        for(int j=0;j<10;j++)
//        {
//            ui->tableWidget_pig->setItem(j+i*10,0,new QTableWidgetItem(QString::number(i)));
//            switch(x[i].Pig[j].pig_name)
//            {
//            case -1:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("已卖出"));break;}
//            case 0:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("黑猪"));break;}
//            case 1:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("小花猪"));break;}
//            case 2:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("大白花猪"));break;}
//            }
//            ui->tableWidget_pig->setItem(j+i*10,2,new QTableWidgetItem(QString::number(x[i].Pig[j].day)));
//            ui->tableWidget_pig->setItem(j+i*10,3,new QTableWidgetItem(QString::number(x[i].Pig[j].weight)));
//            ui->tableWidget_pig->setItem(j+i*10,4,new QTableWidgetItem(QString::number(x[i].Pig[j].weight_unit)));
//        }
//    }
//}

//要
//void write(PigSty *s)
//{
//    PigSty p;
//    ofstream ofs;
//    ofs.open("D:\\Qtproject\\yangzhu\\pigsty.txt",ios::out|ios::binary);
//    while(s!=NULL){
//        ofs.write((const char *)s,sizeof(p));
//        s=s->next;
//    }
//    ofs.close();
//}

//Dialog_1::Dialog_1(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::Dialog_1)
//{
//    ui->setupUi(this);

//    PigSty *head=CreatPigStyList(100);
//    PigSty *s=head;

//    //把整个猪场的信息存入文件中
//    write(s);

//    //设置打开窗口时默认页面是猪圈信息的那一面
//    ui->stackedWidget->setCurrentIndex(0);
//    //跳转到猪圈的表格
//    connect(ui->tab_btnPigsty,&QPushButton::clicked,[=](){
//        ui->stackedWidget->setCurrentIndex(0);
//    });
//    //跳转到猪的表格
//    connect(ui->tab_btnPig,&QPushButton::clicked,[=](){
//        ui->stackedWidget->setCurrentIndex(1);
//    });
//    //退出该窗口
//    connect(ui->btn_back,&QPushButton::clicked,this,&Dialog_1::close);

//    ui->tableWidget->setColumnCount(4);
//    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<"猪圈编号"<<"猪的种类"<<"猪的数量"<<"猪圈收入");
//    ui->tableWidget->setRowCount(100);


//    ui->tableWidget_pig->setColumnCount(5);
//    ui->tableWidget_pig->setHorizontalHeaderLabels(QStringList()<<"猪圈编号"<<"猪的种类"<<"饲养天数"<<"体重"<<"体重增长：kg/d");
//    ui->tableWidget_pig->setRowCount(1000);

//    PigSty x[100];
//    tab(x);
//    for(int i=0;i<100;i++)
//    {
//        //将读取到的信息插入猪圈的表格
//        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(x[i].Sty_id)));
//        switch(x[i].flag)
//        {
//        case 0:{ui->tableWidget->setItem(i,1,new QTableWidgetItem("黑猪"));break;}
//        case 1:{ui->tableWidget->setItem(i,1,new QTableWidgetItem("小花猪和大白花猪"));break;}
//        }
//        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(x[i].PigNum)));
//        ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(x[i].income)));
//        //将读取到的信息插入猪的表格
//        //"猪圈编号"<<"猪的种类"<<"饲养天数"<<"体重"<<"体重增长：kg/d"
//        for(int j=0;j<10;j++)
//        {
//            ui->tableWidget_pig->setItem(j+i*10,0,new QTableWidgetItem(QString::number(i)));
//            switch(x[i].Pig[j].pig_name)
//            {
//            case -1:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("已卖出"));break;}
//            case 0:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("黑猪"));break;}
//            case 1:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("小花猪"));break;}
//            case 2:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("大白花猪"));break;}
//            }
//            ui->tableWidget_pig->setItem(j+i*10,2,new QTableWidgetItem(QString::number(x[i].Pig[j].day)));
//            ui->tableWidget_pig->setItem(j+i*10,3,new QTableWidgetItem(QString::number(x[i].Pig[j].weight)));
//            ui->tableWidget_pig->setItem(j+i*10,4,new QTableWidgetItem(QString::number(x[i].Pig[j].weight_unit)));
//        }
//    }

//不要
//    //试一下清空功能是怎么样的
//    connect(ui->btn_clear,&QPushButton::clicked,[=](){
//        ui->tableWidget->clearContents();
//    });
    //实验结果是：表头和横线都在，只是框中的内容不在了
    //引出问题：清空之后，怎么重新放内容进去呢？
    //int *sum;//卖出的猪的数量

//要
//    connect(ui->btn_sell,&QPushButton::clicked,[=]()
//    {
//        Sold_outPig(head);
//        PigSty *s1=head;

//不
//        PigSty p;
//        ofstream ofs1;
//        ofs1.open("D:\\Qtproject\\yangzhu\\pigsty.txt",ios::trunc|ios::out|ios::binary);
//        while(s1!=NULL){
//            ofs1.write((const char *)s1,sizeof(p));
//            s1=s1->next;
//        }
//        ofs1.close();

//yes
//        write(s1);
//    });
//    connect(ui->btn_buy,&QPushButton::clicked,[=]()
//    {
//        Buy_inPig(head);
//        PigSty *s1=head;
//        write(s1);
//    });
//    connect(ui->btn_new,&QPushButton::clicked,[=]()
//    {
//        //清空表格内容
//        ui->tableWidget->clearContents();
//        ui->tableWidget_pig->clearContents();

//        //重新把文件内容插入两个表格
//        PigSty y[100];
//        tab(y);
//        for(int i=0;i<100;i++)
//        {
//            //将读取到的信息插入猪圈的表格
//            ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(y[i].Sty_id)));
//            switch(y[i].flag)
//            {
//            case 0:{ui->tableWidget->setItem(i,1,new QTableWidgetItem("黑猪"));break;}
//            case 1:{ui->tableWidget->setItem(i,1,new QTableWidgetItem("小花猪和大白花猪"));break;}
//            }
//            ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(y[i].PigNum)));
//            ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(y[i].income)));
//            //将读取到的信息插入猪的表格
//            //"猪圈编号"<<"猪的种类"<<"饲养天数"<<"体重"<<"体重增长：kg/d"
//            for(int j=0;j<10;j++)
//            {
//                ui->tableWidget_pig->setItem(j+i*10,0,new QTableWidgetItem(QString::number(i)));
//                switch(y[i].Pig[j].pig_name)
//                {
//                case -1:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("已卖出"));break;}
//                case 0:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("黑猪"));break;}
//                case 1:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("小花猪"));break;}
//                case 2:{ui->tableWidget_pig->setItem(j+i*10,1,new QTableWidgetItem("大白花猪"));break;}
//                }
//                ui->tableWidget_pig->setItem(j+i*10,2,new QTableWidgetItem(QString::number(y[i].Pig[j].day)));
//                ui->tableWidget_pig->setItem(j+i*10,3,new QTableWidgetItem(QString::number(y[i].Pig[j].weight)));
//                ui->tableWidget_pig->setItem(j+i*10,4,new QTableWidgetItem(QString::number(y[i].Pig[j].weight_unit)));
//            }
//        }
//    });
//}

Dialog_1::~Dialog_1()
{
    delete ui;
}
