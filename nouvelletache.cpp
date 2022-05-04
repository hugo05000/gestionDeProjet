#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>

void MainWindow::on_pushButton_ajouterTache_clicked()
{
    QSqlQuery maxIdTache("SELECT IFNULL((SELECT MAX(idTache)+1 FROM Tache),0)");
    maxIdTache.first();
    QString idtache = maxIdTache.value(0).toString();

    QSqlQuery ajoutTacheRequest("INSERT INTO Tache VALUES("+idtache+",'"
                                +ui->lineEdit_nomTache->text().replace("'","\'").replace(";","")+"','"
                                +ui->timeEdit_dureeTache->text()+":00',"
                                +ui->comboBox_listeProjets->currentData().toString()+","
                                +getMaxTache()+")");

    if(ajoutTacheRequest.numRowsAffected() > 0){
        affichageTache();
        ui->stackedWidget->setCurrentIndex(0);
    } else{
        qDebug()<<"Erreur lors de l'ajout de la tâche";
    }
}


void MainWindow::on_pushButton_backFromAdd_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


QString MainWindow::getMaxTache()
{
    if(ui->tableWidget_listeTache->rowCount()>0) {
        QSqlQuery maxTacheRequest("SELECT MAX(ordreTache)+1 FROM Tache "
                                  "WHERE idProjet="+ui->tableWidget_listeTache->item(0,3)->text());
        maxTacheRequest.first();

        QString maxTache = maxTacheRequest.value(0).toString();

        return maxTache;
    } else {
        return "1";
    }
}
