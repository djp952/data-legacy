//---------------------------------------------------------------------------
// zDBCollationWrapper Implementation
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#include "stdafx.h"					// Include project pre-compiled headers
#include "zDBCollationWrapper.h"	// Include zDBCollationWrapper declarations
#include "zDBConnection.h"			// Include zDBConnection declarations

#pragma warning(push, 4)			// Enable maximum compiler warnings

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// zDBCollationWrapper::Invoke
//
// Invokes the contained delegate.  Depending on what kind of delegate was
// provided, the data will be treated as native UTF16 strings or a pair of
// byte arrays.
//
// Arguments:
//
//	pvLeft			- Pointer to the left-hand value
//	cbLeft			- Size of the left-hand value, in bytes
//	pvRight			- Pointer to the right-hand value
//	cbRight			- Size of the right-hand value, in bytes

int zDBCollationWrapper::Invoke(const void* pvLeft, int cbLeft, const void* pvRight, int cbRight)
{
	// Call into one of the specialized delegate invokers to do the conversion
	// and work.  If for some reason there is no delegate, we have no way to 
	// communicate that back to SQLite so just return zero

	if(m_std != nullptr) return InvokeString(pvLeft, cbLeft, pvRight, cbRight);
	else if(m_bin != nullptr) return InvokeBinary(pvLeft, cbLeft, pvRight, cbRight);
	else return 0;
}

//---------------------------------------------------------------------------
// zDBCollationWrapper::InvokeBinary
//
// Invokes the contained byte array collation delegate
//
// Arguments:
//
//	pvLeft			- Pointer to the left-hand value
//	cbLeft			- Size of the left-hand value, in bytes
//	pvRight			- Pointer to the right-hand value
//	cbRight			- Size of the right-hand value, in bytes

int zDBCollationWrapper::InvokeBinary(const void* pvLeft, int cbLeft, const void* pvRight, int cbRight)
{
	array<System::Byte>^		left;			// Left-hand array of bytes
	array<System::Byte>^		right;			// Right-hand array of bytes
	PinnedBytePtr				pinBytes;		// Pinned byte array pointer
	int							result;			// Result of collation function

	Debug::Assert(m_bin != nullptr);

	// Allocate and initialize the left-hand collation byte array

	left = gcnew array<System::Byte>(cbLeft);
	if(cbLeft) {

		pinBytes = &left[0];
		memcpy_s(pinBytes, left->Length, pvLeft, cbLeft);
	}

	// Allocate and initialize the right-hand collection byte array
	right = gcnew array<System::Byte>(cbRight);
	if(cbRight) {

		pinBytes = &right[0];
		memcpy_s(pinBytes, right->Length, pvRight, cbRight);
	}

	zDBConnection^ conn = zDBConnection::FindConnection(m_hDatabase);

	result = m_bin(conn, left, right);			// Invoke the delegate handler
	if(conn != nullptr) GC::KeepAlive(conn);	// Keep alive until here
	return result;								// Return result from collation
}

//---------------------------------------------------------------------------
// zDBCollationWrapper::InvokeString
//
// Invokes the contained string collation delegate
//
// Arguments:
//
//	pvLeft			- Pointer to the left-hand value
//	cbLeft			- Size of the left-hand value, in bytes
//	pvRight			- Pointer to the right-hand value
//	cbRight			- Size of the right-hand value, in bytes

int zDBCollationWrapper::InvokeString(const void* pvLeft, int cbLeft, const void* pvRight, int cbRight)
{
	String^						left;			// Left-hand string for comparison
	String^						right;			// Right-hand string for comparison
	int							result;			// Result of collation function

	Debug::Assert(m_std != nullptr);

	// Allocate and initialize the managed strings.  We always pass UTF16 into create()
	// for this provider, so this would work just dandy.  It's also much faster than
	// calling Marshal::PtrToStringUni, which uses a StringBuilder of all things

	left = gcnew String(reinterpret_cast<const wchar_t*>(pvLeft), 0, cbLeft / sizeof(wchar_t));
	right = gcnew String(reinterpret_cast<const wchar_t*>(pvRight), 0, cbRight / sizeof(wchar_t));
	
	zDBConnection^ conn = zDBConnection::FindConnection(m_hDatabase);

	result = m_std(conn, left, right);			// Invoke the delegate handler
	if(conn != nullptr) GC::KeepAlive(conn);	// Keep alive until here
	return result;								// Return result from collation
}

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)
