
#include <iostream>
#include <fstream>
#include "ast/fwd.h"
#include "ast/cppwritervisitor.h"
#include "ast/treeprintervisitor.h"
#include "typing/typevisitor.h"
#include "parser/parser.h"

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
		return 1;
	}

	// Open the output file for writing.
	std::ofstream outFile(argv[2]);
	if (!outFile.is_open())
	{
		std::cerr << "\"" << argv[2] << "\" could not be opened for writing." << std::endl;
		return 1;
	}

	// Parse the file and generate the AST
	Nany::Ast::Node* tree = parseFile(argv[1]);
	if (!tree)
		return 1;

	// Run the AST printer visitor on the AST
	Nany::Ast::TreePrinterVisitor printerVisitor;
	tree->accept(&printerVisitor);

	// Run the CPP writer visitor on the AST
	Nany::Ast::CppWriterVisitor cppVisitor(outFile);
	tree->accept(&cppVisitor);

	// Run the type visitor on the AST
	Nany::Typing::TypeVisitor typeVisitor;
	tree->accept(&typeVisitor);

	outFile.close();

	return 0;
}
