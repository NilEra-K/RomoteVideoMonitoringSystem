#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QThread>
#include "facedetection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

signals:
    // 自定义信号
    void imageAcquired(QImage);

private slots:
    void on_btnGetMjpg_clicked();
    void onMjpgReadyRead();             // 接收到视频流数据时
    void onJpegReadyRead();

    void on_btnGetJpeg_clicked();

private:
    Ui::Widget *ui;
    QNetworkAccessManager* manager;     // 管理整个通信过程
    QNetworkRequest request;            // 根据 Url 生成请求包
    QNetworkReply* mjpgReply;           // 获取视频流响应数据包
    QByteArray mjpgBuffer;              // 保存视频流响应数据的缓冲区
    QImage mjpgImage;                   // 保存从视频流中截取的图片帧

    QNetworkReply* jpegReply;           // 获取快照响应数据包
    QByteArray jpegBuffer;              // 保存快照响应数据的缓冲区
    QImage jpegImage;                   // 保存快照

    QThread* thread;
    FaceDetection* detectWork;          // 人脸检测工作对象

    QVector<QLabel*> labelJpegs;        // 保存显示的快照 label
    int m_index;                        // 索引
};
#endif // WIDGET_H
