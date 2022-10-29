
#include "acf_Types.h"
#include "acf_Class.h"
#include "acf_Conv.h"

#include "include/cef_request_handler.h"
#include "include/cef_x509_certificate.h"

extern DWORD acf_certificate_funcs[];
extern DWORD acf_certprincipal_funcs[];
extern DWORD acf_ssl_status_funcs[];
extern DWORD acf_callback_certificate[];
extern DWORD acf_binary_funcs[];

void ECALL certselect_select(CefSelectClientCertificateCallback* obj, CefX509Certificate* cert)
{
	ISVALID(obj);

	obj->Select(cert);
}

DWORD acf_callback_certificate[] = {
	(DWORD)&certselect_select,
};

bool ECALL cert_get_subject(CefX509Certificate* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefX509CertPrincipal> pObj = obj->GetSubject();

	pObj->AddRef();
	target[1] = (DWORD)((LPVOID)pObj.get());
	target[2] = (DWORD)acf_certprincipal_funcs;

	return !!pObj;
}

bool ECALL cert_get_issuer(CefX509Certificate* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefX509CertPrincipal> pObj = obj->GetIssuer();

	pObj->AddRef();
	target[1] = (DWORD)((LPVOID)pObj.get());
	target[2] = (DWORD)acf_certprincipal_funcs;

	return !!pObj;
}

bool ECALL cert_get_serial_number(CefX509Certificate* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefBinaryValue> pObj = obj->GetSerialNumber();

	pObj->AddRef();
	target[1] = (DWORD)((LPVOID)pObj.get());
	target[2] = (DWORD)acf_binary_funcs;

	return !!pObj;
}

bool ECALL cert_get_valid_start(CefX509Certificate* obj, cef_time_t** target)
{
	ISVALIDR(obj, false);

	cef_time_from_basetime(obj->GetValidStart(), *target);

	return target != NULL;
}

bool ECALL cert_get_valid_expiry(CefX509Certificate* obj, cef_time_t** target)
{
	ISVALIDR(obj, false);

	cef_time_from_basetime(obj->GetValidExpiry(), *target);

	return target != NULL;
}

bool ECALL cert_get_DER_encoded(CefX509Certificate* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefBinaryValue> pObj = obj->GetDEREncoded();

	pObj->AddRef();
	target[1] = (DWORD)((LPVOID)pObj.get());
	target[2] = (DWORD)acf_binary_funcs;

	return !!pObj;
}

bool ECALL cert_get_PEM_encoded(CefX509Certificate* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefBinaryValue> pObj = obj->GetPEMEncoded();

	pObj->AddRef();
	target[1] = (DWORD)((LPVOID)pObj.get());
	target[2] = (DWORD)acf_binary_funcs;

	return !!pObj;
}

int ECALL cert_get_issuer_chain_size(CefX509Certificate* obj)
{
	ISVALIDR(obj, false);

	return obj->GetIssuerChainSize();
}

BOOL ECALL cert_get_der_encoded_issuer_chain(CefX509Certificate* obj, LPVOID* eArray)
{
	ISVALIDR(obj, false);

	std::vector<CefRefPtr<CefBinaryValue>> binary_list;
	obj->GetDEREncodedIssuerChain(binary_list);

	DWORD* pStrs = new DWORD[binary_list.size()];
	for (size_t i = 0; i < binary_list.size(); i++)
	{
		PECLASS_VFPTR pNewClass = new ECLASS_VFPTR;
		pNewClass->dwVfTable = eClass::m_pVfBinaryValueTable;
		pNewClass->pCFuncs = acf_binary_funcs;
		binary_list[i]->AddRef();
		pNewClass->pObject = ((LPVOID)(binary_list[i].get()));

		pStrs[i] = (DWORD)pNewClass;
	}

	int nSize = binary_list.size() * sizeof(DWORD);
	LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
	*(LPINT)pAry = 1;
	*(LPINT)(pAry + sizeof(INT)) = binary_list.size();
	memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
	delete[]pStrs;

	*eArray = pAry;

	return eArray != NULL;
}

