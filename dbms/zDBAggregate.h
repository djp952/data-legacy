//---------------------------------------------------------------------------
// zDBAggregate Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBAGGREGATE_H_
#define __ZDBAGGREGATE_H_
#pragma once

#include "zDBArgumentCollection.h"		// Include zDBArgumentCollection decls
#include "zDBResult.h"					// Include zDBResult declarations

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Data;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Class zDBAggregate
//
// zDBAggregate is the base class that must be implemented by all custom
// aggregate function classes.  With this new provider, I've decided to
// make this work significantly differently than it used to.  Now you'll
// need to register a TYPE instead of an INSTANCE.  This lets the provider
// construct and destroy the aggregates as needed, which solves the problem
// of the derived class needing to maintain it's own state, which was kinda
// icky and I didn't like it much.
//
// Note: The ability for SQLite to count the number of rows on the aggregate's
// behalf has been deprecated and does not appear here.  The aggregate must
// keep track of that on it's own now.  Another good reason to switch to
// the type-based single instance methodology.
//---------------------------------------------------------------------------

public ref class zDBAggregate abstract
{
protected public:

	// Accumulate (must override)
	//
	// Called once per row to allow accumulation of the final result
	virtual void Accumulate(zDBArgumentCollection^ args) abstract;

	// GetResult (must override)
	//
	// Called when all rows have been processed to get the final result
	virtual void GetResult(zDBResult^ result) abstract;

private:

	// DESTRUCTOR (STUB)
	~zDBAggregate() {}
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBAGGREGATE_H_