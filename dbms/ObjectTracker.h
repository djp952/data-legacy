//---------------------------------------------------------------------------
// ObjectTracker Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __OBJECTTRACKER_H_
#define __OBJECTTRACKER_H_
#pragma once

#include "ITrackableObject.h"			// Include ITrackableObject decls

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Runtime::InteropServices;

//---------------------------------------------------------------------------
// Class ObjectTracker (internal)
//
// ObjectTracker works with the ITrackableObject interface to keep tabs
// on the status of an object instance.  A weak GCHandle is allocated for
// the tracked object, and that along with ITrackableObject is how this
// determines if an object is alive or dead.
//---------------------------------------------------------------------------

ref class ObjectTracker
{
public:

	ObjectTracker() {}

	//-----------------------------------------------------------------------
	// Member Functions

	// IsObjectAlive
	//
	// Static method that can be called as a convenience to test an instance
	// of ITrackableObject outside of this class
	static bool IsObjectAlive(ITrackableObject^ obj);

	// SetObject
	//
	// Sets the object to be tracked.  Automatically removes any previous one
	void SetObject(ITrackableObject^ instance);

	//-----------------------------------------------------------------------
	// Properties

	// Instance
	//
	// Gets a reference to the contained ITrackableObject interface
	property ITrackableObject^ Instance 
	{ 
		ITrackableObject^ get(void);
		void set(ITrackableObject^ value) { SetObject(value); }
	}

	// IsAlive
	//
	// Determines if the referenced object is alive or not
	property bool IsAlive { bool get(void); }

private:

	// DESTRUCTOR / FINALIZER
	~ObjectTracker() { this->!ObjectTracker(); m_disposed = true; }
	!ObjectTracker() { Free(); }

	//-----------------------------------------------------------------------
	// Private Member Functions

	// Free
	//
	// Releases the contained GCHandle, if it's allocated
	void Free(void);

	//-----------------------------------------------------------------------
	// Member Variables

	bool					m_disposed;			// Object disposal flag
	bool					m_alloc;			// GCHandle allocation flag
	GCHandle				m_gchandle;			// Object weak GCHandle
};

//---------------------------------------------------------------------------

#pragma warning(pop)

#endif		// __OBJECTTRACKER_H_