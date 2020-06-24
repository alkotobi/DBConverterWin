#include "mnbookshowform.h"
#include "ui_mnbookshowform.h"

MNBookShowForm::MNBookShowForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MNBookShowForm)
{
    ui->setupUi(this);
    MNShowBookWid *frm = new MNShowBookWid(this);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(frm);
    this->setLayout(layout);
}

MNBookShowForm::~MNBookShowForm()
{
    delete ui;
}
