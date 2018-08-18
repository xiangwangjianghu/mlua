#include "Scanner.h"
#include <cstring>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <iterator>

using namespace std;

Scanner::Scanner()
{
    _row = 0;
    _nBufferPos = 0;
    initKeyWords();
    initSymbols();
}

void Scanner::resetRow()
{
    _row = 0;
}

int Scanner::openFile(string filename)
{
    string suffix = filename.substr(filename.size() - 4, 4);
    if (suffix != ".lua")  {
        cerr <<  "file '"<<filename << "' is not a standard lua  file" << endl;
		return -1;
    }
    _fIn.open(filename);
    if (_fIn.fail())  {
        cerr << "file " << filename << " does not exit" << endl;
		return -1;
    }
	return 0;
}

void Scanner::closeFile()
{
    _fIn.close();
}

void Scanner::initKeyWords()
{
    m_vtkeyWords.insert("and");
    m_vtkeyWords.insert("break");
    m_vtkeyWords.insert("function");
    m_vtkeyWords.insert("do");
    m_vtkeyWords.insert("end");
    m_vtkeyWords.insert("then");
    m_vtkeyWords.insert("in");
    m_vtkeyWords.insert("local");
    m_vtkeyWords.insert("nil");
    m_vtkeyWords.insert("not");
	m_vtkeyWords.insert("or");
	m_vtkeyWords.insert("repeat");
	m_vtkeyWords.insert("until");
    m_vtkeyWords.insert("true");
    m_vtkeyWords.insert("false");
    m_vtkeyWords.insert("for");
    m_vtkeyWords.insert("if");
    m_vtkeyWords.insert("else");
	m_vtkeyWords.insert("elseif");
    m_vtkeyWords.insert("while");
    m_vtkeyWords.insert("return");
}

void Scanner::initSymbols()
{
    m_vtStrSymbols.insert("{");
    m_vtStrSymbols.insert("}");
    m_vtStrSymbols.insert("(");
    m_vtStrSymbols.insert(")");
    m_vtStrSymbols.insert("[");
    m_vtStrSymbols.insert("]");
    m_vtStrSymbols.insert(".");
    m_vtStrSymbols.insert(",");
    m_vtStrSymbols.insert(";");
    m_vtStrSymbols.insert("+");
    m_vtStrSymbols.insert("-");
    m_vtStrSymbols.insert("*");
    m_vtStrSymbols.insert("/");
    m_vtStrSymbols.insert("&");
    m_vtStrSymbols.insert("|");
    m_vtStrSymbols.insert("~");
    m_vtStrSymbols.insert("<");
    m_vtStrSymbols.insert(">");
    m_vtStrSymbols.insert("=");
    m_vtStrSymbols.insert(">=");
    m_vtStrSymbols.insert("<=");
    m_vtStrSymbols.insert("==");
    m_vtStrSymbols.insert("!=");
}

string Scanner::detailType2Lexeme(TokenType_Detail detail)
{
	string lexeme;
	switch (detail)
	{
	case Scanner::Token_And:
		break;
	case Scanner::Token_Break:
		break;
	case Scanner::Token_Do:
		break;
	case Scanner::Token_Else:
		lexeme = "else";
		break;
	case Scanner::Token_Elseif:
		lexeme = "elseif";
		break;
	case Scanner::Token_End:
		lexeme = "end";
		break;
	case Scanner::Token_False:
		break;
	case Scanner::Token_For:
		break;
	case Scanner::Token_Function:
		lexeme = "function";
		break;
	case Scanner::Token_If:
		lexeme = "if";
		break;
	case Scanner::Token_In:
		break;
	case Scanner::Token_Local:
		lexeme = "local";
		break;
	case Scanner::Token_Nil:
		break;
	case Scanner::Token_Not:
		break;
	case Scanner::Token_Or:
		break;
	case Scanner::Token_Repeat:
		break;
	case Scanner::Token_Return:
		lexeme = "return";
		break;
	case Scanner::Token_Then:
		lexeme = "then";
		break;
	case Scanner::Token_True:
		break;
	case Scanner::Token_Until:
		break;
	case Scanner::Token_While:
		break;
	case Scanner::Token_Id:
		break;
	case Scanner::Token_String:
		break;
	case Scanner::Token_Number:
		break;
	case Scanner::Token_Equal:
		break;
	case Scanner::Token_NotEqual:
		break;
	case Scanner::Token_LessEqual:
		break;
	case Scanner::Token_GreaterEqual:
		break;
	case Scanner::Token_Concat:
		break;
	case Scanner::Token_VarArg:
		break;
	case Scanner::Token_EOF:
		break;
	case Scanner::Token_LeftRoundBracket:
		lexeme = "(";
		break;
	case Scanner::Token_RightRoundBracket:
		lexeme = ")";
		break;
	case Scanner::Token_LeftSquareBracket:
		lexeme = "[";
		break;
	case Scanner::Token_RightSquareBracket:
		lexeme = "]";
		break;
	case Scanner::Token_LeftBrace:
		lexeme = "{";
		break;
	case Scanner::Token_RightBrace:
		lexeme = "}";
		break;
	case Scanner::Token_Comma:
		lexeme = ",";
		break;
	case Scanner::Token_Semicolon:
		lexeme = ";";
		break;
	case Scanner::Token_Assign:
		lexeme = "=";
		break;
	default:
		break;
	}
	return lexeme;
}

