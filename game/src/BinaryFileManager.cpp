#include <spdlog/spdlog.h>

#include <BinaryFileManager.hpp>
#include <utils.hpp>

BinaryFileManager::BinaryFileManager() {
    this->file_name = "default_file_name.dat";
    this->mode = std::ios_base::in | std::ios_base::out | std::ios_base::binary;
    stream.open(this->file_name, this->mode);
    checkOpen();
}

BinaryFileManager::BinaryFileManager(const std::string& file_name, const std::ios_base::openmode& mode) {
    this->file_name = file_name;
    this->mode = mode;
    stream.open(file_name, mode);
    checkOpen();
}

std::string BinaryFileManager::getFileName() const { return this->file_name; }

std::ios_base::openmode BinaryFileManager::getMode() const { return this->mode; }

std::fstream* BinaryFileManager::getStream() { return &this->stream; }

void BinaryFileManager::openFile(const std::ios_base::openmode& mode) {
    this->mode = mode;
    stream.open(this->file_name, mode);
    checkOpen();
}

BinaryFileManager::~BinaryFileManager() {
    if (stream.is_open()) {
        stream.close();
    }
}

void BinaryFileManager::commit() {
    if (stream.fail()) {
        IOErrorMessage(("Error committing changes to file " + this->file_name).c_str());
        return;
    }
    stream.close();
}

char* BinaryFileManager::readBitsSequence(const uint32_t& position, const uint32_t& n_bit) {
    char* read_string = new char[n_bit + 1];
    read_string[n_bit] = '\0';
    stream.seekg(position);
    stream.read(read_string, n_bit);

    if (stream.fail()) {
        IOErrorMessage(("End of file reached at position " + std::to_string(position)).c_str());
        return nullptr;
    }

    return read_string;
}

uint8_t BinaryFileManager::readBitsSequence(uint8_t &output, const uint32_t& position, const uint32_t& n_bit) {
    char* read_string = readBitsSequence(position, n_bit);
    output = uint8_t(atoll(read_string));
    delete[] read_string;
    return output;
}

uint16_t BinaryFileManager::readBitsSequence(uint16_t &output, const uint32_t& position, const uint32_t& n_bit) {
    char* read_string = readBitsSequence(position, n_bit);
    output = uint16_t(atoll(read_string));
    delete[] read_string;
    return output;
}

uint32_t BinaryFileManager::readBitsSequence(uint32_t &output, const uint32_t& position, const uint32_t& n_bit) {
    char* read_string = readBitsSequence(position, n_bit);
    output = uint32_t(atoll(read_string));
    delete[] read_string;
    return output;
}

uint64_t BinaryFileManager::readBitsSequence(uint64_t &output, const uint32_t& position, const uint32_t& n_bit) {
    char* read_string = readBitsSequence(position, n_bit);
    output = uint64_t(atoll(read_string));
    delete[] read_string;
    return output;
}

std::string BinaryFileManager::readBitsSequence(std::string &output, const uint32_t& position, const uint32_t& n_bit) {
    char* read_string = readBitsSequence(position, n_bit);
    output = std::string(read_string);
    delete[] read_string;
    return output;
}

char BinaryFileManager::readBitsSequence(char &output, const uint32_t& position, const uint32_t& n_bit) {
    output = *(readBitsSequence(position, n_bit));
    return output;
}

float BinaryFileManager::readBitsSequence(float &output, const uint32_t& position, const uint32_t& n_bit) {
    char* read_string = readBitsSequence(position, n_bit);
    output = atof(read_string);
    delete[] read_string;
    return output;
}

double BinaryFileManager::readBitsSequence(double &output, const uint32_t& position, const uint32_t& n_bit) {
    char* read_string = readBitsSequence(position, n_bit);
    uint32_t shift = sizeof(double)*8/sizeof(char);
    char** stop_string = new char*(read_string+shift);
    output = strtod(read_string, stop_string);
    delete[] read_string;
    return output;
}

bool BinaryFileManager::readBitsSequence(bool &output, const uint32_t& position, const uint32_t& n_bit) {
    char* read_string = readBitsSequence(position, n_bit);
    output = utils::readBit<bool>(read_string, 0);
    delete[] read_string;
    return output;
}

int BinaryFileManager::readBitsSequence(int &output, const uint32_t& position, const uint32_t& n_bit) {
    char* read_string = readBitsSequence(position, n_bit);
    output = atoi(read_string);
    delete[] read_string;
    return output;
}

void BinaryFileManager::writeBitsAtPosition(const char* target, uint32_t n_bit, uint32_t position) {
    if (!stream.is_open() && position < 0) {
        IOErrorMessage(("Can not write to file " + this->file_name + " at position " + std::to_string(position)).c_str());
        return;
    }
    if (position != 0) {
        stream.seekg(position);
    }
    stream.write(target, n_bit);
}

void BinaryFileManager::writeBitsInAppend(const char* target, const uint32_t& n_bit) {
    if (!utils::readBit(getMode(), std::fstream::app)) {
        IOErrorMessage("Stream is not in append mode");
        return;
    }
    stream.write(target, n_bit);
}

void BinaryFileManager::writeBitsInAppend(const char* target) { writeBitsInAppend(target, strlen(target)); }

void BinaryFileManager::setPermission(std::ios_base::openmode mode) {
    std::streampos position = stream.tellg();
    stream.close();
    stream.open(this->file_name, mode);
    this->mode = mode;
    checkOpen();
    stream.seekg(position);
}

void BinaryFileManager::checkOpen() {
    if (!stream.is_open()) {
        IOErrorMessage(("File " + this->file_name + " is not open").c_str());
    }
}

void BinaryFileManager::IOErrorMessage(const char* c) {
    SPDLOG_ERROR(c);
    throw std::ios_base::failure(c);
}