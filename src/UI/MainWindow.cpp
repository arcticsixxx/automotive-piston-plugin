#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QToolTip>
#include <QMessageBox>

#include "Core/PistonParameters.h"
#include "Core/ParameterType.h"
#include "Core/PistonBuilder.h"
#include "Core/Validator.h"

#include <exception>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) 
{
    ui->setupUi(this);

    _pistonParameters = std::shared_ptr<PistonParameters>(new PistonParameters);
    _pistonBuilder = std::make_unique<PistonBuilder>(_pistonParameters);
    _pistonBuilder->setMaterial(MaterialType::CastIron);

    _setupConnections();
    _setComboBoxTooltip();

    _connectComboBoxes();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buildPistonButton_clicked()
{
    if (!_isErrorFields())
    {
        _pistonBuilder->build();
        return;
    }

    QMessageBox::warning(this, QString::fromLocal8Bit("Ошибка"), 
        QString::fromLocal8Bit("C заданными Вами параметрами невозможно построить объект.\nИсправьте заданные Вами значения параметров"));
}

void MainWindow::_setupConnections()
{
    connect(ui->pistonHeightLineEdit, &QLineEdit::textEdited, this,
    [this](const QString& text)
    {
        if (_pistonParameters->setValue(ParameterType::PistonHeight,
            ui->pistonHeightLineEdit->text().toDouble()))
        {
            ui->pistonHeightLineEdit->setStyleSheet(_uiColor.noErrorColor);
        }
        else
        {
            ui->pistonHeightLineEdit->setStyleSheet(_uiColor.errorColor);
        }

        _checkDependentField(ui->pistonHeadHeightLineEdit, ParameterType::PistonHeadHeight);

        _setupTooltip(ui->pistonHeightLineEdit, ParameterType::PistonHeight, 
            QString::fromLocal8Bit("Этот параметр содержит данные о высоте поршня."));
    });

    connect(ui->pistonHeadHeightLineEdit, &QLineEdit::textEdited, this,
    [this](const QString& text)
    {
        if (_pistonParameters->setValue(ParameterType::PistonHeadHeight,
            ui->pistonHeadHeightLineEdit->text().toDouble()))
        {
            ui->pistonHeadHeightLineEdit->setStyleSheet(_uiColor.noErrorColor);
        }
        else
        {
            ui->pistonHeadHeightLineEdit->setStyleSheet(_uiColor.errorColor);
        }

        _setupTooltip(ui->pistonHeadHeightLineEdit, ParameterType::PistonHeadHeight,
            QString::fromLocal8Bit("Этот параметр содержит данные о высоте головки поршня."));
    });

    connect(ui->pistonDiameterLineEdit, &QLineEdit::textEdited, this,
    [this](const QString& text)
    {
        if (_pistonParameters->setValue(ParameterType::PistonBottomDiameter,
            ui->pistonDiameterLineEdit->text().toDouble()))
        {
            ui->pistonDiameterLineEdit->setStyleSheet(_uiColor.noErrorColor);
        }
        else
        {
            ui->pistonDiameterLineEdit->setStyleSheet(_uiColor.errorColor);
        }
        
        _checkDependentField(ui->diametePinHoleLineEdit, ParameterType::PistonPinHoleDiameter);

        _setupTooltip(ui->pistonDiameterLineEdit, ParameterType::PistonBottomDiameter,
            QString::fromLocal8Bit("Этот параметр содержит данные о диаметре головки поршня."));
    });

    connect(ui->diametePinHoleLineEdit, &QLineEdit::textEdited, this,
    [this](const QString& text)
    {
        if (_pistonParameters->setValue(ParameterType::PistonPinHoleDiameter,
            ui->diametePinHoleLineEdit->text().toDouble()))
        {
            ui->diametePinHoleLineEdit->setStyleSheet(_uiColor.noErrorColor);
        }
        else
        {
            ui->diametePinHoleLineEdit->setStyleSheet(_uiColor.errorColor);
        }

        _setupTooltip(ui->diametePinHoleLineEdit, ParameterType::PistonPinHoleDiameter,
            QString::fromLocal8Bit("Этот параметр содержит данные об отверстии для порневого пальца."));
    });

    connect(ui->heightRingLineEdit, &QLineEdit::textEdited, this,
    [this](const QString& text)
    {
        if (_pistonParameters->setValue(ParameterType::RingHeight,
        ui->heightRingLineEdit->text().toDouble()))
        {
            ui->heightRingLineEdit->setStyleSheet(_uiColor.noErrorColor);
        }
        else
        {
            ui->heightRingLineEdit->setStyleSheet(_uiColor.errorColor);
        }

        _setupTooltip(ui->heightRingLineEdit, ParameterType::RingHeight,
            QString::fromLocal8Bit("Этот параметр содержит данные о высоте маслосъемного кольца."));
    });

    connect(ui->widthRingLineEdit, &QLineEdit::textEdited, this,
    [this](const QString& text)
    {
        if (_pistonParameters->setValue(ParameterType::RingWidth,
        ui->widthRingLineEdit->text().toDouble()))
        {
            ui->widthRingLineEdit->setStyleSheet(_uiColor.noErrorColor);
        }
        else
        {
            ui->widthRingLineEdit->setStyleSheet(_uiColor.errorColor);
        }

        _setupTooltip(ui->widthRingLineEdit, ParameterType::RingWidth,
            QString::fromLocal8Bit("Этот параметр содержит данные о ширине маслосъемного кольца."));
    });

    const QList<QLineEdit*> lineEdits = ui->centralwidget->findChildren<QLineEdit*>();
    for (const QLineEdit* lineEdit : lineEdits)
    {
        connect(lineEdit, &QLineEdit::textEdited, this,
        [this](const QString& text)
        {
            _pistonBuilder->setParameters(_pistonParameters);
        });
    }
}

void MainWindow::_setupTooltip(QLineEdit* lineEdit, ParameterType pType, const QString& tooltipStr)
{
    if (!lineEdit)
    {
        return;
    }

    QPoint point = QPoint(geometry().left() + lineEdit->geometry().left(),
        geometry().top() + lineEdit->geometry().bottom());

    const double minV = _pistonParameters->getParameter(pType).getMinValue();
    const double maxV = _pistonParameters->getParameter(pType).getMaxValue();

    QToolTip::showText(point, tooltipStr + QString::fromLocal8Bit("\nДопустимые значения : [%1, %2] ")
        .arg(minV).arg(maxV));
}

void MainWindow::_setComboBoxTooltip()
{
    ui->engineTypeComboBox->setItemData(0,
        QString::fromLocal8Bit("Бензиновый двигатель имеет два маслосъемных кольца"), Qt::ToolTipRole);

    ui->engineTypeComboBox->setItemData(1,
        QString::fromLocal8Bit("Дизельный двигатель имеет два маслосъемных кольца"), Qt::ToolTipRole);
}

bool MainWindow::_isErrorFields() const
{
    const QList<QLineEdit*> lineEdits = ui->centralwidget->findChildren<QLineEdit*>();
    for (const QLineEdit* lineEdit : lineEdits)
    {
        if (lineEdit->styleSheet() == _uiColor.errorColor)
        {
            return true;
        }
    }
    
    return false;
}

void MainWindow::_connectComboBoxes()
{
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
        default:
            break;
        }

        _pistonBuilder->setParameters(_pistonParameters);
    });

    connect(ui->materialComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
    [this](int index)
    {
        switch (index)
        {
        case 0:
            _pistonBuilder->setMaterial(MaterialType::CastIron);
            break;
        case 1:
            _pistonBuilder->setMaterial(MaterialType::Aluminum);
            break;
        default:
            break;
        }
    });
}

void MainWindow::_checkDependentField(QLineEdit* lineEdit, ParameterType pType)
{
    if (!lineEdit)
    {
        return;
    }

    const Parameter param = _pistonParameters->getParameter(pType);
    
    if (!Validator::ValidateParameter(lineEdit->text().toDouble(), param.getMinValue(), param.getMaxValue()))
    {
        lineEdit->setStyleSheet(_uiColor.errorColor);
    }
    else
    {
        lineEdit->setStyleSheet(_uiColor.noErrorColor);
    }
}

