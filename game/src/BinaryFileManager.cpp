#include <spdlog/spdlog.h>

#include <BinaryFileManager.hpp>
#include <utils.hpp>

BinaryFileManager::BinaryFileManager() {
    this->filename = "";
    this->mode = "r";
}

BinaryFileManager::BinaryFileManager(std::string filename, std::ios_base::openmode mode) {
    this->filename = filename;
    this->mode = mode;
    this->stream.open(filename, mode);
    checkOpen();
}

std::string BinaryFileManager::getFilename() { return this->filename; }

std::ios_base::openmode BinaryFileManager::getMode() { return this->mode; }

void BinaryFileManager::openFile(std::ios_base::openmode mode) {
    this->mode = mode;
    stream.open(this->filename, mode);
    checkOpen();
}

void BinaryFileManager::closeFile() {
    if (this->stream.is_open()) {
        this->stream.close();
    }
}

BinaryFileManager::~BinaryFileManager() {
    if (this->stream.is_open()) {
        this->stream.close();
    }
}

void BinaryFileManager::checkFailAndClose() {
    if (this->stream.fail()) {
        IOErrorMessage(("Error committing changes to file " + this->filename).c_str());
        return;
    }
    this->stream.close();
}

std::string BinaryFileManager::readBitsAtPosition(const uint32_t& position, const uint32_t& n_bit) {
    char* read_string;
    this->stream.seekg(position);
    this->stream.get(read_string, n_bit);
    return read_string;
}

void BinaryFileManager::writeBitsAtPosition(const char* target, uint32_t n_bit, uint32_t position) {
    if (!this->stream.is_open() && position < 0) {
        IOErrorMessage(("Can not write to file " + this->filename + " at position " + std::to_string(position)).c_str());
        return;
    }
    if (position != 0) {
        this->stream.seekg(position);
    }
    this->stream.write(target, n_bit);
}

void BinaryFileManager::writeBitsInAppend(const char* target, const uint32_t& n_bit) {
    if (!utils::readBit(getMode(), std::fstream::app)) {
        IOErrorMessage("Stream is not in append mode");
        return;
    }
    this->stream.write(target, n_bit);
}

void BinaryFileManager::writeBitsInAppend(const char* target) { writeBitsInAppend(target, strlen(target)); }

void BinaryFileManager::setPermission(std::ios_base::openmode mode) {
    std::streampos position = this->stream.tellg();
    this->stream.close();
    this->stream.open(this->filename, mode);
    this->mode = mode;
    checkOpen();
    this->stream.seekg(position);
}

void BinaryFileManager::checkOpen() {
    if (!this->stream.is_open()) {
        IOErrorMessage(("File " + this->filename + " is not open").c_str());
    }
}

void BinaryFileManager::IOErrorMessage(const char* c) {
    SPDLOG_ERROR(c);
    throw std::ios_base::failure(c);
}