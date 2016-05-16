//---------------------------------------------------------------------------
// zDBPermissionAttribute Implementation
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#include "stdafx.h"					// Include project pre-compiled headers
#include "zDBPermissionAttribute.h"	// Include zDBPermissionAttribute decls
#include "zDBPermission.h"			// Include zDBPermission declarations

#pragma warning(push, 4)			// Enable maximum compiler warnings

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// zDBPermissionAttribute::CreatePermission
//
// Creates an instance of the zDBPermission class
//
// Arguments:
//
//	NONE

IPermission^ zDBPermissionAttribute::CreatePermission(void)
{
	return gcnew zDBPermission(this);
}

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)
