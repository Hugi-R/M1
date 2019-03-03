pkg load signal

[signal,fs] = audioread("parole.wav");
info = audioinfo("parole.wav");
plot(signal);
taille = size(signal)(1);
minmax = [min(signal),max(signal)];
signal_int = signal*2^15;
duree = taille/fs;
specgram(signal);
portion = signal(11300:12323);
plot(portion);
zero = signal(int16(0.530*fs):int16(0.920*fs));
zero = zero*5;
signal_nobip = signal(int16(0.3*fs):end);

# partie 2
[music,fsm] = audioread("musique.wav");
info_m = audioinfo("musique.wav");
#fe = 44100 Hz, quanti 16 bit
plot(music); #une seule note, freq elevee
#freq : 100 samples, f = 44100/100 = 440 Hz => La
ft = abs(fft(music));
plot(ft);
# on voit un pic à l'abscisse 1320, 1 d'abscisse = 44100/132301 = 0.3333, donc freq = 440 Hz
freq = (fsm/size(music)(1))*1320
