define _USE_MATdt_DEFINES
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
double * RungeKutta(double t_pasado, double x_pasado, double y_pasado, double vx_pasado, double vy_pasado);

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

double * RungeKutta(double t_pasado, double x_pasado, double y_pasado, double vx_pasado, double vy_pasado){
  double k_1_x=ddx(vx_pasado);
  double k_1_y=ddy(vy_pasado);
  double k_1_vx=ddvx(vx_pasado,vy_pasado);
  double k_1_vy=ddvy(vx_pasado,vy_pasado);

  double x_1=x_pasado+(dt/2.0)*k_1_x;
  double y_1=y_pasado+(dt/2.0)*k_1_y;
  double vx_1=vx_pasado+(dt/2.0)*k_1_vx;
  double vy_1=vy_pasado+(dt/2.0)*k_1_vy;
  double k_2_x=ddx(vx_1);
  double k_2_y=ddy(vy_1);
  double k_2_vx=ddvx(vx_1, vy_1);
  double k_2_vy=ddvy(vx_1, vy_1);

  double x_2=x_pasado+(dt/2.0)*k_2_x;
  double y_2=y_pasado+(dt/2.0)*k_2_y;
  double vx_2=vx_pasado+(dt/2.0)*k_2_vx;
  double vy_2=vy_pasado+(dt/2.0)*k_2_vy;
  double k_3_x=ddx(vx_2);
  double k_3_y=ddy(vy_2);
  double k_3_vx=ddvx(vx_2, vy_2);
  double k_3_vy=ddvy(vx_2, vy_2);

  double x_3=x_pasado+dt*k_3_x;
  double y_3=y_pasado+dt*k_3_y;
  double vx_3=vx_pasado+dt*k_3_vx;
  double vy_3=vy_pasado+dt*k_3_vy;
  double k_4_x=ddx(vx_3);
  double k_4_y=ddy(vy_3);
  double k_4_vx=ddvx(vx_3, vy_3);
  double k_4_vy=ddvy(vx_3, vy_3);

  double promedio_k_1=(1.0/6.0)*(k_1_x+2.0*k_2_x+2.0*k_3_x+k_4_x);
  double promedio_k_2=(1.0/6.0)*(k_1_y+2.0*k_2_y+2.0*k_3_y+k_4_y);
  double promedio_k_3=(1.0/6.0)*(k_1_vx+2.0*k_2_vx+2.0*k_3_vx+k_4_vx);
  double promedio_k_4=(1.0/6.0)*(k_1_vy+2.0*k_2_vy+2.0*k_3_vy+k_4_vy);

  static double rk[5];
  rk[0]=t_pasado+dt;
  rk[1]=x_pasado+dt*promedio_k_1;
  rk[2]=y_pasado+dt*promedio_k_2;
  rk[3]=vx_pasado+dt*promedio_k_3;
  rk[4]=vy_pasado+dt*promedio_k_4;

  return rk;
}
