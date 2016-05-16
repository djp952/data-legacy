//---------------------------------------------------------------------------
// zDBFunctionWrapper Implementation
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#include "stdafx.h"					// Include project pre-compiled headers
#include "zDBFunctionWrapper.h"		// Include zDBFunctionWrapper declarations
#include "zDBConnection.h"			// Include zDBConnection declarations

#pragma warning(push, 4)			// Enable maximum compiler warnings

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// zDBFunctionWrapper::Invoke
//
// Invokes the contained delegate using the provided argument information
//
// Arguments:
//
//	context		- SQLite function context pointer
//	argc		- Number of function arguments
//	argv		- Array of function argument values

void zDBFunctionWrapper::Invoke(sqlite3_context* context, int argc, sqlite3_value** argv)
{
	zDBArgumentCollection^		args;		// Function argument collection
	zDBResult^					result;		// Function result object

	if(m_func == nullptr) return;			// No delegate, nothing to do

	zDBConnection^ conn = zDBConnection::FindConnection(m_hDatabase);

	// Both the arguments as well as the result need to be disposed of
	// as soon as we are finished with them, so use an ugly little nested
	// try/finally setup in here

	args = gcnew zDBArgumentCollection(argc, argv);
	try { 

		result = gcnew zDBResult(conn, context);

		try { m_func(conn, args, result); }		// Invoke the delegate
		finally { delete result; }				// Dispose of result
	}
	
	finally { delete args; }					// Dispose of arguments

	GC::KeepAlive(conn);						// Keep the connection alive
}	

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)
