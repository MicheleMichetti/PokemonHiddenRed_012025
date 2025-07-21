#include <spdlog/spdlog.h>

#include <BinaryFileManager.hpp>
#include <utils.hpp>

BinaryFileManager::BinaryFileManager() {
    this->file_name = "default_file_name.dat";
    this->mode = std::ios_base::in | std::ios_base::out | std::ios_base::binary;
    this->stream.open(this->file_name, this->mode);
    checkOpen();
}

BinaryFileManager::BinaryFileManager(const std::string& file_name, const std::ios_base::openmode& mode) {
    if (!std::filesystem::exists(file_name)) {
        std::cerr << "File does not exist: " << file_name << std::endl;
    }
    this->file_name = file_name;
    this->mode = mode;
    this->stream.open(file_name, mode);
    checkOpen();
}

std::string BinaryFileManager::getFileName() const { return this->file_name; }

std::ios_base::openmode BinaryFileManager::getMode() const { return this->mode; }

std::fstream* BinaryFileManager::getStream() { return &this->stream; }

void BinaryFileManager::openFile(const std::ios_base::openmode& mode) {
    this->mode = mode;
    this->stream.open(this->file_name, mode);
    checkOpen();
}

BinaryFileManager::~BinaryFileManager() {
    if (this->stream.is_open()) {
        this->stream.close();
    }
}

void BinaryFileManager::commit() {
    if (this->stream.fail()) {
        IOErrorMessage(("Error committing changes to file " + this->file_name).c_str());
        return;
    }
    this->stream.close();
}

char* BinaryFileManager::readBitsSequence(const uint32_t& position, const uint32_t& n_bit) {
    char* read_string = new char[n_bit + 1];
    read_string[n_bit] = '\0';
    this->stream.seekg(position);
    if (this->stream.fail()) {
        failbit = true;
        SPDLOG_ERROR(("Failed to seek to position " + std::to_string(position) + " in file " + this->file_name).c_str());
        delete[] read_string;
        return nullptr;
    }
    this->stream.read(read_string, n_bit);

    // if (this->stream.fail()) {
    //     IOErrorMessage(("End of file reached at position " + std::to_string(position)).c_str());
    //     return nullptr;
    // }

    return read_string;
}

uint8_t BinaryFileManager::readBitsSequence(uint8_t& output, const uint32_t& position, const uint32_t& n_bit) {
    output = 0;
    char* read_string = readBitsSequence(position, n_bit);
    if (failbit == true) {
        return output;
    }

    for (uint8_t index = 0; index < n_bit; ++index) {
        if (read_string[index] == '1') {
            utils::setBit<uint8_t>(output, index);
        } else {
            utils::clearBit<uint8_t>(output, index);
        }
    }
    // output = static_cast<uint8_t>(atoll(read_string));
    delete[] read_string;
    return output;
}

uint16_t BinaryFileManager::readBitsSequence(uint16_t& output, const uint32_t& position, const uint32_t& n_bit) {
    output = 0;
    char* read_string = readBitsSequence(position, n_bit);
    if (failbit == true) {
        return output;
    }

    for (uint8_t index = 0; index < n_bit; ++index) {
        if (read_string[index] == '1') {
            utils::setBit<uint16_t>(output, index);
        } else {
            utils::clearBit<uint16_t>(output, index);
        }
    }
    // output = uint16_t(atoll(read_string));
    delete[] read_string;
    return output;
}

uint32_t BinaryFileManager::readBitsSequence(uint32_t& output, const uint32_t& position, const uint32_t& n_bit) {
    output = 0;
    char* read_string = readBitsSequence(position, n_bit);
    if (failbit == true) {
        return output;
    }

    for (uint8_t index = 0; index < n_bit; ++index) {
        if (read_string[index] == '1') {
            utils::setBit<uint32_t>(output, index);
        } else {
            utils::clearBit<uint32_t>(output, index);
        }
    }
    // output = uint32_t(atoll(read_string));
    delete[] read_string;
    return output;
}

