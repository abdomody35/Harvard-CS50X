# Quizzzy.com: a quiz making web application

#### Video Demo:
[Video Demo Link](https://youtu.be/Drp0xcB4qgU)

#### Description:
Quizzzy.com is a web application designed to simplify the process of creating and managing quizzes. It allows users to register, log in, create quizzes, view their created quizzes, and delete them if necessary. The application is built using Flask, a micro web framework for Python, along with SQLite database for data storage.

#### Features:
- **User Authentication**: Users can register for an account and log in securely using their username and password. Passwords are hashed using Werkzeug's password hashing utility.
- **Quiz Creation**: Authenticated users can create quizzes by adding various types of questions, including multiple-choice questions (MCQ), true/false questions (TF), and text-based questions. They can also specify correct answers for MCQs.
- **Quiz Viewing**: Users can view the quizzes they've created, along with the questions and corresponding answers.
- **Quiz Deletion**: Users have the ability to delete the quizzes they've created, removing them from the system.

#### Usage:
1. **Registration and Login**: Users can register for an account by providing a unique username and a password. Once registered, they can log in using their credentials.
2. **Creating Quizzes**: After logging in, users can navigate to the "Make a Quiz" page to start creating quizzes. They can add questions of different types and specify correct answers where applicable.
3. **Viewing Quizzes**: Users can see a list of quizzes they've created by visiting the "My Quizzes" page. From there, they can click on a quiz to view its details.
4. **Deleting Quizzes**: If users wish to remove a quiz, they can do so by clicking the "Delete" button next to the quiz they want to delete on the "My Quizzes" page.

#### Technologies Used:
- **Flask**: Flask is a micro web framework written in Python. It is lightweight and provides tools and libraries for building web applications.
- **SQLite**: SQLite is a relational database management system contained in a C library. It is self-contained, serverless, and zero-configuration.
- **CS50 Library**: CS50 is a library provided by Harvard University for interacting with SQLite databases using Python.
- **Werkzeug**: Werkzeug is a comprehensive WSGI web application library for Python. It includes utilities for handling requests, responses, and security features like password hashing.
- **Bootstrap**: Bootstrap is a popular front-end framework for designing responsive and mobile-first websites.

#### File Structure:
- **app.py**: Contains the main Flask application code, including route definitions, database interactions, and user authentication functions.
- **make.html**: HTML template for the page where users can create quizzes.
- **quizzes.html**: HTML template for the page displaying the list of quizzes created by the user.
- **view.html**: HTML template for the page displaying the details of a specific quiz.
- **login.html**: HTML template for the login page.
- **register.html**: HTML template for the registration page.
- **apology.html**: HTML template for rendering apology messages in case of errors.
- **delete.html**: HTML template for the confirmation page when deleting a quiz.
- **layout.html**: Base HTML template containing the common layout structure for all pages.

#### Setup Instructions:
1. Clone the repository to your local machine.
2. Make sure you have Python installed on your system.
3. Install Flask and other required dependencies using pip.
4. Run the Flask application using the command `flask run` while at the directory where **app.py** is.
5. Access the application through your web browser at `http://localhost:5000`.

#### Contributions:
Contributions to the project are welcome. If you find any bugs or have suggestions for improvements, feel free to open an issue or submit a pull request on the GitHub repository.

#### License:
This project is licensed under the [MIT License](https://opensource.org/licenses/MIT). You are free to use, modify, and distribute the code for both commercial and non-commercial purposes.
