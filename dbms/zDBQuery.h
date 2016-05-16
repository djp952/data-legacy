//---------------------------------------------------------------------------
// zDBQuery Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBQUERY_H_
#define __ZDBQUERY_H_
#pragma once

#include "DatabaseHandle.h"				// Include DatabaseHandle decls
#include "StatementHandle.h"			// Include StatementHandle decls
#include "zDBException.h"				// Include zDBException declarations
#include "zDBStatement.h"				// Include zDBStatement decls

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Class zDBQuery (internal)
//
// zDBQuery implements an enumerable collection of zDBStatement objects.
// This collection is build by parsing a single SQL statement string into
// all of it's individual statements.
//---------------------------------------------------------------------------

ref class zDBQuery sealed : public Generic::IEnumerable<zDBStatement^>
{
public:

	// Constructor
	// 
	// Accepts an existing SQLITE database handle and the SQL query text
	zDBQuery(DatabaseHandle* pDatabase, String^ query);

	//-----------------------------------------------------------------------
	// Member Functions

	// GetEnumerator (IEnumerable<T>)
	//
	// Returns an IEnumerator<T> against the member collection
	virtual Generic::IEnumerator<zDBStatement^>^ GetEnumerator(void);

	//-----------------------------------------------------------------------
	// Properties

	// ChangeCount
	//
	// Retrieves the total number of rows affected by the entire query
	property int ChangeCount { int get(void); }

	// StatementCount
	//
	// Retrieves the number of statements in the collection
	property int StatementCount { int get(void); }

	//-----------------------------------------------------------------------
	// Indexers

	property zDBStatement^ default[int] { zDBStatement^ get(int index); }

private:

	// DESTRUCTOR
	~zDBQuery();

	//-----------------------------------------------------------------------
	// Private Member Functions

	// IEnumerator::GetEnumerator
	virtual Collections::IEnumerator^ _GetEnumerator(void) sealed = 
		Collections::IEnumerable::GetEnumerator { return GetEnumerator(); }

	//-----------------------------------------------------------------------
	// Member Variables

	bool						m_disposed;		// Object disposal flag
	List<zDBStatement^>^		m_col;			// Contained collection
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBQUERY_H_