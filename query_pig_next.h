#ifndef QUERY_PIG_NEXT_H
#define QUERY_PIG_NEXT_H

#include <QWidget>

namespace Ui {
class query_pig_next;
}

class query_pig_next : public QWidget
{
    Q_OBJECT

public:
    explicit query_pig_next(QWidget *parent = 0);
    ~query_pig_next();

private:
    Ui::query_pig_next *ui;
};

#endif // QUERY_PIG_NEXT_H
