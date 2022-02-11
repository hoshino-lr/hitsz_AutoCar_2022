/*
 * @Author: 李龙
 * @Date: 2022-02-03 14:11:54
 * @Last Modified by: 李龙
 * @Last Modified time: 2022-02-11 22:22:09
 */
#include <map.h>
#include <iostream>
#include <fstream>

map::map(bool debug, bool SHOW_MAP) : DEBUG(debug), show_map(SHOW_MAP), lidar(com_path)
{
  pic_map = cv::imread(map_name);
  msg_read(filename);
  map_init();
}

void map::update_msg(float yaw, cv::Point2d radar_pos);
{
  if (radar_pos.x != -1)
  {
    this->r_pos = radar_pos;
  }
  this->angle = yaw;
}

void map::map_init(void)
{
  int h_step = pic_map.row / cost_map.size();
  int w_step = pic_map.col / cost_map[0].size();
  for (size_t i = 0; i < cost_map.size(); i++)
  {
    for (size_t j = 0; j < cost_map[i].size(); j++)
    {
      auto r = cv::Rect(j * w_step, i * h_step, w_step, h_step);
      cv::rectangle(pic_map, r, enum(cost_map[i][j].type_), -1);
    }
  }
}

void map::msg_read(string filename)
{
  fstream infile(filename);
  if (!infile.is_open())
  {
    cout << "Error opening file";
    return;
  }
  int row, col;
  cin >> row >> col;
  cost_map.resize(row);
  for (auto &i : cost_map)
  {
    i.resize(col);
  }
  while (!infile.eof())
  {
    int i = 0, j = 0;
    cin >> cost_map[i][j].type_;
    cout << cost_map[i][j].type_ << endl;
  }
}

void map::show()
{
  cv::Mat pic_ = pic_map.clone();
  cv::rectangle(pic_, cv::Rect((m_pos.x0 - 1) * pic_.width / 20, (m_pos.y - 1) * pic_.height / 20, pic_.width / 20 * 2, pic_.height / 20 * 2), cv::Scalar(0, 255, 0), -1);
  if (this->enemy_pos.x != -1)
  {
    cv::rectangle(pic_, cv::Rect((enemy_pos.x - 1) * pic_.width / 20.0, (enemy_pos.y - 1) * pic_.height / 20.0, pic_.width / 20.0 * 2, pic_.height / 20.0 * 2), cv::Scalar(255, 0, 255), -1);
  }
  cv::imshow("MAP", pic_);
}

double map::dtn_dorm1(cv::Point2d p1, cv::Point2d p2)
{
  return (abs(p1.x - p2.x) + abs(p1.y - p2.y)) * scale_;
}

double map::dtn_dorm2(cv::Point2d p1, cv::Point2d p2)
{
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2)) * scale_;
}

map::~map() {}

void map::gen_sps(void)
{
  if (l_pos == m_pos and abs(angle - l_angle) < 15)
  {
    return;
  }
  else
  {
    l_angle = angle;
    for (size_t i = 0; i < 9; i++)
    {
      sps[i] = gen_sp((m_pos + cv::Point2d(-1 + i % 3, -1 + i / 3)), angle, cost_map);
    }
  }
}

mp::SP gen_sp(const cv::Point2d pos, const float &angle, const vector<vector<mp::MP>> &map_)
{
  auto r = cv::Rect(cv::Point2d(0, 0), cv::Point2d(map_.size() - 1, map_[0].size() - 1));
  if (!r.contains(pos))
  {
    return mp::SP;
  }
  if (map_[pos.y][pos.x] != 0)
  {
    return mp::SP;
  }
}