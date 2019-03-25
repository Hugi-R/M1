# ROUSSEL Hugo

function res = convolution(b, a)
  ra = a(end:-1:1, end:-1:1);
  z = zeros(size(ra)(1)+size(b)(1)-1, size(ra)(2)+size(b)(2)-1);
  for r = size(ra)(1):size(b)(1)-size(ra)(1)
    for l = size(ra)(2):size(b)(2)-size(ra)(2)
      #ra
      #b(r:r+size(ra)(1)-1, l:l+size(ra)(2)-1)
      #sum(ra .* b(r:r+size(ra)(1)-1, l:l+size(ra)(2)-1))
      z(r,l) = sum(sum(ra .* b(r:r+size(ra)(1)-1, l:l+size(ra)(2)-1)));
    endfor
  endfor
  res = z;
endfunction
