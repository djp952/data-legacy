//---------------------------------------------------------------------------
// zDBCryptoKey Declarations
//
// ZukiSoft ADO.NET provider for SQLite
//
// Copyright (C)2006 Michael Brehm
// All Rights Reserved
//---------------------------------------------------------------------------

#ifndef __ZDBCRYPTOKEY_H_
#define __ZDBCRYPTOKEY_H_
#pragma once

#pragma warning(push, 4)				// Enable maximum compiler warnings

using namespace System;
using namespace System::ComponentModel;
using namespace System::Runtime::InteropServices;
using namespace System::Security;
using namespace System::Security::Cryptography;
using namespace System::Text;

BEGIN_NAMESPACE(zuki)
BEGIN_NAMESPACE(data)
BEGIN_NAMESPACE(dbms)

//---------------------------------------------------------------------------
// Class zDBCryptoKey (internal)
//
// zDBCryptoKey is used to generate and store the cryptography key(s) used
// with the ENCRYPT() and DECRYPT() scalar functions built into the provider.
//
// Note that this is a carry-over from the 1.1 provider in order to maintain
// compatibility with both it and the Windows CE version of it.  It has been
// modified slightly to use SecureString, but otherwise it's pretty much an
// identical implementation. for better or worse.
//---------------------------------------------------------------------------

ref class zDBCryptoKey
{
public:

	//-----------------------------------------------------------------------
	// Constructor / Destructor

	zDBCryptoKey(SecureString^ password);

	//-----------------------------------------------------------------------
	// Properties

	// Key
	//
	// Returns the HCRYPTKEY handle
	property HCRYPTKEY Key
	{
		HCRYPTKEY get(void) { return reinterpret_cast<HCRYPTKEY>(m_ptKey.ToPointer()); }
	}

private:

	// DESTRUCTOR / FINALIZER
	~zDBCryptoKey() { this->!zDBCryptoKey(); m_disposed = true; }
	!zDBCryptoKey();

	//-----------------------------------------------------------------------
	// Private Member Functions

	// CreatePrivateExponentOneKey
	//
	// Used for key generation -- see code
	static BOOL CreatePrivateExponentOneKey(LPCTSTR szProvider, DWORD dwProvType, 
		LPCTSTR szContainer, DWORD dwKeySpec, HCRYPTPROV *hProv, HCRYPTKEY *hPrivateKey);
		
	// ImportPlainSessionBlob
	//
	// Used for key generation -- see code
	static BOOL ImportPlainSessionBlob(HCRYPTPROV hProv, HCRYPTKEY hPrivateKey, 
		ALG_ID dwAlgId, const BYTE* pbKeyMaterial, DWORD dwKeyMaterial, HCRYPTKEY *hSessionKey);

	//-----------------------------------------------------------------------
	// Member Variables

	bool					m_disposed;			// Object disposal flag
	IntPtr					m_ptProv;			// Really HCRYPTPROV
	IntPtr					m_ptPrivKey;		// Really HCRYPTKEY
	IntPtr					m_ptKey;			// Really HCRYPTKEY
};

//---------------------------------------------------------------------------

END_NAMESPACE(dbms)
END_NAMESPACE(data)
END_NAMESPACE(zuki)

#pragma warning(pop)

#endif	// __ZDBCRYPTOKEY_H_