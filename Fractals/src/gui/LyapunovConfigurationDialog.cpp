#include "LyapunovConfigurationDialog.h"

#include "LyapunovRandomRendererDialog.h"

LyapunovConfigurationDialog::LyapunovConfigurationDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.myButtonOk, &QPushButton::clicked, this, &LyapunovConfigurationDialog::onOk);
	connect(ui.myButtonCancel, &QPushButton::clicked, this, &LyapunovConfigurationDialog::onCancel);
	connect(ui.myButtonConfigureRenderer, &QPushButton::clicked, this, &LyapunovConfigurationDialog::onClickConfigureRenderer);
}

LyapunovConfigurationDialog::~LyapunovConfigurationDialog()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LyapunovConfigurationDialog::setParameters(Parameters* params)
{
	myParams = params;
	ui.mySpinXMin->setValue(myParams->getDouble("xmin", 0));
	ui.mySpinYMin->setValue(myParams->getDouble("ymin", 0));
	ui.mySpinXMax->setValue(myParams->getDouble("xmax", 4.));
	ui.mySpinYMax->setValue(myParams->getDouble("ymax", 4.));
	ui.mySpinSizeX->setValue(myParams->getInt("sizeX", 800));
	ui.mySpinSizeY->setValue(myParams->getInt("sizeY", 800));
	ui.mySpinIterations->setValue(myParams->getInt("maxIter", 50));
	ui.mySpinInitialValue->setValue(myParams->getDouble("initialValue", 0.5));
	ui.myEditSequence->setText(myParams->getString("sequence", "ab").c_str());
	ui.myComboRenderer->setCurrentText(myParams->getString("renderer", "Random").c_str());
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LyapunovConfigurationDialog::onOk()
{
	myParams->addDouble("xmin", ui.mySpinXMin->value());
	myParams->addDouble("ymin", ui.mySpinYMin->value());
	myParams->addDouble("xmax", ui.mySpinXMax->value());
	myParams->addDouble("ymax", ui.mySpinYMax->value());
	myParams->addInt("sizeX", ui.mySpinSizeX->value());
	myParams->addInt("sizeY", ui.mySpinSizeY->value());
	myParams->addInt("maxIter", ui.mySpinIterations->value());
	myParams->addDouble("initialValue", ui.mySpinInitialValue->value());
	myParams->addString("sequence", ui.myEditSequence->text().toStdString());
	myParams->addString("renderer", ui.myComboRenderer->currentText().toStdString());

	hide();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LyapunovConfigurationDialog::onCancel()
{
	hide();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LyapunovConfigurationDialog::onClickConfigureRenderer()
{
	if (ui.myComboRenderer->currentText() == "Random")
	{
		LyapunovRandomRendererDialog dlg(this, myParams);
		dlg.setWindowModality(Qt::WindowModality::WindowModal);
		//dlg->setAttribute(Qt::WA_DeleteOnClose);
		dlg.exec();
	}
}