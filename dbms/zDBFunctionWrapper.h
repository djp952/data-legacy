//---------------------------------------------------------------------------
// zDBFunctionWrapper Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBFUNCTIONWRAPPER_H_
#define __ZDBFUNCTIONWRAPPER_H_
#pragma once

#include "zDBArgumentCollection.h"		// Include zDBArgumentCollection decls
#include "zDBFunction.h"				// Include zDBFunction declarations
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
// Class zDBFunctionWrapper (internal)
//
// zDBFunctionWrapper represents a wrapper around the main zDBFunction delegate.
// This wrapper allows us to associate a SQLite database handle with the
// function so the connection context is known at the time of execution.
// This kinda slows things down a tad, but it represents a significant
// improvement over my 1.1 provider in that the format of boolean, date,
// and GUID results can be set automatically for the application.  That's
// really the ONLY purpose to this thing
//---------------------------------------------------------------------------

ref class zDBFunctionWrapper
{
public:

	zDBFunctionWrapper(zDBFunction^ func) : m_func(func) {}

	//-----------------------------------------------------------------------
	// Member Functions

	// Invoke
	//
	// Invokes the contained delegate given the arguments provided
	void Invoke(sqlite3_context* context, int argc, sqlite3_value** argv);

	//-----------------------------------------------------------------------
	// Public Properties

	// DatabaseHandle
	//
	// Gets/sets the database handle to associate with this function.  Changes
	// every time the connection is opened or closed, or at least that was the plan
	property sqlite3* DatabaseHandle
	{
		sqlite3* get(void) { return m_hDatabase; }
		void set(sqlite3* value) { m_hDatabase = value; }
	}

private:

	//-----------------------------------------------------------------------
	// Member Variables

	zDBFunction^				m_func;			// Function delegate
	sqlite3*					m_hDatabase;	// Active database handle
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBFUNCTIONWRAPPER_H_