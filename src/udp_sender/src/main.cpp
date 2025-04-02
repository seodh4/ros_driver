#include "rgbd_ros_driver.hpp"
#include <thread>
#include <chrono>

int main() {
    rgbd_ros_driver driver("192.168.0.5", 5000);
    driver.start();

    std::this_thread::sleep_for(std::chrono::seconds(10));  // 예시 실행 시간
    driver.stop();

    return 0;
}


