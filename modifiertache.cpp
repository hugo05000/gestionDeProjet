#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>

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

void MainWindow::on_pushButton_backFromModify_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
