//---------------------------------------------------------------------------
// zDBIndexConstraint Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBINDEXCONSTRAINT_H_
#define __ZDBINDEXCONSTRAINT_H_
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
// Class zDBIndexConstraint
//
// zDBIndexConstraint is a managed wrapper around the sqlite3_index_info's
// aConstraint array.  This information is used with virtual tables, when
// the xBestIndex callback is invoked to allow the virtual table to select
// the 'best' index to use for a given SQL query against it.
//---------------------------------------------------------------------------

public ref class zDBIndexConstraint sealed
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

	// DoubleCheck
	//
	// Gets/Sets a flag indicating if SQLite should double-check this
	// constraint for each row or not
	property bool DoubleCheck
	{
		bool get(void) { return m_doubleCheck; }
		void set(bool value) { m_doubleCheck = value; }
	}

	// FilterArgumentIndex
	//
	// Gets/Sets the index into the Filter() argument list where this
	// constraint will appear. Note that this is base 1, not base zero
	property int FilterArgumentIndex
	{
		int get(void) { return m_filterArgIndex; }
		void set(int value) { m_filterArgIndex = value; }
	}

	// IsUsable
	//
	// Determines if this constraint is usable or not
	property bool IsUsable
	{
		bool get(void) { return m_usable; }
	}

	// Operator
	//
	// Gets the constraint operator value
	property zDBSearchOperator Operator
	{
		zDBSearchOperator get(void) { return m_op; }
	}

internal:

	// INTERNAL CONSTRUCTOR
	zDBIndexConstraint(const sqlite3_index_info::sqlite3_index_constraint* constraint,
		sqlite3_index_info::sqlite3_index_constraint_usage* usage)
	{
		m_ordinal = constraint->iColumn;
		m_op = static_cast<zDBSearchOperator>(constraint->op);
		m_usable = (constraint->usable != 0);

		m_filterArgIndex = usage->argvIndex;		// Set default value
		m_doubleCheck = (usage->omit == 0);			// Set default value
	}

private:

	//-----------------------------------------------------------------------
	// Member Variables

	int						m_ordinal;				// aConstraint.iColumn
	zDBSearchOperator		m_op;					// aConstraint.op
	bool					m_usable;				// aConstraint.usable
	int						m_filterArgIndex;		// aConstraintUsage.argvIndex
	bool					m_doubleCheck;			// aConstraintUsage.omit
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBINDEXCONSTRAINT_H_