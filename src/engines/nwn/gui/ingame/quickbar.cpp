/* xoreos - A reimplementation of BioWare's Aurora engine
 *
 * xoreos is the legal property of its developers, whose names can be
 * found in the AUTHORS file distributed with this source
 * distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 * The Infinity, Aurora, Odyssey, Eclipse and Lycium engines, Copyright (c) BioWare corp.
 * The Electron engine, Copyright (c) Obsidian Entertainment and BioWare corp.
 */

/** @file engines/nwn/gui/ingame/quickbar.cpp
 *  The ingame quickbar.
 */

#include "common/error.h"

#include "graphics/graphics.h"

#include "graphics/aurora/modelnode.h"
#include "graphics/aurora/model.h"

#include "engines/aurora/model.h"

#include "engines/nwn/gui/widgets/panel.h"

#include "engines/nwn/gui/ingame/quickbar.h"

namespace Engines {

namespace NWN {

QuickbarButton::QuickbarButton(::Engines::GUI &gui, uint n) : NWNWidget(gui, ""),
	_buttonNumber(n) {

	Graphics::Aurora::ModelNode *invisible = 0;

	if (_buttonNumber == 11) {

		_model = loadModelGUI("qb_but67end");
		if (!_model)
			throw Common::Exception("Failed to load quickbar model");
		invisible = _model->getNode("Plane72");

	} else {

		_model = loadModelGUI("qb_but67");
		if (!_model)
			throw Common::Exception("Failed to load quickbar model");
		invisible = _model->getNode("Plane52");

	}

	if (invisible)
		invisible->setInvisible(true);

	NWNWidget::setTag(Common::UString::sprintf("Quickbar%d", _buttonNumber));
	_model->setTag(NWNWidget::getTag());

}

QuickbarButton::~QuickbarButton() {
	delete _model;
}

void QuickbarButton::show() {
	_model->show();
}

void QuickbarButton::hide() {
	_model->hide();
}

void QuickbarButton::setPosition(float x, float y, float z) {
	NWNWidget::setPosition(x, y, z);

	getPosition(x, y, z);
	_model->setPosition(x, y, z);
}

float QuickbarButton::getWidth() const {
	return _model->getWidth();
}

float QuickbarButton::getHeight() const {
	return _model->getHeight();
}

void QuickbarButton::setTag(const Common::UString &tag) {
}


Quickbar::Quickbar() {
	getSlotSize();

	WidgetPanel *bottomEdge = new WidgetPanel(*this, "QBBottomEdge", "pnl_quick_bar");
	addWidget(bottomEdge);

	_edgeHeight = bottomEdge->getHeight();

	for (int i = 0; i < 12; i++) {
		QuickbarButton *button = new QuickbarButton(*this, i);

		button->setPosition(i * _slotWidth, bottomEdge->getHeight(), 0.0);
		addWidget(button);
	}

	WidgetPanel *topEdge = new WidgetPanel(*this, "QBTopEdge", "pnl_quick_bar");
	topEdge->setPosition(0.0, _slotHeight, 0.0);
	addWidget(topEdge);

	notifyResized(0, 0, GfxMan.getScreenWidth(), GfxMan.getScreenHeight());
}

Quickbar::~Quickbar() {
}

float Quickbar::getWidth() const {
	return 12 * _slotWidth;
}

float Quickbar::getHeight() const {
	return _slotHeight + 2 * _edgeHeight;
}

void Quickbar::callbackActive(Widget &widget) {
}

void Quickbar::getSlotSize() {
	Graphics::Aurora::Model *_model = loadModelGUI("qb_but67");

	_slotWidth  = floorf(_model->getWidth());
	_slotHeight = floorf(_model->getHeight());

	delete _model;
}

void Quickbar::notifyResized(int oldWidth, int oldHeight, int newWidth, int newHeight) {
	setPosition(- ((12 * _slotWidth) / 2.0), - (newHeight / 2.0), -10.0);
}

} // End of namespace NWN

} // End of namespace Engines
