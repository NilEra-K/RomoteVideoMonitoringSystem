#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
    labelJpegs.append(ui->labelJpeg1);
    labelJpegs.append(ui->labelJpeg2);
    labelJpegs.append(ui->labelJpeg3);
    labelJpegs.append(ui->labelJpeg4);
    manager = new QNetworkAccessManager(this);
    thread = new QThread(this);
    detectWork = new FaceDetection;     // 不能指定父对象, 因为要移动到线程中, 有父对象无法移动
    detectWork->moveToThread(thread);   // 将工作对象移动到线程
    connect(this, SIGNAL(imageAcquired(QImage)), detectWork, SLOT(onFaceDetection(QImage)));
    thread->start();
}

Widget::~Widget()
{
    delete manager;
    manager = nullptr;
    thread->terminate();
    thread->wait();
    delete ui;
}

// 获取视频按钮被点击
void Widget::on_btnGetMjpg_clicked() {
    // 1. 准备请求包, 获取 Url 地址, 根据 Url 地址自动生成请求包
    // 视频流 <img src="./?action=stream"/>
    // 快照 <img src="./?action=snapshot"/>
    request.setUrl(QUrl("http://192.168.26.128:8080?action=stream"));
    // 2. 发送请求包, 使用 get 方法请求获取视频流数据, 返回专门用于接收视频流数据的响应对象
    mjpgReply = manager->get(request);
    // 3. 当服务器发送来数据时, 会触发 readyRead() 信号的发射
    connect(mjpgReply, SIGNAL(readyRead()),this, SLOT(onMjpgReadyRead()));
}

// 接收 mjpg 视频流数据, 从中剥离一帧
void Widget::onMjpgReadyRead() {
    // 1. 接收数据
    mjpgBuffer += mjpgReply->readAll();     // 防止前一次数据没接全
    // 2. 定义保存图片帧的标记 - 可查看 Blog: https://www.cnblogs.com/-chenxs/p/11493898.html
    // 起始标记: 0xff 0xd8
    // 结束标记: 0xff 0xd9
    char startFlag[3] = {(char)0xff, (char)0xd8};
    char endFlag[3] = {(char)0xff, (char)0xd9};
    // 3. 查找发送来的数据流中的图片起始标志
    qDebug() << startFlag << ' ' << endFlag;
    int startIndex = mjpgBuffer.indexOf(startFlag, 0);  // 从 0 位置查找 mjpgBuffer 的起始标志
    if(startIndex == -1) { // 没找到起始标记, 说明当前处于某张图片的中间部分(缓冲数据接收不完整), 这些数据也没有读取的必要了
        mjpgBuffer.clear();
        return;
    }
    int endIndex = mjpgBuffer.indexOf(endFlag, startIndex);     // 从起始位置向后查找结束标记的位置
    if(endIndex == -1) { // 有起始标记, 但是没找到结束标记, 说明图片没接收完, 下次继续接收
        return;
    }
    // 4. 从视频流中截取一张图片帧数据
    // 从 startIndex 开始, 截取 (endIndex - startIndex) + 2 个长度的数据
    QByteArray imgBuff = mjpgBuffer.mid(startIndex, (endIndex - startIndex) + 2);
    // 5. 将 QByteArray 中的数据加载到为 QImage 中, 图片格式为 JPG
    bool ret = mjpgImage.loadFromData(imgBuff, "JPG");
    if(ret == false) {
        mjpgBuffer.clear();
        return;
    }
    // 6. 加载图片成功, 显示到对应的 label 上
    ui->labelMjpg->setPixmap(QPixmap::fromImage(mjpgImage));
    emit imageAcquired(mjpgImage);  // 发射信号, 进行人脸检测
    mjpgBuffer.clear();
}

// 获取快照
void Widget::on_btnGetJpeg_clicked() {
    // 1. 准备请求包, 获取 Url 地址, 根据 Url 地址自动生成请求包
    // 视频流 <img src="./?action=stream"/>
    // 快照 <img src="./?action=snapshot"/>
    request.setUrl(QUrl("http://192.168.26.128:8080?action=snapshot"));
    // 2. 发送请求包, 使用 get 方法请求获取快照数据, 返回专门用于接收快照数据的响应对象
    jpegReply = manager->get(request);
    // 3. 当服务器发送来数据时, 会触发 readyRead() 信号的发射
    connect(jpegReply, SIGNAL(readyRead()),this, SLOT(onJpegReadyRead()));
}

// 有快照数据时
void Widget::onJpegReadyRead() {
    // 1. 接收数据
    jpegBuffer += jpegReply->readAll();     // 防止前一次数据没接全
    // 2. 定义保存图片帧的标记 - 可查看 Blog: https://www.cnblogs.com/-chenxs/p/11493898.html
    // 起始标记: 0xff 0xd8
    // 结束标记: 0xff 0xd9
    char startFlag[3] = {(char)0xff, (char)0xd8};
    char endFlag[3] = {(char)0xff, (char)0xd9};
    // 3. 查找发送来的数据流中的图片起始标志
    qDebug() << startFlag << ' ' << endFlag;
    int startIndex = jpegBuffer.indexOf(startFlag, 0);  // 从 0 位置查找 mjpgBuffer 的起始标志
    if(startIndex == -1) { // 没找到起始标记, 说明当前处于某张图片的中间部分(缓冲数据接收不完整), 这些数据也没有读取的必要了
        jpegBuffer.clear();
        return;
    }
    int endIndex = jpegBuffer.indexOf(endFlag, startIndex);     // 从起始位置向后查找结束标记的位置
    if(endIndex == -1) { // 有起始标记, 但是没找到结束标记, 说明图片没接收完, 下次继续接收
        return;
    }
    // 4. 截取一张图片帧数据
    // 从 startIndex 开始, 截取 (endIndex - startIndex) + 2 个长度的数据
    QByteArray imgBuff = jpegBuffer.mid(startIndex, (endIndex - startIndex) + 2);
    // 5. 将 QByteArray 中的数据加载到为 QImage 中, 图片格式为 JPG
    bool ret = jpegImage.loadFromData(imgBuff, "JPG");
    if(ret == false) {
        jpegBuffer.clear();
        return;
    } else {
        // 加载图片成功, 显示到 labelJpeg 上
        labelJpegs[m_index]->setPixmap(QPixmap::fromImage(jpegImage.scaled(labelJpegs[m_index]->size(), Qt::KeepAspectRatio)));
        m_index = (++m_index) % 4;
        jpegBuffer.clear();
    }
}
