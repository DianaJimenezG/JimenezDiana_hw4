#define _USE_MATdt_DEFINES
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define g 10.0
#define m 0.2
#define c 0.2
#define dt 0.00001
#define tiempo 7.0

double ddx(double vx);
double ddy(double vy);
double ddvx(double vx, double vy);
double ddvy(double vx, double vy);

int main(){

}

double ddx(double vx){
  return vx;
}

double ddy(double vy){
  return vy;
}

double ddvx(double vx, double vy){
  return -c*sqrt(vx*vx+vy*vy)*vx/m;
}

double ddvy(double vx, double vy){
  return -g-c*sqrt(vx*vx+vy*vy)*vy/m;
}
