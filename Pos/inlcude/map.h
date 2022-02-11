/*
 * @Author: 李龙
 * @Date: 2022-02-03 12:41:09
 * @Last Modified by: 李龙
 * @Last Modified time: 2022-02-11 22:22:34
 */

#ifndef CRH_2022_MAP_H_
#define CRH_2022_MAP_H_

#include <vector>
#include <queue>
#include <data.hpp>
#include <opencv2/opencv.hpp>
#include <mutex>
#include <lidar.h>

using namespace std;

class map
{
private:
  double dtn_dorm2(cv::Point2d p1, cv::Point2d p2);
  double dtn_dorm1(cv::Point2d p1, cv::Point2d p2);
  void map_init(void);

  string map_name = 'map.png';
  string filename = 'map.txt';

  float angle = 0;
  float l_angle = 0;

  cv::Mat pic_map;
  vector<vector<mp::MP>> cost_map;
  unique_lock<mutex> map_key;
  bool show_map = false;
  bool DEBUG = false;
  double scale_ = 250.0;
  cv::Point2d r_pos(-1, -1);
  cv::Point2d l_pos(0, 0);
  cv::Point2d m_pos(0, 0);
  cv::Point2d enemy_pos(-1, -1);
  vector<vector<mp::MP>> sps;

public:
  map(bool debug, bool SHOW_MAP, string com_path);
  void msg_read(string filename);
  void show(void);
  void update_msg(float yaw, cv::Point2d radar_pos);
  void update_pos(mp::SM);
  vector<mp::SM> gen_sps(cv::Point2d pos, float angle, vector<vector<mp::MP>> map_);
  ~map();
};

#endif CRH_2022_MAP_H_
