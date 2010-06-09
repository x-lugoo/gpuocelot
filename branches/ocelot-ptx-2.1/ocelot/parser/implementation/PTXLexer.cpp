/*!
	\file PTXLexer.cpp
	\date Monday January 19, 2009
	\author Gregory Diamos <gregory.diamos@gatech.edu>
	\brief The header file for the PTXLexer class.
*/

#ifndef PTX_LEXER_CPP_INCLUDED
#define PTX_LEXER_CPP_INCLUDED

#undef yyFlexLexer
#define yyFlexLexer ptxFlexLexer
#include <FlexLexer.h>
#include <ocelot/parser/interface/PTXLexer.h>

#include <cstring>
#include <cassert>

#define CASE(x) case x: { return "x"; break; }

namespace parser
{
	PTXLexer::PTXLexer( std::istream* arg_yyin, std::ostream* arg_yyout ):
		yyFlexLexer( arg_yyin, arg_yyout ), yylval( 0 ), column( 0 ), 
		nextColumn( 0 )
	{
	
	}
	
	int PTXLexer::yylexPosition()
	{
		int token = yylex();
		column = nextColumn;
		nextColumn = column + strlen( YYText() );
		return token;
	}
	
	std::string PTXLexer::toString( int token )
	{
		switch( token )
		{			
			CASE(TOKEN_LABEL)
			CASE(TOKEN_IDENTIFIER)
			CASE(TOKEN_STRING)
			CASE(TOKEN_INV_PREDICATE_IDENTIFIER)
			CASE(TOKEN_PREDICATE_IDENTIFIER)
			CASE(TOKEN_SHIFT_AMOUNT)
			CASE(OPCODE_COS)
			CASE(OPCODE_SQRT)
			CASE(OPCODE_ADD)
			CASE(OPCODE_BFIND)
			CASE(OPCODE_RSQRT)
			CASE(OPCODE_ADDC)
			CASE(OPCODE_MUL)
			CASE(OPCODE_SAD)
			CASE(OPCODE_SUB)
			CASE(OPCODE_EX2)
			CASE(OPCODE_LG2)
			CASE(OPCODE_RCP)
			CASE(OPCODE_SIN)
			CASE(OPCODE_REM)
			CASE(OPCODE_MUL24)
			CASE(OPCODE_MAD24)
			CASE(OPCODE_DIV)
			CASE(OPCODE_ABS)
			CASE(OPCODE_NEG)
			CASE(OPCODE_MIN)
			CASE(OPCODE_MAX)
			CASE(OPCODE_MAD)
			CASE(OPCODE_SET)
			CASE(OPCODE_SETP)
			CASE(OPCODE_SELP)
			CASE(OPCODE_SLCT)
			CASE(OPCODE_MOV)
			CASE(OPCODE_ST)
			CASE(OPCODE_CLZ)
			CASE(OPCODE_CVT)
			CASE(OPCODE_AND)
			CASE(OPCODE_XOR)
			CASE(OPCODE_OR)
			CASE(OPCODE_BRA)
			CASE(OPCODE_CALL)
			CASE(OPCODE_RET)
			CASE(OPCODE_EXIT)
			CASE(OPCODE_TRAP)
			CASE(OPCODE_BRKPT)
			CASE(OPCODE_SUBC)
			CASE(OPCODE_TEX)
			CASE(OPCODE_LD)
			CASE(OPCODE_BARSYNC)
			CASE(OPCODE_ATOM)
			CASE(OPCODE_RED)
			CASE(OPCODE_NOT)
			CASE(OPCODE_CNOT)
			CASE(OPCODE_VOTE)
			CASE(OPCODE_SHR)
			CASE(OPCODE_SHL)
			CASE(OPCODE_FMA)
			CASE(OPCODE_MEMBAR)
			CASE(OPCODE_PMEVENT)
			CASE(OPCODE_POPC)
			CASE(PREPROCESSOR_INCLUDE)
			CASE(PREPROCESSOR_DEFINE)
			CASE(PREPROCESSOR_IF)
			CASE(PREPROCESSOR_IFDEF)
			CASE(PREPROCESSOR_ELSE)
			CASE(PREPROCESSOR_ENDIF)
			CASE(PREPROCESSOR_LINE)
			CASE(PREPROCESSOR_FILE)
			CASE(TOKEN_ENTRY)
			CASE(TOKEN_EXTERN)
			CASE(TOKEN_FILE)
			CASE(TOKEN_VISIBLE)
			CASE(TOKEN_LOC)
			CASE(TOKEN_FUNCTION)
			CASE(TOKEN_STRUCT)
			CASE(TOKEN_UNION)
			CASE(TOKEN_TARGET)
			CASE(TOKEN_VERSION)
			CASE(TOKEN_SECTION)
			CASE(TOKEN_MAXNREG)
			CASE(TOKEN_MAXNTID)
			CASE(TOKEN_MAXNCTAPERSM)
			CASE(TOKEN_SM10)
			CASE(TOKEN_MINNCTAPERSM)
			CASE(TOKEN_SM11)
			CASE(TOKEN_SM12)
			CASE(TOKEN_SM13)
			CASE(TOKEN_SM20)
			CASE(TOKEN_SM21)
			CASE(TOKEN_MAP_F64_TO_F32)
			CASE(TOKEN_CONST)
			CASE(TOKEN_GLOBAL)
			CASE(TOKEN_LOCAL)
			CASE(TOKEN_PARAM)
			CASE(TOKEN_PRAGMA)
			CASE(TOKEN_REG)
			CASE(TOKEN_SHARED)
			CASE(TOKEN_SREG)
			CASE(TOKEN_TEX)
			CASE(TOKEN_SURF)
			CASE(TOKEN_CTA)
			CASE(TOKEN_GL)
			CASE(TOKEN_SYS)
			CASE(TOKEN_U32)
			CASE(TOKEN_S32)
			CASE(TOKEN_S8)
			CASE(TOKEN_S16)
			CASE(TOKEN_S64)
			CASE(TOKEN_U8)
			CASE(TOKEN_U16)
			CASE(TOKEN_U64)
			CASE(TOKEN_B8)
			CASE(TOKEN_B16)
			CASE(TOKEN_B32)
			CASE(TOKEN_B64)
			CASE(TOKEN_F16)
			CASE(TOKEN_F64)
			CASE(TOKEN_F32)
			CASE(TOKEN_PRED)
			CASE(TOKEN_EQ)
			CASE(TOKEN_NE)
			CASE(TOKEN_LT)
			CASE(TOKEN_LE)
			CASE(TOKEN_GT)
			CASE(TOKEN_GE)
			CASE(TOKEN_LS)
			CASE(TOKEN_HS)
			CASE(TOKEN_EQU)
			CASE(TOKEN_NEU)
			CASE(TOKEN_LTU)
			CASE(TOKEN_LEU)
			CASE(TOKEN_GTU)
			CASE(TOKEN_GEU)
			CASE(TOKEN_NUM)
			CASE(TOKEN_NAN)
			CASE(TOKEN_HI)
			CASE(TOKEN_LO)
			CASE(TOKEN_AND)
			CASE(TOKEN_OR)
			CASE(TOKEN_XOR)
			CASE(TOKEN_RN)
			CASE(TOKEN_RM)
			CASE(TOKEN_RZ)
			CASE(TOKEN_RP)
			CASE(TOKEN_SAT)
			CASE(TOKEN_VOLATILE)
			CASE(TOKEN_UNI)
			CASE(TOKEN_ALIGN)
			CASE(TOKEN_BYTE)
			CASE(TOKEN_WIDE)
			CASE(TOKEN_CARRY)
			CASE(TOKEN_RNI)
			CASE(TOKEN_RMI)
			CASE(TOKEN_RZI)
			CASE(TOKEN_RPI)
			CASE(TOKEN_FTZ)
			CASE(TOKEN_APPROX)
			CASE(TOKEN_FULL)
			CASE(TOKEN_V2)
			CASE(TOKEN_V4)
			CASE(TOKEN_X)
			CASE(TOKEN_Y)
			CASE(TOKEN_Z)
			CASE(TOKEN_W)
			CASE(TOKEN_ANY)
			CASE(TOKEN_ALL)
			CASE(TOKEN_MIN)
			CASE(TOKEN_MAX)
			CASE(TOKEN_DEC)
			CASE(TOKEN_INC)
			CASE(TOKEN_ADD)
			CASE(TOKEN_CAS)
			CASE(TOKEN_EXCH)
			CASE(TOKEN_1D)
			CASE(TOKEN_2D)
			CASE(TOKEN_3D)
			CASE(TOKEN_CA)
			CASE(TOKEN_WB)
			CASE(TOKEN_CG)
			CASE(TOKEN_CS)
			CASE(TOKEN_LU)
			CASE(TOKEN_CV)
			CASE(TOKEN_WT)
			CASE(TOKEN_L1)
			CASE(TOKEN_L2)
			CASE(TOKEN_WIDTH)
			CASE(TOKEN_DEPTH)
			CASE(TOKEN_HEIGHT)
			CASE(TOKEN_NORMALIZED_COORDS)
			CASE(TOKEN_FILTER_MODE)
			CASE(TOKEN_ADDR_MODE_0)
			CASE(TOKEN_ADDR_MODE_1)
			CASE(TOKEN_ADDR_MODE_2)
			CASE(TOKEN_TRAP)
			CASE(TOKEN_CLAMP)
			CASE(TOKEN_ZERO)
			CASE(TOKEN_ARRIVE)
			CASE(TOKEN_RED)
			CASE(TOKEN_POPC)
			CASE(TOKEN_BALLOT)
			CASE(TOKEN_DECIMAL_CONSTANT)
			CASE(TOKEN_UNSIGNED_DECIMAL_CONSTANT)
			CASE(TOKEN_SINGLE_CONSTANT)
			CASE(TOKEN_DOUBLE_CONSTANT)
			case ',':
			{
				return ",";
				break;
			}
			case ';':
			{
				return ";";
				break;
			}
			case '.':
			{
				return ".";
				break;
			}
			case '{':
			{
				return "{";
				break;
			}
			case '}':
			{
				return "}";
				break;
			}
			case '[':
			{
				return "[";
				break;
			}
			case ']':
			{
				return "]";
				break;
			}
			case '(':
			{
				return "(";
				break;
			}
			case ')':
			{
				return ")";
				break;
			}
			case '+':
			{
				return "+";
				break;
			}
			case '<':
			{
				return "<";
				break;
			}
			case '>':
			{
				return ">";
				break;
			}
			case '=':
			{
				return "=";
				break;
			}
			case '-':
			{
				return "-";
				break;
			}
			case '_':
			{
				return "_";
				break;
			}
			default:
			{
				return "INVALID";
			}
		}
		
		return "";
	}
}

#endif

