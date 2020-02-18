function  z = exp(x)
%EXP  Exponential with accurate argument reduction.
%   Y = EXP(X) overrides the built-in EXP(X) on machines where the
%   manufacturer-supplied math library does a poor argument reduction.
%   Store this M-file in a new directory, ../toolbox/matlab/elfun/@double.

%   If ln2hi + ln2lo were to be computed in extended precision,
%   it would equal log(2) to about 20 significant digits.
    ln2hi = 355/512;
    ln2lo = -2.1219444005469058277e-4;

%   Separate real and imaginary parts.
    y = imag(x);
    x = real(x);

%   Argument reduction.
%   n = round(x/log(2))
    n = round(1.44269504088896340736*x);
    f = x - n*ln2hi - n*ln2lo;

%   If n is not too large, then -log(2)/2 <= f <= log(2)/2
%   and exp(f) can be computed accurately by the builtin exp.
    z = pow2(builtin('exp',f),n);

%   In n is large, the result overflows or underflows.
    z(n > 1024) = Inf;
    z(n < -1074) = 0;

%   Process any imaginary part.
    if any(y ~= 0)
      y = mod(y,2*pi);
      z = z .* (cos(y) + i*sin(y));
    end


