
#include "acf_ResourceFilter.h"

extern DWORD acf_resource_filter_funcs[];

int ECALL filter_get_url(ACFResourceFilter* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetURL().c_str());

	return str != NULL;
}

int ECALL filter_get_mime_type(ACFResourceFilter* obj, DWORD* str)
{
	ISVALIDR(obj, NULL);

	USES_CONVERSION;

	*str = (DWORD)UnicodeToEStream(obj->GetMimeType().c_str());

	return str != NULL;
}

int ECALL filter_get_total_bytes(ACFResourceFilter* obj)
{
	ISVALIDR(obj, NULL);

	return obj->GetTotalBytes();
}

void ECALL filter_get_buffer(ACFResourceFilter* obj, LPVOID buffer, int length)
{
	ISVALID(obj);

	obj->GetBuffer(buffer, length);
}

void ECALL filter_set_buffer(ACFResourceFilter* obj, LPVOID buffer, int length)
{
	ISVALID(obj);

	obj->SetBuffer(buffer, length);
}

DWORD acf_resource_filter_funcs[] = {
	(DWORD)&filter_get_url,
	(DWORD)&filter_get_mime_type,
	(DWORD)&filter_get_total_bytes,
	(DWORD)&filter_get_buffer,
	(DWORD)&filter_set_buffer,
};

ACFlibResourceFilter::ACFlibResourceFilter(LPVOID callback, CefRefPtr<CefBrowser> browser, const CefString& url, const CefString& mime_type) :
	_browser(browser), _responseURL(url), _responseMimeType(mime_type), _totalReadBytes(0), _readEnded(0), _rawcallback(callback) {}

ACFlibResourceFilter::~ACFlibResourceFilter()
{
	_browser = nullptr;
	_rdbuf.clear();
}

CefString ACFlibResourceFilter::GetURL()
{
	return _responseURL;
}

CefString ACFlibResourceFilter::GetMimeType()
{
	return _responseMimeType;
}

size_t ACFlibResourceFilter::GetTotalBytes()
{
	return _totalReadBytes;
}

void ACFlibResourceFilter::GetBuffer(void* outputBuffer, size_t length)
{
	if (!outputBuffer || length <= 0 || _totalReadBytes <= 0 || length > _totalReadBytes) {
		return;
	}
	_rdbuf.seekg(0, std::ios_base::beg);
	_rdbuf.read((char*)outputBuffer, length);
	_rdbuf.seekg(0, std::ios_base::beg);
}

void ACFlibResourceFilter::SetBuffer(void* inputBuffer, size_t length)
{
	_rdbuf.clear();
	_rdbuf.seekp(0, std::ios_base::beg);
	_rdbuf.write((char*)inputBuffer, length);
	_totalReadBytes = length;
}

bool ACFlibResourceFilter::InitFilter() {
	_readEnded = false;
	_rdbuf.clear();
	_totalReadBytes = NULL;

	return true;
}

ACFlibResourceFilter::FilterStatus ACFlibResourceFilter::Filter(void* data_in,
	size_t data_in_size,
	size_t& data_in_read,
	void* data_out,
	size_t data_out_size,
	size_t& data_out_written)
{
	// Read All Data
	if (data_in && data_in_size > 0) {
		_rdbuf.write((char*)data_in, data_in_size);
		_totalReadBytes += data_in_size;
		data_in_read = data_in_size;
	}
	else {
		if (_readEnded == false) {
			
			// Handler
			if (_rawcallback != NULL)
			{
				LPVOID pClass = _rawcallback;

				CefRefPtr<ACFResourceFilter> filter = new ACFResourceFilter(this);

				IMP_NEWECLASS(TempBrowser, _browser.get(), eClass::m_pVfBrowserTable, acf_browser_funcs);
				IMP_NEWECLASS(TempFilter, filter.get(), eClass::m_pVfResourceFilterTable, acf_resource_filter_funcs);

				USES_CONVERSION;

				LPVOID paUrl = UnicodeToEStream(_responseURL.c_str());
				LPVOID paMimeType = UnicodeToEStream(_responseMimeType.c_str());

				LPVOID lpUrlAddr = &paUrl;
				LPVOID lpTypeAddr = &paMimeType;

				_browser->AddRef();
				filter->AddRef();
				__asm {
					push ecx;
					push ebx;
					push edi;
					push esi;
					mov ebx, pClass;
					mov edx, [ebx];
					lea ecx, pClass;
					push TempFilter;
					push lpTypeAddr;
					push lpUrlAddr;
					push TempBrowser;
					push ecx;
					call[edx + 0x104];
					pop esi;
					pop edi;
					pop ebx;
					pop ecx;
				}
				_browser->Release();
				filter->Release();
			}

			_readEnded = true;
		}

		if (_totalReadBytes > 0) {

			if (_totalReadBytes < data_out_size) {
				_rdbuf.read((char*)data_out, _totalReadBytes);
				data_out_written = _totalReadBytes;
				_totalReadBytes = 0;
				return FilterStatus::RESPONSE_FILTER_DONE;
			}
			else {
				_rdbuf.read((char*)data_out, data_out_size);
				data_out_written = data_out_size;
				_totalReadBytes -= data_out_size;
			}

		}
	}

	return FilterStatus::RESPONSE_FILTER_NEED_MORE_DATA;
}

ACFResourceFilter::ACFResourceFilter(CefRefPtr<ACFlibResourceFilter> filter) : _rawptr(filter) {}

ACFResourceFilter::~ACFResourceFilter() {}

CefString ACFResourceFilter::GetURL()
{
	return _rawptr->GetURL();
}

CefString ACFResourceFilter::GetMimeType()
{
	return _rawptr->GetMimeType();
}

size_t ACFResourceFilter::GetTotalBytes()
{
	return _rawptr->GetTotalBytes();
}

void ACFResourceFilter::GetBuffer(void* outputBuffer, size_t length)
{
	_rawptr->GetBuffer(outputBuffer, length);
}

void ACFResourceFilter::SetBuffer(void* inputBuffer, size_t length)
{
	_rawptr->SetBuffer(inputBuffer, length);
}
