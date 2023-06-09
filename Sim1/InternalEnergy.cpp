//Compilar como 'g++ InternalEnergy.cpp -lgsl -lgslcblas'
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <gsl/gsl_integration.h>

double f(double x, void * params) //Función a integrar
{
  double f=std::pow(x,3)/(std::exp(x)-1);
  return f;
}

int main(void)
{
  gsl_integration_workspace * w = gsl_integration_workspace_alloc (10000);
  double result, error;

  //Cte de Planck reducida, cte de Boltzmann, # de Avogadro, densidad del Cu(kg/m^3),...
  //...,módulo de Young (N/m^2), Peso molecular del Cu (kg/mol)
  const double hbar=1.054e-34,kB=1.38e-23, NA=6.022e23, rho=8890.0, Y=76.0e9, Mw=63.456e-3;
  //velocidad del sonido en el Cu
  double v=std::sqrt(Y/rho);
  //Cociente N/V
  double NV=rho*NA/Mw;
  //Temperatura de Debye
  double Theta=hbar*v*std::cbrt(6*M_PI*M_PI*NV)/kB;
  
  gsl_function F;
  F.function = &f;
  
  std::ofstream fout;
  fout.open("DebyeCu.txt");
  for (int t=10; t<400;t+=5)
    {
      double U,Ularge,Ulow;
      double T=1.0*t;
      //Ejecución del algoritmo para el cálculo de la integral
      gsl_integration_qags (&F, 0, Theta/T, 0, 1e-8,10000, w, &result, &error);
      //Cálculo de la U
      U=9*T*kB*NA*std::pow(T/Theta, 3)*result;
      //Cálculo de la aproximación para T de gran magnitud
      Ularge=3*NA*kB*T*(1-3*Theta/(8*T));
      //Cálculo de la aproximación para T que tiende a 0
      Ulow=3*std::pow(M_PI*T/Theta,4)*NA*kB*Theta;
	fout <<T<<"\t"<<U<<"\t"<<Ularge<<"\t"<<Ulow<<std::endl;
    }
  fout.close();
  return 0;
}
