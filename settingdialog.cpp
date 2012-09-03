#include "settingdialog.h"
#include "ui_settingdialog.h"
#include <QSettings>
#include "comm.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    connect(ui->okBtn, SIGNAL(clicked()), this, SLOT(onOkButtonClick()));
    connect(ui->cancelBtn, SIGNAL(clicked()), this, SLOT(onCancelButtonClick()));
    connect(ui->resetBtn, SIGNAL(clicked()), this, SLOT(onResetButtonClick()));

    QSettings settings(SETTING_ORGANIZATION, SETTING_APPLICATION);
    int groupNumber = settings.value(SETTING_GROUP_NUMBER_KEY, 0).toInt();
    int targetNumber = settings.value(SETTING_GROUP_TARGET_NUMBER_KEY, 0).toInt();
    int skyTargetNumber = settings.value(SETTING_SKY_TARGET_NUMBER_KEY, 0).toInt();
    int groundTargetNumber = settings.value(SETTING_GROUND_TARGET_NUMBER_KEY, 0).toInt();

    ui->groupNumSpinBox->setValue(groupNumber);
    ui->targetNumSpinBox->setValue(targetNumber);
    ui->skyTargetNumSpinBox->setValue(skyTargetNumber);
    ui->groundTargetNumSpinBox->setValue(groundTargetNumber);

    connect(ui -> groupNumSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onGroupNumberSpinValueChanged(int)));
    connect(ui -> skyTargetNumSpinBox, SIGNAL(valueChanged(int)), this, SLOT(onSkyGroupNumberSpinValueChanged(int)));
    connect(ui -> groundTargetNumSpinBox, SIGNAL(valueChanged(int))
            , this, SLOT(onGroundGroupNumberSpinValueChanged(int)));
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
    QSettings settings(SETTING_ORGANIZATION, SETTING_APPLICATION);
    settings.setValue(SETTING_GROUP_NUMBER_KEY, ui -> groupNumSpinBox -> value());
    settings.setValue(SETTING_GROUP_TARGET_NUMBER_KEY, ui -> targetNumSpinBox -> value());
    settings.setValue(SETTING_SKY_TARGET_NUMBER_KEY, ui -> skyTargetNumSpinBox -> value());
    settings.setValue(SETTING_GROUND_TARGET_NUMBER_KEY, ui -> groundTargetNumSpinBox -> value());
    this->accept();
}
void SettingDialog::onResetButtonClick()
{
    ui->groundTargetNumSpinBox->setValue(0);
    ui->targetNumSpinBox->setValue(0);
    ui->skyTargetNumSpinBox->setValue(0);
    ui->groupNumSpinBox->setValue(0);

}

void SettingDialog::onGroupNumberSpinValueChanged(int value)
{
    if (value < ui -> skyTargetNumSpinBox -> value() + ui -> groundTargetNumSpinBox -> value()){
        ui -> groupNumSpinBox -> setValue(ui -> skyTargetNumSpinBox -> value()
                                            + ui -> groundTargetNumSpinBox -> value());
    }
}

void SettingDialog::onSkyGroupNumberSpinValueChanged(int value)
{
    if (value > ui -> groupNumSpinBox -> value() - ui -> groundTargetNumSpinBox -> value()) {
        ui -> skyTargetNumSpinBox -> setValue(ui -> groupNumSpinBox -> value()
                                              - ui -> groundTargetNumSpinBox -> value());
    }
}

void SettingDialog::onGroundGroupNumberSpinValueChanged(int value)
{
    if (value > ui -> groupNumSpinBox -> value() - ui -> skyTargetNumSpinBox -> value()) {
        ui -> groundTargetNumSpinBox -> setValue(ui -> groupNumSpinBox -> value()
                                              - ui -> skyTargetNumSpinBox -> value());
    }
}
