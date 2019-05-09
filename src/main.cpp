//******************************************************
//
//			Instituto Tecnológico de Costa Rica
//				Computer Engineering
//
//		Programmer: Esteban Agüero Pérez (estape11)
//		Language: C++
//		Version: 1.0
//		Last Update: 08/05/2019
//
//				Computer Architecture II
//			Professor. Jeferson González Gómez
//
//******************************************************
#include <stdio.h>
#include <stdlib.h>
#include <InstructionHelper.hpp>

int main(int argc, const char* argv[]){
	std::string line;
	// Hard coded path
	std::ifstream memFile ("/home/estape/Documents/ArquitecturaComputadoresII/ProyectoII/VectorZapCompiler/test.asm");
	int index = 0;
	std::vector<std::vector<std::string>> lines;
	if (memFile.is_open()){
		while (getline(memFile,line)){
			if (InstructionHelper::IsPragma(line)){
				printf("IsPragma\n"); // Not handled yet

			} else if (!InstructionHelper::IsComment(line) && line != ""){
				bit *t = InstructionHelper::GetInstructionBinary(line);
					if (t!=NULL){
						BaseHelper::PrintBin(t, 32);
					}
			}
		}
		memFile.close();
	}
	
	printf("Completed \u26A1\n");
	return 0;

}