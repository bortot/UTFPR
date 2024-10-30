#Comparacao metodos integracao numerico

clear all

f = input('Digite a funcao: ',"s");
a = input('Intervalo inferior: ');
b = input('Intervalo superior: ');
n = input('n: ');

f = inline(f);
h = (b-a)/n;

#=============================================#
#Regra dos Trapezios

R = 0;

for i=(a+h):h:(b-h)
  R = R+f(i);
end

trapezio = (h/2)*(f(a)+f(b)+2*R);

#=============================================#
#1/3 Simpson

j = 0;

for i=(a+h):h:(b-h)
  j = j+1;
  R(j) = f(i);
end

soma=0;

for i=1:2:j
  soma = 4*R(i)+soma;
end

for i=2:2:j
  soma = 2*R(i)+soma;
end

simpson = (h/3)*(soma+f(a)+f(b));

#=============================================#
#Quadratura Gaussiana

dx = 1; g = @(y) y;
t0 = -sqrt(3)/3; t1 = sqrt(3)/3; 

if a!=-1 || b!=1
  g = @(y) 0.5*(a+b+(y*(b-a)));
  dx = (b-a)/2;
end

gauss = dx*(f(g(t0))+f(g(t1)));

printf("\nTrapezio Repetido:\t %f\n",trapezio);
printf("1/3 Simpson Repetido:\t %f\n",simpson);
printf("Quadratura Gaussiana:\t %f\n",gauss);