//Compilar como 'g++ Debye.cpp -lgsl -lgslcblas'
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>

double f(double x, void * params) //Función a integrar
{
  double f=std::exp(x)*std::pow(x,4)/std::pow(std::exp(x)-1,2);
  return f;
}

int main(void)
{
  gsl_integration_workspace * w = gsl_integration_workspace_alloc (10000);
  double result, error;

  //Constantes físicas
  const double kB=1.38e-23, NA=6.022e23;
  double Theta=1706.0;
  
  gsl_function F;
  F.function = &f;
  
  std::ofstream fout;
  fout.open("DatossimuladosD.txt");
  for (int t=10; t<1000;t+=5)
    {
      double CV;
      double T=1.0*t;
      //Ejecución del algoritmo para el cálculo de la integral
      gsl_integration_qags (&F, 0, Theta/T, 0, 1e-9,10000, w, &result, &error);
      //Cálculo de la cv
      CV=9*kB*NA*std::pow(T/Theta, 3)*result;
      fout <<T<<"\t"<<CV<<std::endl;
    }
  fout.close();
  return 0;
}
