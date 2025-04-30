#include <spdlog/spdlog.h>

#include <BinaryFileManager.hpp>
#include <utils.hpp>

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

std::string BinaryFileManager::readBitsAtPosition(const uint32_t& position, const uint32_t& n_bit) {
    char* read_string;
    stream.seekg(position);
    stream.get(read_string, n_bit);
    return read_string;
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