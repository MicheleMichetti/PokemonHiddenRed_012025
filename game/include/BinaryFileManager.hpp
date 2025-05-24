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
    std::string file_name;
    std::fstream stream;
    std::ios_base::openmode mode;

    void checkOpen();

   public:
    BinaryFileManager();
    BinaryFileManager(const std::string& file_name, const std::ios_base::openmode& mode);
    std::ios_base::openmode getMode() const;
    std::string getFileName() const;
    std::fstream* getStream();

    void openFile(const std::ios_base::openmode& mode);
    /**
     * Check that the stream is not failed, then closes it.
     */
    void commit();
    ~BinaryFileManager();

    /**
     * Read a sequence of bits from the file, starting at the given position.
     * The sequence is read as a string of '0's and '1's.
     * @param position The position in the file to start reading from.
     * @param n_bit The number of bits to read.
     * @return A string containing the sequence of bits.
     */
    char* readBitsSequence(const uint32_t& position, const uint32_t& n_bit);
    uint8_t readBitsSequence(uint8_t& output, const uint32_t& position, const uint32_t& n_bit);
    uint16_t readBitsSequence(uint16_t& output, const uint32_t& position, const uint32_t& n_bit);
    uint32_t readBitsSequence(uint32_t& output, const uint32_t& position, const uint32_t& n_bit);
    uint64_t readBitsSequence(uint64_t& output, const uint32_t& position, const uint32_t& n_bit);
    std::string readBitsSequence(std::string& output, const uint32_t& position, const uint32_t& n_bit);
    char readBitsSequence(char& output, const uint32_t& position, const uint32_t& n_bit);
    float readBitsSequence(float& output, const uint32_t& position, const uint32_t& n_bit);
    double readBitsSequence(double& output, const uint32_t& position, const uint32_t& n_bit);
    bool readBitsSequence(bool& output, const uint32_t& position, const uint32_t& n_bit);
    int readBitsSequence(int& output, const uint32_t& position, const uint32_t& n_bit);

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