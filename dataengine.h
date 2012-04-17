#ifndef _DATA_ENGINE_H
#define _DATA_ENGINE_H

#include "xsearch.h"

enum dataengine_type
{
	FILE_ENGINE,
	DATABASE_ENGINE
};

class DataEngine
{
public:
	DataEngine(string filename);
	DataEngine();
	virtual ~DataEngine();

	virtual int getEngineType() = 0;
	virtual bool write(void *arg) = 0;
	virtual bool open(string str) = 0;
	virtual void close() = 0;
public:
        string m_filename;
};

#endif
