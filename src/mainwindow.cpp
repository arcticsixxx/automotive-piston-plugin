#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QToolTip>
#include <QMessageBox>

#include "PistonParameters.h"
#include "PistonBuilder.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _pistonParameters = std::make_shared<PistonParameters>();
    _pistonBuilder = std::make_unique<PistonBuilder>();

    _setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buildPistonButton_clicked()
{
    // if все валидно
    _pistonBuilder->build();
}

void MainWindow::_setupConnections()
{
    connect(ui->pistonHeightLineEdit, &QLineEdit::textEdited, this,
    [this](const QString& text)
    {
        _pistonParameters->setValue(ParameterType::PistonHeight,
                                    ui->pistonHeightLineEdit->text().toDouble());
    });

    connect(ui->pistonHeadHeightLineEdit, &QLineEdit::textEdited, this,
    [this](const QString& text)
    {
        _pistonParameters->setValue(ParameterType::PistonHeadHeight,
                                    ui->pistonHeadHeightLineEdit->text().toDouble());
    });

    connect(ui->pistonDiameterLineEdit, &QLineEdit::textEdited, this,
    [this](const QString& text)
    {
        _pistonParameters->setValue(ParameterType::PistonBottomDiameter,
                                    ui->pistonDiameterLineEdit->text().toDouble());
    });

    connect(ui->diametePinHoleLineEdit, &QLineEdit::textEdited, this,
    [this](const QString& text)
    {
        _pistonParameters->setValue(ParameterType::PistonPinHoleDiameter,
                                    ui->diametePinHoleLineEdit->text().toDouble());
    });

    connect(ui->engineTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
    [this](int index)
    {
        switch (index)
        {
        case 0:
            _pistonParameters->setValue(ParameterType::RingsCount, 2);
            break;
        case 1:
            _pistonParameters->setValue(ParameterType::RingsCount, 3);
            break;
        }

        _pistonBuilder->setParameters(_pistonParameters);
    }
    );

    const QList<QLineEdit*> lineEdits = ui->centralwidget->findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits)
    {
        connect(lineEdit, &QLineEdit::textEdited, this,
        [this](const QString& text)
        {
            _pistonBuilder->setParameters(_pistonParameters);
        });
    }
}