BOOL ECALL cert_get_pem_encoded_issuer_chain(CefX509Certificate* obj, LPVOID* eArray)
{
	ISVALIDR(obj, false);

	std::vector<CefRefPtr<CefBinaryValue>> binary_list;
	obj->GetPEMEncodedIssuerChain(binary_list);

	DWORD* pStrs = new DWORD[binary_list.size()];
	for (size_t i = 0; i < binary_list.size(); i++)
	{
		PECLASS_VFPTR pNewClass = new ECLASS_VFPTR;
		pNewClass->dwVfTable = eClass::m_pVfBinaryValueTable;
		pNewClass->pCFuncs = acf_binary_funcs;
		binary_list[i]->AddRef();
		pNewClass->pObject = ((LPVOID)(binary_list[i].get()));

		pStrs[i] = (DWORD)pNewClass;
	}

	int nSize = binary_list.size() * sizeof(DWORD);
	LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
	*(LPINT)pAry = 1;
	*(LPINT)(pAry + sizeof(INT)) = binary_list.size();
	memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
	delete[]pStrs;

	*eArray = pAry;

	return eArray != NULL;
}

DWORD acf_certificate_funcs[] = {
	(DWORD)&cert_get_subject,
	(DWORD)&cert_get_issuer,
	(DWORD)&cert_get_serial_number,
	(DWORD)&cert_get_valid_start,
	(DWORD)&cert_get_valid_expiry,
	(DWORD)&cert_get_DER_encoded,
	(DWORD)&cert_get_PEM_encoded,
	(DWORD)&cert_get_issuer_chain_size,
	(DWORD)&cert_get_der_encoded_issuer_chain,
	(DWORD)&cert_get_pem_encoded_issuer_chain,
};

int ECALL certpl_get_display_name(CefX509CertPrincipal* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetDisplayName().c_str());

	return ansi_str != 0;
}

int ECALL certpl_get_common_name(CefX509CertPrincipal* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetCommonName().c_str());

	return ansi_str != 0;
}

int ECALL certpl_get_locality_name(CefX509CertPrincipal* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetLocalityName().c_str());

	return ansi_str != 0;
}

int ECALL certpl_get_state_province_name(CefX509CertPrincipal* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetStateOrProvinceName().c_str());

	return ansi_str != 0;
}

int ECALL certpl_get_country_name(CefX509CertPrincipal* obj, DWORD* ansi_str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*ansi_str = (DWORD)UnicodeToEStream(obj->GetCountryName().c_str());

	return ansi_str != 0;
}

bool ECALL certpl_get_street_addresses(CefX509CertPrincipal* obj, LPVOID* eArray)
{
	ISVALIDR(obj, NULL);

	std::vector<CefString> keys;
	obj->GetStreetAddresses(keys);

	DWORD* pStrs = new DWORD[keys.size()];
	USES_CONVERSION;
	for (size_t i = 0; i < keys.size(); i++)
	{
		pStrs[i] = (DWORD)UnicodeToEStream(keys[i].c_str());
	}

	FreeAryElement(*eArray);

	int nSize = keys.size() * sizeof(DWORD);
	LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
	*(LPINT)pAry = 1;
	*(LPINT)(pAry + sizeof(INT)) = keys.size();
	memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
	delete[]pStrs;

	*eArray = pAry;

	return !!eArray;
}

bool ECALL certpl_get_organization_names(CefX509CertPrincipal* obj, LPVOID* eArray)
{
	ISVALIDR(obj, NULL);

	std::vector<CefString> keys;
	obj->GetOrganizationNames(keys);

	DWORD* pStrs = new DWORD[keys.size()];
	USES_CONVERSION;
	for (size_t i = 0; i < keys.size(); i++)
	{
		pStrs[i] = (DWORD)UnicodeToEStream(keys[i].c_str());
	}

	FreeAryElement(*eArray);

	int nSize = keys.size() * sizeof(DWORD);
	LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
	*(LPINT)pAry = 1;
	*(LPINT)(pAry + sizeof(INT)) = keys.size();
	memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
	delete[]pStrs;

	*eArray = pAry;

	return !!eArray;
}

