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

// Contatins color constants
struct UiColors
{
    // Light red error color
    const QString errorColor = "background-color: rgb(255, 102, 102);";
   
    // White noerror color
    const QString noErrorColor = "background-color: white;";
};

// Default Qt MainWindow class that provides GUI
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Default constructor 
    // @param parent: pointer to parent that will own object
    MainWindow(QWidget *parent = nullptr);

    // Default destructor 
    ~MainWindow();

private slots:
    // Provides handling of button press operations
    void on_buildPistonButton_clicked();

private:
    // Sets up all connections in GUI
    void _setupConnections();

    // Sets up tooltips connections
    // @param lineEdit: pointer to QLineEdit object
    // @param pType: ParameterType constant
    // @param toolTipStr: QString that hold tooltip string
    void _setupTooltip(QLineEdit* lineEdit, ParameterType pType, const QString& tooltipStr);
    
    // Sets up combobox tooltips
    void _setComboBoxTooltip();

    // Checks all fields for errors
    // @return: bool value that indicates existence of errors
    bool _isErrorFields() const;

    // Make connect for comboboxes
    void _connectComboBoxes();

    // Checks for dependent lineEdits values and change color of it
    // @param lineEdit: pointer to QLineEdit object
    // @param pType: ParameterType constant
    void _checkDependentField(QLineEdit* lineEdit, ParameterType pType);

private:
    // Pointer to internal Qt class
    Ui::MainWindow *ui;

    // Pointer to piston parameters
    std::shared_ptr<PistonParameters> _pistonParameters;
    
    // Pointer to piston builder
    std::unique_ptr<PistonBuilder> _pistonBuilder;

private:
    // UiColors structure object
    UiColors _uiColor;
};
