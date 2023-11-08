#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    initWidget();
}

Widget::~Widget()
{
    delete ui;
}

// 初始化窗口
void Widget::initWidget() {
    QString imgPath = "../OpencvFace/images/baby.jpg";
    Mat imgData = imread(imgPath.toLatin1().data());
    cvtColor(imgData, imgData, COLOR_BGR2RGB);
    myImg = imgData;
    myQImg = QImage(imgData.data, imgData.cols, imgData.rows, QImage::Format_RGB888);
    imgShow();
}

// 图片处理(人脸识别)
void Widget::imgProc(QImage image) {
    CascadeClassifier faceDetector;     // 定义人脸识别分类器
    CascadeClassifier eyeDetector;      // 定义人脸识别分类器
//    string faceDetector
}

// 图片显示
void Widget::imgShow() {
    ui->labelView->setPixmap(QPixmap::fromImage(myQImg.scaled(ui->labelView->size(), Qt::KeepAspectRatio)));
}

