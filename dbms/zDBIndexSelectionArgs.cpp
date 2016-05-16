//---------------------------------------------------------------------------
// zDBIndexSelectionArgs Implementation
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#include "stdafx.h"					// Include project pre-compiled headers
#include "zDBIndexSelectionArgs.h"	// Include zDBIndexSelectionArgs declarations

#pragma warning(push, 4)			// Enable maximum compiler warnings

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// zDBIndexSelectionArgs Constructor (internal)
//
// Arguments:
//
//	info		- Pointer to the sqlite3_index_info structure to wrap

zDBIndexSelectionArgs::zDBIndexSelectionArgs(sqlite3_index_info* info)
{
	if(!info) throw gcnew ArgumentNullException();

	// Convert the aConstraint[] array into a read-only collection of zDBIndexConstraints
	// that indicate both the index constraint inputs as well as the constraint outputs

	array<zDBIndexConstraint^>^ constraints = gcnew array<zDBIndexConstraint^>(info->nConstraint);
	for(int index = 0; index < info->nConstraint; index++)
		constraints[index] = gcnew zDBIndexConstraint(&info->aConstraint[index], &info->aConstraintUsage[index]);

	m_constraints = Array::AsReadOnly(constraints);		// Store as read-only

	// Convert the aOrderBy[] array into a read-only collection of zDBSortColumn 
	// objects that indicate the index ORDER BY information

	array<zDBIndexSortColumn^>^ sortcols = gcnew array<zDBIndexSortColumn^>(info->nOrderBy);
	for(int index = 0; index < info->nOrderBy; index++)
		sortcols[index] = gcnew zDBIndexSortColumn(&info->aOrderBy[index]);

	m_sortcols = Array::AsReadOnly(sortcols);			// Store as read-only

	// Copy out the remaining values that are of interest to us from the info

	m_identifier = gcnew zDBIndexIdentifier(info->idxNum, info->idxStr);
	m_sortRequired = (info->orderByConsumed == 0);
	m_estimatedCost = info->estimatedCost;
}

//---------------------------------------------------------------------------
// zDBIndexSelectionArgs::OutputToStructure (internal)
//
// Copies the output information provided by the application into a 
// sqlite3_index_info structure
//
// Arguments:
//
//	info		- Pointer to the structure to be modified

void zDBIndexSelectionArgs::OutputToStructure(sqlite3_index_info* info)
{
	Debug::Assert(info->nConstraint == m_constraints->Count);	// Should be equal

	// First walk over the array of constraint usage and apply the values to the
	// output data structure.  Note the boolean NOT used to convert 'DoubleCheck'

	for(int index = 0; (index < m_constraints->Count) && (index < info->nConstraint); index++) {

		zDBIndexConstraint^ constraint = m_constraints[index];
		info->aConstraintUsage[index].argvIndex = constraint->FilterArgumentIndex;
		info->aConstraintUsage[index].omit = (constraint->DoubleCheck) ? 0 : 1;
	}

	info->idxNum = m_identifier->Code;			// Set the identifier code

	// If an identifier description was set, use sqlite3_malloc and set the
	// needToFreeIdxStr flag so that SQLite can own the resultant string

	info->needToFreeIdxStr = (m_identifier->Description != nullptr) ? 1 : 0;
	if(info->needToFreeIdxStr) info->idxStr = sqlite3_mprintf(AutoAnsiString(m_identifier->Description));

	info->orderByConsumed = (m_sortRequired) ? 0 : 1;	// Set flag opposite
	info->estimatedCost = m_estimatedCost;				// Set estimated cost
}

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)
