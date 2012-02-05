
#include <iostream>
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
		return EXIT_FAILURE;
	}

	// Parse the file and generate the AST
	Nany::Ast::Node* tree = parseFile(argv[1]);
	if (!tree)
		return EXIT_FAILURE;

	// Run the AST printer visitor on the AST
	Nany::Ast::TreePrinterVisitor printerVisitor;
	tree->accept(&printerVisitor);

	// Run the type visitor on the AST
	Nany::Typing::TypeVisitor typeVisitor;
	tree->accept(&typeVisitor);

	// Run the CPP writer visitor on the AST
	Nany::Ast::CppWriterVisitor visitor;
	if (!visitor.out.openRW(argv[2]))
	{
		std::cerr << "\"" << argv[2] << "\" could not be opened for writing." << std::endl;
		return EXIT_FAILURE;
	}
	tree->accept(&visitor);

	return 0;
}
