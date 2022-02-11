/*
 * @Author: 李龙
 * @Date: 2022-01-27 15:35:14
 * @Last Modified by: 李龙
 * @Last Modified time: 2022-02-11 22:22:00
 */
#ifndef CRH_2022_POSITION_H_
#define CRH_2022_POSITION_H_

#include <lidar.h>
#include <opencv2/opencv.hpp>
class position : public lidar
{
  /*

  */
private:
  bool show_map = false;
  cv::Mat now_map(640, 640, CV_8UC3);
  float scale_ = 640 / 8;

public:
  position(bool show, string com_path);
  void update(void);
  ~position();
};
#endif CRH_2022_POSITION_H_