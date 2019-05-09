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

#include <InstructionHelper.hpp>

// Tokens for the instruction translate
std::vector<std::string> static vectorRegisters = {"Z", "A", "B", "C", "D"};
std::vector<std::string> static scalarRegisters = {"z", "a", "b", "c", "d", "e", "f", "g", "h"};
std::vector<std::string> static opTypeA = {"+", "-"};
std::vector<std::string> static opTypeL = {"&", "|", "^", ">>", "<<", "))", "(("};
std::vector<std::string> static opTypeD = {"=", ":=", "=:"};

std::vector<std::string> InstructionHelper::SplitLineByChar(std::string line, char splitChar){
	std::vector<std::string> tempSplit;
	std::string temp = "";

	for (unsigned int i = 0;i <= line.size();i++){
		if (line[i] == splitChar){
			tempSplit.push_back(temp);
			temp = "";

		} else if (line[i] == ']' || i == line.size()){
			tempSplit.push_back(temp);
			temp = "";
			break;

		} else {
			if (line[i] != '[' && line[i] != ' '){
				temp+=line[i];

			}

		}

	}
	return tempSplit;
}

bool InstructionHelper::IsComment(std::string line){
	return line[0] == '%';
}

bool InstructionHelper::IsPragma(std::string line){
	return line[0] == '#';
}

bool InstructionHelper::IsVector(std::string data){
	bool temp = true;
	for ( unsigned int i=0 ; i < data.size() ; i++ ){
		if (!isupper(data[i])){
			temp = false;
			break;
		}

	}
	return temp;

}

bit *InstructionHelper::GetRegister(std::string data){
	int index = -1;
	bit *pTemp = NULL;
	if (IsVector(data)){ // Vector Register
		for ( unsigned int i = 0 ; i < vectorRegisters.size() ; i++){
			if (vectorRegisters[i] == data){
				index = i;
				break;

			}
		}
		
	} else { // Scalar Register
		for ( unsigned int i = 0 ; i < scalarRegisters.size() ; i++){
			if (scalarRegisters[i] == data){
				index = i;
				break;

			}
		}

	}

	if (index != -1){
		pTemp = BaseHelper::DecimalToBin(index, 4);
	}

	return pTemp;

}

bit *InstructionHelper::GetOperation(std::string data){
	int opCode = -1;
	int type = 0;
	bit *pTemp = NULL;
	// Aritmetic Type
	for (unsigned int i = 0 ; i < opTypeA.size() ; i++){
		if (opTypeA[i] == data){
			opCode = i;
			break;

		}

	}

	if (opCode == -1){
		type++;
		// Logical Type
		for (unsigned int i = 0 ; i < opTypeL.size() ; i++){
			if (opTypeL[i] == data){
				opCode = i;
				break;
				
			}

		}

	}

	if (opCode == -1){
		type++;
		// Data Type
		for (unsigned int i = 0 ; i < opTypeD.size() ; i++){
			if (opTypeD[i] == data){
				opCode = i;
				break;

			}

		}

	}

	if (opCode != -1){
		pTemp = BaseHelper::DecimalToBin(type, 7);
		memcpy(pTemp+3, BaseHelper::DecimalToBin(opCode, 4), 4);

	}
	return pTemp;

}

bit *InstructionHelper::GetImmediate(std::string data){
	try{
		int i = std::stoi(data);
		return BaseHelper::DecimalToBin(i, 15);
	}
	catch (std::invalid_argument const &e) {
		return NULL;
	}
}

