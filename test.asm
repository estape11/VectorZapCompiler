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


#for(10)
[+, a, a, 1]
#end

#for(2)
[=:, A, a]
[+, a, a, 1]
[+, B, A, A]
#end

[#]
[@]
[_]

[=:, A, a]
[+, a, a, 1]
[+, B, A, A]