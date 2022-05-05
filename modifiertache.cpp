#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>

/**
 * @brief MainWindow::on_pushButton_ModificationTache_clicked()
 * Modifie la tâche en base de données.
 */

void MainWindow::on_pushButton_ModificationTache_clicked()
{
    QSqlQuery modifierTacheRequest("UPDATE Tache SET libelleTache='"+ui->lineEdit_ModifierNomTache->text().replace("'","\'").replace(";","")+"',"
                                   +"duréeTache='"+ui->timeEdit_ModifierDureeTache->text()+"' "
                                   +"WHERE idTache="+ui->tableWidget_listeTache->item(ui->tableWidget_listeTache->currentRow(),0)->text());


    if(modifierTacheRequest.numRowsAffected() > 0){
        affichageTache();
        ui->stackedWidget->setCurrentIndex(0);
    } else{
        qDebug()<<"Erreur lors de la modification de la tâche";
    }
}

/**
 * @brief MainWindow::on_pushButton_backFromModify_clicked()
 * Change l'index du widget "stackedWidget" à "0" afin d'afficher la fenêtre principale.
 */

void MainWindow::on_pushButton_backFromModify_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
