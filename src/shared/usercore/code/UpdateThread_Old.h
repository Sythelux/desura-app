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

#ifndef DESURA_UPDATETHREAD_OLD_H
#define DESURA_UPDATETHREAD_OLD_H
#ifdef _WIN32
#pragma once
#endif

#include "UpdateThread.h"

namespace UnitTest
{
	class UpdateThreadOldFixture;
}

namespace UserCore
{

	class UpdateThreadOld : public UpdateThreadI
	{
	public:
		UpdateThreadOld(Event<std::tuple<gcOptional<bool>, gcOptional<bool>, gcOptional<bool>>> *onForcePollEvent, bool loadLoginItems);

	protected:
		friend class UnitTest::UpdateThreadOldFixture;

		virtual void doRun();
		virtual void onStop();

		bool pollUpdates();
		void parseXML(const XML::gcXMLDocument &xmlDocument);


		void updateBuildVer();
		void onForcePoll(std::tuple<gcOptional<bool>, gcOptional<bool>, gcOptional<bool>> &info);

		bool onMessageReceived(const char* resource, const XML::gcXMLElement &xmlElement) override;
		void setInfo(const gcRefPtr<UserCore::UserI> &user, const gcRefPtr<WebCore::WebCoreI> &webcore) override;

#ifdef WIN32
		void checkFreeSpace();
#endif

		void loadLoginItems();
		void checkAppUpdate(const XML::gcXMLElement &xmlElement);
		void checkAppUpdate(const XML::gcXMLElement &uNode, std::function<void(uint32, uint32, bool)> &updateCallback);

	private:
		uint32 m_iAppId = 100;
		uint32 m_iAppVersion = 0;

		uint32 m_uiLastAppId = 0;
		uint32 m_uiLastVersion = 0;

		::Thread::WaitCondition m_WaitCond;

		Event<std::tuple<gcOptional<bool>, gcOptional<bool>, gcOptional<bool>>> *m_pOnForcePollEvent = nullptr;

		volatile bool m_bForcePoll = false;

#ifdef DESURA_OFFICIAL_BUILD
		volatile bool m_bInternalTesting = false;
		volatile bool m_bForceTestingUpdate = false;
#endif

		gcRefPtr<UserCore::UserI> m_pUser;
		gcRefPtr<WebCore::WebCoreI> m_pWebCore;

		bool m_bLastFailed = false;
		bool m_bLoadLoginItems = false;
	};
}

#endif //DESURA_UPDATETHREAD_OLD_H
