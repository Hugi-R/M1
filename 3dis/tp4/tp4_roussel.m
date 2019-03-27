#ROUSSEL Hugo

1+1 #file not starting with a function, for whatever reason

# I
function res = P(u, p0, p1, t0, t1)
  res = (((u-1)^2) * (2*u+1))*p0 + ((u*u) * (3-2*u))*p1 + (u*(u-1)^2)*t0 + ((u*u)*(u-1))*t1;
endfunction


X = [];
Y = [];
for u = 0:0.01:1
  X = [X; P(u, 50, 150, -180, -5)];
  Y = [Y; P(u, 50, 50, 400, 100)];
endfor

#plot(X,Y)


# II

function res = B(u, n, k)
  res = nchoosek(n, k)*(u^k)*((1-u)^(n-k));
endfunction

function res = b(u, P)
  n = length(P);
  sum = 0;
  for j = 0:(n-1)
    sum = sum + B(u, n-1, j)*P(j+1);
  endfor  
  res = sum;
endfunction

function res = bezier(L, pas)
  figure;
  hold on;
  for i = 1:2:size(L)(1)
    X = [];
    Y = [];
    for u = 0:pas:1
      l1 = L(i,:)(find(L(i,:)));
      l2 = L(i+1,:)(find(L(i+1,:)));
      X = [X b(u, l1)];
      Y = [Y b(u, l2)];
    endfor
    plot(X,Y)
  endfor
  hold off;
endfunction

L = [ 2 1 4 4 5 6 6 9 8 ; 
     3 2 1 7 9 7 1 2 3];
     
#bezier(L, 0.01);

A = [ 2 1 4 4 5 6 6 9 8 ;  
      3 2 1 7 9 7 1 2 3 ;  
      2 1 9 8 0 0 0 0 0 ;  
      5 4 5 4 0 0 0 0 0];
      
bezier(A, 0.01);
bezier(A, 0.1); # la courbure disparait, les segment sont apparent

H = [ 3 2 4 3 ;
      3 2 7 6 ;
      5 4 6 5 ;
      3 2 7 6 ;
      2 1 7 6 ;
      5 4 5 4 ];
bezier(H, 0.01);

