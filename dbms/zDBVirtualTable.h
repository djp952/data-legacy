//---------------------------------------------------------------------------
// Copyright (c) 2016 Michael G. Brehm
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------------

#ifndef __ZDBVIRTUALTABLE_H_
#define __ZDBVIRTUALTABLE_H_
#pragma once

#include "AutoAnsiString.h"					// Include AutoAnsiString declarations
#include "FunctionMap.h"					// Include FunctionMap declarations
#include "GCHandleRef.h"					// Include GCHandleRef declarations
#include "zDBExceptions.h"					// Include zDB exception declarations
#include "zDBFunction.h"					// Include zDBFunction declarations
#include "zDBFunctionWrapper.h"				// Include zDBFunctionWrapper decls
#include "zDBIndexSelectionArgs.h"			// Include zDBIndexSelectionArgs decls
#include "zDBVirtualTableBase.h"			// Include zDBVirtualTableBase decls
#include "zDBVirtualTableConstructorArgs.h"	// Include zDBVirtualTableConstructorArgs
#include "zDBVirtualTableCursor.h"			// Include zDBVirtualTableCursor decls

#pragma warning(push, 4)			// Enable maximum compiler warnings
#pragma warning(disable:4100)		// "unreferenced formal parameter"

using namespace System;
using namespace System::Data;
using namespace System::Text;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Forward Class Declarations
//---------------------------------------------------------------------------

ref class zDBConnection;					// zDBConnection.h

//---------------------------------------------------------------------------
// Class zDBVirtualTable
//
// zDBVirtualTable is the base class from which all custom virtual tables
// must inherit so that the unmanaged implementation can communicate with
// the registered table class instance.
//---------------------------------------------------------------------------

