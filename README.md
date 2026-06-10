# 💉 Vaccine Management System

A C project developed for a programming course.

## 📖 Overview

This project implements a vaccine management system that manages vaccine batches and inoculation records through a command-line interface.

The system supports vaccine registration, dose administration, inoculation tracking, batch management and simulated date progression.

## ✨ Features

* 💉 Register vaccine batches
* 📋 List available vaccines
* 🧑 Manage vaccine inoculations
* 🚫 Remove vaccine availability
* 🗑️ Delete vaccination records
* 🔎 Query user inoculations
* 📅 Simulated date management
* 🧠 Dynamic memory allocation and management

## 🛠️ Built With

* C
* GCC

## ⚙️ Compilation

Compile the program with:

```bash
gcc -O3 -Wall -Wextra -Werror -Wno-unused-result -o proj *.c
```

## ▶️ Running

Run the program by redirecting an input file:

```bash
./proj < test.in > test.myout
```

## 🧪 Testing

Compare your output with the expected output:

```bash
diff test.out test.myout
```

Alternatively, use the provided public tests:

```bash
make
```

## 🐞 Debugging

For debugging with tools such as `gdb` or `valgrind`, compile with:

```bash
gcc -g -Wall -Wextra -Werror -Wno-unused-result -o proj *.c
```

## 📄 Additional Information

For a detailed description of the project requirements, please refer to the project specification PDF included in this repository.
