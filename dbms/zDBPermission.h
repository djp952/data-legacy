//---------------------------------------------------------------------------
// zDBPermission Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBPERMISSION_H_
#define __ZDBPERMISSION_H_
#pragma once

#include "zDBPermissionAttribute.h"		// Include zDBPermissionAttribute decls

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::Data;
using namespace System::Data::Common;
using namespace System::Security;
using namespace System::Security::Permissions;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Class zDBPermission
//
// zDBPermission is ... useful ... somehow.  Not really sure how, so this is
// pretty much just a stub until I figure out why Code Access Security is a 
// useful thing in ADO.NET.
//---------------------------------------------------------------------------

public ref class zDBPermission sealed : public DBDataPermission
{
public:

	//-----------------------------------------------------------------------
	// Constructors

	zDBPermission(PermissionState state) : DBDataPermission(state) {}

	//-----------------------------------------------------------------------
	// Member Functions

	// Copy (DBDataPermission)
	//
	// Creates a copy of this permission object
	virtual IPermission^ Copy(void) override { return gcnew zDBPermission(this); }

internal:

	// INTERNAL CONSTRUCTOR
	zDBPermission(zDBPermissionAttribute^ attribute) : DBDataPermission(attribute) {}

private:

	// PRIVATE COPY CONSTRUCTOR
	zDBPermission(zDBPermission^ rhs) : DBDataPermission(rhs) {}
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBPERMISSION_H_