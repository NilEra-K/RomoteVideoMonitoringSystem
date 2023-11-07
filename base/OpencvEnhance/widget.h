#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void on_verticalSliderContrast_valueChanged(int value);

    void on_verticalSliderBrightness_valueChanged(int value);

private:
    // 界面初始化
    void initWidget();
    // 处理图片
    void imgProc(float contrast, int brightned);
    // 显示图片
    void imgShow();
private:
    Ui::Widget *ui;
    Mat myImg;      // Mat 为 OpenCV 中用于保存图片的矩阵类型
    QImage myQImg;  // QT 中用于保存图片的类型
};
#endif // WIDGET_H
