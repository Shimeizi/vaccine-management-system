# 💉 Vaccine Management System

A C project developed for a programming course.

## 📖 Overview

This project implements a command-line vaccine management system.

The system manages vaccine batches and inoculation records, allowing users to register vaccine batches, administer doses, track inoculations and manage vaccine availability through a set of commands.

## ✨ Features

* 💉 Register vaccine batches
* 📋 List available vaccine batches
* 🧑 Record vaccine inoculations
* 🚫 Remove vaccine batch availability
* 🗑️ Delete inoculation records
* 🔎 Query inoculations by user
* 📅 Simulated date management
* 🧠 Dynamic memory management

## 🛠️ Built With

* C
* GCC

## ⚙️ Compilation

Compile the project using:

```bash
gcc -O3 -Wall -Wextra -Werror -Wno-unused-result -o proj *.c
```

## ▶️ Running

Run the program with an input file:

```bash
./proj < test.in > test.myout
```

## 🧪 Testing

Compare your output with the expected output:

```bash
diff test.out test.myout
```

You can also run the provided public tests using:

```bash
make
```

## 🐞 Debugging

For debugging with tools such as `gdb` or `valgrind`, compile the project with:

```bash
gcc -g -Wall -Wextra -Werror -Wno-unused-result -o proj *.c
```

## 📄 Additional Information

For a detailed description of the project requirements, please refer to the project specification PDF included in this repository.
