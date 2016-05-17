//---------------------------------------------------------------------------
// DatabaseHandle Implementation
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#include "stdafx.h"						// Include project pre-compiled headers
#include "DatabaseHandle.h"				// Include DatabaseHandle declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings
#pragma warning(disable:4100)			// "unreferenced formal parameter"

//---------------------------------------------------------------------------
// DatabaseHandle Constructor
//
// Arguments:
//
//	caller			- Object calling the ctor (for tracing purposes)
//	hDatabase		- The database handle to take ownership of

DatabaseHandle::DatabaseHandle(Object^ caller, sqlite3* hDatabase) : 
	m_hDatabase(hDatabase), m_cRefCount(1)
{
	if(!hDatabase) throw gcnew ArgumentNullException();	// Cannot be NULL

#ifdef ZDB_TRACE_HANDLEREF
	Debug::WriteLine(String::Format("DatabaseHandle 0x{0:X} ---> 1 (NEW via {1})", 
		IntPtr(this), caller->GetType()->Name));
#endif
}

//---------------------------------------------------------------------------
// DatabaseHandle Destructor (private)

DatabaseHandle::~DatabaseHandle()
{
	int nResult = sqlite3_close(m_hDatabase);
	if(nResult != SQLITE_OK); /* TODO (REMOVED): throw gcnew zDBException(m_hDatabase, nResult); */

#ifdef ZDB_TRACE_HANDLEREF
	Debug::WriteLine(String::Format("DatabaseHandle 0x{0:X} destroyed.", 
		IntPtr(this)));
#endif
}

//---------------------------------------------------------------------------
// DatabaseHandle::AddRef
//
// Increments the object reference count
//
// Arguments:
//
//	caller		- Object calling AddRef() for tracing purposes

void DatabaseHandle::AddRef(Object^ caller)
{
	InterlockedIncrement(&m_cRefCount);		// Increment reference count

#ifdef ZDB_TRACE_HANDLEREF
	Debug::WriteLine(String::Format("DatabaseHandle 0x{0:X} ---> {1} ({2})", 
		IntPtr(this), m_cRefCount, 
		(caller != nullptr) ? caller->GetType()->Name : "StatementHandle"));
#endif
}

//---------------------------------------------------------------------------
// DatabaseHandle::Release
//
// Releases a reference count on the object, and destroys itself at zero
//
// Arguments:
//
//	caller		- Object calling AddRef() for tracing purposes

void DatabaseHandle::Release(Object^ caller)
{
#ifdef ZDB_TRACE_HANDLEREF
	Debug::WriteLine(String::Format("DatabaseHandle 0x{0:X} <--- {1} ({2})", 
		IntPtr(this), m_cRefCount - 1, 
		(caller != nullptr) ? caller->GetType()->Name : "StatementHandle"));
#endif

	if(InterlockedDecrement(&m_cRefCount) == 0) delete this;
}

//---------------------------------------------------------------------------

#pragma warning(pop)
