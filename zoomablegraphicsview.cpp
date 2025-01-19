#include "ZoomableGraphicsView.h"
#include <QWheelEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <qmath.h>
#include <QDebug>

ZoomableGraphicsView::ZoomableGraphicsView(QWidget *parent)
    : QGraphicsView(parent),
      _modifiers(Qt::ControlModifier), // 默认按Ctrl键进行缩放
      _zoomFactorBase(1.0015),         // 默认缩放因子基准值
      _zoomThreshold(0.1),             // 默认缩放阈值
      _lastZoomFactor(1.0)
{ // 默认缩放因子
    setRenderHint(QPainter::Antialiasing);
    setRenderHint(QPainter::SmoothPixmapTransform);
}

void ZoomableGraphicsView::setModifiers(Qt::KeyboardModifiers modifiers)
{
    _modifiers = modifiers;
}

void ZoomableGraphicsView::setZoomFactorBase(double value)
{
    _zoomFactorBase = value;
}

void ZoomableGraphicsView::setZoomThreshold(double threshold)
{
    _zoomThreshold = threshold;
}

void ZoomableGraphicsView::wheelEvent(QWheelEvent *event)
{
    if (event->modifiers() & _modifiers)
    {
        double angle = event->angleDelta().y();
        double factor = qPow(_zoomFactorBase, angle);

        // 计算缩放增量
        double zoomIncrement = qAbs(factor - _lastZoomFactor);
        if (zoomIncrement >= _zoomThreshold)
        {
            applyZoom(factor);
            _lastZoomFactor = factor; // 更新缩放因子
            emit zoomed();            // 发出缩放完成信号
            qDebug() << "Zoom Factor: " << factor;
        }
    }
    else
    {
        QGraphicsView::wheelEvent(event); // 默认行为：滚动事件
    }
}

void ZoomableGraphicsView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Plus && event->modifiers() & Qt::ControlModifier)
    {
        applyZoom(_zoomFactorBase);
        emit zoomed();
    }
    else if (event->key() == Qt::Key_Minus && event->modifiers() & Qt::ControlModifier)
    {
        applyZoom(1.0 / _zoomFactorBase);
        emit zoomed();
    }

    QGraphicsView::keyPressEvent(event); // 继续默认处理
}

void ZoomableGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF delta = _targetViewportPos - event->pos();
    if (qAbs(delta.x()) > 5 || qAbs(delta.y()) > 5)
    {
        _targetViewportPos = event->pos();
        _targetScenePos = mapToScene(event->pos());
    }

    QGraphicsView::mouseMoveEvent(event); // 继续默认处理
}

void ZoomableGraphicsView::applyZoom(double factor)
{
    scale(factor, factor);
    adjustZoomCenter(_targetScenePos);
}

void ZoomableGraphicsView::adjustZoomCenter(QPointF targetScenePos)
{
    // 获取视口的当前中心点
    QPointF deltaViewportPos = _targetViewportPos - QPointF(width() / 2.0, height() / 2.0);
    QPointF viewportCenter = mapFromScene(targetScenePos) - deltaViewportPos;
    centerOn(mapToScene(viewportCenter.toPoint()));
}
