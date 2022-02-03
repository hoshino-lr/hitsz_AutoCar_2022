/*
 * @Author: 李龙 
 * @Date: 2022-01-29 16:14:15 
 * @Last Modified by: 李龙
 * @Last Modified time: 2022-01-29 22:42:54
 */
#include <string>
#include <vector>
#include <map>
using namespace std;
class designtree
{
private:
  //属性个数，不包括类别
  int attribute_Num;
  //本节点的属性
  string node_Attribute;
  //数据集属性
  vector<string> data_Attribute;
  //本节点的所有属性值
  vector<string> node_AttValues;
  //剩余属性集
  vector<string> remain_Attributes;
  //子节点,本节点属性对应的属性值与子节点地址进行一一映射
  //为空说明该节点为叶节点
  map<string, designtree *> childNode;
  //样本集合表
  map<string, vector<int>> MyDateTable;
  //定义各属性对应的属性值
  map<string, vector<int>> data_AttValues;

public:
  designtree(string file_name);
  ~designtree();
  //生成子节点
  void generate_ChildNode();
  //计算信息增益 寻找最优划分属性
  string findBestAttribute();
  //计算信息熵
  double calc_Entropy(map<string, vector<string>> temp_Table);
  //设置节点的属性
  void set_NodeAttribute(string atttribute);
  //根据所给属性，对数据进行分类
  string findClass(vector<string> attributes);
};

designtree::designtree(/* args */)
{
}

designtree::~designtree()
{
}
