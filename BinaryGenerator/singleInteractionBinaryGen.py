import csv
import os
import sys

# Define standard field lengths for binary conversion
FIELD_LENGTHS = {
    "ID": 32,  # Length for ID field
    "TYPE": 8,  # Length for TYPE field
    "NSEQ": 16,  # Length for number of sequences field
    "SINGLE_SEQ": 34 * 8,  # Length for each dialog sequence
    "MONEY": 32,  # Length for MONEY field
    "CHOICE1": 32,  # Length for first choice field
    "CHOICE2": 32,  # Length for second choice field
    "CHOICE3": 32,  # Length for third choice field
    "CHOICE4": 32,  # Length for fourth choice field
    "ID_OBJECT": 32,  # Length for object ID field
    "ID_TRAINER": 32,  # Length for trainer ID field
    "ID_TRIGGER": 16,  # Length for trigger ID field
    "STATUS_CHANGE": 8,  # Length for status change field
}

# Request CSV file name from the user
FILE_NAME = sys.argv[1]
FILE_PATH = f"{FILE_NAME}.csv"  # Full path to the input CSV file
OUTPUT_DIR = "output_files"  # Directory to save the output files
OUTPUT_FILE_PATH = os.path.join(OUTPUT_DIR, f"{FILE_NAME}.txt")  # Full path to the output text file


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
    binary_parts.append(to_binary(row[0], FIELD_LENGTHS["ID"]))  # Convert ID field
    binary_parts.append(to_binary(row[1], FIELD_LENGTHS["TYPE"]))  # Convert TYPE field
    binary_parts.append(to_binary(row[2], FIELD_LENGTHS["NSEQ"]))  # Convert NSEQ field

    # Process dialog sequences (dynamic number based on NSEQ)
    n_seq = int(row[2])  # Number of dialog sequences
    for seq in range(n_seq):
        binary_parts.append(to_binary(row[3 + seq], FIELD_LENGTHS["SINGLE_SEQ"]))  # Convert each dialog sequence

    # Process additional fields based on TYPE
    type_value = int(row[1])  # Determine the TYPE value
    offset = 3 + n_seq  # Calculate the starting index for additional fields

    # Handle additional fields for specific TYPE values
    if type_value in {1, 2}:
        pass  # No additional fields for TYPE 1 and 2
    elif type_value == 3:
        binary_parts.append(to_binary(row[offset], FIELD_LENGTHS["CHOICE1"]))
        binary_parts.append(to_binary(row[offset + 1], FIELD_LENGTHS["CHOICE2"]))
    elif type_value == 4:
        binary_parts.append(to_binary(row[offset], FIELD_LENGTHS["CHOICE1"]))
        binary_parts.append(to_binary(row[offset + 1], FIELD_LENGTHS["CHOICE2"]))
        binary_parts.append(to_binary(row[offset + 2], FIELD_LENGTHS["CHOICE3"]))
        binary_parts.append(to_binary(row[offset + 3], FIELD_LENGTHS["CHOICE4"]))
    elif type_value == 5:
        binary_parts.append(to_binary(row[offset], FIELD_LENGTHS["ID_OBJECT"]))
    elif type_value == 6:
        binary_parts.append(to_binary(row[offset], FIELD_LENGTHS["STATUS_CHANGE"]))
    elif type_value == 7:
        binary_parts.append(to_binary(row[offset], FIELD_LENGTHS["ID_TRIGGER"]))
    elif type_value == 8:
        binary_parts.append(to_binary(row[offset], FIELD_LENGTHS["ID_TRAINER"]))
        binary_parts.append(to_binary(row[offset + 1], FIELD_LENGTHS["MONEY"]))

    return ''.join(binary_parts)  # Concatenate all binary parts into a single string


# Ensure the output directory exists
os.makedirs(OUTPUT_DIR, exist_ok=True)

# Process the CSV file
try:
    with open(FILE_PATH, mode="r", encoding="utf-8") as file:
        reader = csv.reader(file, delimiter=";")  # Read the CSV file with ';' as the delimiter

        # Clear the content of the output file before writing
        with open(OUTPUT_FILE_PATH, "w", encoding="utf-8") as output_file:
            output_file.write("")

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

