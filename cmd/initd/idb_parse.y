%include {
	#include <cstdlib>
	#include <iostream>
	#include <fstream>
	#include <list>

	#include "InitKit/ik_cxxutil.hh"

	#include "idb_parse.hh"
	#include "idb_parse.tab.h"
	#include "idb_parse.l.h"

	#define LEMON_SUPER IDB_Parser
}

%token_type	{token_t}
%token_prefix 	TOK_

%code {

IDB_Parser::IDB_Parser()
{
	idblex_init_extra(this, &scanner);
}

void
IDB_Parser::parse(std::string src)
{
	YY_BUFFER_STATE yyb;

	yyb = idb_scan_string(src.c_str(), scanner);
	fText = &src;
	idb_switch_to_buffer(yyb, scanner);
	while (idblex(scanner))
		;
	idb_delete_buffer(yyb, scanner);

	/* parse a 0 to complete */
	parse(0);
	fText = NULL;
}

IDB_Parser *
IDB_Parser::create()
{
	return new yypParser();
}

position_t
IDB_Parser::pos()
{
	yypParser *self = (yypParser *)this;
	return position_t(self->m_oldLine, self->m_oldCol, self->m_oldPos,
			self->m_line, self->m_col, self->m_pos);
}

}

%syntax_error {
	const YYACTIONTYPE stateno = yytos->stateno;
	size_t eolPos = fText->find("\n", m_pos);
	std::string eLine = fText->substr(m_pos, eolPos - m_pos);
	size_t i;

	std::cerr << "idb: " "(" << toStr(m_line) + "," 
			  << toStr(m_col) << "): "
			  << "Syntax error: unexpected " 
			  << yyTokenName[yymajor] << "\n";

	std::cerr << "+ " << eLine << "\n";
	std::cerr << "+ ";
	for (i = 0; i < m_oldCol; i++)
		std::cerr << " ";
	for (; i < m_col; i++)
		std::cerr << "^";

	std::cerr << "\n\texpected one of: \n";

	for (unsigned i = 0; i < YYNTOKEN; ++i)
	{
		int yyact = yy_find_shift_action(i, stateno);
		if (yyact != YY_ERROR_ACTION && yyact != YY_NO_ACTION)
			std::cerr << "\t" << yyTokenName[i] << "\n";
	}
}


file ::= cmds.

cmds ::= cmd.
cmds ::= cmds cmd.

cmd ::= NL.
cmd ::= TEXT.