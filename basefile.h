#ifndef _BASEFILE_H
#define _BASEFILE_H

class BaseFile 
{

// the public functions
public:
    BaseFile();
    BaseFile(string filename);
    virtual ~BaseFile();

    virtual bool write (void * arg) = 0
    virtual int getFileType() = 0;
    bool open(string filename);
    void close();

// the member variable
private:
    ofstream m_ofsfile;
    string m_filename;
};

#endif
