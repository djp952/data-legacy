//---------------------------------------------------------------------------
// zDBArgumentCollection Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBARGUMENTCOLLECTION_H_
#define __ZDBARGUMENTCOLLECTION_H_
#pragma once

#include "zDBArgument.h"				// Include zDBArgument declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Class zDBArgumentCollection
//
// zDBArgumentCollection represents a read-only collection of zDBArgument
// object instances.  Essentially just a typedef of ReadOnlyCollection<>
// with some constructors to make my own life slightly easier
//
// Note that arguments (or sqlite3_values, if you prefer) are designed to
// be volatile and must be properly disposed of when done working with them.
// This allows for the performance we need and prevents applications from
// sneaking references to the arguments out of context and accessing bad data
// long after the underlying SQLite pointers have disappeared.
//---------------------------------------------------------------------------

public ref class zDBArgumentCollection sealed : public ReadOnlyCollection<zDBArgument^>
{
internal:

	// INTERNAL CONSTRUCTORS
	zDBArgumentCollection(int argc, sqlite3_value** argv) : ReadOnlyCollection(MakeList(argc, argv)) {}

private:

	// DESTRUCTOR
	~zDBArgumentCollection() { for each(zDBArgument^ arg in this) delete arg; }

	//-----------------------------------------------------------------------
	// Private Member Functions

	// MakeList
	//
	// Creates a List<zDBArgument^>^ that can be used to back the underlying
	// ReadOnlyCollection.  Provided mainly for flexibility
	static List<zDBArgument^>^ MakeList(int argc, sqlite3_value** argv)
	{
		List<zDBArgument^>^ list = gcnew List<zDBArgument^>(argc);
		for(int index = 0; index < argc; index++) list->Add(gcnew zDBArgument(argv[index]));

		return list;				// Return the generated List<> object
	}
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBARGUMENTCOLLECTION_H_