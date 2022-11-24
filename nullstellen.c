#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double f1(double x)
{
  //#  return /* Hier f_1(x) */;
  double out = x * x * x - 2 * x + 2;
  return out;
}

double df1(double x)
{
  return 3 * x * x - 2;
}

double f2(double x)
{
  double out = sin(M_PI * x / 2.0) - cos(x * M_PI) * exp(-3.0 * x);
  return out;
}

double df2(double x)
{ // Note: Wolfram alpha confirms the correct result for the derivative and h = 1e-12 seems to be sufficient
  double h = 1e-12;
  double out = (f2(x + h) - f2(x - h)) / (2.0 * h);
  return out;
}

double Bisektion(double (*f)(double), double xa, double xb)
{
  double m; // Nullstelle
  // 1) Initialisierung
  double x_1 = xa;
  double x_2 = xb;
  double f_1 = f(x_1);
  double f_2 = f(x_2);
  double delta = 1e-12;

  double x_3;
  double f_3;
  // 2) Iteration
  int i = 1;

  while (fabs(x_1 - x_2) > delta)
  {
    x_3 = 0.5 * (x_1 + x_2);
    f_3 = f(x_3);
    if (f_3 * f_2 <= 0.0)
    {
      x_1 = x_3;
      f_1 = f_3;
    }
    else
    {
      x_2 = x_3;
      f_2 = f_3;
    }
    i = i + 1;
  }
  m = x_3;
  // Kopfzeile für die Ausgabe
  printf("x1: %.16f                 x2: %.16f                 f1: %.16f          f2: %.16f\n", x_1, x_2, f_1, f_2);
  return m; // Rückgabe der gefundenen Nullstelle
}

double Sekanten(double (*f)(double), double x0, double x1)
{
  // Initialisierung und erste Iteration
  double delta = 1e-12;
  double x2 = x0 - f(x0) * (x1 - x0) / (f(x1) - f(x0));
  int maxItr = 1000;
  int i = 0;
  while (fabs(x2 - x1) >= delta)
  {
    x0 = x1;
    x1 = x2;
    x2 = x0 - f(x0) * (x1 - x0) / (f(x1) - f(x0));
    i = i + 1;
    if (i >= maxItr)
    {
      return x2;
    }
  }
  return x2;
  //
}

double Newton(double (*f)(double), double (*dfdx)(double), double x0)
{ // Initialisierung
  double delta = 1e-12;
  double x1;
  int maxIter = 1000;
  // Iteration
  for (int itr = 1; itr <= maxIter; itr++)
  {
    x1 = x0 - f(x0) / dfdx(x0);
    if (fabs(x1 - x0) < delta)
    {
      return x1;
    }
    x0 = x1;
  }
}

int main()
{
  double result;

  // Aufgabe 1
  printf("\n\n---- AUFGABE 1: Polynom ---- \n");
  printf("\n\nBisektion\n --- \n");
  result = Bisektion(f1, -3.0, -0.5);
  printf("Nullstelle Bisektion: %.14lf\n", result);

  printf("\n\nSekanten\n --- \n");
  result = Sekanten(f1, -3.0, -0.5);
  printf("Nullstelle Sekanten: %.14lf\n", result);

  printf("\n\nNewton\n --- \n");
  result = Newton(f1, df1, -1.5);
  printf("Nullstelle: %.14lf\n", result);

  // Aufgabe 2
  printf("\n\n---- AUFGABE 2: Transzendente Gleichung ---- \n");

  printf("\n\nBisektion\n --- \n");
  result = Bisektion(f2, -0.5, 3);
  printf("Nullstelle Bisektion: x=%.16lf, f(x)=%.16lf\n", result, f2(result));

  printf("\n\nSekanten\n --- \n");
  result = Sekanten(f2, 0, 1);
  printf("Nullstelle Sekanten:  x=%.16lf, f(x)=%.16lf\n", result, f2(result));

  printf("\n\nNewton\n --- \n");
  result = Newton(f2, df2, 0.9);
  printf("Nullstelle Newton:    x=%.16lf, f(x)=%.16lf\n", result, f2(result));
  return 0;
}
