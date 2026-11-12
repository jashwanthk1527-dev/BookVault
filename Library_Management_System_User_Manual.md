# Library Management System: User Manual & Documentation

Welcome to the **Library Management System**! This application is designed to simulate core library operations using fundamental data structures—specifically **Stacks** and **Queues**—to manage books, holds, and recent user actions efficiently.

---

## 1. System Overview & Architecture

Unlike traditional database-backed systems, this project utilizes in-memory data structures to demonstrate algorithmic principles:
*   **Queues (FIFO - First In, First Out):** Used for managing the book reservation or waitlist queue. When a popular book is checked out, subsequent requesters join the queue and are served in the exact order they arrived.
*   **Stacks (LIFO - Last In, First Out):** Used for tracking recent transactions, undoing actions, or managing browsing history (e.g., recently viewed books or undoing the last check-in/check-out action).

---

## 2. Getting Started & Installation

### Prerequisites
*   Ensure you have the appropriate runtime installed depending on the language of the code provided in your repository (e.g., Python 3.x, Java, or Node.js).

### Running the Application
1. Clone your repository from GitHub:
   ```bash
   git clone https://github.com/your-username/your-library-repo.git
   cd your-library-repo
   ```
2. Execute the main program file (example for Python):
   ```bash
   python main.py
   ```

---

## 3. User Guide: Features & Menu Options

When you launch the application, you will be presented with a text-based interactive menu. Here is how to navigate each feature:

### A. Adding and Managing Books
*   **Add New Book:** Input the book ID, title, and author. The system registers the book into the main inventory.
*   **Search Book:** Look up a book by its title or ID to check its current availability status.

### B. Queue Operations (Reservations / Waitlists)
*   **Place Hold / Join Waitlist:** If a book is currently checked out, a user can request it. The system adds the user to a **Queue**.
*   **Process Next Reservation:** When the book is returned, the system automatically pulls the first user from the queue (FIFO principle) to notify them that the book is now available.

### C. Stack Operations (History & Undo Actions)
*   **View Recent Activity:** Inspect the **Stack** of recent transactions (e.g., last books checked out or returned).
*   **Undo Last Action:** If an erroneous check-in or check-out is logged, the system pops the most recent operation off the stack (LIFO principle) to revert the state.

---

## 4. Troubleshooting & FAQ

*   **Q: What happens if I try to process a reservation queue when no one is waiting?**
    *   *A:* The system will output a message indicating that the queue is empty.
*   **Q: Can I undo multiple actions?**
    *   *A:* Yes, as long as the stack still contains previous transaction states. Once the stack is empty, further undo requests will prompt an underflow warning.

---
*Maintained with ❤️ for your GitHub repository.*