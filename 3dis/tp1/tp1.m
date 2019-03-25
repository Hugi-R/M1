#ROUSSEL Hugo

[signal,fs] = audioread("diner.wav") ;

info = audioinfo("diner.wav") ;

# fe : 22050
# quantification : 16 bit 
# canaux : 1

first10 = signal(find(signal, 10));

plot(first10)
hold on;
plot(first10, 'x')
hold off;

signal_int = signal*2^15;

img=imread('photo.jpg');
iminfo = imfinfo('photo.jpg');
image(img);
# 595*900, 3 couleurs, 8 bits par couleur

img2 = img(:,:,1);
image(img2)

function res = sous_quantifier(signal, bit)
  res = (round(signal*(2^(bit-1))))/(2^(bit-1));
endfunction

s = sous_quantifier(signal, 4);

function res = sous_echantillonage(signal, x)
  res = signal(1:x:end);
endfunction

s2 = sous_echantillonage(signal, 2);

function res = n_bit_fort(img, n)
  res = (img/2^(8-n))*2^(8-n);
endfunction

i = n_bit_fort(img, 2); 
image(i)

im = imread("2CV.jpg");
im2 = n_bit_fort(im, 2);
imwrite(im2, "2CV_2bit.jpg")
#imshow(im2);
