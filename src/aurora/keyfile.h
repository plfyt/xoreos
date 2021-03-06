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

/** @file aurora/keyfile.h
 *  Handling BioWare's KEYs (resource index files).
 */

#ifndef AURORA_KEYFILE_H
#define AURORA_KEYFILE_H

#include <vector>

#include "common/types.h"
#include "common/ustring.h"

#include "aurora/types.h"
#include "aurora/aurorafile.h"

namespace Common {
	class SeekableReadStream;
	class File;
}

namespace Aurora {

/** Class to hold resource index information of a key file. */
class KEYFile : public AuroraBase {
public:
	/** A key resource index. */
	struct Resource {
		Common::UString name; ///< The resource's name.
		FileType        type; ///< The resource's type.

		uint32 bifIndex; ///< Index into the bif list.
		uint32 resIndex; ///< Index into the bif's resource table.
	};

	typedef std::vector<Resource> ResourceList;
	typedef std::vector<Common::UString> BIFList;

	KEYFile(const Common::UString &fileName);
	~KEYFile();

	/** Return a list of all managed bifs. */
	const BIFList &getBIFs() const;

	/** Return a list of all containing resources. */
	const ResourceList &getResources() const;

private:
	BIFList      _bifs;      ///< All managed bifs.
	ResourceList _resources; ///< All containing resources.

	void load(Common::SeekableReadStream &key);

	void readBIFList(Common::SeekableReadStream &key, uint32 offset);
	void readResList(Common::SeekableReadStream &key, uint32 offset);
};

} // End of namespace Aurora

#endif // AURORA_KEYFILE_H