generic<class Cursor>
where Cursor : zDBVirtualTableCursor
public ref class zDBVirtualTable abstract : public zDBVirtualTableBase
{
protected:

	// PROTECTED CONSTRUCTOR
	zDBVirtualTable();

	//-----------------------------------------------------------------------
	// Protected Member Functions

	// BeginTransaction (must override)
	//
	// Begins a new transaction against the virtual table
	virtual void BeginTransaction(void) abstract;

	// Close (must override)
	//
	// Invoked when the virtual table is being closed.  Corresponds to the
	// SQLite xDisconnect callback
	virtual void Close(void) abstract;

	// CommitTransaction (must override)
	//
	// Commits the current transaction against the virtual table
	virtual void CommitTransaction(void) abstract;

	// CreateCursor (must override)
	//
	// Creates a new cursor instance used to read data from the virtual table
	virtual Cursor CreateCursor(void) abstract;

	// DeleteRow (must override)
	//
	// Deletes the row with the specified ROWID from the virtual table
	virtual void DeleteRow(__int64 rowid) abstract;

	// GetSchema (must override)
	//
	// Returns a DataTable instance that contains the schema for this
	// virtual table.  Constraints and keys are ignored, only the column
	// names and data types are important.
	virtual DataTable^ GetSchema(void) abstract;

	// InsertRow (must override)
	//
	// Inserts a new row with the specified ROWID and values into the table
	virtual void InsertRow(__int64 rowid, zDBArgumentCollection^ values) abstract;

	// NewRowID (must override)
	//
	// Generates a new unique ROWID for the virtual table
	virtual __int64 NewRowID(void) abstract;

	// Open (must override)
	//
	// Invoked when the virtual table is being opened.  Corresponds to the
	// SQLite xConnect callback
	virtual void Open(void) abstract;

	// OnCreate (overridable; do not invoke base version)
	//
	// Invoked when the virtual table is actually being created in response
	// to a CREATE VIRTUAL TABLE statement.  Only necessary to implement if
	// the virtual table requires some kind of backing store or special
	// initialization when it's first created.  Base class version does nothing
	virtual void OnCreate(void) {}

	// OnDrop (overridable; do not invoke base version)
	//
	// Invoked when the virtual table is being dropped from the database.
	// Only necessary to implement if the virtual table has some kind of 
	// backing store or special initializations created in OnCreate()
	virtual void OnDrop(void) {}

	// OnSynchronize (overridable; do not invoke base version)
	//
	// Forces the virtual table to synchronize itself with it's backing store
	virtual void OnSynchronize(void) {}

	// OverrideFunction
	//
	// Allows the virtual table to override a scalar function implementation
	void OverrideFunction(String^ name, zDBFunction^ function) { return OverrideFunction(name, -1, function); }
	void OverrideFunction(String^ name, int argCount, zDBFunction^ function);

	// RollbackTransaction (must override)
	//
	// Rolls back the current transaction against the virtual table
	virtual void RollbackTransaction(void) abstract;

	// SelectBestIndex (must override)
	//
	// Given the provided constraint and order by information, provides the
	// SQLite engine with the 'best' index to use for a SQL statement against
	// this virtual table
	virtual void SelectBestIndex(zDBIndexSelectionArgs^ args) abstract;

	// UpdateRow (must override)
	//
	// Updates the contents of the row with the specified ROWID in the table
	virtual void UpdateRow(__int64 rowid, zDBArgumentCollection^ values) abstract;

	// UpdateRowID (must override)
	//
	// Replaces an existing ROWID code with a new one.  In this wrapper, you
	// do not update the row contents, that will be done with a subsequent
	// call into UpdateRow
	virtual void UpdateRowID(__int64 oldrowid, __int64 newrowid) abstract;

	//-----------------------------------------------------------------------
	// Protected Properties

	// Arguments
	//
	// Exposes the arguments passed into the CREATE VIRTUAL TABLE statement
	property ReadOnlyCollection<String^>^ Arguments { ReadOnlyCollection<String^>^ get(void); }

	// Connection
	//
	// Exposes the parent zDBConnection that this virtual table has been
	// registered with
	property zDBConnection^ Connection { zDBConnection^ get(void); }

	// DatabaseName
	//
	// Exposes the name of the database instance holding the virtual table
	property String^ DatabaseName { String^ get(void); }

	// ModuleName
	//
	// Exposes the module name used to create the virtual table
	property String^ ModuleName { String^ get(void); }

	// TableName
	//
	// Exposes the virtual table name
	property String^ TableName { String^ get(void); }

private:

	// DESTRUCTOR / FINALIZER
	~zDBVirtualTable() { this->!zDBVirtualTable(); m_disposed = true; }
	!zDBVirtualTable();

	//-----------------------------------------------------------------------
	// Private Member Functions

	// BeginTransactionInternal (zDBVirtualTableBase)
	//
	// Private implementation of zDBVirtualTableBase::BeginTransaction
	virtual void BeginTransactionInternal(void) sealed = zDBVirtualTableBase::BeginTransaction
	{
		return BeginTransaction();		// Invoke specialized version]
	}

	// CloseInternal (zDBVirtualTableBase)
	//
	// Private implementation of zDBVirtualTableBase::Close
	virtual void CloseInternal(void) sealed = zDBVirtualTableBase::Close
	{
		return Close();					// Invoke specialized version
	}

	// CommitTransactionInternal (zDBVirtualTableBase)
	//
	// Private implementation of zDBVirtualTableBase::CommitTransaction
	virtual void CommitTransactionInternal(void) sealed = zDBVirtualTableBase::CommitTransaction
	{
		return CommitTransaction();		// Invoke specialized version]
	}

	// CreateInternal (zDBVirtualTableBase)
	//
	// Private implementation of zDBVirtualTableBase::Create
	virtual void CreateInternal(void) sealed = zDBVirtualTableBase::Create
	{
		return OnCreate();			// "OnXXX" indicates an optional override
	}

	// CreateCursorInternal (zDBVirtualTableBase)
	//
	// Private implementation of zDBVirtualTableBase::CreateCursor
	virtual zDBVirtualTableCursor^ CreateCursorInternal(void) sealed = zDBVirtualTableBase::CreateCursor
	{
		return safe_cast<zDBVirtualTableCursor^>(CreateCursor());
	}

	// DataTableToSchema
	//
	// Converts a DataTable schema into a CREATE TABLE statement for SQLite
	static String^ DataTableToSchema(String^ name, DataTable^ dt);

	// DeleteRowInternal (zDBVirtualTableBase)
	//
	// Private implementation of zDBVirtualTableBase::DeleteRow
	virtual void DeleteRowInternal(__int64 rowid) sealed = zDBVirtualTableBase::DeleteRow
	{
		return DeleteRow(rowid);
	}

	// DropInternal (zDBVirtualTableBase)
	//
	// Private implementation of zDBVirtualTableBase::Drop
	virtual void DropInternal(void) sealed = zDBVirtualTableBase::Drop
	{
		return OnDrop();			// "OnXXX" indicates an optional override
	}

	// FindFunctionInternal (zDBVirtualTableBase)
	//
	// Private implementation of zDBVirtualTableBase::FindFunction
	virtual bool FindFunctionInternal(String^ name, int argc, GCHandle% funcwrapper) sealed = zDBVirtualTableBase::FindFunction;

	// GetCreateTableStatementInternal (zDBVirtualTableBase)
	//
	// Private implementation of zDBVirtualTableBase::GetSchema
	virtual String^ GetCreateTableStatementInternal(String^ name) sealed = zDBVirtualTableBase::GetCreateTableStatement
	{
		return DataTableToSchema(name, GetSchema());
	}

	// InsertRowInternal (zDBVirtualTableBase)
	//
	// Private implementation of zDBVirtualTableBase::InsertRow
	virtual void InsertRowInternal(__int64 rowid, zDBArgumentCollection^ values) sealed = zDBVirtualTableBase::InsertRow
	{
		return InsertRow(rowid, values);
	}

	// NewRowIDInternal (zDBVirtualTableBase)
	//
	// Private implementation of zDBVirtualTableBase::NewRowID
	virtual __int64 NewRowIDInternal(void) sealed = zDBVirtualTableBase::NewRowID
	{
		return NewRowID();
	}

	// OpenInternal (zDBVirtualTableBase)
	//
	// Private implementation of zDBVirtualTableBase::Open
	virtual void OpenInternal(void) sealed = zDBVirtualTableBase::Open
	{
		return Open();				// Invoke specialized version
	}

	// RollbackTransactionInternal (zDBVirtualTableBase)
	//
	// Private implementation of zDBVirtualTableBase::RollbackTransaction
	virtual void RollbackTransactionInternal(void) sealed = zDBVirtualTableBase::RollbackTransaction
	{
		return RollbackTransaction();		// Invoke specialized version
	}

	// SelectBestIndexInternal (zDBVirtualTableBase)
	//
	// Private implementation of zDBVirtualTableBase::SelectBestIndex
	virtual void SelectBestIndexInternal(zDBIndexSelectionArgs^ args) sealed = 
		zDBVirtualTableBase::SelectBestIndex
	{
		return SelectBestIndex(args);		// Invoke specialized version
	}

	// SynchronizeInternal (zDBVirtualTableBase)
	//
	// Private implementation of zDBVirtualTableBase::Synchronize
	virtual void SynchronizeInternal(void) sealed = zDBVirtualTableBase::Synchronize
	{
		return OnSynchronize();			// Invoke specialized version
	}

	// UpdateRowInternal (zDBVirtualTableBase)
	//
	// Private implementation of zDBVirtualTableBase::UpdateRow
	virtual void UpdateRowInternal(__int64 rowid, zDBArgumentCollection^ values) sealed = zDBVirtualTableBase::UpdateRow
	{
		return UpdateRow(rowid, values);
	}

	// UpdateRowIDInternal (zDBVirtualTableBase)
	//
	// Private implementation of zDBVirtualTableBase::UpdateRowID
	virtual void UpdateRowIDInternal(__int64 oldrowid, __int64 newrowid) sealed = zDBVirtualTableBase::UpdateRowID
	{
		return UpdateRowID(oldrowid, newrowid);
	}

	//-----------------------------------------------------------------------
	// Member Variables

	bool							m_disposed;		// Object disposal flag
	zDBVirtualTableConstructorArgs^	m_args;			// Constructor arguments
	FunctionMap*					m_pFuncs;		// Overloaded functions
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBVIRTUALTABLE_H_
