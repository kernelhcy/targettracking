#include "settingdialog.h"
#include "ui_settingdialog.h"
#include <QSettings>
#include <QFileDialog>
#include <QRadioButton>
#include <QMessageBox>
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

    connect(ui -> kalmanCB, SIGNAL(stateChanged(int)), this, SLOT(kalmanFileterCheckboxStateChanged(int)));
    connect(ui -> ekalmanCB, SIGNAL(stateChanged(int)), this, SLOT(ekalmanFileterCheckboxStateChanged(int)));
    connect(ui -> ukalmanCB, SIGNAL(stateChanged(int)), this, SLOT(ukalmanFileterCheckboxStateChanged(int)));
    connect(ui -> particalCB, SIGNAL(stateChanged(int)), this, SLOT(particalFileterCheckboxStateChanged(int)));

    QSettings settings(SETTING_ORGANIZATION, SETTING_APPLICATION);
    int groupNumber = settings.value(SETTING_GROUP_NUMBER_KEY, 0).toInt();
    int targetNumber = settings.value(SETTING_GROUP_TARGET_NUMBER_KEY, 0).toInt();
    int skyTargetNumber = settings.value(SETTING_SKY_TARGET_NUMBER_KEY, 0).toInt();
    int groundTargetNumber = settings.value(SETTING_GROUND_TARGET_NUMBER_KEY, 0).toInt();
    QString filePath = settings.value(SETTING_FILE_PATH_KEY, "").toString();

    ui -> kalmanCB -> setChecked(settings.value(SETTING_KALMAN_FILTER_KEY, true).toBool());
    ui -> ekalmanCB -> setChecked(settings.value(SETTING_EKALMAN_FILTER_KEY, false).toBool());
    ui -> ukalmanCB -> setChecked(settings.value(SETTING_UKALMAN_FILTER_KEY, false).toBool());
    ui -> particalCB -> setChecked(settings.value(SETTING_PARTICAL_FILTER_KEY, false).toBool());

    if (ui -> kalmanCB -> isChecked()) filters.append(SETTING_KALMAN_FILTER_KEY);
    if (ui -> ekalmanCB -> isChecked()) filters.append(SETTING_EKALMAN_FILTER_KEY);
    if (ui -> ukalmanCB -> isChecked()) filters.append(SETTING_UKALMAN_FILTER_KEY);
    if (ui -> particalCB -> isChecked()) filters.append(SETTING_PARTICAL_FILTER_KEY);

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
    if (filters.size() <= 0) {
        QMessageBox::critical(this, tr("参数有误"), tr("请至少选择一个滤波算法！"));
        return;
    }

    QSettings settings(SETTING_ORGANIZATION, SETTING_APPLICATION);
    settings.setValue(SETTING_GROUP_NUMBER_KEY, ui -> groupNumSpinBox -> value());
    settings.setValue(SETTING_GROUP_TARGET_NUMBER_KEY, ui -> targetNumSpinBox -> value());
    settings.setValue(SETTING_SKY_TARGET_NUMBER_KEY, ui -> skyTargetNumSpinBox -> value());
    settings.setValue(SETTING_GROUND_TARGET_NUMBER_KEY, ui -> groundTargetNumSpinBox -> value());
    settings.setValue(SETTING_FILE_PATH_KEY, ui -> filePathEdit -> text());

    settings.setValue(SETTING_KALMAN_FILTER_KEY, ui -> kalmanCB -> isChecked());
    settings.setValue(SETTING_EKALMAN_FILTER_KEY, ui -> ekalmanCB -> isChecked());
    settings.setValue(SETTING_UKALMAN_FILTER_KEY, ui -> ukalmanCB -> isChecked());
    settings.setValue(SETTING_PARTICAL_FILTER_KEY, ui -> particalCB -> isChecked());

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
    ui->kalmanCB->setChecked(true);
    ui->ekalmanCB->setChecked(false);
    ui->ukalmanCB->setChecked(false);
    ui->particalCB->setChecked(false);
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

void SettingDialog::kalmanFileterCheckboxStateChanged(int state)
{
    if (state == Qt::Checked) {
        filters.append(SETTING_KALMAN_FILTER_KEY);
    } else if (state == Qt::Unchecked) {
        int idx = filters.indexOf(SETTING_KALMAN_FILTER_KEY);
        if (idx >= 0) {
            filters.remove(idx);
        }
    }
}

void SettingDialog::ekalmanFileterCheckboxStateChanged(int state)
{
    if (state == Qt::Checked) {
        filters.append(SETTING_EKALMAN_FILTER_KEY);
    } else if (state == Qt::Unchecked) {
        int idx = filters.indexOf(SETTING_EKALMAN_FILTER_KEY);
        if (idx >= 0) {
            filters.remove(idx);
        }
    }
}

void SettingDialog::ukalmanFileterCheckboxStateChanged(int state)
{
    if (state == Qt::Checked) {
        filters.append(SETTING_UKALMAN_FILTER_KEY);
    } else if (state == Qt::Unchecked) {
        int idx = filters.indexOf(SETTING_UKALMAN_FILTER_KEY);
        if (idx >= 0) {
            filters.remove(idx);
        }
    }
}

void SettingDialog::particalFileterCheckboxStateChanged(int state)
{
    if (state == Qt::Checked) {
        filters.append(SETTING_PARTICAL_FILTER_KEY);
    } else if (state == Qt::Unchecked) {
        int idx = filters.indexOf(SETTING_PARTICAL_FILTER_KEY);
        if (idx >= 0) {
            filters.remove(idx);
        }
    }
}
