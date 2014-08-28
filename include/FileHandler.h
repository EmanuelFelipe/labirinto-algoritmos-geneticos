#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include "Maze.h"

class FileHandler
{
    public:
        FileHandler( const char* );
        virtual ~FileHandler();

        void printMaze( const Maze * );
        inline const char* getFilename() const { return filename; };
        inline std::string getErrorMessage() const { return errorMessage; };
    protected:
    private:
        const char *filename;
        std::fstream *file;
        std::string errorMessage;
};

#endif // FILEHANDLER_H
