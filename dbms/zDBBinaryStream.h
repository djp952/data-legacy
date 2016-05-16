//---------------------------------------------------------------------------
// zDBBinaryStream Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBBINARYSTREAM_H_
#define __ZDBBINARYSTREAM_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Data;
using namespace System::Diagnostics;
using namespace System::IO;
using namespace System::Runtime::InteropServices;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Class zDBBinaryStream
//
// zDBBinaryStream provides a wrapper around a regular old MemoryStream object
// that is used to pass very large BLOB data more efficiently with zDBResult.
// Instead of forcing SQLite to make a copy of the data, this class will have
// it's underlying buffer pinned in place and provide SQLite a callback that
// it will call when it's done to unpin it.  As a side effect of this, once
// the pin has been generated, the data becomes immutable.  This isn't really
// an issue in the context that this class is used (function results).
//
// In order to accomplish this, the MemoryStream is prepended with a pair
// of serialized GCHandles.  The first, at offset -8, is a strong GCHandle
// against the zDBBinaryStream itself.  The second, at offset -4, is a 
// pinning GCHandle against the MemoryStream's backing byte array.  These
// are allocated and set when the object is locked, and cleaned up when the
// object is released by SQLite (via the unmanaged callback in the .cpp file)
//---------------------------------------------------------------------------

public ref class zDBBinaryStream sealed : public Stream
{
public:

	zDBBinaryStream();
	zDBBinaryStream(int capacity);

	//-----------------------------------------------------------------------
	// Member Functions
	
	// NOTE: You never override Stream::Close(), you implement IDisposable

	// Flush (Stream)
	//
	// Flushes any changes to this stream to the backing store
	virtual void Flush() override;
	
	// Read (Stream)
	//
	// Reads a set of values from the stream into the provided buffer
	virtual	int	Read(array<System::Byte>^ buffer, int offset, int count) override;
	
	// Seek (Stream)
	//
	// Moves the internal stream data pointer
	virtual __int64	Seek(__int64 offset, SeekOrigin origin) override;
	
	// SetLength (Stream)
	//
	// Extends or truncates the stream to the specified length
	virtual void SetLength(__int64 value) override;
	
	// Write (Stream)
	//
	// Writes a specific number of bytes into the stream
	virtual void Write(array<System::Byte>^ buffer, int offset, int count) override;

	//-----------------------------------------------------------------------
	// Properties

	// CanRead (Stream)
	//
	// Determines if the stream can currently be read from
	virtual property bool CanRead { bool get(void) override; }
	
	// CanSeek (Stream)
	//
	// Determines if the stream pointer can be repositioned
	virtual property bool CanSeek { bool get(void) override; }
	
	// CanWrite (Stream)
	//
	// Determines if the stream can currently be written into
	virtual property bool CanWrite { bool get(void) override; }
	
	// Length (Stream)
	//
	// Exposes the current overall length of the stream
	virtual property __int64 Length { __int64 get(void) override; }

	// Position (Stream)
	//
	// Gets or sets the absolute position of the stream pointer
	virtual property __int64 Position 
	{ 
		__int64 get(void) override;
		void set(__int64 value) override;
	}

internal:

	//-----------------------------------------------------------------------
	// Internal Constants

	// RESERVED_SPACE
	//
	// Amount of space, in bytes, to reserve in the MemoryStream
	literal int RESERVED_SPACE = (sizeof(void*) * 2);

	//-----------------------------------------------------------------------
	// Internal Type Declarations

	// RELEASEFUNC
	//
	// Typedef for a standard SQLite result release function
	typedef void(* RELEASEFUNC)(void*);

	//-----------------------------------------------------------------------
	// Internal Member Functions

	// Lock
	//
	// Locks down and pins the contained memory stream for direct access.
	// When SQLite invokes the release function, the class will be disposed
	// of, so once this happens it's not possible to ever modify the stream
	int Lock(void** ppv);

	//-----------------------------------------------------------------------
	// Internal Properties

	// OnRelease
	//
	// Exposes the local unmanaged function passed into SQLite to release
	// a zDBBinaryStream that has been locked
	static property RELEASEFUNC OnRelease { RELEASEFUNC get(void); }

private:

	// DESTRUCTOR
	~zDBBinaryStream() { delete m_stream; m_disposed = true; }

	//-----------------------------------------------------------------------
	// Member Variables

	bool					m_disposed;		// Object disposal flag
	bool					m_locked;		// Flag if stream is locked
	MemoryStream^			m_stream;		// Underlying MemoryStream object
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBBINARYSTREAM_H_