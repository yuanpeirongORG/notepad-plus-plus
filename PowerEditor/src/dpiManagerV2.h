// This file is part of Notepad++ project
// Copyright (c) 2024 ozone10 and Notepad++ team

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// at your option any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.


#pragma once
#include "NppDarkMode.h"

class DPIManagerV2
{
public:
	DPIManagerV2() {
		setDpiWithSystem();
	}
	virtual ~DPIManagerV2() = default;

	enum class FontType { menu, status, message, caption, smcaption };

	static void initDpiAPI();

	static int getSystemMetricsForDpi(int nIndex, UINT dpi);
	static DPI_AWARENESS_CONTEXT setThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT dpiContext);

	static UINT getDpiForSystem();
	static UINT getDpiForWindow(HWND hWnd);
	static UINT getDpiForParent(HWND hWnd) {
		return getDpiForWindow(::GetParent(hWnd));
	}

	void setDpiWithSystem() {
		_dpi = getDpiForSystem();
	}

	// parameter is WPARAM
	void setDpiWP(WPARAM wParam) {
		_dpi = LOWORD(wParam);
	}

	void setDpi(UINT newDpi) {
		_dpi = newDpi;
	}

	void setDpi(HWND hWnd) {
		setDpi(getDpiForWindow(hWnd));
	}

	void setDpiWithParent(HWND hWnd) {
		setDpi(::GetParent(hWnd));
	}

	UINT getDpi() const {
		return _dpi;
	}

	static void setPositionDpi(LPARAM lParam, HWND hWnd);

	static int scale(int x, UINT dpi, UINT dpi2) {
		return MulDiv(x, dpi, dpi2);
	}

	static int scale(int x, UINT dpi) {
		return scale(x, dpi, USER_DEFAULT_SCREEN_DPI);
	}

	static int unscale(int x, UINT dpi) {
		return scale(x, USER_DEFAULT_SCREEN_DPI, dpi);
	}

	int scale(int x) {
		return scale(x, _dpi);
	}

	int unscale(int x) {
		return unscale(x, _dpi);
	}

	int scaleX(int x) {
		return scale(x);
	}

	int unscaleX(int x) {
		return unscale(x);
	}

	int scaleY(int y) {
		return scale(y);
	}

	int unscaleY(int y) {
		return unscale(y);
	}

	static int scaleFont(int pt, UINT dpi) {
		return -(scale(pt, dpi, 72));
	}

	int scaleFont(int pt) {
		return scaleFont(pt, _dpi);
	}

	static LOGFONT getDefaultGUIFontForDpi(UINT dpi, FontType type = FontType::message);
	static LOGFONT getDefaultGUIFontForDpi(HWND hWnd, FontType type = FontType::message) {
		return getDefaultGUIFontForDpi(getDpiForWindow(hWnd), type);
	}

private:
	UINT _dpi = USER_DEFAULT_SCREEN_DPI;
};
