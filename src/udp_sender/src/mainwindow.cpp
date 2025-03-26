#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      // udp server ip와 port 설정 (필요에 따라 수정)
      driver_("192.168.0.5", 5000)
{
    ui->setupUi(this);
    driver_.start();
}

MainWindow::~MainWindow() {
    driver_.stop();
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    // 버튼 클릭 시 udp packet 전송 함수 호출
    driver_.send_udp_packet();
}
