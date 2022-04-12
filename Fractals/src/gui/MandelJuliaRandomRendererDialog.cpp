#include "MandelJuliaRandomRendererDialog.h"

#include "tools/SignalBlocker.h"

//#include <boost/any.hpp>

MandelJuliaRandomRendererDialog::MandelJuliaRandomRendererDialog(QWidget *parent, Parameters* params)
	: QDialog(parent)
	,myParams(params)
{
	myColors.resize(6);

	ui.setupUi(this);

	connect(ui.myButtonOk, &QPushButton::clicked, this, &MandelJuliaRandomRendererDialog::onOk);
	connect(ui.myButtonCancel, &QPushButton::clicked, this, &MandelJuliaRandomRendererDialog::onCancel);
	connect(ui.myScrollBarRed,
		static_cast<void (QScrollBar::*)(int)>(&QScrollBar::valueChanged),
		this,
		&MandelJuliaRandomRendererDialog::onValueScrollbarsChanged);
	connect(ui.myScrollBarGreen,
		static_cast<void (QScrollBar::*)(int)>(&QScrollBar::valueChanged),
		this,
		&MandelJuliaRandomRendererDialog::onValueScrollbarsChanged);
	connect(ui.myScrollBarBlue,
		static_cast<void (QScrollBar::*)(int)>(&QScrollBar::valueChanged),
		this,
		&MandelJuliaRandomRendererDialog::onValueScrollbarsChanged);

	connect(ui.myRadioColor1,
		&QRadioButton::toggled,
		this,
		&MandelJuliaRandomRendererDialog::onRadioChanged);

	connect(ui.myRadioColor2,
			&QRadioButton::toggled,
			this,
			&MandelJuliaRandomRendererDialog::onRadioChanged);
	connect(ui.myRadioColor3,
			&QRadioButton::toggled,
			this,
			&MandelJuliaRandomRendererDialog::onRadioChanged);
	connect(ui.myRadioColor4,
			&QRadioButton::toggled,
			this,
			&MandelJuliaRandomRendererDialog::onRadioChanged);
	connect(ui.myRadioColor5,
			&QRadioButton::toggled,
			this,
			&MandelJuliaRandomRendererDialog::onRadioChanged);
	connect(ui.myRadioFractalColor6,
			&QRadioButton::toggled,
			this,
			&MandelJuliaRandomRendererDialog::onRadioChanged);

	connect(ui.myButtonPredefined, &QPushButton::clicked, this, &MandelJuliaRandomRendererDialog::onPredefined);
	connect(ui.myButtonRandom, &QPushButton::clicked, this, &MandelJuliaRandomRendererDialog::onRandom);

	ui.myRadioColor1->setChecked(true);
	//Tirer aléatoirement

	setParameters(params);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
MandelJuliaRandomRendererDialog::~MandelJuliaRandomRendererDialog()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void MandelJuliaRandomRendererDialog::setParameters(Parameters* params)
{
	std::vector<std::any> vec = myParams->getVector("iterationColors", std::vector<std::any>());
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		myColors[i] = std::any_cast<Color>(vec[i]);
	}

	myColors[myColors.size() - 1] = myParams->getColor("fractalColor", Color());


}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void MandelJuliaRandomRendererDialog::onValueScrollbarsChanged(int value)
{
	//QObject* obj = sender();

	//if(obj == ui.my)

	setPreviewColor(ui.myScrollBarRed->value(), ui.myScrollBarGreen->value(), ui.myScrollBarBlue->value());

	int selectedRadio = getIndexSelectedRadio();

	myColors[selectedRadio].r = ui.myScrollBarRed->value() / 255.;
	myColors[selectedRadio].g = ui.myScrollBarGreen->value() / 255.;
	myColors[selectedRadio].b = ui.myScrollBarBlue->value() / 255.;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void MandelJuliaRandomRendererDialog::onOk()
{
	std::vector<std::any> myColorVector;
	myColorVector.resize(myColors.size() - 1); //subtract fractal color (last element)
	for (unsigned int i = 0; i < myColors.size() - 1; i++)
		myColorVector[i] = myColors[i];

	myParams->addVector("iterationColors", myColorVector);
	myParams->addColor("fractalColor", myColors[5]);

	hide();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void MandelJuliaRandomRendererDialog::onCancel()
{
	hide();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void MandelJuliaRandomRendererDialog::onRadioChanged(int checked)
{
	updateGUI();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void MandelJuliaRandomRendererDialog::setPreviewColor(int r, int g, int b)
{
	int alpha = 255;
	QString values = QString::number(r) + "," +
		QString::number(g) + "," +
		QString::number(b) + "," +
		QString::number(alpha);
	//std::cout << values.toStdString() << std::endl;
	ui.myLabelColorPreview->setStyleSheet("QLabel { background-color: rgba(" + values + "); }");
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
int MandelJuliaRandomRendererDialog::getIndexSelectedRadio()
{
	if (ui.myRadioColor1->isChecked())
		return 0;
	else if (ui.myRadioColor2->isChecked())
		return 1;
	else if (ui.myRadioColor3->isChecked())
		return 2;
	else if (ui.myRadioColor4->isChecked())
		return 3;
	else if (ui.myRadioColor5->isChecked())
		return 4;
	else if (ui.myRadioFractalColor6->isChecked())
		return 5;
	else
		return -1;
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void MandelJuliaRandomRendererDialog::onPredefined()
{
	myColors[0] = Color(1., 0., 0.);
	myColors[1] = Color(1., 0.5, 0.);
	myColors[2] = Color(1., 1., 0.);
	myColors[3] = Color(0., 1., 0.);
	myColors[4] = Color(0., 0., 1.);

	updateGUI();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void MandelJuliaRandomRendererDialog::onRandom()
{
	for(int i = 0; i < 6; i++)
		myColors[i] = Color(myRng.nextDouble(), myRng.nextDouble(), myRng.nextDouble());

	updateGUI();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void MandelJuliaRandomRendererDialog::updateGUI()
{
	int selectedRadio = getIndexSelectedRadio();

	//Don't fire signals
	whileBlocking(ui.myScrollBarRed)->setValue(myColors[selectedRadio].r * 255);
	whileBlocking(ui.myScrollBarGreen)->setValue(myColors[selectedRadio].g * 255);
	whileBlocking(ui.myScrollBarBlue)->setValue(myColors[selectedRadio].b * 255);

	setPreviewColor(ui.myScrollBarRed->value(), ui.myScrollBarGreen->value(), ui.myScrollBarBlue->value());
}