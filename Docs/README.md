# Vaccine Tracking System

## Description

Implement an “Egyptian Vaccine Tracking System” in C++. That allows the users to enter their personal and vaccination information and let the administrator calculate basic statistics to draw insights from such data. [https://www.washingtonpost.com/graphics/2020/health/covid-vaccine-states-distribution-doses/] What is meant by Egyptian is that it should be specifically tailored to tracking the vaccination process for Egyptians in Egypt in the sense that the National IDs should be 13 numbers, the user can only enter Egyptian governorates, etc To make things easier, we won’t account for Egyptians living abroad or non-Egyptian residents. Only Egyptian residents.

## Minimum Requirements

The program has two type of users:

    1) Normal User
        - Register as new account by providing personal record containing: 
          - Full Name
          - National ID [Unique = Shouldn’t accept duplicates]
          - Password
          - Gender
          - Age
          - Country [Maybe an Egyptian is Living abroad]
          - Governorate
          - Already vaccinated or applying for vaccination?
          - If vaccinated, received only one or both doses?
          - If not, the user should be added to a waiting list.
        - Login using the National ID and password
        - Display his own records
        - Edit any of his information
        - Delete his personal records (Account)
    
    2) Admin
        - All the above features as every admin is a normal user in the first place
        - Login using the National ID and admin password
        - Root admin can give normal users admin privilage (set an admin password for this account to be able to login in the admin restricted part)
        - View all users
        - View specific user by his National ID
        - Delete all users
        - Delete specific user by his National ID
        - Get basic statistics about the registered people like: 
          - Percentage of people that has received the first dose
          - Percentage of people that has received both doses
          - Percentage of people that has not received any dose
          - Percentage of females and males registered
          - Percentage of people registered from each government

## UI Forms

The UI contains mainly 7 forms (Views):

    - Normal User Platform Forms
      - Register new users
      - Login for normal users
      - Display all his records, enable him to edit any one of them, and delete his account
    - Admin Platform Forms
      - Login an admin
      - A form for viewing all users, search about specific one using his National ID and deletion option
      - A form displaying the basic statistics using data visualization way
      - A form for giving admin privilage for specific normal use
