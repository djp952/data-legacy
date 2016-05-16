//---------------------------------------------------------------------------
// zDBDelegates Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBDELEGATES_H_
#define __ZDBDELEGATES_H_
#pragma once

#include "zDBEventArgs.h"				// Include zDB eventarg declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Delegate zDBAuthorizeEventHandler
//
// Used by zDBConnection to raise a hooked authorization event
public delegate void zDBAuthorizeEventHandler(Object^ sender, zDBAuthorizeEventArgs^ args);

//---------------------------------------------------------------------------
// Delegate zDBCollationNeededEventHandler
//
// Used by zDBConnection to raise a hooked collation needed event
public delegate void zDBCollationNeededEventHandler(Object^ sender, zDBCollationNeededEventArgs^ args);

//---------------------------------------------------------------------------
// Delegate zDBProfileEventHandler
//
// Used by zDBConnection to raise a hooked profile message event
public delegate void zDBProfileEventHandler(Object^ sender, zDBProfileEventArgs^ args);

//---------------------------------------------------------------------------
// Delegate zDBRowChangedEventHandler
//
// Used by zDBConnection to raise a hooked DELETE/INSERT/UPDATE event
public delegate void zDBRowChangedEventHandler(Object^ sender, zDBRowChangedEventArgs^ args);

//---------------------------------------------------------------------------
// Delegate zDBRowUpdatingEventHandler
//
// Used by zDBDataAdapter to raise an event
public delegate void zDBRowUpdatingEventHandler(Object^ sender, zDBRowUpdatingEventArgs^ args);

//---------------------------------------------------------------------------
// Delegate zDBRowUpdatedEventHandler
//
// Used by zDBDataAdapter to raise an event
public delegate void zDBRowUpdatedEventHandler(Object^ sender, zDBRowUpdatedEventArgs^ args);

//---------------------------------------------------------------------------
// Delegate zDBTraceEventHandler
//
// Used by zDBConnection to raise a hooked trace message event
public delegate void zDBTraceEventHandler(Object^ sender, zDBTraceEventArgs^ args);

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBDELEGATES_H_