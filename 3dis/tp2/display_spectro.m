function out = display_spectro(signal, spectro)

    sr = 8000;
    [ysize, xsize] = size(spectro);
    
    t = linspace(1, length(signal) / sr, xsize);
    freq = linspace(1, sr/2, ysize);

    % affichage
    surf(t, freq, spectro, "EdgeColor", "none");
    axis xy; axis tight; colormap(jet); view(0,90);
end

