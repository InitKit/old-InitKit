/*
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * 		PROPRIETARY NOTICE:
 *
 * The software contained on this media is unpublished proprietary information
 * constituting or derived under licence from NetaScale Advanced Executive (tm),
 * a product of NetaScale Systems, Ltd.
 *
 * 		Copyright Notice:
 *
 * Notice of copyright on this source code product does not indicate
 * publication.
 *
 * 	(c) 2008-2021 NetaScale Systems, Ltd.
 * 		All rights reserved.
 */
/**
 * @file idb_parse.hh
 * @brief InitKit Internal Debugger parser definitions.
 */

#ifndef IDB_PARSE_HH_
#define IDB_PARSE_HH_

#include <list>
#include <map>
#include <memory>
#include <stack>
#include <string>
#include <vector>

class IDB_Parser;

#include "lemon_base.h"

#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void *yyscan_t;
#endif

struct Program;
struct Arg;
struct TypeDef;
struct TrlUnit;

/* Details of the position of some source code. */
class position_t {
	size_t m_oldLine, m_oldCol, m_oldPos;
	size_t m_line, m_col, m_pos;

    public:
	position_t(size_t oldLine, size_t oldCol, size_t oldPos, size_t line,
		   size_t col, size_t pos)
		: m_oldLine(oldLine), m_oldCol(oldCol), m_oldPos(oldPos),
		  m_line(line), m_col(col), m_pos(pos)
	{
	}

	/* Get line number */
	size_t line() const;
	/* Get column number*/
	size_t col() const;
	/* Get absolute position in source-file */
	size_t pos() const;
};

inline size_t
position_t::line() const
{
	return m_line;
}

inline size_t
position_t::col() const
{
	return m_col;
}

inline size_t
position_t::pos() const
{
	return m_pos;
}

struct token_t {
	token_t() = default;
	token_t(const token_t &) = default;
	token_t(token_t &&) = default;

	token_t(double f) : floatValue(f)
	{
	}
	token_t(long i) : intValue(i)
	{
	}
	token_t(const std::string &s) : stringValue(s)
	{
	}
	token_t(std::string &&s) : stringValue(std::move(s))
	{
	}

	token_t &operator=(const token_t &) = default;
	token_t &operator=(token_t &&) = default;

	operator std::string() const
	{
		return stringValue;
	}
	operator const char *() const
	{
		return stringValue.c_str();
	}
	operator double() const
	{
		return floatValue;
	}

	double floatValue = 0.0;
	long intValue = 0;
	std::string stringValue;
};

struct ProgramNode;
struct MethodNode;

class IDB_Parser : public lemon_base<token_t> {
    protected:
	std::string *fText = NULL;
	std::list<std::string> includeDirs;
	yyscan_t scanner;
	int m_line = 0, m_col = 0, m_pos = 0;
	int m_oldLine = 0, m_oldCol = 0, m_oldPos = 0;

    public:
	using lemon_base::parse;
	TrlUnit *trlunit;

	int line() const
	{
		return m_line;
	}
	int col() const
	{
		return m_col;
	}
	int pos1() const
	{
		return m_pos;
	}

	static IDB_Parser *create();

	IDB_Parser();

	/* parsing */
	void parse(std::string text);

	void parse(int major)
	{
		parse(major, token_t{});
	}

	template <class T> void parse(int major, T &&t)
	{
		parse(major, token_t(std::forward<T>(t)));
	}

	virtual void trace(FILE *, const char *)
	{
	}

	/* line tracking */
	position_t pos();

	void recOldPos()
	{
		m_oldPos = m_pos;
		m_oldLine = m_line;
		m_oldCol = m_col;
	}

	void cr()
	{
		m_pos += m_col + 1;
		m_line++;
		m_col = 0;
	}
	void incCol()
	{
		m_col++;
	}
};

#endif
