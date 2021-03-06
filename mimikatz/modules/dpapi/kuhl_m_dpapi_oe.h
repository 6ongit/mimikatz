/*	Benjamin DELPY `gentilkiwi`
	http://blog.gentilkiwi.com
	benjamin@gentilkiwi.com
	Licence : http://creativecommons.org/licenses/by/3.0/fr/
*/
#pragma once
#include "globals.h"
#include "kuhl_m_dpapi.h"

typedef struct _KUHL_M_DPAPI_OE_MASTERKEY_ENTRY {
	LIST_ENTRY navigator;
	GUID	guid;
	BYTE	keyHash[SHA_DIGEST_LENGTH];
} KUHL_M_DPAPI_OE_MASTERKEY_ENTRY, *PKUHL_M_DPAPI_OE_MASTERKEY_ENTRY;

#define KUHL_M_DPAPI_OE_CREDENTIAL_FLAG_MD4		0x00000001
#define KUHL_M_DPAPI_OE_CREDENTIAL_FLAG_SHA1	0x00000002
#define KUHL_M_DPAPI_OE_CREDENTIAL_FLAG_MD4p	0x00000004
#define KUHL_M_DPAPI_OE_CREDENTIAL_FLAG_GUID	0x80000000
typedef struct _KUHL_M_DPAPI_OE_CREDENTIAL_ENTRY {
	LIST_ENTRY navigator;
	
	DWORD	flags;
	GUID	guid;
	PWSTR	sid;

	BYTE	md4hash[LM_NTLM_HASH_LENGTH];
	BYTE	md4hashDerived[SHA_DIGEST_LENGTH];
	
	BYTE	sha1hash[SHA_DIGEST_LENGTH];
	BYTE	sha1hashDerived[SHA_DIGEST_LENGTH];
	
	BYTE	md4protectedhash[LM_NTLM_HASH_LENGTH];
	BYTE	md4protectedhashDerived[SHA_DIGEST_LENGTH];
/*	
	PVOID DPAPI_SYSTEM_machine;
	PVOID DPAPI_SYSTEM_user;
	GUID  domainKeyGuid;
	DWORD domainKeyLen;
	PVOID domainKey;
*/
} KUHL_M_DPAPI_OE_CREDENTIAL_ENTRY, *PKUHL_M_DPAPI_OE_CREDENTIAL_ENTRY;

NTSTATUS kuhl_m_dpapi_oe_clean();
NTSTATUS kuhl_m_dpapi_oe_cache(int argc, wchar_t * argv[]);

LIST_ENTRY gDPAPI_Masterkeys;
LIST_ENTRY gDPAPI_Credentials;

PKUHL_M_DPAPI_OE_MASTERKEY_ENTRY kuhl_m_dpapi_oe_masterkey_get(LPCGUID guid);
BOOL kuhl_m_dpapi_oe_masterkey_add(LPCGUID guid, LPCVOID keyHash, DWORD keyLen);
void kuhl_m_dpapi_oe_masterkey_delete(PKUHL_M_DPAPI_OE_MASTERKEY_ENTRY entry);
void kuhl_m_dpapi_oe_masterkey_descr(PKUHL_M_DPAPI_OE_MASTERKEY_ENTRY entry);
void kuhl_m_dpapi_oe_masterkeys_delete();
void kuhl_m_dpapi_oe_masterkeys_descr();

PKUHL_M_DPAPI_OE_CREDENTIAL_ENTRY kuhl_m_dpapi_oe_credential_get(LPCWSTR sid, LPCGUID guid);
BOOL kuhl_m_dpapi_oe_credential_add(LPCWSTR sid, LPCGUID guid, LPCVOID md4hash, LPCVOID sha1hash, LPCVOID md4protectedhash, LPCWSTR password);
void kuhl_m_dpapi_oe_credential_delete(PKUHL_M_DPAPI_OE_CREDENTIAL_ENTRY entry);
void kuhl_m_dpapi_oe_credential_descr(PKUHL_M_DPAPI_OE_CREDENTIAL_ENTRY entry);
void kuhl_m_dpapi_oe_credentials_delete();
void kuhl_m_dpapi_oe_credentials_descr();

BOOL kuhl_m_dpapi_oe_credential_addtoEntry(PKUHL_M_DPAPI_OE_CREDENTIAL_ENTRY entry, LPCGUID guid, LPCVOID md4hash, LPCVOID sha1hash, LPCVOID md4protectedhash, LPCWSTR password);
BOOL kuhl_m_dpapi_oe_credential_copyEntryWithNewGuid(PKUHL_M_DPAPI_OE_CREDENTIAL_ENTRY entry, LPCGUID guid);