/*
 * @Author: 李龙 
 * @Date: 2022-01-27 15:35:21 
 * @Last Modified by: 李龙
 * @Last Modified time: 2022-02-05 16:47:11
 */
#include<position.h>

position::position(bool show, string com_path): show_map(show),lidar(com_path)
{

}

position::~position()
{
  
}

void position::update(void){
  lidar_mtx.lock();
  
  lidar_mtx.unlock();
}