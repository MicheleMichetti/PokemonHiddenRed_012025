#include <fstream>
#include <iostream>
#include <string>

/***
fstream class flags.
std::fstream::
in:         input	    File open for reading: the internal stream buffer supports input operations.
out:        output	    File open for writing: the internal stream buffer supports output operations.
binary: 	binary	    Operations are performed in binary mode rather than text.
ate:        at end	    The output position starts at the end of the file.
app:        append	    All output operations happen at the end of the file, appending to its existing contents.
trunc:      truncate	Any contents that existed in the file before it is open are discarded.
*/

#define N_BIT_SEQUENCE 34 * 8;

class BinaryFileManager {
   private:
    std::string filename;
    std::fstream stream;
    std::ios_base::openmode mode;

    void checkOpen();

   public:
    BinaryFileManager(std::string filename, std::ios_base::openmode mode);
    std::ios_base::openmode getMode();
    std::string getFilename();
    void openFile(std::ios_base::openmode mode);
    /**
     * Check that the stream is not failed, then closes it.
     */
    void commit();
    ~BinaryFileManager();
    std::string readBitsAtPosition(const uint32_t& position, const uint32_t& n_bit);
    void writeBitsAtPosition(const char* target, uint32_t n_bit, uint32_t position = 0);
    void writeBitsInAppend(const char* target, const uint32_t& n_bit);
    /**
     * Automatically calculate the lenght of the char* argument using strlen(). WARNING: working ONLY is string is \0 terminated.
     */
    void writeBitsInAppend(const char* target);
    /**
     * Closes the stream and reopens it read-only, setting back to position to where it was.
     * Heavy on resources, use carefully.
     */
    void setPermission(std::ios_base::openmode mode);
    void IOErrorMessage(const char* c);
};