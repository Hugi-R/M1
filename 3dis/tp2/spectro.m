function mat_spectro = spectro(signal,taille_fenetre, step)

%Initialisation du compteur de fenêtres 
k = 1;

%Initialisation de la matrice stockant le spectrogramme 
nbCol = floor((length(signal)-taille_fenetre+1) / step); 
mat_spectro = zeros(taille_fenetre/2,nbCol); 

%Calcul du spectrogramme 
for x = 1:step:length(signal) - taille_fenetre
    spectre = abs(fft(signal(x:x+taille_fenetre-1)));
    mat_spectro(:,k)=spectre(1:taille_fenetre/2)';
    
    k = k+1; 
end
