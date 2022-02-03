/*
 * @Author: 李龙 
 * @Date: 2022-01-29 19:09:28 
 * @Last Modified by: 李龙
 * @Last Modified time: 2022-02-03 13:07:51
 */

// 数据类型
#ifndef CRH_2022_DATA_HPP_
#define CRH_2022_DATA_HPP_
#include <opencv2/opencv.hpp>
namespace armor
{
  struct Armor // 代表一个装甲板
  {
    cv::Rect_<float> rect;
    cv::Point2f pts[5];
    float conf;
    int color;
    int type;
  };
}

namespace ml // machine learninge
{
  struct OutLayer
  {
    int idx;
    int stride;
    int num_anchor;
    int num_out;
  };
} // namespace ml

namespace mp
{
  struct MAP_POINT
  {
    int type_; // 0: 可移动点 1: 墙 2: 障碍物 4：移动障碍物 5：车
    int cnt;
  };
  
}

struct SENSOR_DATA_MSG
{
  cv::Mat src;
  std::array<float, 3> imu_data;
  double time_stamp;
};

//收imu信息
struct IMU_DATA_MSG
{
  float x, y, z; // x-绕x轴转角-pitch  y-绕y轴转角-roll  z-绕z轴转角-yaw
  uint8_t mode;  //意义不明，我暂时没看懂
  double time_stamp;
};

//机器人信息
struct ROBOT_DATA
{
  int color; //颜色
  int id;    //id
  int blood; //血量
  int power; //功率
}

//从电控接收到的信息
struct RECEIVE_MSG
{
  IMU_DATA_MSG imu_msg;
  ROBOT_DATA own;
  ROBOT_DATA enemy;
}

//机器人运动控制
struct ROBOT_CONTROL
{
  uint8_t mode;
}

//底盘控制
struct BED_CONTROL
{
  float x, y; //底盘运动，x控制左右，y控制前后
}
//云台控制
struct PTZ_CONTROL
{
  float roll, pitch, yaw, wait; //云台角度
}
//发送给电控的控制
#pragma pack(1)
struct CONTROL_CMD
{
  ROBOT_CONTROL robot_ctrl;
  PTZ_CONTROL ptz_ctrl;
  BED_CONTROL bed_ctrl;
};
#pragma pack()

struct DETECT_MSG
{
  std::vector<armor::Armor> res; // 检测到的所有可能的目标
  cv::Mat src;
  std::array<float, 3> imu_data; // 陀螺仪数据x,y,z
  double time_stamp;             // 单位: millionsecond
};

enum ROBOT_MODE // 运行模式
{
  NO_ACTION, // 无动作
  SEARCHING, // 侦察(巡回)模式
  SHOTTING,  // 攻击模式
  FLEXING,   // 灵活模式
};

enum BED_MODE //底盘模式
{
  NO_ACTION, //无动作
  FOLLOW,    //底盘跟随云台
  TOP,       //小陀螺
  NO_FOLLOW, //底盘不跟随云台
}

#endif // CRH_2022_DATA_HPP_