//******************************************************
//
//			Instituto Tecnológico de Costa Rica
//				Computer Engineering
//
//		Programmer: Esteban Agüero Pérez (estape11)
//		Language: C++
//		Version: 1.0
//		Last Update: 12/05/2019
//
//				Computer Architecture II
//			Professor. Jeferson González Gómez
//
//******************************************************
#include <stdio.h>
#include <stdlib.h>
#include <InstructionHelper.hpp>
#include <string>

#define LENGTH 31

std::vector<int> pipeVecReg = {-1, -1};

void UpdateVecReg(int reg){
	pipeVecReg.pop_back(); // out from pipe
    pipeVecReg.insert(pipeVecReg.begin(), reg);

}

int IsInVegReg(int reg){
	int temp = -1;

	for (int i = 0 ; i < pipeVecReg.size() ; i++){
		if (pipeVecReg[i] == reg){
			temp = pipeVecReg.size() - i;
			break;
		}

	}
	return temp;

}

int main(int argc, const char* argv[]){
	printf(">> \u26A1 Compilation started \u26A1\n");

	bit *pNop = BaseHelper::DecimalToBin(0, 32); // to have a nop
	std::string inFile ("test.asm"); // default file
	std::string outFile ("test.bin"); // default file

	std::vector<std::string> lines; // stores the lines readed
	std::string line; // temp line readed

	if ( argc > 1 ) {
		inFile = argv[1];
		if (argc > 2) {
			outFile = argv[2];

		} else {
			printf(">> Warning: Default Output file\n");
		}

	} else {
		printf(">> Warning: Default Input/Output file\n");
	}

	std::ifstream memFileIn (inFile); // default file
	if (memFileIn.is_open()){

		while (getline(memFileIn,line)){
			if (!InstructionHelper::IsComment(line) && line != ""){
				lines.push_back(line);

			}
			
		}
		memFileIn.close();

	} else {
		printf("## Error: Input file not found\n");
		return -1;
	}

	int pragmaStart = -1;
	int pragmaEnd = -1;
	int pragmaCount = -1;
	bool pragmaPresent = false;

	int validLines = 0;

	std::cout<< ">>\n>> \t"<<inFile<<" >> "<<outFile<<"\n>>\n";

	// Open the file
	std::ofstream memFile (outFile);
	
	for (int i = 0 ; i < lines.size() ; i++){
		//printf(">> i = %d\n",i);
		//std::cout<< lines[i] <<std::endl;
		if (InstructionHelper::IsPragma(lines[i])){

			if (pragmaStart == -1){
				pragmaStart = i; // save the index where the pragmaStar stars
				pragmaCount = InstructionHelper::GetPragmaValue(lines[i]);
				pragmaPresent = true;

			} else {
				if (pragmaEnd == -1) {
					pragmaEnd = i;
					pragmaCount--;

				}

			}

			if (pragmaPresent) {
				if (i == pragmaEnd && pragmaCount > 0) {
					i = pragmaStart; // restarts
					pragmaCount--;

				} else if(i == pragmaEnd && pragmaCount == 0){ // pragma finished
					pragmaStart = -1;
					pragmaEnd = -1;
					pragmaCount = -1;
					pragmaPresent = false;

				}

			}

		} else {
			bit *pTemp = InstructionHelper::GetInstructionBinary(lines[i]);
			if (pTemp!=NULL){
				if (pTemp[1] == 1 && pTemp[0] == 0){
					int ra = BaseHelper::BinToDecimal(pTemp+13,4);
					int rb = BaseHelper::BinToDecimal(pTemp+17,4);

					// NOPS
					int nops = IsInVegReg(ra);
					if (nops != 0){
						for (int i = 0 ; i< nops ; i++){
							//BaseHelper::PrintBin(pNop, 32);
							validLines++;
							for (int i = LENGTH; i >= 0; i--){
								memFile << (int) pNop[i];

							}
							memFile << "\n";

						}
						
					} else {
						nops = IsInVegReg(rb);
						if (nops != 0) {
							for (int i = 0 ; i< nops ; i++){
								//BaseHelper::PrintBin(pNop, 32);
								validLines++;
								for (int i = LENGTH; i >= 0; i--){
									memFile << (int) pNop[i];

								}
								memFile << "\n";

							}

						}
					}

					//BaseHelper::PrintBin(pTemp, 32);
					//BaseHelper::PrintBin(pTemp, 32);
					UpdateVecReg(BaseHelper::BinToDecimal(pTemp+9,4));
					validLines+=2;
					for (int i = LENGTH; i >= 0; i--){
						memFile << (int) pTemp[i];

					}
					memFile << "\n";
					for (int i = LENGTH; i >= 0; i--){
						memFile << (int) pTemp[i];

					}
					memFile << "\n";

				} else if (pTemp[1] == 1 && pTemp[0] == 1){
					//BaseHelper::PrintBin(pTemp, 32);
					//BaseHelper::PrintBin(pTemp, 32);
					UpdateVecReg(BaseHelper::BinToDecimal(pTemp+9,4));
					validLines+=2;
					for (int i = LENGTH; i >= 0; i--){
						memFile << (int) pTemp[i];

					}
					memFile << "\n";
					for (int i = LENGTH; i >= 0; i--){
						memFile << (int) pTemp[i];

					}
					memFile << "\n";

				} else {
					//BaseHelper::PrintBin(pTemp, 32);
					UpdateVecReg(-1);
					validLines++;
					for (int i = LENGTH; i >= 0; i--){
						memFile << (int) pTemp[i];

					}
					memFile << "\n";

				}
			}
		}

	}
	memFile.close();
	printf(">> Total lines = %d\n", validLines);
	printf(">> \u26A1 Completed \u26A1\n");
	return 0;
}