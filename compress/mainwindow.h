#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    short threadCount;
private slots:

    void on_compress_clicked();

    void on_extract_clicked();

    void on_browse_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
