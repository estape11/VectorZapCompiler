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

#include <Types.hpp>
#include <BaseHelper.hpp>
#include <iostream>
#include <vector>

class InstructionHelper{
public:
	InstructionHelper(void){}

	// Splits (using char) a line into a vector 
	// @author estape11
	// @params line, char
	// @return void
	static std::vector<std::string> SplitLineByChar(std::string, char);

	// Verify if a line is a comment
	// @author estape11
	// @params line
	// @return bool
	static bool IsComment(std::string);

	// Verify if a register is a vector
	// @author estape11
	// @params register
	// @return bool
	static bool IsVector(std::string);

	// Verify if a line is a pragma
	// @author estape11
	// @params line
	// @return bool
	static bool IsPragma(std::string);

	// Gets a binary of a register
	// @author estape11
	// @params register
	// @return binary
	static bit *GetRegister(std::string);

	// Gets a binary of operation and type
	// @author estape11
	// @params register
	// @return binary
	static bit *GetOperation(std::string);

	// Gets a binary of the immediate
	// @author estape11
	// @params data
	// @return binary
	static bit *GetImmediate(std::string);

	// Gets a binary of the mode
	// @author estape11
	// @params splittedInstruction, immediate
	// @return binary
	static bit *GetMode(std::vector<std::string>, bool);

	// Gets the binary of a instruction
	// @author estape11
	// @params instruction
	// @return binary
	static bit *GetInstructionBinary(std::string);

private:

};