# Database Management System with C
### Overview
This project implements a lightweight database management system written in C.
It focuses on core database concepts such as **data structure design, indexing, and SQL-like query parsing**, providing a minimal yet educational implementation of a relational data engine.

### 🎥 Demo
![Project Demo](/static/demo.gif) 

### Key Features
**1. Structured and Modular Design**

- Separation between data (USERDATA) and linked list nodes (Node)
  
- Independent layers for data storage, index management, and UI interaction
  
- Improves modularity and maintainability of the codebase

**2. SQL-Like Query Engine**

- Supports simplified SQL syntax:
  - `SELECT`, `WHERE`, `ORDER BY`, `INSERT`, `DELETE`
    
- Queries are parsed and executed against in-memory data
  
- Designed for intuitive command-line interaction

  - *SELECT*:
    
    <img src="/static/capture1-select-all.png" width=700/>

  - *WHERE*:
    
    <img src="/static/capture5-where.png" width=700/>

  - *ORDER BY*:
  
    <img src="/static/capture3-order.png" width=700/>

  - *INSERT*:

    <img src="/static/capture2-insert.png" width=700/>

  - *DELETE*:

    <img src="/static/capture4-delete.png" width=700/>


**3. Doubly Linked List–Based Storage**

- Core database operations are executed on a doubly linked list

- Enables efficient traversal and manipulation of records

- Demonstrates understanding of dynamic memory management in C


**4. Indexing for Optimized Search**

- Index fields are maintained separately from main data structures

- Enables efficient range and key-based lookups without sorting the entire dataset

- Provides a simple index mechanism for faster query execution


**5. File and Memory Management**

- Database is loaded from file into memory at startup

- Users can modify in-memory data and selectively save changes back to disk

- Demonstrates separation between persistent and transient data layers
