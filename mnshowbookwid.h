#ifndef MNSHOWBOOKWID_H
#define MNSHOWBOOKWID_H

#include <QWidget>
#include <QHBoxLayout>
#include "./imports/mndb.h"
#include "./imports/mnpathes.h"
#include "./databases/mnpage.h"
#include "./databases/mnbook.h"

namespace Ui {
class MNShowBookWid;
}

class MNShowBookWid : public QWidget
{
    Q_OBJECT

public:
    explicit MNShowBookWid(QWidget *parent = nullptr);
    ~MNShowBookWid();

private slots:
    void on_nextPageBtn_clicked();

private:
    Ui::MNShowBookWid *ui;
};

#endif // MNSHOWBOOKWID_H
