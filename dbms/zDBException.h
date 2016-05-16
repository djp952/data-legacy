//---------------------------------------------------------------------------
// zDBException Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBEXCEPTION_H_
#define __ZDBEXCEPTION_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Data::Common;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Class zDBException
//
// The exception that is thrown when a database engine error has occurred.
// Also used as a base class for all custom provider exceptions to allow
// applications to simply "catch(zDBException^)" instead of specific ones.
// This works out pretty well, since a provider exception is essentially the
// same thing as an engine exception to the end user.
//---------------------------------------------------------------------------

public ref class zDBException : public DbException
{
public:

	//-----------------------------------------------------------------------
	// Properties

	// IsEngineException
	//
	// Flag determining if this is a SQLite engine error or not
	property bool IsEngineException { bool get(void) { return (ErrorCode != SQLITE_PROVIDER); } }

	// IsProviderException
	//
	// Flag determining if this is a provider-based error or not
	property bool IsProviderException { bool get(void) { return (ErrorCode == SQLITE_PROVIDER); } }

protected private:

	// PROTECTED CONSTRUCTORS
	//
	// Use these when deriving from the zDBException class for a custom
	// provider exception instead of an engine exception
	zDBException(String^ message);

internal:

	// INTERNAL CONSTRUCTORS
	//
	// Use these when a SQLite engine error has occurred
	zDBException(int nResult);
	zDBException(int nResult, String^ context);
	zDBException(sqlite3* hDatabase, int nResult);
	zDBException(sqlite3* hDatabase, int nResult, String^ context);

private:

	//-----------------------------------------------------------------------
	// Private Constants

	// SQLITE_PROVIDER
	//
	// Indicates a provider specific error, not a SQLite engine error
	literal int SQLITE_PROVIDER = 255;

	//-----------------------------------------------------------------------
	// Private Member Functions

	static String^ GenerateMessage(sqlite3* hDatabase, int nResult);
	static HRESULT MakeHResult(int nResult);
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBEXCEPTION_H_