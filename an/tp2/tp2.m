# ROUSSEL Hugo

#1
[signal, fs] = audioread("P2.5s.wav");
signal = signal(2600:3623);

figure;
subplot(5,1,1);
t = (0:length(signal)-1)/fs;
plot(t, signal);
legend("Signal");
ylabel("Amplitude");
xlabel("Temps (s)");
subplot(5,1,2);
h = hamming(1024);
plot(h);
title("Hamming");
subplot(5,1,3);
signalHamming = signal .* h;
plot(signalHamming);
title("Signal avec Hamming");
subplot(5,1,4);
plot(abs(fft(signal)(1:end/2)));
title("FFT signal");
subplot(5,1,5);
plot(abs(fft(signalHamming)(1:end/2)));
title("FFT signal hamming");

#figure;
#plot(abs(fft(signal)(1:end/2)));
#figure;
#plot(abs(fft(signalHamming)(1:end/2)));

#2
#[signal, fs] = audioread("parole.wav");
#signal = signal(11060:11571);
[signal, fs] = audioread("P2.5s.wav");
signal = signal(2600:3623);

figure;
subplot(5,1,1);
t = (0:length(signal)-1)/fs;
plot(t, signal);
legend("Signal");
ylabel("Amplitude");
xlabel("Temps (s)");
subplot(5,1,2);
h = hamming(length(signal));
signalHamming = signal .* h;
plot(signalHamming);
title("Signal avec Hamming");
subplot(5,1,3);
spectre = fft(signalHamming);
plot(abs(spectre(1:end/2)));
title("spectre signal");
subplot(5,1,4);
logSpectre = log(spectre);
plot(abs(logSpectre(1:end/2)));
title("log spectre signal");
subplot(5,1,5);
cepstre = ifft(logSpectre);
plot(abs(cepstre(1:end/2)));
title("Cepstre");

figure;
plot(abs(cepstre(1:end/2)));

[val, index] = max(abs(cepstre(35:350)));
T0 = index+35-1
F0 = fs/T0

#3
canaux(spectre, fs, 24);

#4
function res = energie(signal, taille_f)
  # Calcul d'énergie d'un signal avec une fenetre glissante de taille taille_f
  y = [];
  for i = 1:floor((taille_f/2)):length(signal)-taille_f+1
    f = signal(i:i+taille_f-1);
    y = [y; sum(f.^2)/length(f)];
  end
  res = y;
endfunction

function plot_energie_ms(signal, fs, t_ms)
  taille_f = floor(fs*(t_ms/1000));
  t = (0:taille_f:length(signal)-(1*taille_f+1))/fs;
  e = energie(signal, taille_f*2);
  plot(t, e);
endfunction

figure;
subplot(2,1,1);
t = (0:length(signal)-1)/fs;
plot(t, signal);
legend("Signal");
ylabel("Amplitude");
xlabel("Temps (s)");
subplot(2,1,2)
plot_energie_ms(signal, fs, 10)
#On remarque des piques sur les zones parlées

#5
function res = zcr(signal)
  y = 0;
  for i = 2:length(signal)
    if sign(signal(i-1)) != sign(signal(i))
      y = y + 1;
    end
  end
  res = y/length(signal);
endfunction

function res = zcr_glissant(signal, taille_f, recouvrement)
  # Calcul du zcr d'un signal avec une fenetre glissante de taille taille_f
  # avec le recouvrement recouvrement.
  y = [];
  for i = 1:floor((taille_f-recouvrement)):length(signal)-taille_f+1
    f = signal(i:i+taille_f-1);
    y = [y; zcr(f)];
  end
  res = y;
endfunction

function plot_zcr_ms(signal, fs, t_ms)
  taille_f = floor(fs*(t_ms/1000));
  t = (0:taille_f:length(signal)-(1*taille_f+1))/fs;
  z = zcr_glissant(signal, taille_f*2, taille_f);
  plot(t, z); 
endfunction

figure;
subplot(2,1,1);
t = (0:length(signal)-1)/fs;
plot(t, signal);
legend("Signal");
ylabel("Amplitude");
xlabel("Temps (s)");
subplot(2,1,2)
plot_zcr_ms(signal, fs, 10);
#On remarque les piques dans les zones sans paroles
#détecter les zones parlés

