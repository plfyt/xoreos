/* eos - A reimplementation of BioWare's Aurora engine
 * Copyright (c) 2010-2011 Sven Hesse (DrMcCoy), Matthew Hoops (clone2727)
 *
 * The Infinity, Aurora, Odyssey and Eclipse engines, Copyright (c) BioWare corp.
 * The Electron engine, Copyright (c) Obsidian Entertainment and BioWare corp.
 *
 * This file is part of eos and is distributed under the terms of
 * the GNU General Public Licence. See COPYING for more informations.
 */

/** @file engines/nwn/gui/main/new.h
 *  The new game menu.
 */

#ifndef ENGINES_NWN_GUI_MAIN_NEW_H
#define ENGINES_NWN_GUI_MAIN_NEW_H

#include "engines/nwn/gui/gui.h"

namespace Engines {

namespace NWN {

class Module;

/** The NWN new game menu. */
class NewMenu : public GUI {
public:
	NewMenu(Module &module, GUI &charType);
	~NewMenu();

protected:
	void callbackActive(Widget &widget);

private:
	Module *_module;

	bool _hasXP;

	GUI *_charType;

	GUI *_modules;

	void loadModule(const Common::UString &module);
};

} // End of namespace NWN

} // End of namespace Engines

#endif // ENGINES_NWN_GUI_MAIN_NEW_H