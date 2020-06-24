#include "mnshowbookwid.h"
#include "ui_mnshowbookwid.h"

MNShowBookWid::MNShowBookWid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MNShowBookWid)
{
    ui->setupUi(this);
    //this solve the right to left problem
    ui->textView->document()->setDefaultTextOption(QTextOption(Qt::AlignRight));

}

MNShowBookWid::~MNShowBookWid()
{
    delete ui;


}

void MNShowBookWid::on_nextPageBtn_clicked()
{
    int bkId=21710;
    QString bkPath=MNPathes::getDbBookPath(bkId);

    int currPageNo =ui->pageNoEdit->value();
    int currTomeNo =ui->tomNoEdit->value();
    ui->pageNoEdit->setValue(currPageNo+1);
    MNDb::openSqliteDb(bkPath);
    MNPage page(bkId);
    MNPage::PageInfo pgInfo;
    page.getPage(currPageNo+1,currTomeNo,&pgInfo);
    if(pgInfo.ID){
        MNBook book(bkId);
        QStringList wordsList;
        book.getWordsList(pgInfo.startFrom,pgInfo.wordsCount,&wordsList);
        if(wordsList.count()!=0){
            QString text=wordsList.join("");
            ui->textView->setPlainText(text);
        }else{
            //TODO: handle exception where we dont get a words list
        }
    }else{
        //TODO: handle exception if we dont get a page info
    }




}
