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

#ifndef DESURA_ICPROGRESSPAGE_H
#define DESURA_ICPROGRESSPAGE_H
#ifdef _WIN32
#pragma once
#endif

#include "wx_controls/gcControls.h"
#include "usercore/UserThreadI.h"
#include "BaseInstallPage.h"

namespace UI
{
namespace Forms
{
namespace ItemFormPage
{


class ICheckProgressPage : public BaseInstallPage
{
public:
	ICheckProgressPage(wxWindow* parent);
	~ICheckProgressPage();

	virtual void init();

protected:
	void onButtonPressed(wxCommandEvent& event);

	void onComplete(uint32&);
	void onError(gcException& e);
	void onProgress(uint32& prog);

private:
	gcStaticText* m_labInfo;
	gcSpinningBar* m_pbProgress;
	gcButton* m_butCancel;
};


}
}
}

#endif //DESURA_ICPROGRESSPAGE_H
