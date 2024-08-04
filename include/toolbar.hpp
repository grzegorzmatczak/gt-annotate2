#pragma once

#include <QObject>
#include <QToolBar>
#include <QToolButton>
#include <QWidget>

class ToolButton : public QToolButton
{
	Q_OBJECT
	public:
		ToolButton();

	public:
		QSize minimumSizeHint() const override;
};

class ToolBar : public QToolBar
{
	Q_OBJECT
	public:
		ToolBar();
		void addAction(QAction *action);
};
