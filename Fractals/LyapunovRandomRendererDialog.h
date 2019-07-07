#pragma once

#include <QDialog>
#include "ui_LyapunovRandomRendererDialog.h"

#include "Parameters.h"
#include "Rng.h"

class LyapunovRandomRendererDialog : public QDialog
{
	Q_OBJECT

public:
	LyapunovRandomRendererDialog(QWidget *parent, Parameters* params);
	~LyapunovRandomRendererDialog();

	void setParameters(Parameters* params);

protected:
	void onOk();
	void onCancel();
	void onRandom();
	void onAddColor();
	void onDeleteColor();
	void onMoveUp();
	void onMoveDown();

private:
	Ui::LyapunovRandomRendererDialog ui;

	Parameters* myParams;

	Rng myRng;
};
