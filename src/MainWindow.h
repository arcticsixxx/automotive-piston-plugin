#pragma once 

#include <QMainWindow>

#include <memory>

class PistonParameters;
class PistonBuilder;
class QLineEdit;

enum ParameterType;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct UiColors
{
    const QString errorColor = "background-color: rgb(255, 102, 102);";
    const QString noErrorColor = "background-color: white;";
};

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

    void _setupTooltip(QLineEdit* lineEdit, ParameterType pType, const QString& tooltipStr);
    void _setComboBoxTooltip();

    bool _isErrorFields() const;

    void _connectComboBoxes();

    void _checkDependentField(QLineEdit* lineEdit, ParameterType pType);

private:
    Ui::MainWindow *ui;

    std::shared_ptr<PistonParameters> _pistonParameters;
    std::unique_ptr<PistonBuilder> _pistonBuilder;

private:
    UiColors _uiColor;
};
