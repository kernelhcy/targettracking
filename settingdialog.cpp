#include "settingdialog.h"
#include "ui_settingdialog.h"
#include <QSettings>

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    connect(ui->okBtn, SIGNAL(clicked()), this, SLOT(onOkButtonClick()));
    connect(ui->cancelBtn, SIGNAL(clicked()), this, SLOT(onCancelButtonClick()));
    connect(ui->resetBtn, SIGNAL(clicked()), this, SLOT(onResetButtonClick()));

    QSettings settings("sslib", "targettracking");
    int groupNumber = settings.value("group number", 0).toInt();
    int targetNumber = settings.value("group target number", 0).toInt();
    int skyTargetNumber = settings.value("sky target number", 0).toInt();
    int groundTargetNumber = settings.value("ground target number", 0).toInt();

    ui->groupNumSpinBox->setValue(groupNumber);
    ui->targetNumSpinBox->setValue(targetNumber);
    ui->skyTargetNumSpinBox->setValue(skyTargetNumber);
    ui->groundTargetNumSpinBox->setValue(groundTargetNumber);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::onCancelButtonClick()
{
    this->reject();
}
void SettingDialog::onOkButtonClick()
{
    QSettings settings("sslib", "targettracking");
    settings.setValue("group number", ui -> groupNumSpinBox -> value());
    settings.setValue("group target number", ui -> targetNumSpinBox -> value());
    settings.setValue("sky target number", ui -> skyTargetNumSpinBox -> value());
    settings.setValue("ground target number", ui -> groundTargetNumSpinBox -> value());
    this->accept();
}
void SettingDialog::onResetButtonClick()
{
    ui->groundTargetNumSpinBox->setValue(0);
    ui->targetNumSpinBox->setValue(0);
    ui->skyTargetNumSpinBox->setValue(0);
    ui->groupNumSpinBox->setValue(0);

}
