#include "LyapunovRandomRendererDialog.h"

#include "qcolordialog.h"

LyapunovRandomRendererDialog::LyapunovRandomRendererDialog(QWidget *parent, Parameters* params)
	: QDialog(parent)
	//,myParams(params)
{
	ui.setupUi(this);

	connect(ui.myButtonOk, &QPushButton::clicked, this, &LyapunovRandomRendererDialog::onOk);
	connect(ui.myButtonCancel, &QPushButton::clicked, this, &LyapunovRandomRendererDialog::onCancel);
	connect(ui.myButtonRandom, &QPushButton::clicked, this, &LyapunovRandomRendererDialog::onRandom);
	connect(ui.myButtonAddColor, &QPushButton::clicked, this, &LyapunovRandomRendererDialog::onAddColor);
	connect(ui.myButtonRemoveColor, &QPushButton::clicked, this, &LyapunovRandomRendererDialog::onDeleteColor);
	connect(ui.myButtonMoveColorUp, &QPushButton::clicked, this, &LyapunovRandomRendererDialog::onMoveUp);
	connect(ui.myButtonMoveColorDown, &QPushButton::clicked, this, &LyapunovRandomRendererDialog::onMoveDown);

	myRng.seed(time(NULL));

	setParameters(params);
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
LyapunovRandomRendererDialog::~LyapunovRandomRendererDialog()
{
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LyapunovRandomRendererDialog::setParameters(Parameters* params)
{
	myParams = params;
	std::vector<boost::any> vec = myParams->getVector("lambdaColors", std::vector<boost::any>());
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		Color color = boost::any_cast<Color>(vec[i]);
		QListWidgetItem* item = new QListWidgetItem(QString().setNum(i));
		item->setBackgroundColor(QColor(color.r * 255, color.g * 255, color.b * 255));
		ui.myListColors->addItem(item);
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LyapunovRandomRendererDialog::onOk()
{
	std::vector<boost::any> myColorVector;
	myColorVector.resize(ui.myListColors->count());
	for (unsigned int i = 0; i < ui.myListColors->count(); i++)
	{
		auto item = ui.myListColors->item(i);
		QColor color = item->backgroundColor();
		myColorVector[i] = Color(color.redF(), color.greenF(), color.blueF());
	}
		;

	myParams->addVector("lambdaColors", myColorVector);

	hide();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LyapunovRandomRendererDialog::onCancel()
{
	hide();
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LyapunovRandomRendererDialog::onRandom()
{
	ui.myListColors->clear();
	for (int i = 0; i < ui.mySpinRandom->value(); i++) {
		Color tmp(myRng.nextDouble(), myRng.nextDouble(), myRng.nextDouble());
		QListWidgetItem* item = new QListWidgetItem(QString().setNum(i));
		item->setBackgroundColor(QColor(tmp.r * 255, tmp.g * 255, tmp.b * 255));
		ui.myListColors->addItem(item);//QString().setNum(tmp.r) + " " + QString().setNum(tmp.g) + " " + QString().setNum(tmp.g));
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LyapunovRandomRendererDialog::onAddColor()
{
	QColor color = QColorDialog::getColor();

	QListWidgetItem* item = new QListWidgetItem;
	item->setBackgroundColor(color);
	ui.myListColors->addItem(item);
}

void LyapunovRandomRendererDialog::onDeleteColor()
{
	QList<QListWidgetItem*> items = ui.myListColors->selectedItems();
	for (QListWidgetItem* item : items) {
		ui.myListColors->removeItemWidget(item);
		delete item;
	}
}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LyapunovRandomRendererDialog::onMoveUp()
{
	int index = ui.myListColors->currentRow();
	if (index > 0)
	{
		auto item = ui.myListColors->takeItem(index);
		ui.myListColors->insertItem(index - 1, item);
	}

}

//=============================================================================
///////////////////////////////////////////////////////////////////////////////
void LyapunovRandomRendererDialog::onMoveDown()
{
	int index = ui.myListColors->currentRow();
	if (index < ui.myListColors->count() - 1)
	{
		auto item = ui.myListColors->takeItem(index);
		ui.myListColors->insertItem(index + 1, item);
	}
}