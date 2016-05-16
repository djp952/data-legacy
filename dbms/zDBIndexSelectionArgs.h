//---------------------------------------------------------------------------
// zDBIndexSelectionArgs Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBINDEXSELECTIONARGS_H_
#define __ZDBINDEXSELECTIONARGS_H_
#pragma once

#include "AutoAnsiString.h"				// Include AutoAnsiString decls
#include "zDBEnumerations.h"			// Include zDB enumeration decls
#include "zDBIndexConstraint.h"			// Include zDBIndexConstraint decls
#include "zDBIndexIdentifier.h"			// Include zDBIndexIdentifier decls
#include "zDBIndexSortColumn.h"			// Include zDBIndexSortColumn decls

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Collections::ObjectModel;
using namespace System::Data;
using namespace System::Diagnostics;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Class zDBIndexSelectionArgs
//
// zDBIndexSelectionArgs is a managed wrapper around the sqlite3_index_info 
// structure.  This information is used with virtual tables, when the xBestIndex 
// callback is invoked to allow the virtual table to select the 'best' index 
// to use for a given SQL query against it.
//---------------------------------------------------------------------------

public ref class zDBIndexSelectionArgs sealed
{
public:

	//-----------------------------------------------------------------------
	// Properties

	// Constraints
	//
	// Gets a reference to the contained zDBIndexConstraint collection
	property ReadOnlyCollection<zDBIndexConstraint^>^ Constraints
	{
		ReadOnlyCollection<zDBIndexConstraint^>^ get(void) { return m_constraints; }
	}

	// EstimatedCost
	//
	// Gets/sets a value indicating what the relative cost of the selected index
	// will be.  SQLite may call xBestIndex multiple times to see what combination
	// of constraints will generate the most efficient query
	property double EstimatedCost
	{
		double get(void) { return m_estimatedCost; }
		void set(double value) { m_estimatedCost = value; }
	}

	// Identifier
	//
	// Gets a reference to the contained index identifier class, which wraps up
	// both the index code and index string values from SQLite
	property zDBIndexIdentifier^ Identifier
	{
		zDBIndexIdentifier^ get(void) { return m_identifier; }
	}

	// SortColumns
	//
	// Gets a reference to the contained zDBIndexSortColumn collection
	property ReadOnlyCollection<zDBIndexSortColumn^>^ SortColumns
	{
		ReadOnlyCollection<zDBIndexSortColumn^>^ get(void) { return m_sortcols; }
	}

	// SortRequired
	//
	// Gets/Sets a flag indicating if SQLite will have to sort the data
	// after it's been retrieved or not
	property bool SortRequired
	{
		bool get(void) { return m_sortRequired; }
		void set(bool value) { m_sortRequired = value; }
	}

internal:

	// INTERNAL CONSTRUCTOR
	zDBIndexSelectionArgs(sqlite3_index_info* info);

	//-----------------------------------------------------------------------
	// Internal Member Functions

	// OutputToStructure
	//
	// Takes the output information provided by the user and applies it to
	// a sqlite3_index_info structure
	void OutputToStructure(sqlite3_index_info* info);

private:

	//-----------------------------------------------------------------------
	// Member Variables

	ReadOnlyCollection<zDBIndexConstraint^>^	m_constraints;		// aConstraint[]
	ReadOnlyCollection<zDBIndexSortColumn^>^	m_sortcols;			// aOrderBy[]

	zDBIndexIdentifier^		m_identifier;				// idxNum, idxStr
	bool					m_sortRequired;				// orderByConsumed
	double					m_estimatedCost;			// estimatedCost
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBINDEXSELECTIONARGS_H_