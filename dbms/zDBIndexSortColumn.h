//---------------------------------------------------------------------------
// zDBIndexSortColumn Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBINDEXSORTCOLUMN_H_
#define __ZDBINDEXSORTCOLUMN_H_
#pragma once

#include "zDBEnumerations.h"			// Include zDB enumeration decls

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Data;
using namespace System::Data::Common;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Class zDBIndexSortColumn
//
// zDBIndexSortColumn is a managed wrapper around the sqlite3_index_info's
// aOrderBy array.  This information is used with virtual tables, when
// the xBestIndex callback is invoked to allow the virtual table to select
// the 'best' index to use for a given SQL query against it.
//---------------------------------------------------------------------------

public ref class zDBIndexSortColumn sealed
{
public:

	//-----------------------------------------------------------------------
	// Properties

	// ColumnOrdinal
	//
	// Gets the column ordinal on the left-hand size of the constraint
	property int ColumnOrdinal
	{
		int get(void) { return m_ordinal; }
	}

	// Direction
	//
	// Defines the direction of the referenced ORDER BY expression
	property zDBSortDirection Direction
	{
		zDBSortDirection get(void) { return m_direction; }
	}

internal:

	// INTERNAL CONSTRUCTOR
	zDBIndexSortColumn(const sqlite3_index_info::sqlite3_index_orderby* orderby)
	{
		m_ordinal = orderby->iColumn;
		m_direction = (orderby->desc) ? zDBSortDirection::Descending : zDBSortDirection::Ascending;
	}

private:

	//-----------------------------------------------------------------------
	// Member Variables

	int						m_ordinal;				// .iColumn
	zDBSortDirection		m_direction;			// .desc
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBINDEXSORTCOLUMN_H_