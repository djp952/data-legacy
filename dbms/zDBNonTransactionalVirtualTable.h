//---------------------------------------------------------------------------
// zDBNonTransactionalVirtualTable Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBNONTRANSACTIONALVIRTUALTABLE_H_
#define __ZDBNONTRANSACTIONALVIRTUALTABLE_H_
#pragma once

#include "zDBVirtualTable.h"		// Include zDBVirtualTable declarations

#pragma warning(push, 4)			// Enable maximum compiler warnings
#pragma warning(disable:4100)		// "unreferenced formal parameter"

using namespace System;
using namespace System::Data;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Class zDBNonTransactionalVirtualTable
//
// zDBNonTransactionalVirtualTable is a specialization of zDBVirtualTable
// that prevents the transaction-based callbacks from being registered, 
// therefore preventing the engine from attempting to include this table
// in it's transactions.
//---------------------------------------------------------------------------

generic<class Cursor>
where Cursor : zDBVirtualTableCursor
public ref class zDBNonTransactionalVirtualTable abstract : public zDBVirtualTable<Cursor>
{
protected:

	//-----------------------------------------------------------------------
	// Protected Member Functions

	// BeginTransaction
	//
	// Begins a new transaction against the virtual table
	virtual void BeginTransaction(void) override sealed
	{
		throw gcnew NotImplementedException();
	}

	// CommitTransaction
	//
	// Commits the current transaction open against the virtual table
	virtual void CommitTransaction(void) override sealed
	{
		throw gcnew NotImplementedException();
	}

	// RollbackTransaction
	//
	// Rolls back the current transaction open against the virtual table
	virtual void RollbackTransaction(void) override sealed
	{
		throw gcnew NotImplementedException();
	}
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBNONTRANSACTIONALVIRTUALTABLE_H_