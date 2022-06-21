#pragma once

#include <sstream>

#include "acf_Class.h"
#include "acf_Conv.h"
#include "acf_Types.h"
#include "include/cef_browser.h"
#include "include/cef_response_filter.h"

class ACFlibResourceFilter;

class ACFResourceFilter : public virtual CefBaseRefCounted
{
public:
	ACFResourceFilter(CefRefPtr<ACFlibResourceFilter> filter);
	~ACFResourceFilter();

	CefString GetURL();

	CefString GetMimeType();

	size_t GetTotalBytes();

	void GetBuffer(void* outputBuffer, size_t length);

	void SetBuffer(void* inputBuffer, size_t length);

private:

	CefRefPtr<ACFlibResourceFilter> _rawptr;

protected:

	IMPLEMENT_REFCOUNTING(ACFResourceFilter);
};

class ACFlibResourceFilter : public CefResponseFilter
{
public:

	ACFlibResourceFilter(LPVOID callback, CefRefPtr<CefBrowser> browser, const CefString& url, const CefString& mime_type);
	~ACFlibResourceFilter();

	CefString GetURL();

	CefString GetMimeType();

	size_t GetTotalBytes();

	void GetBuffer(void* outputBuffer, size_t length);

	void SetBuffer(void* inputBuffer, size_t length);

private:

	LPVOID _rawcallback;
	CefString _responseURL;
	CefString _responseMimeType;
	CefRefPtr<CefBrowser> _browser;
	BOOL _readEnded;
	std::stringstream _rdbuf;
	size_t _totalReadBytes;

protected:

	virtual bool InitFilter() OVERRIDE;

	virtual FilterStatus Filter(void* data_in,
		size_t data_in_size,
		size_t& data_in_read,
		void* data_out,
		size_t data_out_size,
		size_t& data_out_written) OVERRIDE;

	IMPLEMENT_REFCOUNTING(ACFlibResourceFilter);
};