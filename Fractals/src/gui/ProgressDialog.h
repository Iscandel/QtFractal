#pragma once

#include <QWidget>
//#include "FractalComputationListener.h"
#include "ui_ProgressDialog.h"

#include <memory>

class ProgressDialog : public QWidget//, public FractalComputationListener
{
	Q_OBJECT

//public:
//	using ptr = WithSmartPtr<Player>::ptr;
public:
	typedef std::shared_ptr<ProgressDialog> ptr;

public:
	ProgressDialog(QWidget *parent = Q_NULLPTR);
	~ProgressDialog();

	void resetProgressBar();

public slots:
	void computationAdvances(int perc);// override;

public:
	void computationAdvances2(int perc);// override;

private:
	Ui::ProgressDialog ui;
};
