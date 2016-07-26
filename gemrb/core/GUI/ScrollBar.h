/* GemRB - Infinity Engine Emulator
 * Copyright (C) 2003 The GemRB Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 */

/**
 * @file ScrollBar.h
 * Declares ScrollBar widget for paging in long text windows.
 * This does not include scales and sliders, which are of Slider class.
 * @author The GemRB Project
 */

#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include "GUI/Control.h"

#include "exports.h"

namespace GemRB {

class Sprite2D;

#define UP_PRESS	 0x0001
#define DOWN_PRESS   0x0010
#define SLIDER_GRAB  0x0100

/**
 * @class ScrollBar
 * Widget displaying scrollbars for paging in long text windows
 */
class GEM_EXPORT ScrollBar : public Control {
public:
	enum IMAGE_TYPE {
		IMAGE_UP_UNPRESSED = 0,
		IMAGE_UP_PRESSED,
		IMAGE_DOWN_UNPRESSED,
		IMAGE_DOWN_PRESSED,
		IMAGE_TROUGH,
		IMAGE_SLIDER,

		IMAGE_COUNT
	};

	unsigned int StepIncrement;

	ScrollBar(const Region& frame, Sprite2D*[IMAGE_COUNT]);
	ScrollBar(const ScrollBar& sb);
	~ScrollBar(void);

	bool IsOpaque() const;

	void ScrollUp();
	void ScrollDown();
	void ScrollBySteps(int steps);

	/** refreshes scrollbar if associated with VarName */
	void UpdateState(unsigned int Sum);
	bool TracksMouseDown() const { return true; }

	/** Mouse Button Down */
	void OnMouseDown(const MouseEvent& /*me*/, unsigned short Mod);
	/** Mouse Button Up */
	void OnMouseUp(const MouseEvent& /*me*/, unsigned short Mod);
	/** Mouse Drag Event */
	void OnMouseDrag(const MouseEvent&);
	/** Mouse Wheel Scroll Event */
	void OnMouseWheelScroll(const Point& delta);

private: //Private attributes
	/** Images for drawing the Scroll Bar */
	Sprite2D* Frames[IMAGE_COUNT];
	/** Range of the slider in pixels. The height - buttons - slider */
	int SliderPxRange;
	/** Scroll Bar Status */
	unsigned short State;

private:
	void DrawSelf(Region drawFrame, const Region& clip);
	void SetPosForY(int y);
	int YPosFromValue();
	int GetFrameHeight(int frame) const;
};

}

#endif
