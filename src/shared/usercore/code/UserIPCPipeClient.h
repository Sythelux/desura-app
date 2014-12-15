/*
Copyright (C) 2011 Mark Chandler (Desura Net Pty Ltd)
Copyright (C) 2014 Bad Juju Games, Inc.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA.

Contact us at legal@badjuju.com.
*/

#ifndef DESURA_USERIPCPIPECLIENT_H
#define DESURA_USERIPCPIPECLIENT_H
#ifdef _WIN32
#pragma once
#endif

#ifdef NIX
#include "SharedObjectLoader.h"
#endif

#include "IPCPipeClient.h"

class IPCServiceMain;
class IPCServerI;

namespace UserCore
{
	class UserIPCPipeClient : public IPC::PipeClient
	{
	public:
		UserIPCPipeClient(const char* user, const char* appDataPath, bool uploadDumps);
		~UserIPCPipeClient();
#ifdef WIN32
		void restart();
#endif
		void start();

		std::shared_ptr<IPCServiceMain> getServiceMain()
		{
			return m_pServiceMain;
		}

		gc_IMPLEMENT_REFCOUNTING(UserIPCPipeClient);

	protected:
#ifdef WIN32
		void stopService();
		void startService();

		void onDisconnect();
#else
		static void recvMessage(void* obj, const char* buffer, size_t size);
		void recvMessage(const char* buffer, size_t size);
		static void sendMessage(void* obj, const char* buffer, size_t size);
		void sendMessage(const char* buffer, size_t size);
		virtual void setUpPipes();
#endif

	private:
		bool m_bUploadDumps;
		gcString m_szUser;
		gcString m_szAppDataPath;

		std::shared_ptr<IPCServiceMain> m_pServiceMain;

#ifdef NIX
		SharedObjectLoader m_hServiceDll;
		IPCServerI *m_pServer;
#endif
	};
}

#endif //DESURA_USERIPCPIPECLIENT_H
