#pragma once

#include <QWidget>
#include <QJsonObject>

class QComboBox;

class ColorPicker : public QWidget
{
	Q_OBJECT
	public:
		ColorPicker(QWidget *parent = nullptr);

	private:
		int addColors(QString color);

	signals:
		void changeColor(QColor color);
	
	private:
		QJsonObject mConfig;
		QComboBox* mColorPenComboBox;
};
