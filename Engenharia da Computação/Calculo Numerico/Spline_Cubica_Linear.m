%Spline Cubica - Abel Antonio Ronsoni

clear all
%clc

%x = [1 1.2 1.4 1.7 1.8];
%y = [0.210 0.320 0.480 0.560 0.780];

%x = [-1 -0.75 -0.6 -0.5 -0.3 0 0.2 0.4 0.5 0.7 1];
%y = [2.05 1.153 0.45 0.4 0.5 0 0.2 0.6 0.512 1.2 2.05];

x = input('Vetor com os valores de x: ');
y = input('Vetor com os valores de f(x): ');
n=length(x)-2;

A = zeros(n,n);

h = inline('x(k)-x(k-1)');

A(1,1) = 2*(h(2)+h(3));
A(1,2) = h(3);
if n>1
  A(n,n-1) = h(n);
  A(n,n) = 2*(h(n)+h(n));
end

for i=2:1:(n-1)
  A(i,i-1) = h(i);
  A(i,i) = 2*(h(i)+h(i+1));
  A(i,i+1) = h(i+1);
end

for i=1:n
  B(i) = 6*(((y(i+2)-y(i+1))/h(i+2))-((y(i+1)-y(i))/h(i+1)));
end

B=B';
g=A\B;

for i=n:-1:1
  g(i+1)=g(i);
end

g(1) = 0;
g(n+2) = 0;

a = inline('(g(k+1)-g(k))/(6*h(k+1))');
b = inline('g(k+1)/2');
c = inline('((y(k+1)-y(k))/h(k+1))+(((2*h(k+1)*g(k+1))+(g(k)*h(k+1)))/6)');
d = inline('y(k+1)');

s = inline('((a(k)*(z-x(k+1)).^3)+(b(k)*(z-x(k+1)).^2)+(c(k)*(z-x(k+1)))+d(k))');
s_lin = inline('((y(k)*((x(k+1)-z)/h(k+1)))+(y(k+1)*((z-x(k))/(h(k+1)))))');

cont=1;
for i=1:(n+1)
  for j=x(i):0.001:x(i+1)
    eixo_x(cont) = j;
    eixo_y(cont) = s(i,j);
    lin_x(cont) = j;
    lin_y(cont) = s_lin(i,j);
    cont = cont+1;
  end
end

figure(1);
plot(eixo_x,eixo_y,"r-:;Spline Cubica;","linewidth",1,lin_x,lin_y,"--;Spline Linear;","linewidth",1);
grid;
title('Spline Cubica x Spline Linear - ');
xlabel('x');
ylabel('f(x)');