/*
 * @Author: 李龙
 * @Date: 2022-01-27 15:35:18
 * @Last Modified by: 李龙
 * @Last Modified time: 2022-02-05 17:51:45
 */
#include <lidar.h>

lidar::lidar(string com_path) : com(com_path)
{
  serial_connect.setBaud(opt_com_baudrate);
  serial_connect.setPort(com.c_str());
  if (serial_connect.openSimple())
  {
    printf("[AuxCtrl] Open serail port sucessful!\n");
    printf("baud rate:%d\n", serial_connect.getBaud());
  }
  else
  {
    printf("[AuxCtrl] Open serail port %s failed! \n", com.c_str());
  }

  printf("C3iroboticslidar connected\n");

  robotics_lidar.initilize(&serial_connect);

  init_ok_ = true;
}

lidar::~lidar()
{
  stop_thread();
}

void lidar_callback(lidar *Lidar)
{
  while (Lidar->thread_running)
  {
    Lidar->lidar_mtx.lock();
    TLidarGrabResult result = robotics_lidar.getScanData();
    switch (result)
    {
    case LIDAR_GRAB_ING:
    {
      break;
    }
    case LIDAR_GRAB_SUCESS:
    {
      TLidarScan lidar_scan = robotics_lidar.getLidarScan();
      size_t lidar_scan_size = lidar_scan.getSize();
      Lidar->lidar_scan_data.clear();
      Lidar->lidar_scan_data.resize(lidar_scan_size);
      RslidarDataComplete one_lidar_data;
      for (size_t i = 0; i < lidar_scan_size; i++)
      {
        one_lidar_data.signal = lidar_scan.signal[i];
        one_lidar_data.angle = -DEG2RAD(lidar_scan.angle[i] + Lidar->angle_scale);
        one_lidar_data.distance = lidar_scan.distance[i];
        Lidar->lidar_scan_data[i] = one_lidar_data;
      }
      break;
    }
    case LIDAR_GRAB_ERRO:
    {
      break;
    }
    case LIDAR_GRAB_ELSE:
    {
      printf("[Main] LIDAR_GRAB_ELSE!\n");
      break;
    }
    }
    Lidar->lidar_mtx.unlock();
  }
}

void lidar::start_thread(void)
{
  thread_running = true;
  receive_mtx = new std::thread(lidar_callback, this);
  receive_mtx.detach();
}

void lidar::stop_thread(void)
{
  if (thread_running)
  {
    thread_running = false;
    receive_mtx.sleep_for(std::chrono::seconds(100));
  }
}