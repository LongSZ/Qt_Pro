#include "combobox.h"
#include <QWheelEvent>
#include <QCompleter>
#include <iostream>
using namespace std;

ComboBox::ComboBox(QWidget *parent)
    : QComboBox(parent)
{
    connect(this, SIGNAL(editTextChanged(const QString &)), this, SLOT(slotEditTextChanged(const QString &)));
    this->setEditable(true);
    setInsertPolicy(InsertPolicy::NoInsert);
}

void ComboBox::wheelEvent(QWheelEvent *e)
{
    e->ignore();
}

//void ComboBox::keyPressEvent(QKeyEvent *e)
//{
//    switch(e->key()) {
//        case Qt::Key_Return:
//            cout << "return" << endl;
//            break;
//        case Qt::Key_Enter:
//            cout << "enter" << endl;
//            break;
//        default:
//            QComboBox::keyPressEvent(e);
//    }
//}

void ComboBox::slotEditTextChanged(const QString &txt)
{
    QStringList word_list;
    for (int i = 0; i < this->count(); i++) {
        QString txt = this->itemText(i);
        word_list << txt;
    }
    QCompleter *completer = new QCompleter(word_list, this);
    this->setCompleter(completer); 
    
    cout << "current index" << this->currentIndex() << endl;
}
