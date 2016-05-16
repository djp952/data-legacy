//---------------------------------------------------------------------------
// zDBVirtualTableCursor Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBVIRTUALTABLECURSOR_H_
#define __ZDBVIRTUALTABLECURSOR_H_
#pragma once

#include "zDBArgument.h"				// Include zDBArgument declarations
#include "zDBArgumentCollection.h"		// Include zDBArgumentCollection decls
#include "zDBIndexIdentifier.h"			// Include zDBIndexIdentifier decls
#include "zDBResult.h"					// Include zDBResult declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Data;
using namespace System::Data::Common;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Class zDBVirtualTableCursor
//
// zDBVirtualTableCursor is the base class from which all virtual table
// cursors must derive.  In order for the provider code to know what cursor
// goes with what virtual table, the cursor type must be declared as a
// generic argument to the zDBVirtualTable class:
//
//	internal class MyCursor : public zDBVirtualTableCursor
//	internal class MyTable : public zDBVirtualTable<MyCursor> 
//---------------------------------------------------------------------------

public ref class zDBVirtualTableCursor abstract
{
protected public:

	// PROTECTED CONSTRUCTOR
	zDBVirtualTableCursor() {}

	//-----------------------------------------------------------------------
	// Protected/Public Member Functions

	// Close
	//
	//
	virtual void Close(void) abstract;

	// GetRowID
	//
	//
	virtual __int64 GetRowID(void) abstract;

	// GetValue
	//
	//
	virtual void GetValue(int ordinal, zDBResult^ result) abstract;

	// MoveNext
	//
	//
	virtual bool MoveNext(void) abstract;

	// SetFilter (must override)
	//
	// Invoked to set/change the filter information for this cursor.  Provides
	// the index identifier created by the zDBVirtualTable::SelectBestIndex()
	// method as the first parameter, and a collection of zDBArguments that
	// represent all constraints set up with a .FilterArgumentIndex from that
	// same call into zDBVirtualTable::SelectBestIndex().
	virtual bool SetFilter(zDBIndexIdentifier^ index, zDBArgumentCollection^ args) abstract;
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBVIRTUALTABLECURSOR_H_