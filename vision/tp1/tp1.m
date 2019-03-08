# ROUSSEL Hugo

# Spacial
#2
img=imread('cameraman2.tif');
imshow(img)

# a
fsize = 3; #augmenter ce nombre (taille du filtre) pour augmenter le filtrage
fmoy1 = ones(fsize,fsize)*(1/(fsize*fsize));
im_moy = uint8(conv2(fmoy, img));
imshow(im_moy)

# b
fmoy2 = [1 2 1 ;2 4 2 ;1 2 1] / 16;
im_moy = uint8(conv2(fmoy, img));
imshow(im_moy)

# c
variance = 10^2;
meanValue = 0;
noise = sqrt(variance)*randn(size(img)) + meanValue;
im_noise = double(img) + noise;
imshow(uint8(im_noise))

imshow(uint8(conv2(fmoy1, im_noise)))
#Bruit réduit, mais image floutée
imshow(uint8(conv2(fmoy2, im_noise)))
#Bruit réduit, image peu floutée

#3
img=imread('moon.tif');
imshow(img)

# b
laplacien = [0 1 0; 1 -4 1; 0 1 0];
moon_fl = (conv2(img, laplacien, 'same' ));
imshow(uint8(moon_fl))

# c
imshow(uint8(img - moon_fl))

# d
#laplacien simple : appliquer ce filtre
laplacien_simple = [0 -1 0; -1 5 -1; 0 -1 0]
imshow(uint8(conv2(img, laplacien_simple)))


# Frequentiel
#1
img=imread('cameraman2.tif');
imshow(img)

ft = norm(fft2(img));
plot(ft)