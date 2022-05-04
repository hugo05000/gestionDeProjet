#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>

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
    void on_comboBox_listeProjets_currentIndexChanged(int index);

    void on_tableWidget_listeTache_cellClicked(int row, int column);

    void on_pushButton_nouvelleTache_clicked();

    void on_pushButton_backFromAdd_clicked();

    void on_pushButton_ajouterTache_clicked();

    void on_pushButton_ModificationTache_clicked();

    void on_pushButton_modifierTache_clicked();

    void on_pushButton_backFromModify_clicked();

    void on_pushButton_chronometre_clicked();

    void chronometre();

    void on_pushButton_pauseChronometre_clicked();

    void on_pushButton_monterTache_clicked();

    void on_pushButton_descendreTache_clicked();

    void on_pushButton_ajouterProjet_clicked();

    void on_pushButton_backProjet_clicked();

    void on_pushButton_AddAjouterProjet_clicked();

private:
    Ui::MainWindow *ui;

    void affichageTache();
    void affichageProjet();
    QString getMaxTache();

    QTimer *timer;
    QTime valeurChronometre;
    QString idTacheEnCours;
    int rowTacheEnCours;

};
#endif // MAINWINDOW_H
