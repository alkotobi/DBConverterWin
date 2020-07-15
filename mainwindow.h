#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"
#include "QString"
#include <QDialog>
#include <QFileDialog>
#include "./databases/mnbooklist.h"
#include "./imports/mnpathes.h"
#include "./databases/mnauthor.h"
#include "./databases/mnmidtableslink.h"
#include "./databases/mncat.h"
#include "./databases/mnwords.h"
#include "mnnass.h"
#include "./databases/mnbook.h"
#include "./databases/mnpage.h"
#include "./databases/mntachkil.h"
#include "./databases/mnsearchbook.h"
#include "./databases/mnindex.h"
#include "mnbookshowform.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_testConvert_clicked();

    void on_bkImport_clicked();

    void on_importCats_clicked();

    void on_testNass_clicked();

    void on_bookView_clicked();

    void on_btnShamelahPath_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
