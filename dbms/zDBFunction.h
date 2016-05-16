//---------------------------------------------------------------------------
// zDBFunction Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBFUNCTION_H_
#define __ZDBFUNCTION_H_
#pragma once

#include "zDBArgumentCollection.h"		// Include zDBArgumentCollection decls
#include "zDBResult.h"					// Include zDBResult declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Forward Class Declarations
//---------------------------------------------------------------------------

ref class zDBConnection;				// zDBConnection.h

//---------------------------------------------------------------------------
// Delegate zDBFunction
//
// Unlike aggregates, scalar functions can be implemented with a simple
// delegate.  Even though this is a carryover from the 1.1 provider, it works
// out really well with the new virtual table function overloading as well.
//---------------------------------------------------------------------------

public delegate void zDBFunction(zDBConnection^ conn, zDBArgumentCollection^ args, 
	zDBResult^ result);

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBFUNCTION_H_