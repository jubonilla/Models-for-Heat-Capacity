#include <array>
#include <cmath>
#include <fstream>

void PrintE(double ExpT[], double ExpCV[]);
void PrintTheo (double N, double thetaE);

int main(void) 
{
  const double thetaE=1305.9;
  const double N=10000.0;
  //Datos del experimento:
  double T_exp[65]={15.94,16.52,17.33,17.75,18.84,19.76,20.49,22.54,23.93,25.71,27.29,29.66,31.88,33.44,36.35,39.98,41.94,43.48,46.70,48.41,51.38,55.20,59.30,63.71,68.45,72.67,77.16,80.94,85.93,89.10,91.27,98.04,100.43,106.63,107.94,113.24,123.10,126.13,133.88,135.51,138.81,147.35,152.75,162.15,178.42,182.80,201.05,213.46,221.31,232.11,252.30,264.70,284.38,335.99,369.58,401.74,468.92,497.76,547.43,623.94,686.32,782.17,829.99,912.82,1003.74};

  double CV_exp[65]={0.001696,0.001872,0.002136,0.002436,0.002779,0.003169,0.003615,0.004551,0.005365,0.006324,0.007961,0.008503,0.01143,0.01262,0.01439,0.01696,0.01935,0.02207,0.02518,0.02872,0.03067,0.03736,0.04404,0.05544,0.06754,0.07961,0.1002,0.1181,0.1393,0.1812,0.2067,0.2281,0.2689,0.3275,0.3736,0.4551,0.5191,0.6535,0.7454,0.7961,0.9081,1.036,1.221,1.393,1.812,2.207,2.436,2.968,3.615,3.861,4.404,5.365,6.535,8.227,9.384,10.7,12.21,13.93,14.87,16.42,18.72,20,20,21.36,21.36};

  PrintE(T_exp, CV_exp);
  PrintTheo(N,thetaE);
  return 0;
  
}

void PrintE(double ExpT[], double ExpCV[])
{
  std::ofstream fout;
  fout.open ("DatosExperimento.txt");
  for (int i=0;i<65;i++)
  {
    fout <<"\t"<<ExpT[i]<<"\t"<<ExpCV[i]<<std::endl;
  }
  fout.close();
}

void PrintTheo (double N, double thetaE)
{
  const double kB=1.380649e-23;
  const double NA=6.022e23;
  std::ofstream fout;
  fout.open ("DatosSimuladosE.txt");
  for (int t=70;t<=1000;t+=5)
  {
    double T=t*1.0;
    fout <<T<<"\t"<<3*NA*kB*std::pow(thetaE/T,2)*std::exp(thetaE/T)/std::pow(std::exp(thetaE/T)-1,2)<<std::endl;
  }
  fout.close();
}
