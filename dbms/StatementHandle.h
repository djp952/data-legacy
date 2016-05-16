//---------------------------------------------------------------------------
// StatementHandle Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __STATEMENTHANDLE_H_
#define __STATEMENTHANDLE_H_
#pragma once

#include "DatabaseHandle.h"				// Include DatabaseHandle declarations
#include "zDBException.h"				// Include zDBException declarations

using namespace System;
using namespace System::Diagnostics;
using namespace zuki::data::dbms;

#pragma warning(push, 4)				// Enable maximum compiler warnings

//---------------------------------------------------------------------------
// Class StatementHandle
//
// StatementHandle is a reference counted wrapper around a SQLite database
// handle that allows it to be treated like a COM object so we can 
// deterministically free it properly from managed class finalizers
//
// NOTE: Set "ZDB_TRACE_HANDLEREF" to enable Debug monitoring of refcounts
//---------------------------------------------------------------------------

class StatementHandle
{
public:

	//-----------------------------------------------------------------------
	// Constructor
	//
	// Arguments:
	//
	//	pDatabase		- CDatabaseHandle wrapper object
	//	hStatement		- Already created sqlite3_stmt handle.

	explicit StatementHandle(Object^ caller, DatabaseHandle* pDatabase, sqlite3_stmt* hStatement);

	//-----------------------------------------------------------------------
	// Overloaded Operators

	operator sqlite3_stmt*() { return m_hStatement; }
	operator sqlite3*()	{ return m_pDatabase->Handle; }

	StatementHandle& operator =(sqlite3_stmt* hStatement);

	//-----------------------------------------------------------------------
	// Member Functions

	void AddRef(Object^ caller);
	void Release(Object^ caller);

	//-----------------------------------------------------------------------
	// Properties

	__declspec(property(get=GetDatabaseHandle))	sqlite3*		DBHandle;
	__declspec(property(get=GetHandle))			sqlite3_stmt*	Handle;

	//-----------------------------------------------------------------------
	// Property Accessors

	sqlite3*		GetDatabaseHandle(void) { return m_pDatabase->Handle; }
	sqlite3_stmt*	GetHandle(void)			{ return m_hStatement; }

private:

	StatementHandle(const StatementHandle &rhs);
	StatementHandle& operator=(const StatementHandle &rhs);

	//-----------------------------------------------------------------------
	// Destructor (private)
	
	~StatementHandle();

	//-----------------------------------------------------------------------
	// Member Variables

	DatabaseHandle*			m_pDatabase;		// Contained database reference
	sqlite3_stmt*			m_hStatement;		// Contained statement handle
	volatile long			m_cRefCount;		// Reference counter
};

//---------------------------------------------------------------------------

#pragma warning(pop)

#endif	// __STATEMENTHANDLE_H_
