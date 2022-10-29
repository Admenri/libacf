#pragma once

#include "include/cef_app.h"
#include "include/cef_client.h"

#include "acf_Types.h"
#include "acf_Class.h"
#include "acf_Conv.h"
#include "acf_Client.h"

class ACFlibResourceHandler : public CefResourceHandler
{
public:

  ACFlibResourceHandler(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefFrame> frame,
    LPVOID callback);
  ~ACFlibResourceHandler();

protected:

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

private:

  CefRefPtr<CefBrowser> m_browser;
  CefRefPtr<CefFrame> m_frame;
  LPVOID m_callback;

public:
  IMPLEMENT_REFCOUNTING(ACFlibResourceHandler);
};