////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan ChuangYou, All Rights Reserved
// Moudle: MsgLoginUserList.cpp
// Author: ������(Peng Wenqi)
// Created: 2014-11-4
////////////////////////////////////////////////////////////////////////
#include "./MsgLoginUserList.h"
#include "./../LoginKernel.h"

//////////////////////////////////////////////////////////////////////////
CMsgLoginUserList::CMsgLoginUserList()
{
	Init();
	m_pInfo	=(MSG_Info *)m_bufMsg;
	m_unMsgType	= _MSG_LOGIN_USER_LIST;
	m_unMsgSize	= sizeof(MSG_Info);
}

//////////////////////////////////////////////////////////////////////////
CMsgLoginUserList::~CMsgLoginUserList()
{

}

//////////////////////////////////////////////////////////////////////////
BOOL CMsgLoginUserList::Create( char* pMsgBuf,DWORD dwSize )
{
	if (!login_kernel::CNetMsg::Create(pMsgBuf, dwSize))
		return false;

	if(_MSG_LOGIN_USER_LIST != this->GetType())
		return false;

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CMsgLoginUserList::CreateBase( OBJID idAccount )
{
	this->Init();
	m_unMsgType	= _MSG_LOGIN_USER_LIST;
	m_unMsgSize	= sizeof(MSG_Info) - sizeof(USER_LOGIN_SNAP);

	m_pInfo->nAccountID	= idAccount;
	m_pInfo->nCount		= 0;

	return true;
}

//////////////////////////////////////////////////////////////////////////
bool CMsgLoginUserList::AppendInfo( const USER_LOGIN_SNAP& rSnap )
{
	CHECKF(sizeof(MSG_Info) + sizeof(USER_LOGIN_SNAP) * m_pInfo->nCount < MAX_PACKETSIZE);
	memcpy(&(m_pInfo->stInfo[m_pInfo->nCount]), &rSnap, sizeof(USER_LOGIN_SNAP));
	m_unMsgSize = sizeof(MSG_Info) + sizeof(USER_LOGIN_SNAP) * m_pInfo->nCount;
	m_pInfo->nCount++;
	return true;
}

