//---------------------------------------------------------------------------
// ITrackableObject Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ITRACKABLEOBJECT_H_
#define __ITRACKABLEOBJECT_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;

//---------------------------------------------------------------------------
// Interface ITrackableObject (internal)
//
// Interface that allows certain classes to keep track of other class
// instance lifetimes.  See zDBConnection and zDBCommand for places that 
// this gets used.
//---------------------------------------------------------------------------

interface class ITrackableObject : public IDisposable
{
	// IsDisposed
	//
	// Exposes an object's internal disposal state.  If the object is disposed,
	// it will be assumed that it's dead and doesn't need to be kept anymore
	bool IsDisposed(void);
};

//---------------------------------------------------------------------------

#pragma warning(pop)

#endif		// __ITRACKABLEOBJECT_H_