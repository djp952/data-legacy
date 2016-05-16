//---------------------------------------------------------------------------
// DatabaseHandle Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __DATABASEHANDLE_H_
#define __DATABASEHANDLE_H_
#pragma once

#include "zDBException.h"				// Include zDBException declarations

using namespace System;
using namespace System::Diagnostics;
using namespace zuki::data::dbms;

#pragma warning(push, 4)				// Enable maximum compiler warnings

//---------------------------------------------------------------------------
// Class DatabaseHandle
//
// DatabaseHandle is a reference counted wrapper around a SQLite database
// handle that allows it to be treated like a COM object so we can 
// deterministically free it properly from managed class finalizers
//
// NOTE: Set "ZDB_TRACE_HANDLEREF" to enable Debug monitoring of refcounts
//---------------------------------------------------------------------------

class DatabaseHandle
{
public:

	//-----------------------------------------------------------------------
	// Constructor
	//
	// Arguments:
	//
	//	caller		- Object calling the ctor (for tracing purposes)
	//	hDatabase	- the database handle to take ownership of

	explicit DatabaseHandle(Object^ caller, sqlite3* hDatabase);

	//-----------------------------------------------------------------------
	// Overloaded Operators

	operator sqlite3*() { return m_hDatabase; }

	bool operator ==(const sqlite3* rhs) const { return m_hDatabase == rhs; }
	bool operator !=(const sqlite3* rhs) const { return m_hDatabase != rhs; }

	//-----------------------------------------------------------------------
	// Member Functions

	void AddRef(Object^ caller);
	void Release(Object^ caller);

	//-----------------------------------------------------------------------
	// Properties

	__declspec(property(get=GetHandle))		sqlite3*	Handle;

	//-----------------------------------------------------------------------
	// Property Accessors

	sqlite3* GetHandle(void) { return m_hDatabase; }

private:

	DatabaseHandle(const DatabaseHandle &rhs);
	DatabaseHandle& operator=(const DatabaseHandle &rhs);

	//-----------------------------------------------------------------------
	// Destructor (private)
	
	~DatabaseHandle();

	//-----------------------------------------------------------------------
	// Member Variables

	sqlite3*				m_hDatabase;		// Contained database handle
	volatile long			m_cRefCount;		// Reference counter
};

//---------------------------------------------------------------------------

#pragma warning(pop)

#endif	// __DATABASEHANDLE_H_
