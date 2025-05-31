import csv
import os
import sys

# Define standard field lengths for binary conversion
FIELD_LENGTHS = {
    "BKG": 8,  # Length for ID field
    "OBJECT": 8,  # Length for TYPE field
    "COLLISION": 8,  # Length for number of sequences field
    "BKG_IMAGE": 56,  # Length for each dialog sequence
    "OBJ_IMAGE": 56,  # Length for MONEY field
    
}

# Request CSV file name from the user
FILE_NAME = sys.argv[1]
FILE_PATH = f"{FILE_NAME}.csv"  # Full path to the input CSV file
OUTPUT_DIR = "output_files"  # Directory to save the output files
OUTPUT_FILE_PATH = os.path.join(OUTPUT_DIR, f"{FILE_NAME}.dat")  # Full path to the output text file


def to_binary(value, bit_length):
    """
    Convert a value to a binary string with a specific bit length.
    - If the value is numeric, it converts it directly to binary.
    - If the value is a string, it converts each character to an 8-bit binary representation.

    Args:
        value (str): The input value (string or number) to convert.
        bit_length (int): The desired length of the binary string.

    Returns:
        str: The binary string of the specified length.
    """
    try:
        binary_value = bin(int(value))[2:]  # Convert numeric value to binary
    except ValueError:
        binary_value = ''.join(format(ord(c), '08b') for c in value)  # Convert string value to binary
    return binary_value.zfill(bit_length)  # Pad with leading zeros if necessary


def process_row(row):
    """
    Process a single row from the CSV file, converting it to a binary string.

    This function handles both the standard fields and additional fields based on the TYPE value.

    Args:
        row (list): A list of strings representing a single row from the CSV file.

    Returns:
        str: The concatenated binary string for the row.
    """
    binary_parts = []  # List to store binary parts of the row

    # Convert standard fields to binary
    binary_parts.append(to_binary(row[0], FIELD_LENGTHS["BKG"]))
    binary_parts.append(to_binary(row[1], FIELD_LENGTHS["OBJECT"]))
    binary_parts.append(to_binary(row[2], FIELD_LENGTHS["COLLISION"]))
    binary_parts.append(to_binary(row[3], FIELD_LENGTHS["BKG_IMAGE"]))
    binary_parts.append(to_binary(row[4], FIELD_LENGTHS["OBJ_IMAGE"]))

    return ''.join(binary_parts)  # Concatenate all binary parts into a single string


# Ensure the output directory exists
os.makedirs(OUTPUT_DIR, exist_ok=True)

# Process the CSV file
try:
    with open(FILE_PATH, mode="r", encoding="utf-8") as file:
        reader = csv.reader(file, delimiter=";")  # Read the CSV file with ';' as the delimiter

        # Clear the content of the output file before writing
        with open(OUTPUT_FILE_PATH, "wb") as output_file: #_ , encoding="utf-8" _ write option
            pass

        # Iterate through each row in the CSV file
        for i, row in enumerate(reader, start=1):
            if not row:  # Skip empty rows
                continue

            binary_data = process_row(row)  # Convert the row to a binary string

            # Append the binary data to the output file
            with open(OUTPUT_FILE_PATH, "a", encoding="utf-8") as output_file:
                output_file.write(binary_data + "\n")  # Add a newline after each binary string

    print(f"File saved as: {OUTPUT_FILE_PATH}")  # Print the path of the saved file

except FileNotFoundError:
    print(f"Error: The file '{FILE_PATH}' was not found. Please check the file name and try again.")


