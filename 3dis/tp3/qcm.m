

[audio, fs] = audioread("vinyle.wav");

ft_audio = fft(audio);
new_audio = abs(ifft(ft_audio(1:3000), length(audio)));

audiowrite("res.wav", new_audio, fs)