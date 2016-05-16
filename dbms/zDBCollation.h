//---------------------------------------------------------------------------
// zDBCollation Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBCOLLATION_H_
#define __ZDBCOLLATION_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Forward Class Declarations
//---------------------------------------------------------------------------

ref class zDBConnection;				// zDBConnection.h

//---------------------------------------------------------------------------
// Delegate zDBCollation
//
// Defines a collation delegate.  This standard version is used to compare
// two strings with the native machine UTF16 encoding.  If something other
// than this is required, use zDBBinaryCollation, which provides both arguments
// as an array of bytes that can be treated however the implementation sees fit
//---------------------------------------------------------------------------

public delegate int zDBCollation(zDBConnection^ conn, String^ left, String^ right);

//---------------------------------------------------------------------------
// Delegate zDBBinaryCollation
//
// Defines a collation delegate.  This version provides the data as two byte
// arrays that can be treated however the implementation sees fit.  If just
// comparing strings and the native UTF16 encoding is acceptable, use the
// standard zDBCollation instead.
//---------------------------------------------------------------------------

public delegate int zDBBinaryCollation(zDBConnection^ conn, array<System::Byte>^ left, array<System::Byte>^ right);

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBCOLLATION_H_