#include "fileengine.h"

FileEngine::FileEngine() {}

FileEngine::FileEngine(string filename) : DataEngine (filename)
{
    this->m_ofs.open(this->m_filename.c_str(), ios::out|ios::app|ios::binary);

    if( !this->m_ofs ){
            cerr << "cannot open " << this->m_filename << "for output" << endl;
    }
}

FileEngine::~FileEngine()
{
    this->m_ofs.close();
}

bool FileEngine::open(string filename)
{
    m_filename = filename;

    this->m_ofs.open(this->m_filename.c_str(), ios::out|ios::app|ios::binary);

    if( !this->m_ofs ){
        cerr << "cannot open " << this->m_filename << "for output" << endl;
        return false;
    } 
    else {
        return true;
    }
}

