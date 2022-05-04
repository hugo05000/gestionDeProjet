#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->statusbar->setVisible(0);
    ui->label_dateDebutPrevu->setVisible(0);
    ui->label_dateFinPrevu->setVisible(0);

    affichageProjet();
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_comboBox_listeProjets_currentIndexChanged(int index)
{
    affichageTache();
}


void MainWindow::on_tableWidget_listeTache_cellClicked(int row, int column)
{
    ui->pushButton_modifierTache->setEnabled(1);
    ui->pushButton_chronometre->setEnabled(1);

    QSqlQuery chronometreRequest("SELECT duréeTache FROM Tache WHERE idTache="+ui->tableWidget_listeTache->item(row,0)->text());
    chronometreRequest.first();

    valeurChronometre = chronometreRequest.value(0).toTime();
}


void MainWindow::on_pushButton_ajouterProjet_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButton_nouvelleTache_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_modifierTache_clicked()
{
    ui->lineEdit_ModifierNomTache->setText(ui->tableWidget_listeTache->item(ui->tableWidget_listeTache->currentRow(),1)->text());
    ui->timeEdit_ModifierDureeTache->setTime(QTime::fromString(ui->tableWidget_listeTache->item(ui->tableWidget_listeTache->currentRow(),2)->text()));
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::affichageTache()
{
    ui->pushButton_modifierTache->setEnabled(0);
    ui->pushButton_chronometre->setEnabled(0);
    ui->pushButton_pauseChronometre->setEnabled(0);

    QString idTache = ui->comboBox_listeProjets->currentData().toString();

    QSqlQuery datePrevuRequest("SELECT dateDebutProjet,dateFinProjet FROM Projet WHERE idProjet="+idTache);

    datePrevuRequest.first();

    ui->label_dateDebutPrevu->setText(datePrevuRequest.value(0).toString());
    ui->label_dateFinPrevu->setText(datePrevuRequest.value(1).toString());
    ui->label_dateDebutPrevu->setVisible(1);
    ui->label_dateFinPrevu->setVisible(1);

    QStringList tableLabels;
    tableLabels << "id" << "Libellé" << "Durée" << "Id projet" << "Ordre tâche";
    ui->tableWidget_listeTache->clear();
    ui->tableWidget_listeTache->setHorizontalHeaderLabels(tableLabels);
    ui->tableWidget_listeTache->setRowCount(0);
    ui->tableWidget_listeTache->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_listeTache->setColumnHidden(0,true);
    ui->tableWidget_listeTache->setColumnHidden(3,true);
    ui->tableWidget_listeTache->setColumnHidden(4,true);

    QSqlQuery listeTacheRequest("SELECT * FROM Tache WHERE idProjet="+idTache+" ORDER BY ordreTache;");

    listeTacheRequest.exec();

    int cptListeTache=0;

    while(listeTacheRequest.next())
    {
        ui->tableWidget_listeTache->insertRow(cptListeTache);
        ui->tableWidget_listeTache->setItem(cptListeTache,0,new QTableWidgetItem(listeTacheRequest.value("idTache").toString()));
        ui->tableWidget_listeTache->setItem(cptListeTache,1,new QTableWidgetItem(listeTacheRequest.value("libelleTache").toString()));
        ui->tableWidget_listeTache->setItem(cptListeTache,2,new QTableWidgetItem(listeTacheRequest.value("duréeTache").toString()));
        ui->tableWidget_listeTache->setItem(cptListeTache,3,new QTableWidgetItem(listeTacheRequest.value("idProjet").toString()));
        ui->tableWidget_listeTache->setItem(cptListeTache,4,new QTableWidgetItem(listeTacheRequest.value("ordreTache").toString()));
        cptListeTache++;
    }
}

void MainWindow::affichageProjet()
{
    ui->comboBox_listeProjets->clear();

    QSqlQuery listeProjetRequest("SELECT * FROM Projet");

    listeProjetRequest.exec();

    while(listeProjetRequest.next())
    {
        ui->comboBox_listeProjets->addItem(listeProjetRequest.value("titreProjet").toString(),
                                      listeProjetRequest.value("idProjet").toInt());
    }
}

void MainWindow::on_pushButton_chronometre_clicked()
{
    ui->pushButton_chronometre->setEnabled(0);
    ui->pushButton_pauseChronometre->setEnabled(1);

    idTacheEnCours = ui->tableWidget_listeTache->item(ui->tableWidget_listeTache->currentRow(),0)->text();
    rowTacheEnCours = ui->tableWidget_listeTache->currentRow();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(chronometre()));
    timer->start(1000);
}

void MainWindow::chronometre()
{
    valeurChronometre = valeurChronometre.addSecs(-1);
    ui->tableWidget_listeTache->setItem(rowTacheEnCours,2,new QTableWidgetItem(valeurChronometre.toString()));

    QSqlQuery updateChronometreRequest("UPDATE Tache SET duréeTache='"+valeurChronometre.toString()+"' WHERE idTache="+idTacheEnCours);

    if(valeurChronometre==QTime::fromString("00:00:00"))
    {
        timer->stop();
    }
}


void MainWindow::on_pushButton_pauseChronometre_clicked()
{
    ui->pushButton_pauseChronometre->setEnabled(0);
    ui->pushButton_chronometre->setEnabled(1);

    timer->stop();
}


void MainWindow::on_pushButton_monterTache_clicked()
{
    if(ui->tableWidget_listeTache->item(ui->tableWidget_listeTache->currentRow(),4)->text() != "1")
    {
        QSqlQuery diminutionOrdreRequest("UPDATE Tache SET ordreTache=ordreTache-1 "
                                         "WHERE idTache="+ui->tableWidget_listeTache->item(ui->tableWidget_listeTache->currentRow(),0)->text());

        QSqlQuery augmentationOrdreRequest("UPDATE Tache SET ordreTache=ordreTache+1 "
                                           "WHERE idTache="+ui->tableWidget_listeTache->item(ui->tableWidget_listeTache->currentRow()-1,0)->text());

        affichageTache();
    }
}


void MainWindow::on_pushButton_descendreTache_clicked()
{
    if(ui->tableWidget_listeTache->item(ui->tableWidget_listeTache->currentRow(),4)->text().toInt() != ui->tableWidget_listeTache->rowCount())
    {
        QSqlQuery augmentationOrdreRequest("UPDATE Tache SET ordreTache=ordreTache+1 "
                                           "WHERE idTache="+ui->tableWidget_listeTache->item(ui->tableWidget_listeTache->currentRow(),0)->text());

        QSqlQuery diminutionOrdreRequest("UPDATE Tache SET ordreTache=ordreTache-1 "
                                         "WHERE idTache="+ui->tableWidget_listeTache->item(ui->tableWidget_listeTache->currentRow()+1,0)->text());

        affichageTache();
    }
}

