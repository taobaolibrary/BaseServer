#ifndef _LOGIN_THREAD_H_
#define _LOGIN_THREAD_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Share/I_Shell.h"
#include "../Share/protocol.h"
#include "../Common/ThreadBase.h"
#include "../Common/MessagePort/MessagePort.h"

class IMessagePort;
class CLoginThread : public CThreadBase
{
public:
	CLoginThread(IMessagePort* pPort);
	virtual ~CLoginThread();

public: 
	virtual	bool	CreateThread(bool bRun = true);		// false: 暂不运行，用 ResumeThread() 运行

protected:
	virtual	void	OnInit();
	virtual bool	OnProcess();		
	virtual void	OnDestroy();

protected: // 核心对象及接口
	I64				m_i64LastOnTimerMS;
	ILoginKernel*	m_pLoginKernel;
	IMessagePort*	m_pMsgPort;
};

#endif	// end of _LOGIN_THREAD_H_