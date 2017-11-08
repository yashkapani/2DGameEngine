#ifndef _Assert_h
#define _Assert_h

#include "Target.h"

bool _MessagedAssert(const char * i_pExpression, const char * i_pMessage, const char * i_pFile, unsigned int i_LineNo);

#ifdef NDEBUG

#define MessagedAssert(_Expression,_Message)     ((void)0)

#else

#define MessagedAssert(_Expression,_Message) if( (!(_Expression)) && !_MessagedAssert(#_Expression, _Message, __FILE__, __LINE__) ) { DEBUGGER_BREAK; }

#endif  

#endif 