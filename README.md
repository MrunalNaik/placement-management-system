# placement-management-system
A C++ project to manage student placement records, demonstrating OOP principles and file handling.

# Placement Management System in C++

This is a simple, command-line based Placement Management System built with C++. It allows a user to create, update, and view placement records for various companies. The project demonstrates core C++ concepts including Object-Oriented Programming (OOP), file I/O for data persistence, and a clean, menu-driven user interface.

## Features

* **Create New Records:** Enter details for a new company placement, including name, address, and the number of students placed. Each record is saved to its own file.
* **Edit Existing Records:** Modify the number of students placed for a previously entered company.
* **Append Salary Data:** Add or update the salary package information (LPA) for a company record.
* **Display All Records:** View a consolidated list of all placement records saved in the system.
* **Data Persistence:** All records are saved to `.txt` files, ensuring data is not lost when the program closes.

## Technical Concepts Used

* **Programming Language:** C++
* **Object-Oriented Programming:** Utilizes a `PlacementSystem` class to encapsulate all logic and a `Record` struct to model the data.
* **File I/O:** Uses C++ `fstream` library to read from and write to text files for data persistence.
* **Standard Template Library (STL):** Employs `std::string`, `std::vector`, and `std::iostream` for data handling and user interaction.
* **Portable Code:** Written to be cross-platform compatible (Windows, macOS, and Linux).
