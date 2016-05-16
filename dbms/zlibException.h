//---------------------------------------------------------------------------
// zlibException Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZLIBEXCEPTION_H_
#define __ZLIBEXCEPTION_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Class zlibException
//
// zlibException is the generic exception thrown when a ZLIB engine error
// has occurred
//---------------------------------------------------------------------------

public ref class zlibException sealed : public Exception
{
internal:

	//-----------------------------------------------------------------------
	// Constructor
	//
	// Arguments:
	//
	//	nResult		- The ZLIB error code returned

	zlibException(int nResult) : Exception(GenerateMessage(nResult)) {}

	//-----------------------------------------------------------------------
	// Constructor
	//
	// Arguments:
	//
	//	nResult		- The ZLIB error code returned
	//	context		- A context message to append at the end

	zlibException(int nResult, String^ context)
		: Exception(String::Format("{0}\r\n\r\nContext:\r\n{1}", GenerateMessage(nResult), context)) {}
	
private:
	
	//-----------------------------------------------------------------------
	// Private Member Functions

	static String^ GenerateMessage(int nResult)
	{
		return String::Format("ZLIB Compression Error {0}: {1}", nResult, 
			Marshal::PtrToStringAnsi(IntPtr(const_cast<char*>(zError(nResult)))));
	}
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __ZLIBEXCEPTION_H_
