#ifndef CLINEEDIT_H
#define CLINEEDIT_H

#include <QLineEdit>

class CLineEdit : public QLineEdit
{
public:
   /* CLineEdit();*/
	CLineEdit(QWidget* parent = nullptr) : QLineEdit(parent) {};
protected:
	void keyPressEvent(QKeyEvent* event) override;
};

#endif // CLINEEDIT_H
