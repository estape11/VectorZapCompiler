%******************************************************
%
%			Instituto Tecnológico de Costa Rica
%				Computer Engineering
%
%		Programmer: Esteban Agüero Pérez (estape11)
%		Language: VectorZap ASM
%		Version: 1.0
%		Last Update: 09/05/2019
%
%				Computer Architecture II
%			Professor. Jeferson González Gómez
%
%******************************************************

[=, A, 100]
[=, b, 1]							% Scalar assignation
[=, c, 10]							% Scalar assignation
[NOP]
[NOP]
[+, A, Z, c]
[)), e, c, 3]
[((, h, c, 3]
[-, a, c, b]
[=, f, b]							% Scalar assignation
[=, A, B]							% Scalar assignation
[+, a, b, c]						% Scalar add
[+, d, b, 345]						% Scalar add
[+, A, B, C]						% Vector add
[+, A, C, b]						% Scalar add operation over vector

#for 10
[NOP]
[HALT]
#end