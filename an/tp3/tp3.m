# ROUSSEL Hugo
[signal, fs] = audioread("P2.5s.wav");
ss = signal(2600:3623);

function res = autoCorr(X, t)
  accu = 0;
  for i = 1:(length(X)-t)
    accu += X(i).*X(i+t);
  end
  res = (1/(length(X)-t))*accu;
endfunction

function res = autoCorr_fen(X, fs)
  y = [];
  for t = 0:(fs/50)
    y = [y; autoCorr(X, t)];
  end
  res = y;
endfunction

figure;
subplot(2,1,1);
plot(ss);
subplot(2,1,2);
plot(autoCorr_fen(ss, fs));

function res = F0_fen(X, fs)
  y = autoCorr_fen(X, fs);
  [val, index] = max(y((fs/500):(fs/50)));
  res = fs/(index+(fs/500)-1);
endfunction

F0 = F0_fen(ss, fs)

function res = F0_glissant(signal, fs, taille_f, intervalle_ms)
  intervalle = floor(fs*(intervalle_ms/1000));
  y = [];
  for i = 1:intervalle:length(signal)-taille_f+1
    f = signal(i:i+taille_f-1);
    y = [y; F0_fen(f, fs)];
  endfor
  res = y;
endfunction

plot(F0_glissant(signal, fs, 1024, 10))
