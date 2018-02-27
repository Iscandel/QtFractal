#include "MandelbrotConfigurationDialog.h"

#include "MandelJuliaRandomRendererDialog.h"
#include "MandelJuliaSineRendererDialog.h"

MandelbrotConfigurationDialog::MandelbrotConfigurationDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.myButtonOk, &QPushButton::clicked, this, &MandelbrotConfigurationDialog::onOk);
	connect(ui.myButtonCancel, &QPushButton::clicked, this, &MandelbrotConfigurationDialog::onCancel);
	connect(ui.myButtonConfigureRenderer, &QPushButton::clicked, this, &MandelbrotConfigurationDialog::onClickConfigureRenderer);
	//connect(ui.myComboRenderer,
	//	static_cast<void (QComboBox::*)(const QString&)>(&QComboBox::currentTextChanged),
	//	this,
	//	&MandelbrotConfigurationDialog::onRendererValueChanged);
}

MandelbrotConfigurationDialog::~MandelbrotConfigurationDialog()
{
}

void MandelbrotConfigurationDialog::setParameters(Parameters* params)
{
	myParams = params;
	ui.mySpinXMin->setValue(myParams->getDouble("xmin", -2.));
	ui.mySpinYMin->setValue(myParams->getDouble("ymin", -2.));
	ui.mySpinXMax->setValue(myParams->getDouble("xmax", 2.));
	ui.mySpinYMax->setValue(myParams->getDouble("ymax", 2.));
	ui.mySpinSizeX->setValue(myParams->getInt("sizeX", 800));
	ui.mySpinSizeY->setValue(myParams->getInt("sizeY", 800));
	ui.mySpinIterations->setValue(myParams->getInt("maxIter", 50));
	ui.myCheckBoxLogLog->setChecked(myParams->getBool("logLog", false));
	ui.myComboRenderer->setCurrentText(myParams->getString("renderer", "Random").c_str());
}

void MandelbrotConfigurationDialog::onOk()
{
	myParams->addDouble("xmin", ui.mySpinXMin->value());
	myParams->addDouble("ymin", ui.mySpinYMin->value());
	myParams->addDouble("xmax", ui.mySpinXMax->value());
	myParams->addDouble("ymax", ui.mySpinYMax->value());
	myParams->addInt("sizeX", ui.mySpinSizeX->value());
	myParams->addInt("sizeY", ui.mySpinSizeY->value());
	myParams->addInt("maxIter", ui.mySpinIterations->value());
	myParams->addBool("logLog", ui.myCheckBoxLogLog->isChecked());
	myParams->addString("renderer", ui.myComboRenderer->currentText().toStdString());

	hide();
}

void MandelbrotConfigurationDialog::onCancel()
{
	hide();
}

void MandelbrotConfigurationDialog::onRendererValueChanged(const std::string& value)
{
	//if(value == "Random")

}	

void MandelbrotConfigurationDialog::onClickConfigureRenderer()
{
	if (ui.myComboRenderer->currentText() == "Random")
	{
		MandelJuliaRandomRendererDialog dlg(this, myParams);
		dlg.setWindowModality(Qt::WindowModality::WindowModal);
		//dlg->setAttribute(Qt::WA_DeleteOnClose);
		dlg.exec();
	}
	else if (ui.myComboRenderer->currentText() == "Sine")
	{
		MandelJuliaSineRendererDialog dlg(this, myParams);
		dlg.setWindowModality(Qt::WindowModality::WindowModal);
		//dlg->setAttribute(Qt::WA_DeleteOnClose);
		dlg.exec();
		//else if (typeRepresentation =="Potentiel")
  //          	{
  //          		Color fractal=Color.red;
  //          		int rouge=0,vert=0,bleu=0;
  //          		
  //          		double r = (double) (Infos.InfSin.getAmplitudeR()*Math.sin(
  //          										Infos.InfSin.getPulsationR()*iterPrecise+ Infos.InfSin.getPhaseR()));
  //      			double g = (double) (Infos.InfSin.getAmplitudeG()*Math.sin(
  //      											Infos.InfSin.getPulsationG()*iterPrecise+ Infos.InfSin.getPhaseG()));
  //      			double bl =  (double)(Infos.InfSin.getAmplitudeB()*Math.sin(
  //      											Infos.InfSin.getPulsationB()*iterPrecise+ Infos.InfSin.getPhaseB()));
  //      			//System.out.println((int)(rouge*255.99));
  //      			rouge = (int)(r*255.99) > 255 ? 255:(int)(r*255.99) < 0 ? 0:(int)(r*255.99);
  //      			vert = (int)(g*255.99)> 255 ? 255:(int)(g*255.99)< 0 ? 0:(int)(g*255.99);
  //  				bleu = (int)(bl*255.99)> 255 ? 255:(int)(bl*255.99)< 0 ? 0:(int)(bl*255.99);
  //  				
  //  				fractal = new Color(rouge,vert,bleu);   //On crée la couleur
  //          		
  //          		argb = fractal.getRGB();
  //          		colorData = model.getDataElements(argb, null);
  //          		raster.setDataElements(i, j, colorData);
  //          	}
  //          	else if (typeRepresentation =="Rendu 3D")
  //          	{
  //          		Color fractal=Color.red;
  //          		int rouge=0,vert=0,bleu=0;
  //          		
  //          		double r = (double) (Infos.InfSin.getAmplitudeR()*Math.sin(
  //          										Infos.InfSin.getPulsationR()*mode3D+ Infos.InfSin.getPhaseR()));
  //      			double g = (double) (Infos.InfSin.getAmplitudeG()*Math.sin(
  //      											Infos.InfSin.getPulsationG()*mode3D+ Infos.InfSin.getPhaseG()));
  //      			double bl =  (double)(Infos.InfSin.getAmplitudeB()*Math.sin(
  //      											Infos.InfSin.getPulsationB()*mode3D+ Infos.InfSin.getPhaseB()));
  //      			//System.out.println((int)(rouge*255.99));
  //      			rouge = (int)(r*255.99) > 255 ? 255:(int)(r*255.99) < 0 ? 0:(int)(r*255.99);
  //      			vert = (int)(g*255.99)> 255 ? 255:(int)(g*255.99)< 0 ? 0:(int)(g*255.99);
  //  				bleu = (int)(bl*255.99)> 255 ? 255:(int)(bl*255.99)< 0 ? 0:(int)(bl*255.99);
  //  				
  //  				fractal = new Color(rouge,vert,bleu);   //On crée la couleur
  //          		
  //          		argb = fractal.getRGB();
  //          		colorData = model.getDataElements(argb, null);
  //          		raster.setDataElements(i, j, colorData);
  //          	}
	}
}