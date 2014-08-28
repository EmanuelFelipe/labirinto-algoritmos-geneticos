#include "../include/FileHandler.h"

FileHandler::FileHandler( const char *_filename ) : filename(_filename) {
    file = new std::fstream();
    file->open( filename, std::ios_base::out );

    if( ! file->is_open() ) {
        errorMessage = "Erro ao abrir arquivo: ";
        errorMessage.append( filename );
        throw -1;
    }
}

void FileHandler::printMaze( const Maze *maze ) {

    if( ! file->good() ) {
        errorMessage.clear();
        errorMessage = "Erro ao gravar arquivo: ";
        errorMessage.append( filename );
        throw -1;
    }

    if( maze == 0 ) {
        errorMessage.clear();
        errorMessage = "Maze vazio";
        throw -1;
    }

    maze->print( *file );
}

FileHandler::~FileHandler()
{
    if( file->is_open() ) {
        file->close();
    }
    delete file;
}
