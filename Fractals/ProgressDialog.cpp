#include "ProgressDialog.h"

ProgressDialog::ProgressDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

ProgressDialog::~ProgressDialog()
{
}

void ProgressDialog::resetProgressBar()
{
	ui.myProgressBar->setValue(0);
}

void ProgressDialog::computationAdvances(int perc)
{
	ui.myProgressBar->setValue(perc);
	//repaint();
}

void ProgressDialog::computationAdvances2(int perc)
{
	ui.myProgressBar->setValue(perc);
	//repaint();
}