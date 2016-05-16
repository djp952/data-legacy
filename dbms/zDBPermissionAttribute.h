//---------------------------------------------------------------------------
// zDBPermissionAttribute Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBPERMISSIONATTRIBUTE_H_
#define __ZDBPERMISSIONATTRIBUTE_H_
#pragma once

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
// Forward Class Declarations
//---------------------------------------------------------------------------

ref class zDBPermission;				// zDBPermission.h

//---------------------------------------------------------------------------
// Class zDBPermissionAttribute
//
// zDBPermissionAttribute associates a security action with a custom security 
// attribute.  Pretty basic stuff, but this is all the built-in ADO.NET
// providers seem to do with their implementations, so I'm assuming this will
// be sufficient (once I realize how Code Access Security is a useful thing
// when dealing with ADO.NET providers)
//---------------------------------------------------------------------------

public ref class zDBPermissionAttribute sealed : public DBDataPermissionAttribute
{
public:

	//-----------------------------------------------------------------------
	// Constructors

	zDBPermissionAttribute(SecurityAction action) : DBDataPermissionAttribute(action) {}

	//-----------------------------------------------------------------------
	// Member Functions

	// CreatePermission
	//
	// Creates a permission object that can be serialized into an assembly's metadata
	virtual IPermission^ CreatePermission(void) override;
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif		// __ZDBPERMISSIONATTRIBUTE_H_