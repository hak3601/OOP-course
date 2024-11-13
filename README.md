# OOP course

This is Object-oriented Programming Language (2-2) course, in 2024.

## Program Structure

## Exam Managing System

This project is a complete Exam System written in C++. It is a system that enables users to set up tests, administer tests, view and grade results, and analyze performance data. Users can set up tests with multiple questions, including objective and essay questions. A Timer for each test can be generated and can randomly select questions from a large pool of questions. It also allows users(professor) to leave comments on the test results for further analysis. The system also allows the administrator to publish test results and print out a summary. It records exam answers, multiple choice, and short answer questions, time spent, and marks obtained. With this system, users will be able to take the exams with ease and accuracy.

Our program will have two main functions:
Exam practicing system, and
Exam taking system

## Rules

1. Define naming
   Class name - start with capital letter (e.g., Student, Exam)
   Member name - all low caps divided by underscore(_)(e.g., studen_id)
   Method name - low to capital letter, don’t use underscore( _ ) (e.g., takingExam())
   File name - all low caps(student.h, main.cpp)
2. For text file, save under “data” folder separately
3. For all code files, save under “code” folder separately
4. Follow the below laws for comments

   1. method(function)and class explanation comments should be inside the function
      example ->
      void simplefunc(int a, int b){
      /_
      (explantion about method right here)
      _/
      ...
      }

   2. variable comments should be on the right side of declaration
      example ->
      int simplevar; // (explantion about variable right here)

   3. Ordinary comments should be placed clean lines(lines with no code)
      example ->
      // calling simplefunc to perform operation
      simplevar = simplefunc(args);
      ...

   —----------------------—----------------------—----------------------—---------------------
   user:
   User(1) => Professor View
   User(2) => Student View

Class User(
member var : name, id, password
)
Class Professor : User(
member var : instructing_courses
Method : create_exam(), mark_exam(), comment_exam()
)
Class Student : User(
member var : enroled_courses
Method : take_exam()
)

"Main Function"

VerifyUser() => verify if the current user is professor or student
Student
course
result
professor()
Course()

Exam()
heldExam(): Professor can held an exam for a course
takeExam(): Student can take an exam for this course

Question()
trueFalseQ()
multilpleChoiceQ()
completionQ()

DynamicDifficultyEngine: Adjusting the difficulty of the questions while taking exam (dynamically)
currentDifficultyLevel
getNextQuestion()
adjustDifficulty()

PreformanceTracker:
quesitonDifficulty
correctAnswers
timeSpent
recordAnswer()
generateReport()
