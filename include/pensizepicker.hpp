#pragma once

#include <QComboBox>
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>


class PenSizePicker : public QWidget
{
	Q_OBJECT
	public:
		explicit PenSizePicker(QWidget *parent = nullptr);

	signals:
		void changePenSize(qint32 size);
};

