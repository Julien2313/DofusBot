#include "bot.h"
#include <stdarg.h>
#include <windows.h>

void logInfo( const char* texte, ... ){
    FILE *logFile = fopen("bot.log", "a");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;


    /* Save current attributes */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY );

    va_list args;
    fprintf( stdout, "Info: " );
    fprintf( logFile, "Info: " );
    va_start( args, texte );
    vfprintf( stdout, texte, args );
    vfprintf( logFile, texte, args );
    va_end( args );
    fprintf( stdout, "\n" );
    fprintf( logFile, "\n");

    fclose(logFile);

    /* Restore old attributes */
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void logDebug( const char* texte, ... ){
    FILE *logFile = fopen("bot.log", "a");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;


    /* Save current attributes */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY );

    va_list args;
    fprintf( stdout, "Debug: " );
    fprintf( logFile, "Debug: " );
    va_start( args, texte );
    vfprintf( stdout, texte, args );
    vfprintf( logFile, texte, args );
    va_end( args );
    fprintf( stdout, "\n" );
    fprintf( logFile, "\n");

    fclose(logFile);

    /* Restore old attributes */
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void logWarning( const char* texte, ... ){
    FILE *logFile = fopen("bot.log", "a");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;


    /* Save current attributes */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

    va_list args;
    fprintf( stdout, "Warning: " );
    fprintf( logFile, "Warning: " );
    va_start( args, texte );
    vfprintf( stdout, texte, args );
    vfprintf( logFile, texte, args );
    va_end( args );
    fprintf( stdout, "\n" );
    fprintf( logFile, "\n");

    fclose(logFile);

    /* Restore old attributes */
    SetConsoleTextAttribute(hConsole, saved_attributes);
}

void logError( const char* texte, ... ){
    FILE *logFile = fopen("bot.log", "a");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;


    /* Save current attributes */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);

    va_list args;
    fprintf( stdout, "Error: " );
    fprintf( logFile, "Error: " );
    va_start( args, texte );
    vfprintf( stdout, texte, args );
    vfprintf( logFile, texte, args );
    va_end( args );
    fprintf( stdout, "\n" );
    fprintf( logFile, "\n");

    fclose(logFile);

    /* Restore old attributes */
    SetConsoleTextAttribute(hConsole, saved_attributes);
}
