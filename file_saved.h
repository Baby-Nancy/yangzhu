#ifndef FILE_SAVED_H
#define FILE_SAVED_H

#include <QWidget>

namespace Ui {
class File_Saved;
}

class File_Saved : public QWidget
{
    Q_OBJECT

public:
    explicit File_Saved(QWidget *parent = 0);
    ~File_Saved();

private:
    Ui::File_Saved *ui;
};

#endif // FILE_SAVED_H