bit *InstructionHelper::GetMode(std::vector<std::string> splittedInst, bool immediate){
	bit *pTemp = NULL;
	if (splittedInst.size() == 3){
		if (immediate){
			if (IsVector(splittedInst[1])){ // Vector
				pTemp = BaseHelper::DecimalToBin(2, 2);

			} else { // Scalar
				pTemp = BaseHelper::DecimalToBin(1, 2);

			}
		} else {
			if (IsVector(splittedInst[1]) && IsVector(splittedInst[2])){ // Vector - Vector
				pTemp = BaseHelper::DecimalToBin(2, 2);

			} else { // Scalar - Scalar
				pTemp = BaseHelper::DecimalToBin(1, 2);

			}

		}

	} else {
		if (immediate){
			if (IsVector(splittedInst[1]) && IsVector(splittedInst[2])){ // Scalar - Vector
				pTemp = BaseHelper::DecimalToBin(3, 2);

			} else { // Scalar - Scalar
				pTemp = BaseHelper::DecimalToBin(1, 2);

			}

		} else {
			if (IsVector(splittedInst[1]) && IsVector(splittedInst[2]) && IsVector(splittedInst[3])){ // Vector - Vector
				pTemp = BaseHelper::DecimalToBin(2, 2);

			} else if (IsVector(splittedInst[1]) && !IsVector(splittedInst[2]) && IsVector(splittedInst[3])) { // Scalar - Vector
				pTemp = BaseHelper::DecimalToBin(3, 2);

			} else { // Scalar - Scalar
				pTemp = BaseHelper::DecimalToBin(1, 2);

			}

		}

	}

	return pTemp;

}

bit *InstructionHelper::GetInstructionBinary(std::string instruction){
	std::vector<std::string> splittedInst = SplitLineByChar(instruction, ',');
	bit *pBinary = (bit *) malloc(sizeof(bit)*32);
	memset(pBinary, 0, 32);
	if (splittedInst.size() == 1 ){
		if (splittedInst[0] == "HALT"){
			pBinary[1] = 1;
			pBinary[2] = 1;

		} // else NOP already set by memset 

	} else if (splittedInst.size() == 3){ // Assign operation
		bit *pImmediate = GetImmediate(splittedInst[2]);
		bit *pOpCode = GetOperation(splittedInst[0]);
		bit *pMode = NULL;
		bit *pDestReg = NULL;
		bit *pOp1Reg = NULL;
		if (pImmediate == NULL){ // There is no immediate
			pMode = GetMode(splittedInst, false);
			pDestReg = GetRegister(splittedInst[1]);
			pOp1Reg = GetRegister(splittedInst[2]);
			memcpy(pBinary, pMode, 2);
			memcpy(pBinary+2, pOpCode, 7);
			memcpy(pBinary+9, pDestReg, 4);
			memcpy(pBinary+17, pOp1Reg, 4);

		} else { // With immediate
			pMode = GetMode(splittedInst, true);
			pOpCode[2] = 1; // Sets the immediate bit
			pDestReg = GetRegister(splittedInst[1]);
			memcpy(pBinary, pMode, 2);
			memcpy(pBinary+2, pOpCode, 7);
			memcpy(pBinary+9, pDestReg, 4);
			memcpy(pBinary+17, pImmediate, 15);

		}

	} else { // The rest
		bit *pImmediate = GetImmediate(splittedInst[3]);
		bit *pOpCode = GetOperation(splittedInst[0]);
		bit *pMode = NULL;
		bit *pDestReg = NULL;
		bit *pOp1Reg = NULL;
		bit *pOp2Reg = NULL;
		if (pImmediate == NULL) {
			pMode = GetMode(splittedInst, false);
			pDestReg = GetRegister(splittedInst[1]);
			pOp1Reg = GetRegister(splittedInst[2]);
			pOp2Reg = GetRegister(splittedInst[3]);
			memcpy(pBinary, pMode, 2);
			memcpy(pBinary+2, pOpCode, 7);
			memcpy(pBinary+9, pDestReg, 4);
			memcpy(pBinary+13, pOp1Reg, 4);
			memcpy(pBinary+17, pOp2Reg, 4);

		} else {
			pMode = GetMode(splittedInst, true);
			pOpCode[2] = 1; // Sets the immediate bit
			pDestReg = GetRegister(splittedInst[1]);
			pOp1Reg = GetRegister(splittedInst[2]);
			memcpy(pBinary, pMode, 2);
			memcpy(pBinary+2, pOpCode, 7);
			memcpy(pBinary+9, pDestReg, 4);
			memcpy(pBinary+13, pOp1Reg, 4);
			memcpy(pBinary+17, pImmediate, 15);

		}

	}
	return pBinary;
}