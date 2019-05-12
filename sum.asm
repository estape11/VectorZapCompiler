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
[=, b, 6]		% To make the mask
[=, c, 20]		% To make the mask
[=, d, 40]		% To make the mask
[=, e, 1260]	% Space to store the temp mask
[=, f, d]		% f = [40, 0, 0, 0] <- MSB
[<<, f, c, 8]	% f = [40, 20, 0, 0]
[<<, f, b, 16]	% f = [40, 20, 6, 0]
[:=, f, e]		% Save the mask
[+, e, e, 1]	% Increment one position
[:=, f, e]		% Save the mask
[-, e, e, 1]	% Restore the address
[=:, C, e]		% Loads the mask into vector C 

#for(1250)

[=:, A, a]		% Loads the data over the vector A
[+, B, A, C]	% Add the mask
[:=, B, a]		% Store the vector in memory
[+, a, a, 2]	% Increment the address by 2

#end