Scanner::TokenType Scanner::searchReserved(string &s)
{
    if (m_vtkeyWords.find(s) != m_vtkeyWords.end())
        return KEY_WORD;
    else
        return ID;
}

char Scanner::nextChar()
{
    if (_nBufferPos >= _strLineBuffer.size())
    {
        _row++;
        getline(_fIn, _strLineBuffer);
        _strLineBuffer += '\n';
        if (!_fIn.fail())
        {
            _nBufferPos = 0;
            return _strLineBuffer[_nBufferPos++];
        }
        else
            return EOF;
    }
    else
    {
        return _strLineBuffer[_nBufferPos++];
    }
}

void Scanner::rollBack()
{
    assert(_nBufferPos > 0);
    _nBufferPos--;
}

Scanner::State Scanner::procStartState(char ch, Token& token)
{
	State state = STATE_START;
	if (ch == ' ' || ch == '\t' || ch == '\n');
	else if (isalpha(ch) || ch == '_')  {
		state = STATE_ID;		// �����ʶ��״̬
		token.kind = ID;
		token.lexeme += ch;
	}
	else if (isdigit(ch))  {
		state = STATE_INT;		// ��������״̬
		token.kind = INT;
		token.lexeme += ch;
	}
	else if (m_vtStrSymbols.find({ ch }) != m_vtStrSymbols.end())  {
		state = STATE_SYMBOL;
		token.kind = SYMBOL;
		token.lexeme += ch;
	}
	else if (ch == '"')  {
		state = STATE_STRING;	// �����ַ���״̬
		token.kind = STRING;
	}
	else if (ch == '\'')  {		// ���뵥�ַ�״̬
		state = STATE_CHAR;
		token.kind = CHAR;
	}
	else	{											// �����Ƿ��ַ�
		state = STATE_ERROR;
		token.kind = ERROR;
		token.lexeme += ch;
	}
	token.row = _row;
	return state;
}

bool Scanner::procIntState(char ch, Token& token)
{
	if (isdigit(ch))  {
		token.lexeme += ch;
	}
	else  {
		rollBack();
		return true;
	}
	return false;
}

bool Scanner::procIdentityState(char ch, Token& token)
{
	if (isalpha(ch) || isdigit(ch) || ch == '_')  {
		token.lexeme += ch;
	}
	else  {
		rollBack();
		return true;
	}
	return false;
}

void Scanner::procStringState(char ch, Token& token, Scanner::State& state)
{
	if (state == STATE_STRING)  {
		if (ch == '"')  {            //���������ַ���
			state = STATE_DONE;
		}
		else if (ch == '\\')  {      //��ʼ��������ַ���
			state = STATE_S_STRING;
			token.lexeme += ch;
		}
		else  {
			token.lexeme += ch;
		}
	}
	else if (state == STATE_S_STRING)  {   //�������ַ����ͽ����ַ���һ��
		state = STATE_STRING;
		if (ch == '\'')                    //ȥ��\ "AB\n\'ab\'CD"   ==> "AB\n'ab'CD"   ��ʵ����ȥ���κ�'\'�����ΪSTATE_STRING��STATE_S_STRING��ֻ�ǻ���""�����Ľ���,"\""�����ǺϷ��ģ�����������"�ͱ����ַ���������
			token.lexeme.pop_back();
		token.lexeme += ch;
	}
}

