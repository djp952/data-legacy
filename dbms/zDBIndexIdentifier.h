//---------------------------------------------------------------------------
// zDBIndexIdentifier Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBINDEXIDENTIFIER_H_
#define __ZDBINDEXIDENTIFIER_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Runtime::InteropServices;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Class zDBIndexIdentifier
//
// zDBIndexIdentifier is a managed wrapper around the sqlite3_index_info's
// idxNum and idzStr values. This information is used with virtual tables,
// both when the xBestIndex callback is invoked to allow the virtual table to 
// select an index, and when the xFilter callback is invoked with that info
//---------------------------------------------------------------------------

public ref class zDBIndexIdentifier sealed
{
public:

	//-----------------------------------------------------------------------
	// Properties

	// Code
	//
	// Gets/Sets a user-defined code to identify the selected index
	property int Code
	{
		int get(void) { return m_code; }
		void set(int value) { m_code = value; }
	}

	// Description
	//
	// Gets/Sets a user-defined description to identify the selected index
	property String^ Description
	{
		String^ get(void) { return m_desc; }
		void set(String^ value) { m_desc = value; }
	}
internal:

	// INTERNAL CONSTRUCTOR
	zDBIndexIdentifier(int idxNum, const char* idxStr)
	{
		// There's nothing to stop the application from using a HUGE
		// string to identify the index, so don't use FastPtrToStringAnsi

		m_code = idxNum;
		m_desc = Marshal::PtrToStringAnsi(IntPtr(const_cast<char*>(idxStr)));
	}

private:

	//-----------------------------------------------------------------------
	// Member Variables

	int						m_code;					// idxNum
	String^					m_desc;					// idxStr
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBINDEXIDENTIFIER_H_