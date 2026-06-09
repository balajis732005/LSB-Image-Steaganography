# LSB Image Steganography

This project is a command-line based **LSB (Least Significant Bit) Image Steganography System** developed in C. It demonstrates the use of file handling, dynamic memory management, bitmap image processing, and modular programming concepts to securely hide and retrieve text files inside BMP images.

## Features

The application supports the following operations:

### 1. Encode Data into Image

Allows the user to hide a text file inside a BMP image using the Least Significant Bit (LSB) steganography technique.

During encoding, the following information is embedded into the image:

* Magic String (`#E#`) for validation
* Input file name
* Input file extension
* Input file size
* Input file content

### 2. Decode Data from Image

Extracts the hidden file from an encoded BMP image.

During decoding, the application:

* Verifies the magic string
* Extracts file metadata
* Reconstructs the original file
* Saves the decoded file in the output directory

### 3. BMP Image Validation

The system validates:

* BMP file signature (`BM`)
* Header format
* Header size
* 24-bit RGB image support
* Uncompressed BMP images

### 4. Capacity Verification

Before encoding, the program verifies whether the selected BMP image has sufficient capacity to store the secret data.

### 5. Error Handling

The application handles various error conditions such as:

* Missing input files
* Invalid image format
* Unsupported BMP types
* Insufficient image capacity
* Output file creation failures

---

## Project Structure

```
LSB_Image_Steganography/

├── src/                     # Source and header files
│   ├── main.c
│   ├── encode.c
│   ├── encode.h
│   ├── decode.c
│   ├── decode.h
│   ├── data.h
│   └── ...
│
├── input/                   # Input BMP and text files
│
├── output/                  # Generated encoded and decoded files
│
├── steganography.out        # Executable file
│
├── Makefile                 # Build automation script
│
└── README.md
```

---

## How LSB Steganography Works

LSB (Least Significant Bit) Steganography hides information by modifying the least significant bit of image pixel data.

Example:

```
Original Byte : 11001010
Secret Bit    : 1
Modified Byte : 11001011
```

The visual appearance of the image remains almost unchanged while carrying hidden information.

---

## How to Build and Run

### Compile the Project

```bash
make run
```

This command will:

* Compile all source files
* Generate object files
* Link all modules
* Create the executable

### Run the Program

```bash
./steganography.out
```

---

## Program Menu

```
Welcome to LSB Image Steganography!

1) ENCODE - E
2) DECODE - D
```

### Encoding

Input:

```
Input Message File Path
Input BMP Image File Path
```

Output:

```
output/<image_name>_encoded.bmp
```

### Decoding

Input:

```
Encoded BMP Image File Path
```

Output:

```
output/<original_file_name>_decoded_<image_name>.<extension>
```

---

## Supported File Formats

### Image Files

Supported:

* BMP (.bmp)
* 24-bit RGB BMP
* Uncompressed BMP

Not Supported:

* PNG
* JPEG
* GIF
* Compressed BMP

### Secret Files

Any file that can be processed as binary/text data can be hidden, subject to image capacity limitations.

Examples:

* .txt
* .c
* .h
* .csv
* .log

---

## Concepts Used

* File Handling (`fopen`, `fread`, `fwrite`, `fclose`)
* Dynamic Memory Allocation (`malloc`, `free`)
* Structures
* Bitwise Operations
* BMP File Processing
* LSB Steganography
* Modular Programming
* Error Handling
* Makefile Automation

---

## Sample Workflow

### Encode

```
Enter Input Message File Path:
input/message.txt

Enter Image File Path:
input/sample.bmp
```

Generated Output:

```
output/sample_encoded.bmp
```

### Decode

```
Enter Encoded Image File Path:
output/sample_encoded.bmp
```

Generated Output:

```
output/message_decoded_sample.txt
```

---

## Notes

* Only 24-bit uncompressed BMP images are supported.
* Ensure the image has sufficient capacity before encoding.
* The output directory must exist before execution.
* The magic string (`#E#`) is used to verify whether an image contains encoded data.
* Memory allocated dynamically is released appropriately to avoid memory leaks.

---

## Learning Objectives

This project demonstrates:

* Real-world usage of bit manipulation
* Binary file processing
* Image data handling
* Dynamic memory management
* Data hiding techniques
* Secure file embedding concepts

---
