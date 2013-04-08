#include "settingdialog.h"
#include "ui_settingdialog.h"
#include <QSettings>
#include <QFileDialog>
#include <QRadioButton>
#include "comm.h"

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);
    connect(ui->okBtn, SIGNAL(clicked()), this, SLOT(onOkButtonClick()));
    connect(ui->cancelBtn, SIGNAL(clicked()), this, SLOT(onCancelButtonClick()));
    connect(ui->resetBtn, SIGNAL(clicked()), this, SLOT(onResetButtonClick()));
    connect(ui->selectFileBtn, SIGNAL(clicked()), this, SLOT(onSelectFileBtnClick()));
    connect(ui->fromFileRBtn, SIGNAL(clicked()),this, SLOT(onFromFileRadioButtonClick()));
    connect(ui->autoGenerateRBtn, SIGNAL(clicked()),this, SLOT(onAutoGenRadioButtonClick()));

    QSettings settings(SETTING_ORGANIZATION, SETTING_APPLICATION);
    int groupNumber = settings.value(SETTING_GROUP_NUMBER_KEY, 0).toInt();
    int targetNumber = settings.value(SETTING_GROUP_TARGET_NUMBER_KEY, 0).toInt();
    int skyTargetNumber = settings.value(SETTING_SKY_TARGET_NUMBER_KEY, 0).toInt();
    int groundTargetNumber = settings.value(SETTING_GROUND_TARGET_NUMBER_KEY, 0).toInt();
    QString filePath = settings.value(SETTING_FILE_PATH_KEY, "").toString();

    ui->groupNumSpinBox->setValue(groupNumber);
    ui->targetNumSpinBox->setValue(targetNumber);
    ui->skyTargetNumSpinBox->setValue(skyTargetNumber);
    ui->groundTargetNumSpinBox->setValue(groundTargetNumber);
    ui->filePathEdit->setText(filePath);

    if (settings.value(SETTING_DATA_SOURCE_KEY, SETTING_DATA_SOURCE_AUTO_GENERATE) == SETTING_DATA_SOURCE_FROM_FILE) {
        ui->fromFileRBtn->setChecked(true);
        onFromFileRadioButtonClick();
    } else {
        ui->autoGenerateRBtn->setChecked(true);
        onAutoGenRadioButtonClick();
    }

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
    settings.setValue(SETTING_FILE_PATH_KEY, ui -> filePathEdit -> text());
    if (ui->fromFileRBtn->isChecked()) {
        settings.setValue(SETTING_DATA_SOURCE_KEY, SETTING_DATA_SOURCE_FROM_FILE);
    } else {
        // 默认自动生成数据
        settings.setValue(SETTING_DATA_SOURCE_KEY, SETTING_DATA_SOURCE_AUTO_GENERATE);
    }
    this->accept();
}
void SettingDialog::onResetButtonClick()
{
    ui->groundTargetNumSpinBox->setValue(0);
    ui->targetNumSpinBox->setValue(0);
    ui->skyTargetNumSpinBox->setValue(0);
    ui->groupNumSpinBox->setValue(0);
    ui->autoGenerateRBtn->setChecked(true);
    ui->filePathEdit->setText("");
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

void SettingDialog::onSelectFileBtnClick()
{
    QString file = QFileDialog::getOpenFileName(this, tr("选择目标信息文件"), tr("./"), "Data (*.*)");
    ui->filePathEdit->setText(file);
}

void SettingDialog::onFromFileRadioButtonClick()
{
    ui->fromFileGroupBox->setEnabled(true);
    ui->autoGenerateGroupBox->setEnabled(false);
}

void SettingDialog::onAutoGenRadioButtonClick()
{
    ui->fromFileGroupBox->setEnabled(false);
    ui->autoGenerateGroupBox->setEnabled(true);
}
