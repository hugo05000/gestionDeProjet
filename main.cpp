#include "mainwindow.h"

#include <QApplication>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/hugomarceau/Documents/BTS_SIO/Deuxieme_annee/Developpement/gestionDeProjet/bdd.sqlite");
    db.open();

    QApplication a(argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
