#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>

void MainWindow::on_pushButton_AddAjouterProjet_clicked()
{
    QSqlQuery maxIdProjet("SELECT IFNULL((SELECT MAX(idProjet)+1 FROM Projet),0)");
    maxIdProjet.first();
    QString idProjet = maxIdProjet.value(0).toString();

    QSqlQuery ajoutProjetRequest("INSERT INTO Projet VALUES("+idProjet+",'"
                                +ui->lineEdit_nomProjet->text().replace("'","\'").replace(";","")+"','"
                                +ui->lineEdit_descriptionProjet->text().replace("'","\'").replace(";","")+"','"
                                +ui->dateEdit_debutProjet->text()+"',')"
                                +ui->dateEdit_finProjet->text()+"')");

    if(ajoutProjetRequest.numRowsAffected() > 0){
        affichageProjet();
        ui->stackedWidget->setCurrentIndex(0);
    } else{
        qDebug()<<"Erreur lors de l'ajout du projet";
    }
}

void MainWindow::on_pushButton_backProjet_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
