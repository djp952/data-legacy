//---------------------------------------------------------------------------
// AutoUnicodeString Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __AUTOUNICODESTRING_H_
#define __AUTOUNICODESTRING_H_
#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

#pragma warning(push, 4)				// Enable maximum compiler warnings

//---------------------------------------------------------------------------
// Class AutoUnicodeString
//
// AutoUnicodeString implements a System::String->Unicode String conversion
// class. There are a load of places in the code where we need to convert
// strings back and forth, and the try/finally blocks can quickly get out
// of hand.  This class ensures that the heap memory is released property
// without the need for any fancy unwind semantics.
//---------------------------------------------------------------------------

class AutoUnicodeString
{
public:

	//-----------------------------------------------------------------------
	// Constructor
	//
	// Arguments:
	//
	//	string		- Managed string to be converted into an ANSI string

	explicit AutoUnicodeString(String^ string) : 
	  m_ptr(reinterpret_cast<intptr_t>(Marshal::StringToHGlobalUni(string).ToPointer())) {}

	//-----------------------------------------------------------------------
	// Destructor
	//
	// Automatically releases the allocated string buffer from the heap

	~AutoUnicodeString() { Marshal::FreeHGlobal(IntPtr(m_ptr)); }

	//-----------------------------------------------------------------------
	// Overloaded Operators

	operator const wchar_t*() const { return reinterpret_cast<wchar_t*>(m_ptr); }

private:

	AutoUnicodeString(const AutoUnicodeString& rhs);
	AutoUnicodeString& operator=(const AutoUnicodeString& rhs);

	//-----------------------------------------------------------------------
	// Member Variables

	intptr_t				m_ptr;			// Pointer to managed buffer
};

//---------------------------------------------------------------------------

#pragma warning(pop)

#endif	// __AUTOUNICODESTRING_H_
