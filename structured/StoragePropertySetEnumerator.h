//---------------------------------------------------------------------------
// Copyright (c) 2016 Michael G. Brehm
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//---------------------------------------------------------------------------

#ifndef __STORAGEPROPERTYSETENUMERATOR_H_
#define __STORAGEPROPERTYSETENUMERATOR_H_
#pragma once

#include "ComStorage.h"					// Include ComStorage declarations
#include "StorageException.h"			// Include StorageException declarations
#include "StorageExceptions.h"			// Include exception declarations
#include "StorageUtil.h"				// Include StorageUtil declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace msclr;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(structured)

//---------------------------------------------------------------------------
// Forward Class Declarations
//
// Include the specified header files in the .CPP file for this class
//---------------------------------------------------------------------------

ref class StructuredStorage;				// <-- StructuredStorage.h
ref class StoragePropertySet;				// <-- StoragePropertySet.h

//---------------------------------------------------------------------------
// Class StoragePropertySetEnumerator
//
// StoragePropertySetEnumerator generates an IEnumerator<> implementation.
// The enumeration is based on a 'snapshot' of the current set of propsets
// that are contained within the parent container rather than a cached off
// collection. This allows for much more advanced techniques than were 
// possible with the old collection implementation.
//---------------------------------------------------------------------------

STRUCTURED_STORAGE_PUBLIC ref class StoragePropertySetEnumerator sealed : 
	public Generic::IEnumerator<StoragePropertySet^>
{
public:

	//-----------------------------------------------------------------------
	// IEnumerator<T> Implementation

	virtual property StoragePropertySet^ Current { StoragePropertySet^ get(void); }
	
	virtual bool MoveNext(void);
	virtual void Reset(void);

internal:

	// INTERNAL CONSTRUCTOR
	StoragePropertySetEnumerator(StructuredStorage^ root, ComStorage^ storage);

private:

	// DESTRUCTOR
	~StoragePropertySetEnumerator() { m_disposed = true; }

	//-----------------------------------------------------------------------
	// Private Member Functions

	virtual property Object^ _Current {
		Object^ get(void) sealed = Collections::IEnumerator::Current::get { return Current; }
	}

	//-----------------------------------------------------------------------
	// Member Variables

	bool						m_disposed;			// Object disposal status
	StructuredStorage^			m_root;				// Root Storage object
	ComStorage^					m_storage;			// Contained ComStorage
	int							m_current;			// Current item index
	array<Guid>^				m_items;			// Enumerated object guids
};

//---------------------------------------------------------------------------

END_NAMESPACE(structured)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __STORAGEPROPERTYSETENUMERATOR_H_
