#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

class PistonParameters;
class PistonBuilder;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buildPistonButton_clicked();

private:
    void _setupConnections();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<PistonParameters> _pistonParameters;
    std::unique_ptr<PistonBuilder> _pistonBuilder;
};
#endif // MAINWINDOW_H
