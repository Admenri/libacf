#pragma once
#include "include/cef_app.h"
#include "acf_Types.h"

class ACFlibTask : public CefTask
{
public:
    ACFlibTask(LPFN_POST_TASK func, int param1, int param2, int param3) :
        m_callback(func),
        lParam1(param1),
        lParam2(param2),
        lParam3(param3) {};
    ~ACFlibTask() {};

private:
    LPFN_POST_TASK m_callback;
    int lParam1;
    int lParam2;
    int lParam3;

protected:
    ///
    // Method that will be executed on the target thread.
    ///
    /*--cef()--*/
    virtual void Execute()  OVERRIDE;

protected:
	IMPLEMENT_REFCOUNTING(ACFlibTask);
};

class ACFlibTaskStd : public CefTask
{
public:
  ACFlibTaskStd(LPVOID lpCallback, bool copy) : m_callback(lpCallback), m_copyData(copy) {};
  ~ACFlibTaskStd();

private:
  LPVOID m_callback;
  bool m_copyData;

protected:
  ///
  // Method that will be executed on the target thread.
  ///
  /*--cef()--*/
  virtual void Execute()  OVERRIDE;

protected:
  IMPLEMENT_REFCOUNTING(ACFlibTaskStd);
};