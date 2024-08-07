#include "colorpicker.hpp"

#include "configreader.hpp"

#include <QComboBox>
#include <QDebug>
#include <QHBoxLayout>
#include <QJsonArray>

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>


constexpr auto NAME{ "Name" };
constexpr auto COLORS_FOREGROUND{ "ColorsForeground" };

constexpr auto ROI{ "ROI" };
constexpr auto R{ "R" };
constexpr auto G{ "G" };
constexpr auto B{ "B" };
constexpr auto A{ "A" };

int ColorPicker::addColors(QString color)
{
	int counter = 0;
	auto colors = mConfig[color].toArray();
	for (int i = 0; i < colors.size(); i++)
	{
		auto colorsIter = colors[i].toObject();
		qint32 r = colorsIter[R].toInt();
		qint32 g = colorsIter[G].toInt();
		qint32 b = colorsIter[B].toInt();
		qint32 a = colorsIter[A].toInt();

		mColorPenComboBox->insertItem(i, colorsIter[NAME].toString());
		mColorPenComboBox->setItemData(i, QColor(r, g, b, a), Qt::DecorationRole);

		counter++;
	}
	return counter;
}

ColorPicker::ColorPicker(QWidget *parent)
	: QWidget(parent)
{
	ConfigReader cf = ConfigReader();
    
	cf.readConfig("config.json", mConfig);

	mColorPenComboBox = new QComboBox();
	int colorAdded{0};

	colorAdded = ColorPicker::addColors(COLORS_FOREGROUND);
	
	QHBoxLayout *penColorLayout = new QHBoxLayout;
	penColorLayout->setContentsMargins(0, 0, 0, 0);

	QLabel *labelPenColor = new QLabel();
	labelPenColor->setText("Pen Color:");

	mColorPenComboBox->setMinimumWidth(80);

	connect(mColorPenComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index) {
		emit(changeColor(mColorPenComboBox->itemData(index, Qt::DecorationRole).value<QColor>()));
		
		#ifdef DEBUG
		qDebug() << "colorPenComboBox:" << mColorPenComboBox->itemData(index, Qt::DecorationRole);
		#endif
	});

	QVBoxLayout *Layout = new QVBoxLayout;
	Layout->setContentsMargins(0, 0, 0, 0);
	Layout->addWidget(labelPenColor);
	Layout->addWidget(mColorPenComboBox);

	if(colorAdded)
		{mColorPenComboBox->setCurrentIndex(1);}

	setLayout(Layout);
}
