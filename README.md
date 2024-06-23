# Database Management Program with C
#### Version 1.0 

[placeholder for gif]  

### 🌄 Objectives
The aim of this project is to develop a database management program in C that is capable of:  
- [Separation of Data Structure and Data](####place-2)
- [SQL Syntax Parsing and Execution](####place-3)
- [Database Operations in a Doubly Linked List](####place-4)
- [Separation of Index and Data Structure](####place-5)
- [Separation of Linked List and UI Code](####place-6)
- [Distinction Between Data Stored in Files and Data Loaded in Memory](####place-7)
  
### 🐈‍⬛ Features
#### 1. Separation of Concerns
[placeholder for image]  
The `Node` structure handles the linked list functionality, while the `USERDATA` structure contains the actual data. This approach enhances modularity and makes the code easier to maintain.

#### 2. SQL-Like Query Parsing
The system can parse and execute SQL-like queries. This allows for a familiar and intuitive interface for database operations.

#### 3. Comprehensive Database Operations
Supported operations include:
- SELECT
- WHERE
- DELETE
- INSERT
- ORDER BY

These operations are efficiently handled within the doubly linked list structure.

#### 4. Optimized Index Management
The index field is separated from the main data structures. This design choice allows for:
- Efficient range searches on integer fields
- Avoiding the need to sort the entire data structure for searches
- Generating and sorting an array of indices for optimized operations
  
#### 5. Modular Code Design
The codebase is organized with a clear separation between linked list operations and user interface code.

#### 6. File vs Memory Data Management
The system operates primarily on in-memory data, but interacts with files in the following ways:
- Loads the initial database from a file into memory
- Allows users to make changes to the in-memory database
- Gives users the option to save their changes back to the file

  
