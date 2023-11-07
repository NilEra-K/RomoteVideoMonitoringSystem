#include "widget.h"
#include "ui_widget.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    Mat image=imread("D:/RomoteVideoMonitoringSystem/base/OpencvTest/images/baby.jpg", 1);//一定要使用绝对路径, 其他可以会报错
    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display window", image);
}

Widget::~Widget()
{
    delete ui;
}

