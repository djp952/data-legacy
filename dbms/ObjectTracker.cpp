//---------------------------------------------------------------------------
// ObjectTracker Implementation
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#include "stdafx.h"					// Include project pre-compiled headers
#include "ObjectTracker.h"			// Include ObjectTracker declarations

#pragma warning(push, 4)			// Enable maximum compiler warnings

//---------------------------------------------------------------------------
// ObjectTracker::Free (private)
//
// Releases the contained GCHandle and resets everything
//
// Arguments:
//
//	NONE

void ObjectTracker::Free(void)
{
	if(m_alloc) m_gchandle.Free();			// Release the GCHandle
	m_alloc = false;						// Reset the allocation flag
}

//---------------------------------------------------------------------------
// ObjectTracker::Instance::get
//
// Gets a reference to the contained ITrackableObject instance, or nullptr
// if the object is no longer alive

ITrackableObject^ ObjectTracker::Instance::get(void)
{
	CHECK_DISPOSED(m_disposed);
	if(!IsAlive) return nullptr;

	return safe_cast<ITrackableObject^>(m_gchandle.Target);
}

//---------------------------------------------------------------------------
// ObjectTracker::IsObjectAlive (static)
//
// Helper function to test an ITrackableObject outside of this class
//
// Arguments:
//
//	obj		- Object instance to be tested

bool ObjectTracker::IsObjectAlive(ITrackableObject^ obj)
{
	if(obj == nullptr) return false;		// Null ref == not alive
	return !obj->IsDisposed();				// Use disposal status
}

//---------------------------------------------------------------------------
// ObjectTracker::IsAlive::get
//
// Determines if the object referenced herein is still alive or not

bool ObjectTracker::IsAlive::get(void)
{
	CHECK_DISPOSED(m_disposed);

	if((!m_alloc) || (!m_gchandle.IsAllocated)) return false;
	return IsObjectAlive(dynamic_cast<ITrackableObject^>(m_gchandle.Target));
}

//---------------------------------------------------------------------------
// ObjectTracker::SetObject
//
// Assigns a new ITrackableObject to this tracker instance.  Any previously
// set instance will be released automatically

void ObjectTracker::SetObject(ITrackableObject^ instance)
{
	CHECK_DISPOSED(m_disposed);

	Free();
	m_gchandle = GCHandle::Alloc(instance, GCHandleType::Weak);
	m_alloc = true;
}

//---------------------------------------------------------------------------

#pragma warning(pop)