uint64_t BinaryFileManager::readBitsSequence(uint64_t& output, const uint32_t& position, const uint32_t& n_bit) {
    output = 0;
    char* read_string = readBitsSequence(position, n_bit);
    if (failbit == true) {
        return output;
    }

    for (uint8_t index = 0; index < n_bit; ++index) {
        if (read_string[index] == '1') {
            utils::setBit<uint64_t>(output, index);
        } else {
            utils::clearBit<uint64_t>(output, index);
        }
    }
    // output = uint64_t(atoll(read_string));
    delete[] read_string;
    return output;
}

std::string BinaryFileManager::readBitsSequence(std::string& output, const uint32_t& position, const uint32_t& n_bit) {
    output = '\0';
    char* read_string = readBitsSequence(position, n_bit);
    if (failbit == true) {
        return output;
    }

    uint8_t aux_value = 0;
    char* aux_output = new char[n_bit / 8 + 1];
    aux_output[n_bit / 8] = '\0';  // Null-terminate the string
    for (int index = 0; index < (n_bit / 8); ++index) {
        for (int bit_index = 0; bit_index < 8; ++bit_index) {
            if (read_string[index * 8 + bit_index] == '1') {
                utils::setBit<uint8_t>(aux_value, bit_index);
            } else {
                utils::clearBit<uint8_t>(aux_value, bit_index);
            }
        }
        aux_output[index] = static_cast<char>(aux_value);
    }

    output = std::string(aux_output);
    delete[] read_string;
    return output;
}

char BinaryFileManager::readBitsSequence(char& output, const uint32_t& position, const uint32_t& n_bit) {
    output = *(readBitsSequence(position, n_bit));
    if (failbit == true) {
        output = '\0';  // or handle error as needed
        return output;
    }
    return output + '\0';  // Null-terminate the string to ensure it is a valid C-style string
}

float BinaryFileManager::readBitsSequence(float& output, const uint32_t& position, const uint32_t& n_bit) {
    char* read_string = readBitsSequence(position, n_bit);
    if (failbit == true) {
        output = 0.;  // or handle error as needed
        return output;
    }
    output = atof(read_string);
    delete[] read_string;
    return output;
}

double BinaryFileManager::readBitsSequence(double& output, const uint32_t& position, const uint32_t& n_bit) {
    char* read_string = readBitsSequence(position, n_bit);
    if (failbit == true) {
        output = 0.;  // or handle error as needed
        return output;
    }
    uint32_t shift = sizeof(double) * 8 / sizeof(char);
    char** stop_string = new char*(read_string + shift);
    output = strtod(read_string, stop_string);
    delete[] read_string;
    return output;
}

bool BinaryFileManager::readBitsSequence(bool& output, const uint32_t& position, const uint32_t& n_bit) {
    char* read_string = readBitsSequence(position, n_bit);
    if (failbit == true) {
        output = false;  // or handle error as needed
        return output;
    }
    output = utils::readBit<bool>(read_string, 0);
    delete[] read_string;
    return output;
}

int BinaryFileManager::readBitsSequence(int& output, const uint32_t& position, const uint32_t& n_bit) {
    char* read_string = readBitsSequence(position, n_bit);
    if (failbit == true) {
        output = 0;  // or handle error as needed
        return output;
    }
    output = atoi(read_string);
    delete[] read_string;
    return output;
}

void BinaryFileManager::writeBitsAtPosition(const char* target, uint32_t n_bit, uint32_t position) {
    if (!this->stream.is_open() && position < 0) {
        IOErrorMessage(("Can not write to file " + this->file_name + " at position " + std::to_string(position)).c_str());
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
    this->stream.open(this->file_name, mode);
    this->mode = mode;
    checkOpen();
    this->stream.seekg(position);
}

void BinaryFileManager::checkOpen() {
    if (this->stream.is_open() == false) {
        IOErrorMessage(("File " + this->file_name + " is not open").c_str());
    }
}

void BinaryFileManager::IOErrorMessage(const char* c) {
    SPDLOG_ERROR(c);
    throw std::ios_base::failure(c);
}