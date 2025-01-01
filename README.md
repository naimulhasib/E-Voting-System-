E-Voting System

An E-Voting System implemented in C that simulates a simple, secure, and efficient voting process. The system allows voters to cast their votes and administrators to manage candidates and view results. This project is designed as a learning exercise, combining file handling, structured programming, and secure access control.

Features

Voter Functionalities:
	1.	Vote Casting: Voters can cast their votes for registered candidates.
	2.	NID Verification: Ensures that only unique and valid 13-digit National IDs (NIDs) are allowed to vote.
	3.	Duplicate Vote Prevention: Checks if a voter has already voted.

Admin Functionalities:
	1.	Admin Authentication: Protected by an admin password to prevent unauthorized access.
	2.	Candidate Management: Admins can add new candidates dynamically.
	3.	Vote Results: View the total votes for all candidates.

Additional Features:
	•	Data Persistence:
	•	Candidate data is stored in candidates.txt for persistence across sessions.
	•	Voter data is logged in voters.txt to track voting activity.
	•	Preloaded Candidates: Includes five predefined candidates for testing purposes.
	•	Interactive Menus: User-friendly menus for easy navigation.

How It Works
	1.	Initialization:
	•	Predefined candidates are loaded at the start.
	•	Additional candidates are loaded from candidates.txt.
	2.	Voting Process:
	•	Voters enter their NID and name.
	•	The system validates the NID and ensures the voter hasn’t already voted.
	•	Voters select a candidate, and the vote is recorded.
	3.	Admin Actions:
	•	Admins log in using the password (admin123 by default).
	•	Admins can add candidates or view the current voting results.

File Details
	•	candidates.txt: Stores candidates and their votes in a name,votes format.
	•	voters.txt: Logs voter details, including NID, name, and the candidate they voted for.

Usage Instructions
	1.	Compile the Code:
Use a C compiler like gcc:

gcc evoting.c -o evoting


	2.	Run the Program:

./evoting


	3.	Choose an Option:
	•	Admin Menu
	•	Voter Menu
	•	View Project Credits
	•	Exit
	4.	Admin Operations:
	•	Add candidates.
	•	View results.
	5.	Voter Operations:
	•	Cast your vote securely.

Technologies Used
	•	Programming Language: C
	•	File Handling: Used for storing and retrieving candidate and voter data.
	•	Input Validation: Ensures data integrity and prevents misuse.

Credits

This project was developed by:
	•	Naimul Hasib Ratul (ID: 2422069642)
	•	Md Aowlad Hussain (ID: 2422785642)
	•	Mohammad Rizwanul Hasan (ID: 2422930042)

Future Improvements
	1.	Enhanced Security: Encrypt voter and candidate data.
	2.	Web-based Interface: Transition to a web application for accessibility.
	3.	Real-time Results: Provide live updates on voting progress.

This E-Voting System showcases the fundamentals of C programming, file handling, and secure access, making it a great starting point for more advanced voting systems.
