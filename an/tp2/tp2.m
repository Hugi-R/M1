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


