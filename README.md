# Database Management Program with C
#### Version 1.0 

### 🎥 Demo
![Project Demo](/static/demo.gif) 

### 🌄 Objectives
The aim of this project is to develop a database management program in C that is capable of:  
- [Separation of Data Structure and Data](#section-1)
- [SQL Syntax Parsing and Execution](#section-2)
- [Database Operations in a Doubly Linked List](#section-3)
- [Separation of Index and Data Structure](#section-4)
- [Separation of Linked List and UI Code](#section-5)
- [Distinction Between Data Stored in Files and Data Loaded in Memory](#section-6)
  
### 🐈‍⬛ Features
<h4 id="section-1"> 1. Separation of Concerns </h4>
<img src="/static/code-structure.png" width=600/>
<br/>
The <code>Node</code> structure handles the linked list functionality, while the <code>USERDATA</code> structure contains the actual data. This approach enhances modularity and makes the code easier to maintain.
<br/>
<h4 id="section-2"> 2. SQL-Like Query Parsing </h4>
The system can parse and execute SQL-like queries. This allows for a familiar and intuitive interface for database operations.
<br/>
<h4 id="section-3"> 3. Comprehensive Database Operations </h4>
Supported operations include:<br/>
<ul>
<li>
<b><</b> <strong>SELECT</strong> <b>></b><br/>
<img src="/static/capture1-select-all.png" width=700/>
</li>
<li>
<b><</b> <strong>WHERE</strong> <b>></b><br/>
<img src="/static/capture5-where.png" width=700/>
</li>
<li>
<b><</b> <strong>ORDER BY</strong> <b>></b><br/>
<img src="/static/capture3-order.png" width=700/>
</li>
<li>
<b><</b> <strong>INSERT</strong> <b>></b><br/>
<img src="/static/capture2-insert.png" width=700/>
</li>
<li>
<b><</b> <strong>DELETE</strong> <b>></b><br/>
<img src="/static/capture4-delete.png" width=700/>
</li>

</ul>

These operations are efficiently handled within the doubly linked list structure.
<br/>
<h4 id="section-4"> 4. Optimized Index Management </h4>
The index field is separated from the main data structures. This design choice allows for:
<ul>
<li>Efficient range searches on integer fields</li>
<li>Avoiding the need to sort the entire data structure for searches</li>
<li>Generating and sorting an array of indices for optimized operations</li>
</ul>

<h4 id="section-5"> 5. Modular Code Design </h4>
The codebase is organized with a clear separation between linked list operations and user interface code.
<br/>
<h4 id="section-6"> 6. File vs Memory Data Management </h4>
The system operates primarily on in-memory data, but interacts with files in the following ways:
<ul>
<li>Loads the initial database from a file into memory</li>
<li>Allows users to make changes to the in-memory database</li>
<li>Gives users the option to save their changes back to the file</li>
</ul>
<br/>

### 🚀 Future Improvements
<ul>
  <li>Implement data caching for improved efficiency with large datasets, allowing for partial loading and updates, modifying only changed portions of the file</li>
  <li>Add roll-back functionality for operations that allows users to undo recent changes</li>
  <li>Enhance input validation and error handling to implement more thorough checks for user input</li>
  <li>Upgrade to a more robust data structure such as tree structure instead of a doubly linked list</li>
  <li>Multi-threading support for improved performance on large datasets</li>
  <li>Implementation of more complex SQL operations (e.g., JOINs, GROUP BY)</li>
</ul>
