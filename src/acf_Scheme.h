#pragma once

#include "acf_Types.h"
#include "include/cef_app.h"
#include "include/cef_scheme.h"

class ACFlibSchemeHandler : public CefSchemeHandlerFactory,
  public CefResourceHandler
{
public:
  ACFlibSchemeHandler(LPVOID lpCallback, BOOL copyData);
  ~ACFlibSchemeHandler();

  void SetBuffer(void* inputBuffer, size_t length);

private:

    LPVOID m_callback;
    CefRefPtr<CefBrowser> m_browser;
    CefRefPtr<CefFrame> m_frame;
    size_t m_totalBytes;
    BYTE* m_buffer;
    size_t m_datasize;
    BOOL m_rawcallback;
    BOOL m_copyData;

protected:

  virtual CefRefPtr<CefResourceHandler> Create(
    CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    const CefString& scheme_name,
    CefRefPtr<CefRequest> request)  OVERRIDE;

    virtual bool Open(CefRefPtr<CefRequest> request,
        bool& handle_request,
        CefRefPtr<CefCallback> callback)  OVERRIDE;

    virtual void GetResponseHeaders(CefRefPtr<CefResponse> response,
        int64& response_length,
        CefString& redirectUrl)  OVERRIDE;

    virtual bool Skip(int64 bytes_to_skip,
        int64& bytes_skipped,
        CefRefPtr<CefResourceSkipCallback> callback)  OVERRIDE;

    virtual bool Read(void* data_out,
        int bytes_to_read,
        int& bytes_read,
        CefRefPtr<CefResourceReadCallback> callback)  OVERRIDE;

    virtual void Cancel()  OVERRIDE;

  IMPLEMENT_REFCOUNTING(ACFlibSchemeHandler);
};
