#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>

class ComboBox : public QComboBox
{
    Q_OBJECT
public:
    ComboBox(QWidget *parent = nullptr);

protected:
    void wheelEvent(QWheelEvent *e) override;
    //void keyPressEvent(QKeyEvent* e) override;               //阻止回车添加条目
    
private slots:
    void slotEditTextChanged(const QString &txt);
};

#endif // COMBOBOX_H
