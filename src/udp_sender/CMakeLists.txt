cmake_minimum_required(VERSION 3.5)
project(udp_sender)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()


# ROS2 패키지 의존성
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

# Boost 라이브러리 (필요한 경우)
find_package(Boost REQUIRED COMPONENTS system)


include_directories(
  include/
)

add_executable(${PROJECT_NAME}_node
  src/main.cpp
  src/udpclient.cpp
  src/binaryparser.cpp
  src/packet.cpp
  src/rgbd_ros_driver.cpp
  ${UI_FILES}
)

ament_target_dependencies(${PROJECT_NAME}_node
  rclcpp
  std_msgs
)
target_link_libraries(${PROJECT_NAME}_node
  Boost::system
  pthread
)

install(TARGETS ${PROJECT_NAME}_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
