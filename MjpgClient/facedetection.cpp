#include "facedetection.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <QDebug>

using namespace cv;

FaceDetection::FaceDetection(QObject *parent) : QObject{parent} { }

// 人脸检测
void FaceDetection::onFaceDetection(QImage img) {
    // 将图像转换为 RGB24 位色
    QImage image = img.convertToFormat(QImage::Format_RGB888);
    // 使用 Mat 构造函数, 将 QImage 格式转换为 Mat 格式
    Mat matImg = Mat(image.height(), image.width(), CV_8UC3, image.bits(), image.bytesPerLine());
    // 将图片进行灰度处理
    Mat imgGray;
    cvtColor(matImg, imgGray, COLOR_RGB2GRAY);
    // 加载分类器
    CascadeClassifier faceDetector;
    std::string detectPath = "../MjpgClient/haarcascade_frontalface_default.xml";
    faceDetector.load(detectPath);  // 加载分类器
    std::vector<Rect> faces;
    equalizeHist(imgGray, imgGray); // 直方图均衡化
    // 多尺度检测人脸
    faceDetector.detectMultiScale(imgGray, faces, 1.1, 3, 0, Size(30, 30));
    if(!faces.empty()) { // 如果检测到人脸
        QString str = "检测到有" + QString::number(faces.size()) + "人进入监控区域";
        qDebug() << str;
    }
}
