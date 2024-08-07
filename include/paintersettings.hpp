#pragma once

#include <QColor>
#include <QHash>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

class Logger;

class PainterSettings
{
    public:
        PainterSettings();
        void configureColors(QJsonObject const& a_config);
        void changeColor(QColor color, QString label);

    public:
        std::vector<QString> m_colors;
        std::vector<QString> m_colors_background;
        std::vector<QString> m_colors_foreground;
        int m_penSize{1};
        QColor m_color;
        QColor m_colorBackground;
    
    private:
        void addrgbColors(QJsonObject json);
        QColor colorFormJsonObject(QJsonObject json);
        
    public:
        QHash<QString, QColor> m_colorHash;
        QHash<QString, int> m_colorIntHash;
    private:
		std::unique_ptr<Logger> mLogger;
};

