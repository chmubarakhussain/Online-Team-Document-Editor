# Online-Team-Document-Editor
Online team document editor is based on Google Docs implemented in C++ with purpose to using relevant Data Structures for this simple project.
An international company with multiple branches around the world maintains an online repository of important and confidential files
on its server. The files can be accessed by authorized employees from the different branches. The employees can read and write the 
files. The different employees (users) can try to simultaneously access the same file. This may pose a problem in some scenarios. 
Let say user A and user B try to access File X from their computer systems.
• If both A and B wants to read the File X, then there is no problem
• If both A and B wants to update(write) the File X. This can create a problem, and system will be confused which value to 
retain. 
• If A wants to write on the File X and B wants to read the File X. This is also problematic. As A is updating file X and B tries to 
read X, the user B can read some invalid values.
The most easy and simple solution is that we allow the different users to simultaneously read a file, but we do not allow them to 
simultaneously update a file. That is, if one user wants to write\update an existing file then other users must wait till he is done. 
Note, if a user wants both read and write access to a file. Then he will just ask for write access as he can read while writing
