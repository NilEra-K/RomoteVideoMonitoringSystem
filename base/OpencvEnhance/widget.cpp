#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    initWidget();   // 界面初始化
}

Widget::~Widget()
{
    delete ui;
}

// 界面初始化
void Widget::initWidget() {
    QString imgPath = "../OpencvEnhance/images/girldriver.jpg";   // 使用相对路径时, 以 Debug 作为当前路径
                                                                  // 路径中不能包含中文
    Mat imgData = imread(imgPath.toLatin1().data());              // 讲路径转化为 Latin1 格式, 读取图片数据
    cvtColor(imgData, imgData, COLOR_BGR2RGB);                    // 将 imgData 中的图片(BGR格式)转化为RGB格式, 并保存到 imgData 中
    myImg = imgData;                                              // 将 imgData 存储与 myImg 中
    // 将 imgData 中的数据(uchar*型)、行数(作为宽)、列数(作为长), 传入 QImage 构造函数中
    // 并设置 QImage 格式为 Format_RGB888, 表示为 RGB 格式, 一个数据一个字节
    myQImg = QImage(imgData.data, imgData.cols, imgData.rows, QImage::Format_RGB888);
    imgShow();
}

void Widget::imgProc(float contrast, int brightned) {
    Mat imgSrc = myImg;
    Mat imgDest = Mat::zeros(imgSrc.size(), imgSrc.type());     // 用于存储处理后的图像矩阵: 初始生成一个空的零像素矩阵
    imgSrc.convertTo(imgDest, -1, contrast, brightned);
    myQImg = QImage(imgDest.data, imgDest.cols, imgDest.rows, QImage::Format_RGB888);
    imgShow();
}

void Widget::imgShow() {
    // scaled() 用于拉伸图片, 可以选择保持横纵比拉伸, 填充等效果
    // qDebug() << ui->labelView->sizeHint() << '\n';
    ui->labelView->setPixmap(QPixmap::fromImage(myQImg.scaled(ui->labelView->size(), Qt::KeepAspectRatio)));
}

// 对比度滑块
void Widget::on_verticalSliderContrast_valueChanged(int value) {
    imgProc(value / 33.3, ui->verticalSliderBrightness->value());
}

// 亮度滑块
void Widget::on_verticalSliderBrightness_valueChanged(int value) {
    imgProc(ui->verticalSliderContrast->value() / 33.3, value);
}

