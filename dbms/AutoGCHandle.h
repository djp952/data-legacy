//---------------------------------------------------------------------------
// AutoGCHandle Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __AUTOGCHANDLE_H_
#define __AUTOGCHANDLE_H_
#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;

#pragma warning(push, 4)				// Enable maximum compiler warnings

//---------------------------------------------------------------------------
// Class AutoGCHandle
//
// AutoGCHandle implements a simple System::Object->GCHandle conversion
// class. There are times when a quick GCHandle is required to pass a managed
// object into a C callback as a void pointer, that's what this is for.  As
// soon as this class unwinds, the GCHandle will be released, so use carefully
//---------------------------------------------------------------------------

class AutoGCHandle
{
public:

	//-----------------------------------------------------------------------
	// Constructor
	//
	// Arguments:
	//
	//	object		- Managed object to be wrapped in a GCHandle temporarily

	explicit AutoGCHandle(Object^ object) :
		m_ptr(reinterpret_cast<intptr_t>(GCHandle::ToIntPtr(GCHandle::Alloc(object)).ToPointer())) {}

	//-----------------------------------------------------------------------
	// Destructor
	//
	// Automatically frees the allocated GCHandle reference

	~AutoGCHandle() { GCHandle::FromIntPtr(IntPtr(m_ptr)).Free(); }

	//-----------------------------------------------------------------------
	// Overloaded Operators

	operator const void*() const { return reinterpret_cast<void*>(m_ptr); }
	operator void*() const { return reinterpret_cast<void*>(m_ptr); }

private:

	AutoGCHandle(const AutoGCHandle& rhs);
	AutoGCHandle& operator=(const AutoGCHandle& rhs);

	//-----------------------------------------------------------------------
	// Member Variables

	intptr_t				m_ptr;			// Pointer to managed buffer
};

//---------------------------------------------------------------------------

#pragma warning(pop)

#endif	// __AUTOGCHANDLE_H_
