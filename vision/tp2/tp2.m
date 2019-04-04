# ROUSSEL Hugo

img = imread("coat_of_arms.png");

imshow(img);

h = fspecial('average', 21);

i = imfilter(img, h, 'conv', 'circular');

imshow(i);

Ideal = fft2(img);
H = fft2(h, 600, 800);
I = fft2(i);

imagesc(log(abs(fftshift(Ideal))))
imagesc(log(abs(fftshift(H))))
imagesc(log(abs(fftshift(I))))

Id = I/H;
imagesc(abs(ifft(Id)))
# H possède des valeurs très proche de 0

Id = I;
for i = 1:length(Id)
  if H(i) > 0.1
    Id(i) = Id(i)/H(i);
  endif
endfor
imagesc(abs(ifft(Id)))

# deconvwnr not yet implemented in octave