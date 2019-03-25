
# I
function res = gen_sinus(time, fe, f0, A)
  t = 0:(1/fe):time;
  res = A*sin(2*pi*f0*t);
endfunction

fe = 8000;
A = 0.8

silence = (0:(1/fe):0.1)*0;

DO3 = gen_sinus(1, fe, 264, A);
MI3 = gen_sinus(1, fe, 330, A);
SOL3 = gen_sinus(1, fe, 396, A);
DO4 = gen_sinus(1, fe, 528, A);

S1 = [ DO3 silence MI3 silence SOL3 silence DO4 ]

#plot(S1);

noise = (-0.4*rand(size(S1)))+0.2;
#plot(noise)

S2 = S1 + noise;
#plot(S2)

# II
#spec = spectro(S1, 1024, 100);
#display_spectro(S1, spec);
specgram(S1, 100, fe, 1024, 512);
specgram(S2, 100, fe, 1024, 512);

# III
# G, f#, d#, a, g#, e, g#, c.
g = gen_sinus(0.3, fe, 392, A);
fd = gen_sinus(0.3, fe, 369.99, A);
dd  = gen_sinus(0.3, fe, 311.13, A);
a = gen_sinus(0.3, fe, 440, A);
gd  = gen_sinus(0.3, fe, 415.30, A);
e  = gen_sinus(0.3, fe, 329.63, A);
c  = gen_sinus(0.3, fe, 261.63, A);

sig = [g fd dd a gd e gd c];
specgram(sig, 100, fe, 1024, 512);


[audio, fs] = audioread("diner.wav");
specgram(audio, 100, fs, 1024, 512);

#EVAL
# sol3 la3 si3 sol3 la3 silence la3 si3 do4 silence do4 si3 silence si3 sol3 la3 si3 sol3 la3 silence la3 si3 do4 re4 sol3 sol3
t_note = 0.5
DO3 = gen_sinus(t_note, fe, 262, A);
MI3 = gen_sinus(t_note, fe, 330, A);
SOL3 = gen_sinus(t_note, fe, 392, A);
LA3 = gen_sinus(t_note, fe, 440, A);
SI3 = gen_sinus(t_note, fe, 494, A);
DO4 = gen_sinus(t_note, fe, 523, A);
RE4 = gen_sinus(t_note, fe, 587, A);

melo = [SOL3 LA3 SI3 SOL3 silence LA3 SI3 DO4 silence DO4 SI3 silence SI3 SOL3 LA3 SI3 SOL3 LA3 silence LA3 SI3 DO4 RE4 SOL3 SOL3];

wavwrite(melo, fe, "melo.wav");

specgram(melo);