bool ECALL certpl_get_organization_unit_names(CefX509CertPrincipal* obj, LPVOID* eArray)
{
	ISVALIDR(obj, NULL);

	std::vector<CefString> keys;
	obj->GetOrganizationUnitNames(keys);

	DWORD* pStrs = new DWORD[keys.size()];
	USES_CONVERSION;
	for (size_t i = 0; i < keys.size(); i++)
	{
		pStrs[i] = (DWORD)UnicodeToEStream(keys[i].c_str());
	}

	FreeAryElement(*eArray);

	int nSize = keys.size() * sizeof(DWORD);
	LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
	*(LPINT)pAry = 1;
	*(LPINT)(pAry + sizeof(INT)) = keys.size();
	memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
	delete[]pStrs;

	*eArray = pAry;

	return !!eArray;
}

bool ECALL certpl_get_domain_components(CefX509CertPrincipal* obj, LPVOID* eArray)
{
	ISVALIDR(obj, NULL);

	std::vector<CefString> keys;
	obj->GetDomainComponents(keys);

	DWORD* pStrs = new DWORD[keys.size()];
	USES_CONVERSION;
	for (size_t i = 0; i < keys.size(); i++)
	{
		pStrs[i] = (DWORD)UnicodeToEStream(keys[i].c_str());
	}

	FreeAryElement(*eArray);

	int nSize = keys.size() * sizeof(DWORD);
	LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
	*(LPINT)pAry = 1;
	*(LPINT)(pAry + sizeof(INT)) = keys.size();
	memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
	delete[]pStrs;

	*eArray = pAry;

	return !!eArray;
}

DWORD acf_certprincipal_funcs[] = {
	(DWORD)&certpl_get_display_name,
	(DWORD)&certpl_get_common_name,
	(DWORD)&certpl_get_locality_name,
	(DWORD)&certpl_get_state_province_name,
	(DWORD)&certpl_get_country_name,
	(DWORD)&certpl_get_street_addresses,
	(DWORD)&certpl_get_organization_names,
	(DWORD)&certpl_get_organization_unit_names,
	(DWORD)&certpl_get_domain_components,
};

BOOL ECALL sslstatus_is_secure_connection(CefSSLStatus* obj)
{
	ISVALIDR(obj, NULL);

	return obj->IsSecureConnection();
}

int ECALL sslstatus_get_cert_status(CefSSLStatus* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetCertStatus();
}

int ECALL sslstatus_get_ssl_version(CefSSLStatus* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetSSLVersion();
}

int ECALL sslstatus_get_content_status(CefSSLStatus* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetContentStatus();
}

bool ECALL sslstatus_get_x509_certficate(CefSSLStatus* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefX509Certificate> pObj = obj->GetX509Certificate();

	pObj->AddRef();
	target[1] = (DWORD)((LPVOID)pObj.get());
	target[2] = (DWORD)acf_certificate_funcs;

	return !!pObj;
}

DWORD acf_ssl_status_funcs[] = {
	(DWORD)&sslstatus_is_secure_connection,
	(DWORD)&sslstatus_get_cert_status,
	(DWORD)&sslstatus_get_ssl_version,
	(DWORD)&sslstatus_get_content_status,
	(DWORD)&sslstatus_get_x509_certficate,
};

int ECALL sslinfo_get_cert_status(CefSSLInfo* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetCertStatus();
}

bool ECALL sslinfo_get_x509_certficate(CefSSLInfo* obj, DWORD* target)
{
	ISVALIDR(obj, false);

	CefRefPtr<CefX509Certificate> pObj = obj->GetX509Certificate();

	pObj->AddRef();
	target[1] = (DWORD)((LPVOID)pObj.get());
	target[2] = (DWORD)acf_certificate_funcs;

	return !!pObj;
}

DWORD acf_ssl_info_funcs[] = {
	(DWORD)&sslinfo_get_cert_status,
	(DWORD)&sslinfo_get_x509_certficate,
};