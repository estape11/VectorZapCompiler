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

[=, a, 0]		% Stores the base address
[=, b, 6]		% Stores the xor key

#for (1250)

[=:, A, a]		% Loads the data over the vector A
[((, B, A, b]	% Circular shit over the pixels
[:=, B, a]		% Store the vector in memory
[+, a, a, 2]	% Increment the address by 2

#end