#include "MandelbrotConfigurationDialog.h"

#include "core/Types.h"

#include "MandelJuliaRandomRendererDialog.h"
#include "MandelJuliaRandomRenderer2Dialog.h"
#include "MandelJuliaSineRendererDialog.h"

#include "fractal/Mandelbrot.h"

#include <any>

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

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
MandelbrotConfigurationDialog::~MandelbrotConfigurationDialog()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void MandelbrotConfigurationDialog::setParameters(Parameters* params)
{
	myParams = params;

	Transform defaultTransform;
	defaultTransform.setScale((real)2., (real)2.);
	auto transform = myParams->getTransform("toWorld", defaultTransform);
	auto scale = transform.getScale();
	auto center = transform.getTranslation();

	//ie, defaultMin * scaleX + centerX -> -1 * scaleX + centerX
	//Or apply transform to min, but then it takes into account rotation
	ui.mySpinXMin->setValue(center.x() - scale.x());//myParams->getDouble("xmin", -2.));
	ui.mySpinYMin->setValue(center.y() - scale.y());//myParams->getDouble("ymin", -2.));
	ui.mySpinXMax->setValue(center.x() + scale.x());//myParams->getDouble("xmax", 2.));
	ui.mySpinYMax->setValue(center.y() + scale.y());//myParams->getDouble("ymax", 2.));
	ui.mySpinSizeX->setValue(myParams->getInt("sizeX", 800));
	ui.mySpinSizeY->setValue(myParams->getInt("sizeY", 800));
	ui.mySpinIterations->setValue(myParams->getInt("maxIter", 50));
	ui.myCheckBoxLogLog->setChecked(myParams->getBool("logLog", false));
	ui.myComboRenderer->setCurrentText(myParams->getString("renderer", "Random").c_str());
	ui.mySpinBailout->setValue(myParams->getDouble("bailout", 128));
	//
	ui.myCheckBoxLambertCorrection->setChecked(myParams->getBool("lambertCorrection", false));
	int val = std::log(myParams->getInt("computationType", 1)) / std::log(2);
	ui.myComboComputationType->setCurrentIndex(val);

	std::vector<std::any> vec = myParams->getVector("parsers", std::vector<std::any>());
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		MathParser parser = std::any_cast<MathParser>(vec[i]);
		if(parser.getId() == Mandelbrot::FUNCTION)
		{
			ui.myCheckBoxUseFunction->setChecked(true);
			ui.myEditFunction->setText(QString::fromStdString(parser.getExpr()));
		}

		if (parser.getId() == Mandelbrot::ADDEND_FUNCTION)
		{
			ui.myCheckBoxUseAddEnd->setChecked(true);
			ui.myEditAddEndFunction->setText(QString::fromStdString(parser.getExpr()));
		}

		if (parser.getId() == Mandelbrot::VALUE_RERANGE)
		{
			ui.myCheckBoxUseRerange->setChecked(true);
			ui.myEditRerangeFunction->setText(QString::fromStdString(parser.getExpr()));
		}

		if (parser.getId() == Mandelbrot::RERANGE_3D_HEIGHT)
		{
			ui.myCheckBoxUseRerangeHeight->setChecked(true);
			ui.myEditRerangeHeight->setText(QString::fromStdString(parser.getExpr()));
		}
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void MandelbrotConfigurationDialog::onOk()
{
	//
	//real scaleX = 2.;
	//real scaleY = 2.;
	//Transform transform;
	//Eigen::Vector2d scale(scaleX, scaleY);
	//Eigen::Rotation2D<real> rot;
	//Eigen::Vector2d translation(0, 0);
	//transform.fromPositionOrientationScale(translation, rot, scale);
	//myParams->addTransform("toWorld", transform);
	//

	Transform transform;
	transform.setScale(Point2r((ui.mySpinXMax->value() - ui.mySpinXMin->value()) / 2.,
		(ui.mySpinYMax->value() - ui.mySpinYMin->value()) / 2.));
	transform.setTranslation((ui.mySpinXMax->value() + ui.mySpinXMin->value()) / 2.,
		(ui.mySpinYMax->value() + ui.mySpinYMin->value()) / 2.);
	myParams->addTransform("toWorld", transform);

	

	//myParams->addDouble("xmin", ui.mySpinXMin->value());
	//myParams->addDouble("ymin", ui.mySpinYMin->value());
	//myParams->addDouble("xmax", ui.mySpinXMax->value());
	//myParams->addDouble("ymax", ui.mySpinYMax->value());
	myParams->addInt("sizeX", ui.mySpinSizeX->value());
	myParams->addInt("sizeY", ui.mySpinSizeY->value());
	myParams->addInt("maxIter", ui.mySpinIterations->value());
	myParams->addBool("logLog", ui.myCheckBoxLogLog->isChecked());
	myParams->addString("renderer", ui.myComboRenderer->currentText().toStdString());
	myParams->addDouble("bailout", ui.mySpinBailout->value());

	//
	myParams->addBool("lambertCorrection", ui.myCheckBoxLambertCorrection->isChecked());
	//std::cout << std::pow(2, ui.myComboComputationType->currentIndex()) << std::endl;
	myParams->addInt("computationType", std::pow(2, ui.myComboComputationType->currentIndex()));

	//
	std::vector<std::any> parsers;
	std::map<int, std::string> functionById;
	if (ui.myCheckBoxUseFunction->isChecked()) {
		std::string vars = "zn, zprev, zpprev, c";
		MathParser parser(ui.myEditFunction->text().toStdString(), vars);
		parser.setId((int)Mandelbrot::FUNCTION);
		parsers.push_back(parser);
	}
	//functionById[(int)Mandelbrot::FUNCTION] = ui.myEditFunction->text().toStdString();

	if (ui.myCheckBoxUseAddEnd->isChecked())
	{
		std::string vars = "zn, zprev, zpprev, c, sum";
		MathParser parser(ui.myEditAddEndFunction->text().toStdString(), vars);
		parser.setId((int)Mandelbrot::ADDEND_FUNCTION);
		parsers.push_back(parser);
	}
	//functionById[(int)Mandelbrot::ADDEND_FUNCTION] = ui.myEditAddEndFunction->text().toStdString();

	if (ui.myCheckBoxUseRerange->isChecked())
	{
		std::string vars = "value";
		MathParser parser(ui.myEditRerangeFunction->text().toStdString(), vars);
		parser.setId((int)Mandelbrot::VALUE_RERANGE);
		parsers.push_back(parser);
	}

	if (ui.myCheckBoxUseRerangeHeight->isChecked())
	{
		std::string vars = "value";
		MathParser parser(ui.myEditRerangeHeight->text().toStdString(), vars);
		parser.setId((int)Mandelbrot::RERANGE_3D_HEIGHT);
		parsers.push_back(parser);
	}
	myParams->addVector("parsers", parsers);
		//functionById[(int)Mandelbrot::VALUE_RERANGE] = ui.myEditRerangeFunction->text().toStdString();
		//myParams->addString("function", ui.myEditFunction->text().toStdString());

	hide();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void MandelbrotConfigurationDialog::onCancel()
{
	hide();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void MandelbrotConfigurationDialog::onRendererValueChanged(const std::string& value)
{
	//if(value == "Random")

}	

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void MandelbrotConfigurationDialog::onClickConfigureRenderer()
{
	if (ui.myComboRenderer->currentText() == "Random")
	{
		MandelJuliaRandomRendererDialog dlg(this, myParams);
		dlg.setWindowModality(Qt::WindowModality::WindowModal);
		//dlg->setAttribute(Qt::WA_DeleteOnClose);
		dlg.exec();
	}
	if (ui.myComboRenderer->currentText() == "Random 2")
	{
		MandelJuliaRandomRenderer2Dialog dlg(this, myParams);
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