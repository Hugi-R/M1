# ROUSSEL Hugo

# I
# 1
img = imread("lena.jpg");
imshow(img)

fpb = 1/16 * [1 2 1 ; 2 4 2 ; 1 2 1];

im_fpb_perso = convolution(img, fpb);
imshow(uint8(im_fpb_perso))

im_fpb = conv2(img, fpb);
imshow(uint8(im_fpb))

# 2
#on utilise conv2 car convolution est trop lent
fph = [-1 -1 -1 ; -1 9 -1 ; -1 -1 -1]
im_fph = conv2(img, fph);
imshow(im_fph)

# le fpb floute l'image, et le fph garde les hautes fréquence, càd les changements
# brusque de d'intensité, et donc garde les contours.

# II
# 1
[audio, fs] = audioread("vinyle.wav");
specgram(audio)

ft_audio = fft(audio);
new_audio = abs(ifft(ft_audio(1:4000), length(audio));