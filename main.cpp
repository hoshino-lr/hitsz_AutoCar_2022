/*
 * @Author: 李龙 
 * @Date: 2022-01-27 15:01:06 
 * @Last Modified by:   李龙 
 * @Last Modified time: 2022-01-27 15:01:06 
 */

#include <csignal>
#include <opencv2/opencv.hpp>

//检测关闭程序键盘中断
static volatile int keepRunning = 1;

void sig_handler(int sig) {
  if (sig == SIGINT) {
    keepRunning = 0;
  }
}

int main(int argc, char **argv) {
  signal(SIGINT, sig_handler);

}