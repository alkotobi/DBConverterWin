#ifndef MNBOOKSHOWFORM_H
#define MNBOOKSHOWFORM_H

#include <QMainWindow>
#include <QHBoxLayout>
#include "mnshowbookwid.h"
namespace Ui {
class MNBookShowForm;
}

class MNBookShowForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit MNBookShowForm(QWidget *parent = nullptr);
    ~MNBookShowForm();

private:
    Ui::MNBookShowForm *ui;
};

#endif // MNBOOKSHOWFORM_H
