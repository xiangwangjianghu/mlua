#include "Visitor.h"
#include "GramTreeNode.h"


void NormalCallFunciton::accept(Visitor* visitor, void* data)
{
	visitor->visit(this, data);
}

void SyntaxTreeNodeBase::accept(Visitor* visitor, void* data)
{
	visitor->visit(this, data);
}

void ChunkNode::accept(Visitor* visitor, void* data)
{
	visitor->visit(this, data);
}

void BlockNode::accept(Visitor* visitor, void* data)
{
	visitor->visit(this, data);
}

void LocalNameListStatement::accept(Visitor* visitor, void* data)
{
	visitor->visit(this, data);
}

void AssignStatement::accept(Visitor* visitor, void* data)
{
	visitor->visit(this, data);
}

void UnaryExpression::accept(Visitor* visitor, void* data)
{
	visitor->visit(this, data);
}

void Terminator::accept(Visitor* visitor, void* data)
{
	visitor->visit(this, data);
}

void IdentifierNode::accept(Visitor* visitor, void* data)
{
	visitor->visit(this, data);
}

void OperateStatement::accept(Visitor* visitor, void* data)
{
	visitor->visit(this, data);
}

void FunctionStatement::accept(Visitor* visitor, void* data)
{
	visitor->visit(this, data);
}

void ReturnStatement::accept(Visitor* visitor, void* data)
{
	visitor->visit(this, data);
}