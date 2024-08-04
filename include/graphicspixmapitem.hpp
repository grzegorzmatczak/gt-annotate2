#pragma once

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>

class GraphicsPixmapItem : public QGraphicsPixmapItem
{
 public:
  GraphicsPixmapItem();

 signals:

  // QGraphicsItem interface
 public:
  int type() const override;
};

