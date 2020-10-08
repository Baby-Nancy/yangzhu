#ifndef DIALOG_1_H
#define DIALOG_1_H

#include <QDialog>
#include <fstream>

//struct A_Pig{
//    int pig_name;//o-黑猪,1-小花猪，2-大花白猪
//    int day;
//    float weight;
//    float weight_unit;
//};

//struct PigSty{
//    int Sty_id;
//    int flag;//当前猪圈猪的种类，flag-0表示全是黑猪
//    int PigNum;//当前猪圈里猪的数量
//    A_Pig Pig[10];
//    float income;
//    PigSty *next;
//};

namespace Ui {
class Dialog_1;
}

class Dialog_1 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_1(QWidget *parent = 0);
    ~Dialog_1();
//    void tab();
//    void write(PigSty *s);

private:
    Ui::Dialog_1 *ui;
};

#endif // DIALOG_1_H
