#include "basefile.h"

BaseFile::BaseFile() {}
BaseFile::~BaseFile() {}

BaseFile::BaseFile( string filename ) {
    /*
     * The Constructor to set the filename
     * Param filename: the file's name str
     * Return: as the member variable
     */
    this->m_filename = filename;
}
