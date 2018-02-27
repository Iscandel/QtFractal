#include "MandelJuliaSineRendererDialog.h"

MandelJuliaSineRendererDialog::MandelJuliaSineRendererDialog(QWidget *parent, Parameters* params)
	: QDialog(parent)
	, myParams(params)
{
	ui.setupUi(this);

	connect(ui.myButtonOk, &QPushButton::clicked, this, &MandelJuliaSineRendererDialog::onOk);
	connect(ui.myButtonCancel, &QPushButton::clicked, this, &MandelJuliaSineRendererDialog::onCancel);

	setParameters(params);
}

MandelJuliaSineRendererDialog::~MandelJuliaSineRendererDialog()
{
}

void MandelJuliaSineRendererDialog::setParameters(Parameters* params)
{
	myParams = params;

	std::vector<boost::any> amplitudes{ 0.2, 0.3, 0.4 };

	initGUIElementVector(ui.mySpinAmplitudeR, "amplitudes", amplitudes, 0);
	initGUIElementVector(ui.mySpinAmplitudeG, "amplitudes", amplitudes, 1);
	initGUIElementVector(ui.mySpinAmplitudeB, "amplitudes", amplitudes, 2);

	std::vector<boost::any> pulsations{ 0.2, 0.3, 0.4 };

	initGUIElementVector(ui.mySpinPulsationR, "pulsations", pulsations, 0);
	initGUIElementVector(ui.mySpinPulsationG, "pulsations", pulsations, 1);
	initGUIElementVector(ui.mySpinPulsationB, "pulsations", pulsations, 2);

	std::vector<boost::any> phases{ 0.2, 0.3, 0.4 };
	initGUIElementVector(ui.mySpinPhaseR, "phases", phases, 0);
	initGUIElementVector(ui.mySpinPhaseG, "phases", phases, 1);
	initGUIElementVector(ui.mySpinPhaseB, "phases", phases, 2);

	Color fractalColor = myParams->getColor("fractalColor", Color());
	ui.myScrollBarRed->setValue(fractalColor.r * 255);
	ui.myScrollBarGreen->setValue(fractalColor.g * 255);
	ui.myScrollBarBlue->setValue(fractalColor.b * 255);

	bool isMode3D = myParams->getBool("isMode3D", false);
	ui.myRadioPotential->setChecked(!isMode3D);
	ui.myRadioMode3D->setChecked(isMode3D);
}

void MandelJuliaSineRendererDialog::onOk()
{
	std::vector<boost::any> amplitudes{ ui.mySpinAmplitudeR->value(), 
										ui.mySpinAmplitudeG->value(), 
										ui.mySpinAmplitudeB->value() };
	std::vector<boost::any> pulsations{ ui.mySpinPulsationR->value(), 
										ui.mySpinPulsationG->value(), 
										ui.mySpinPulsationB->value() };
	std::vector<boost::any> phases{ ui.mySpinPhaseR->value(), 
									ui.mySpinPhaseG->value(), 
									ui.mySpinPhaseB->value() };

	myParams->addVector("amplitudes", amplitudes);
	myParams->addVector("pulsations", pulsations);
	myParams->addVector("phases", phases);
	myParams->addColor("fractalColor", Color(ui.myScrollBarRed->value(), 
											 ui.myScrollBarGreen->value(), 
											 ui.myScrollBarBlue->value()));

	myParams->addBool("isMode3D", ui.myRadioMode3D->isChecked());

	hide();
}

void MandelJuliaSineRendererDialog::onCancel()
{
	hide();
}

void MandelJuliaSineRendererDialog::initGUIElementVector(QDoubleSpinBox* element, const std::string& key, const std::vector<boost::any>& default, int index)
{
	std::vector<boost::any> vec = myParams->getVector(key, default);
	element->setValue(boost::any_cast<double>(vec[index]));
}