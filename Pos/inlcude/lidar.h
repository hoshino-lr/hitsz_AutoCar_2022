/*
 * @Author: 李龙
 * @Date: 2022-01-27 15:35:12
 * @Last Modified by: 李龙
 * @Last Modified time: 2022-02-11 22:20:45
 */
#ifndef CRH_2022_LIDAR_H_
#define CRH_2022_LIDAR_H_

#include "C3iroboticsLidar.h"
#include "CSerialConnection.h"
#include <mutex>
#include <thread>
#include <time.h>

#define DEG2RAD(x) ((x)*M_PI / 180.)

typedef struct _rslidar_data
{
  _rslidar_data()
  {
    signal = 0;
    angle = 0.0;
    distance = 0.0;
  }
  uint8_t signal;
  float angle;
  float distance;
} RslidarDataComplete;

using namespace std;
using namespace everest::hwdrivers;

class lidar
{
private:
  float angle_scale = -192.5;
  int opt_com_baudrate = 115200;
  string com;
  CSerialConnection serial_connect;
  C3iroboticsLidar robotics_lidar;

  bool thread_running = false;
  thread *receive_mtx;

public:
  lidar(string com_path);
  ~lidar();
  void start_thread(void);
  void release_thread(void);
  bool init_ok_ = false;

  vector<RslidarDataComplete> lidar_scan_data;
  mutex lidar_mtx;
};

#endif CRH_2022_LIDAR_H_