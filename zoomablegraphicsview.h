#ifndef ZOOMABLE_GRAPHICS_VIEW_H
#define ZOOMABLE_GRAPHICS_VIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QPointF>
#include <QApplication>

class ZoomableGraphicsView : public QGraphicsView {
    Q_OBJECT
public:
    explicit ZoomableGraphicsView(QWidget* parent = nullptr);

    // 设置缩放的修饰符（默认Ctrl键）
    void setModifiers(Qt::KeyboardModifiers modifiers);

    // 设置缩放因子基准值
    void setZoomFactorBase(double value);

    // 设置缩放的阈值，避免不必要的信号发射
    void setZoomThreshold(double threshold);

protected:
    // 重新实现鼠标滚轮事件
    void wheelEvent(QWheelEvent* event) override;

    // 处理键盘事件
    void keyPressEvent(QKeyEvent* event) override;

    // 处理鼠标移动事件
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    void applyZoom(double factor);
    void adjustZoomCenter(QPointF targetScenePos);

signals:
    void zoomed();  // 缩放后的信号

private:
    Qt::KeyboardModifiers _modifiers;  // 缩放修饰符
    double _zoomFactorBase;           // 缩放因子基准值
    double _zoomThreshold;            // 缩放阈值
    QPointF _targetScenePos;          // 目标场景位置
    QPointF _targetViewportPos;       // 目标视口位置
    double _lastZoomFactor;           // 上一次的缩放因子，用于检测缩放变化
};

#endif // ZOOMABLE_GRAPHICS_VIEW_H
