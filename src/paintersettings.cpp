#include "paintersettings.hpp"

#include "logger.hpp"

constexpr auto NAME{ "Name" };
constexpr auto COLORS_FOREGROUND{ "ColorsForeground" };
constexpr auto COLORS_BACKGROUND{ "ColorsBackground" };
constexpr auto BLACK{ "Black" };
constexpr auto WHITE{ "White" };
constexpr auto SHADOW{ "Shadow" };
constexpr auto OUT_OF_SCOPE{ "OutOfScope" };
constexpr auto UNKNOWN{ "Unknown" };

constexpr auto ROI{ "ROI" };
constexpr auto GRAY_COLOR{ "GrayColor" };
constexpr auto R{ "R" };
constexpr auto G{ "G" };
constexpr auto B{ "B" };
constexpr auto A{ "A" };


PainterSettings::PainterSettings()
{
	mLogger = std::make_unique<Logger>(LogType::PAINTER_SETTINGS, LogLevel::LOW, LogFunction::YES);
	mLogger->printStartFunction(__FUNCTION__);
}

void PainterSettings::configureColors(QJsonObject const& a_config)
{
	mLogger->printStartFunction(__FUNCTION__);
	QJsonArray colorsForeground = a_config[COLORS_FOREGROUND].toArray() ;
	QJsonArray colorsBackground = a_config[COLORS_BACKGROUND].toArray() ;

	for (int i = 0; i < colorsBackground.size(); i++)
	{
		QJsonObject _colorsIter = colorsBackground[i].toObject();
		QString _name = _colorsIter[NAME].toString();
		m_colors.push_back(_name);
		m_colors_background.push_back(_name);
		PainterSettings::addrgbColors(_colorsIter);
		m_colorBackground = colorFormJsonObject(_colorsIter);
	}

	for (int i = 0; i < colorsForeground.size(); i++)
	{
		QJsonObject _colorsIter = colorsForeground[i].toObject();
		QString _name = _colorsIter[NAME].toString();
		m_colors.push_back(_name);
		m_colors_foreground.push_back(_name);
		PainterSettings::addrgbColors(_colorsIter);
		m_color = colorFormJsonObject(_colorsIter);
		
	}
}

void PainterSettings::addrgbColors(QJsonObject json)
{
	mLogger->printStartFunction(__FUNCTION__);
	QString _name = json[NAME].toString();
	int _r = json[R].toInt();
	int _g = json[G].toInt();
	int _b = json[B].toInt();
	int _a = json[A].toInt();
	int _gray = json[GRAY_COLOR].toInt();

	m_colorIntHash.insert(_name, _gray);
	m_colorHash.insert(_name, { _r, _g, _b, _a });
}

QColor PainterSettings::colorFormJsonObject(QJsonObject json)
{
	mLogger->printStartFunction(__FUNCTION__);
	int _r = json[R].toInt();
	int _g = json[G].toInt();
	int _b = json[B].toInt();
	int _a = json[A].toInt();
	return QColor{ _r, _g, _b, _a };
}

void PainterSettings::changeColor(QColor color, QString label)
{
	this->m_colorHash[label] = color;
}
