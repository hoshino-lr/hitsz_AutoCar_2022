/*
 * @Author: 李龙 
 * @Date: 2022-02-03 12:41:09 
 * @Last Modified by: 李龙
 * @Last Modified time: 2022-02-03 13:11:18
 */
#include <vector>
#include <queue>
#include <data.hpp>

using namespace std;
using namespace mp;
class map
{
private:
  /* data */
  vector<vector<MAP_POINT>> map_points(51, vector<int>(51, 0));

public:
  map(int DEBUG);
  distance_caculate();
  ~map();
};

map::map(/* args */)
{
}

map::~map()
{
}
