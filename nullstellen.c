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
}

double f2(double x)
{
}

double df2(double x)
{
}

double Bisektion(double (*f)(double), double xa, double xb)
{
  double m; // Nullstelle
  // 1) Initialisierung
  double x_1 = xa;
  double x_2 = xb;
  double f_1 = f1(x_1);
  double f_2 = f1(x_2);
  double delta = 1e-12;

  double x_3;
  double f_3;
  // 2) Iteration
  int i = 1;

  printf("x_1: %f \n", x_1);
  printf("x_2: %f \n", x_2);
  printf("%f \n", fabs(x_1 - x_2));

  while (fabs(x_1 - x_2) > delta)
  {
    printf("Iteration Number: %d \n",i);
    printf("x_1: %f \n", x_1);
    printf("x_2: %f \n", x_2);
    printf("f_1: %f \n", f_1);
    printf("f_2: %f \n", f_2);
    x_3 = 0.5*(x_1 + x_2);
    f_3 = f1(x_3);
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
    i = i +1; 
  }
  m = x_3;
  // Kopfzeile für die Ausgabe
  printf("  n:  %.6f                 %.6f                 %.6f          %.6f\n", x_1, x_2, f_1, f_2);
  return m; // Rückgabe der gefundenen Nullstelle
}

double Sekanten(double (*f)(double), double x0, double x1)
{
}

double Newton(double (*f)(double), double (*dfdx)(double), double x0)
{
}

int main()
{
  double result;

  printf("\n\nBisektion\n --- \n");
  result = Bisektion(f1, -3.0, -0.5);
  printf("Nullstelle Bisektion: %.14lf\n", result);

  printf("\n\nSekanten\n --- \n");
  result = Sekanten(f1, -3.0, -0.5);
  printf("Nullstelle Sekanten: %.14lf\n", result);

  printf("\n\nNewton\n --- \n");
  result = Newton(f1, df1, -0.5);
  printf("Nullstelle: %.14lf\n", result);

  return 0;
}
