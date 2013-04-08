#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QAbstractButton>

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
private:
    Ui::SettingDialog *ui;
};

#endif // SETTINGDIALOG_H
