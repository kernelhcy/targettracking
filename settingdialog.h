#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QCheckBox>
#include <QVector>
#include <QString>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

public slots:
    void onResetButtonClick();
    void onOkButtonClick();
    void onCancelButtonClick();

    void onGroupNumberSpinValueChanged(int);
    void onSkyGroupNumberSpinValueChanged(int);
    void onGroundGroupNumberSpinValueChanged(int);

    void onSelectFileBtnClick();
    void onFromFileRadioButtonClick();
    void onAutoGenRadioButtonClick();

    void onLocalRadioButtonClick();
    void onRemoteRadioButtonClick();

    void kalmanFileterCheckboxStateChanged(int);
    void ekalmanFileterCheckboxStateChanged(int);
    void ukalmanFileterCheckboxStateChanged(int);
    void particalFileterCheckboxStateChanged(int);
private:
    Ui::SettingDialog *ui;
    QVector<QString> filters;
};

#endif // SETTINGDIALOG_H
