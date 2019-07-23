#include "MandelJuliaRandomRenderer2Dialog.h"

#include "qcolordialog.h"

MandelJuliaRandomRenderer2Dialog::MandelJuliaRandomRenderer2Dialog(QWidget *parent, Parameters* params)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.myButtonOk, &QPushButton::clicked, this, &MandelJuliaRandomRenderer2Dialog::onOk);
	connect(ui.myButtonCancel, &QPushButton::clicked, this, &MandelJuliaRandomRenderer2Dialog::onCancel);
	connect(ui.myButtonRandom, &QPushButton::clicked, this, &MandelJuliaRandomRenderer2Dialog::onRandom);
	connect(ui.myButtonAddColor, &QPushButton::clicked, this, &MandelJuliaRandomRenderer2Dialog::onAddColor);
	connect(ui.myButtonRemoveColor, &QPushButton::clicked, this, &MandelJuliaRandomRenderer2Dialog::onDeleteColor);
	connect(ui.myButtonMoveColorUp, &QPushButton::clicked, this, &MandelJuliaRandomRenderer2Dialog::onMoveUp);
	connect(ui.myButtonMoveColorDown, &QPushButton::clicked, this, &MandelJuliaRandomRenderer2Dialog::onMoveDown);
	connect(ui.myButtonChangeFractalColor, &QPushButton::clicked, this, &MandelJuliaRandomRenderer2Dialog::onChangeFractalColor);

	myRng.seed(time(NULL));

	setParameters(params);
}

MandelJuliaRandomRenderer2Dialog::~MandelJuliaRandomRenderer2Dialog()
{

}

void MandelJuliaRandomRenderer2Dialog::setParameters(Parameters* params)
{
	myParams = params;
	std::vector<boost::any> vec = myParams->getVector("iterationColors", std::vector<boost::any>());
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		Color color = boost::any_cast<Color>(vec[i]);
		QListWidgetItem* item = new QListWidgetItem(QString().setNum(i));
		item->setBackgroundColor(QColor(color.r * 255, color.g * 255, color.b * 255));
		ui.myListColors->addItem(item);
	}

	myFractalColor = params->getColor("fractalColor", Color());
	setPreviewColor(myFractalColor.r * 255, myFractalColor.g * 255, myFractalColor.b * 255);
}

void MandelJuliaRandomRenderer2Dialog::onOk()
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

	myParams->addVector("iterationColors", myColorVector);
	myParams->addColor("fractalColor", myFractalColor);

	hide();
}

void MandelJuliaRandomRenderer2Dialog::onCancel()
{
	hide();
}

void MandelJuliaRandomRenderer2Dialog::onRandom()
{
	ui.myListColors->clear();
	for (int i = 0; i < ui.mySpinRandom->value(); i++) {
		Color tmp(myRng.nextDouble(), myRng.nextDouble(), myRng.nextDouble());
		QListWidgetItem* item = new QListWidgetItem(QString().setNum(i));
		item->setBackgroundColor(QColor(tmp.r * 255, tmp.g * 255, tmp.b * 255));
		ui.myListColors->addItem(item);//QString().setNum(tmp.r) + " " + QString().setNum(tmp.g) + " " + QString().setNum(tmp.g));
	}
}

void MandelJuliaRandomRenderer2Dialog::onAddColor()
{
	QColor color = QColorDialog::getColor();

	QListWidgetItem* item = new QListWidgetItem;
	item->setBackgroundColor(color);
	ui.myListColors->addItem(item);
}

void MandelJuliaRandomRenderer2Dialog::onDeleteColor()
{
	QList<QListWidgetItem*> items = ui.myListColors->selectedItems();
	for (QListWidgetItem* item : items) {
		ui.myListColors->removeItemWidget(item);
		delete item;
	}
}

void MandelJuliaRandomRenderer2Dialog::onMoveUp()
{
	int index = ui.myListColors->currentRow();
	if (index > 0)
	{
		auto item = ui.myListColors->takeItem(index);
		ui.myListColors->insertItem(index - 1, item);
	}

}

void MandelJuliaRandomRenderer2Dialog::onMoveDown()
{
	int index = ui.myListColors->currentRow();
	if (index < ui.myListColors->count() - 1)
	{
		auto item = ui.myListColors->takeItem(index);
		ui.myListColors->insertItem(index + 1, item);
	}
}

void MandelJuliaRandomRenderer2Dialog::onChangeFractalColor()
{
	QColor color = QColorDialog::getColor();
	myFractalColor = Color(color.redF(), color.greenF(), color.blueF());
	setPreviewColor(color.red(), color.green(), color.blue());
}

void MandelJuliaRandomRenderer2Dialog::setPreviewColor(int r, int g, int b)
{
	int alpha = 255;
	QString values = QString::number(r) + "," +
		QString::number(g) + "," +
		QString::number(b) + "," +
		QString::number(alpha);
	//std::cout << values.toStdString() << std::endl;
	ui.myLabelColorPreview->setStyleSheet("QLabel { background-color: rgba(" + values + "); }");
}
