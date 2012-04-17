#ifndef _SEARCH_FILE_H
#define _SEARCH_FILE_H

#include "url.h"
#include "page.h"
#include "fileengine.h"
#include "xsearch.h"

class SearchFile : public FileEngine
{
public:
	SearchFile(string filename);
	SearchFile();
	virtual ~SearchFile();

	inline int getFileType() { return XSEARCH; }

	virtual bool write(void *arg);
};

#endif
