//---------------------------------------------------------------------------
// FunctionMap Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __FUNCTIONMAP_H_
#define __FUNCTIONMAP_H_
#pragma once

#include <map>							// Include STL map<> declarations
#include <string>						// Include STL string<> declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

//---------------------------------------------------------------------------
// Class FunctionMapKey
//
// Used as the key type for the FunctionMap collection.  The Argument field
// means something different depending on if you're working with functions
// or collations.  With functions, this defines the number of arguments.  With
// collations, this is the encoding mode used when SQLite invokes the callback.
//---------------------------------------------------------------------------

struct FunctionMapKey
{
	FunctionMapKey(const wchar_t* name, int arg) : Name(name), Argument(arg) {}
	FunctionMapKey(const FunctionMapKey& rhs) : Name(rhs.Name), Argument(rhs.Argument) {}

	//-----------------------------------------------------------------------
	// Overloaded Operators

	FunctionMapKey& operator=(const FunctionMapKey& rhs)
	{
		Name = rhs.Name;
		Argument = rhs.Argument;
		return *this;
	}

	//-----------------------------------------------------------------------
	// Public Fields

	std::wstring	Name;				// Function name string
	int				Argument;			// Argument data (depends on context)
};

//---------------------------------------------------------------------------
// Class FunctionMapKeyComparer
//
// Used as the "less" binary function for STL collections
//---------------------------------------------------------------------------

struct FunctionMapKeyComparer : 
	public std::binary_function<const FunctionMapKey&, const FunctionMapKey&, bool>
{
	bool operator ()(const FunctionMapKey& lhs, const FunctionMapKey& rhs) const 
	{
		// Use the string portion of the key as the main comparison, and only
		// when they are equal (case-insensitive), head over to the argument.
		
		int result = _wcsicmp(lhs.Name.c_str(), rhs.Name.c_str());
		if(result == 0) return (lhs.Argument < rhs.Argument);
		else return (result < 0);
	}
};

//---------------------------------------------------------------------------
// Typedef FunctionMap
//
// FunctionMap implements an STL map<> of FunctionMapKeys->intptr_t.  This
// is used as the collection basis in zDBAggregateCollection, zDBCollationCollection
// and zDBFunctionCollection so that the class finalizers can reliably release
// any serialized GCHandles that still exist
//---------------------------------------------------------------------------

typedef std::map<FunctionMapKey, intptr_t, FunctionMapKeyComparer>	FunctionMap;
typedef FunctionMap::iterator										FunctionMapIterator;

//---------------------------------------------------------------------------

#pragma warning(pop)

#endif		// __FUNCTIONMAP_H_