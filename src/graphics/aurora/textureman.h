/* eos - A reimplementation of BioWare's Aurora engine
 * Copyright (c) 2010 Sven Hesse (DrMcCoy), Matthew Hoops (clone2727)
 *
 * The Infinity, Aurora, Odyssey and Eclipse engines, Copyright (c) BioWare corp.
 * The Electron engine, Copyright (c) Obsidian Entertainment and BioWare corp.
 *
 * This file is part of eos and is distributed under the terms of
 * the GNU General Public Licence. See COPYING for more informations.
 */

/** @file graphics/aurora/textureman.h
 *  The Aurora texture manager.
 */

#ifndef GRAPHICS_AURORA_TEXTUREMAN_H
#define GRAPHICS_AURORA_TEXTUREMAN_H

#include "boost/unordered/unordered_map.hpp"

#include "graphics/types.h"

#include "common/types.h"
#include "common/singleton.h"
#include "common/ustring.h"

namespace Graphics {

class Texture;

namespace Aurora {

struct ManagedTexture {
	Texture *texture;
	uint32 referenceCount;

	ManagedTexture(const Common::UString &name);
	~ManagedTexture();
};

typedef boost::unordered_map<Common::UString, ManagedTexture *, Common::hashUStringCaseInsensitive> TextureMap;

struct TextureHandle {
	bool empty;
	TextureMap::iterator it;

	TextureHandle();
	TextureHandle(TextureMap::iterator &i);

	void clear();
};

class TextureManager : public Common::Singleton<TextureManager> {
public:
	TextureManager();
	~TextureManager();

	void clear();

	TextureHandle get(const Common::UString &name);
	void release(TextureHandle &handle);

	void set();
	void set(const TextureHandle &handle);

private:
	TextureMap _textures;
};

} // End of namespace Aurora

} // End of namespace Graphics

/** Shortcut for accessing the texture manager. */
#define TextureMan Graphics::Aurora::TextureManager::instance()

#endif // GRAPHICS_AURORA_TEXTUREMAN_H