void Scanner::procCharState(char ch, Token& token, Scanner::State& state)
{
	bool match = false;
	if (state == STATE_CHAR)  {                 //�ַ���ʼ'
		if (ch != '\\' && ch != '\'')  {        //�ַ�'A'��ʼ
			state = STATE_CHAR_A;
			token.lexeme += ch;
			match = true;
		}
		else if (ch == '\\')  {
			state = STATE_CHAR_B;
			token.lexeme += ch;
			match = true;
		}
	}
	else if (state == STATE_CHAR_A)  {       //�ַ�'A'����
		if (ch == '\'')  {
			state = STATE_DONE;
			match = true;
		}
	}
	else if (state == STATE_CHAR_B)  {      //�����ַ�'\a'
		if (ch == 'a' || ch == 'b' || ch == 'f' || ch == 'n' || ch == 'r' || ch == 't' ||
			ch == 'v' || ch == '\\' || ch == '?' || ch == '\'' || ch == '"')  {
			state = STATE_CHAR_C;
			token.lexeme += ch;
			match = true;
		}
	}
	else if (state == STATE_CHAR_C)  {      //�����ַ�'\a'����
		if (ch == '\'')  {
			state = STATE_DONE;
			match = true;
		}
	}
	if (!match)  {
		state = STATE_ERROR;
		token.kind = ERROR;
		string tmp = "'";
		tmp.append(token.lexeme);
		tmp += ch;
		token.lexeme = tmp;
	}
}

void Scanner::procSymbolState(char ch, Token& token, Scanner::State& state)
{
	bool match = false;
	if (token.lexeme == "/")  {
		if (ch == '*')  {
			state = STATE_COMMENT;
			token.lexeme.clear();
			match = true;
		}
		else if (ch == '/')  {
			state = STATE_START;
			_nBufferPos = _strLineBuffer.length();
			token.lexeme.clear();
			match = true;
		}
	}
	else if (token.lexeme == "<")  {
		if (ch == '=')  {
			token.lexeme += ch;
			state = STATE_DONE;
			match = true;
		}
	}
	else if (token.lexeme == "=")  {
		if (ch == '=')  {
			token.lexeme += ch;
			state = STATE_DONE;
			match = true;
		}
	}
	else if (token.lexeme == "!")  {
		if (ch == '=')  {
			token.lexeme += ch;
			state = STATE_DONE;
			match = true;
		}
	}
	else if (token.lexeme == "&")  {
		if (ch == '&')  {
			token.lexeme += ch;
			state = STATE_DONE;
			match = true;
		}
	}
	else if (token.lexeme == "|")  {
		if (ch == '|')  {
			token.lexeme += ch;
			state = STATE_DONE;
			match = true;
		}
	}
	if (!match)  {
		rollBack();
		state = STATE_DONE;
	}
}

void Scanner::procCommentState(char ch, Token& token, Scanner::State& state)
{
	if (state == STATE_COMMENT)  {
		if (ch == '*')                     //ע��״̬�£�����*,˵���п�����ע�ͽ���*/
			state = STATE_P_COMMENT;
	}
	else if (state == STATE_P_COMMENT)  {
		if (ch == '/')                     //ע����Ľ�����
			state = STATE_START;
		else
			state = STATE_COMMENT;         //��Ȼ�Ļ�����ע������ /*this is * */ 
	}
}

Scanner::Token Scanner::nextToken()
{
    Token token;
    unsigned tokenStringIndex = 0;
    State state = STATE_START;
    while (state != STATE_DONE)  {
        char ch = nextChar();
        if (ch == EOF)  {
            token.kind = ENDOFFILE;
            break;
        }
		switch (state)  {
        case STATE_START:										// ��ʼ״̬
			state = procStartState(ch, token);
            break;

        case STATE_INT:											// ����״̬
			if (procIntState(ch, token)) state = STATE_DONE;
            break;

        case STATE_ID:											// ��ʶ��״̬
			if (procIdentityState(ch, token)) state = STATE_DONE;
            break;

		case STATE_SYMBOL:
			procSymbolState(ch, token, state);
			break;

		case STATE_CHAR:										// �ַ�״̬
		case STATE_CHAR_A:
		case STATE_CHAR_B:
		case STATE_CHAR_C:
			procCharState(ch, token, state);
			break;

        case STATE_STRING:										// �ַ���״̬
        case STATE_S_STRING:
			procStringState(ch, token, state);
            break;

        case STATE_COMMENT:								    	// ע��״̬
		case STATE_P_COMMENT:
			procCommentState(ch, token, state);
            break;

		case STATE_ERROR:										// ����״̬
			if (ch == ' ' || ch == '\n' || ch == '\t')
				state = STATE_DONE;
			else
				token.lexeme += ch;
			break;
        }
        if (state == STATE_DONE && token.kind == ID)
            token.kind = searchReserved(token.lexeme);          //�п����ǹؼ���
    }
    return token;
}