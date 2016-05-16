//---------------------------------------------------------------------------
// zDBAggregateCollection Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBAGGREGATECOLLECTION_H_
#define __ZDBAGGREGATECOLLECTION_H_
#pragma once

#include "AutoAnsiString.h"				// Include AutoAnsiString declarations
#include "DatabaseHandle.h"				// Include DatabaseHandle declarations
#include "FunctionMap.h"				// Include FunctionMap declarations
#include "GCHandleRef.h"				// Include GCHandleRef declarations
#include "zDBAggregate.h"				// Include zDBAggregate declarations
#include "zDBAggregateWrapper.h"		// Include zDBAggregateWrapper decls
#include "zDBException.h"				// Include zDBException declarations
#include "zDBExceptions.h"				// Include zDBExceptions declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings
#pragma warning(disable:4461)			// "finalizer without destructor"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Data;
using namespace System::Runtime::InteropServices;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Class zDBAggregateCollection
//
// zDBAggregateCollection implements a collection of zDBAggregate-based
// types.  Unlike scalar functions and collations, aggregates are created
// and destroyed as necessary.  No instance is actually stored anymore.
//
// Also different in the 2.0 implementation is how duplicate aggregates are
// handled.  The 1.1 version threw exceptions, but this one will just 
// replace any matching aggregate with the newly added one.  This behavior
// is more in line with how the SQLite engine itself works.
//---------------------------------------------------------------------------

public ref class zDBAggregateCollection sealed
{
public:

	//-----------------------------------------------------------------------
	// Member Functions

	// Add
	//
	// Attempts to add a new aggregate implementation to this collection.
	// You can have multiple versions of the same aggregate that accept a
	// different number of arguments.  If no argument count is specified,
	// that implies that the aggregate accepts any number of arguments
	void Add(String^ name, Type^ aggregateType) { return Add(name, -1, aggregateType); }
	void Add(String^ name, int argCount, Type^ aggregateType);

	// Clear
	//
	// Removes all registered aggregates from the collection
	void Clear(void);

	// Remove
	//
	// Removes an aggregate implementation from this collection.  If the version
	// without an argument count is called, ALL aggregates with a matching name
	// will be removed.  To specifically remove just a dynamic argument version,
	// pass -1 as the argument count to the more specific implementation
	bool Remove(String^ name);
	bool Remove(String^ name, int argCount);

internal:

	// INTERNAL CONSTRUCTOR
	zDBAggregateCollection();

	//-----------------------------------------------------------------------
	// Internal Member Functions

	// InternalDispose
	//
	// Behaves as a pseudo-Disposal mechanism to prevent it from being called
	// outside of the ADO.NET Provider library
	void InternalDispose(void);

	// OnCloseConnection
	//
	// Invoked when the parent connection has been closed to revoke all
	// scalar functions without removing them from this collection
	void OnCloseConnection(void);

	// OnOpenConnection
	//
	// Invoked when the parent connection has been opened to (re)register
	// all scalar functions contained in this collection
	void OnOpenConnection(DatabaseHandle* pDatabase);

private:

	// FINALIZER
	!zDBAggregateCollection();

	//-----------------------------------------------------------------------
	// Private Member Functions

	// InstallAggregate
	//
	// Installs an aggregate into the specified database connection
	static void InstallAggregate(sqlite3 *hDatabase, std::wstring name, int argCount, 
		intptr_t aggwrapper);

	// IsValidAggregateType
	//
	// Determines if the specified type derives from zDBAggregate or not
	static bool IsValidAggregateType(Type^ aggregateType);

	// RemoveAggregate
	//
	// Uninstalls an aggregate from the specified database connection
	static void RemoveAggregate(sqlite3 *hDatabase, std::wstring name, int argCount,
		intptr_t aggwrapper);

	//-----------------------------------------------------------------------
	// Member Variables

	bool						m_disposed;			// Object disposal flag
	DatabaseHandle*				m_pDatabase;		// SQLite database handle
	FunctionMap*				m_pCol;				// Function map collection
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBAGGREGATECOLLECTION_H_