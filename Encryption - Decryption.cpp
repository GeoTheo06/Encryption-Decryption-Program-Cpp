#include <string>
#include <iostream>
#include <ctime>
using namespace std;

void encryption() {
	srand(time(0));

	string text;
	cout << "Write the text You want to be encrypted: ";
	cin.ignore();
	getline(cin, text);

	int textLength = text.length(); //number of the characters in the user's text
	char* textChar = new char[textLength];

	textChar = &text[0]; //converting string "text" to char "textChar"

	int* textNum = new int[textLength];

	for (int i = 0; i < textLength; i++) { //user's each character to ascii
		textNum[i] = textChar[i];
	}

	int words = 1;
	for (int i = 0; i < textLength; i++) { //counting how many words user's text has. (By counting the spaces he uses)
		if (textNum[i] == 32) {
			words += 1;
		}
	}

	char* privateKey = new char[words];

	cout << "select character encode: "; //character which will be encrypted (private key - has to be included in the output)
	char privateKeyCharacter;
	cin >> privateKeyCharacter;

	for (int i = 0; i < words; i++) { //Each letter of the private key corresponds to each word from the user's text
		privateKey[i] = privateKeyCharacter;
	}

	int* numbersOfPrivateKey = new int[words];
	for (int i = 0; i < words; i++) { //converting private key to ascii
		numbersOfPrivateKey[i] = privateKey[i];
	}

	cout << "---------------------------------------------------------";
	cout << "---------------------------------------------------------" << endl;

	cout << privateKeyCharacter << " ";

		//adding random numbers to each private Key and storing the output in "additionNumbers". If the output is greater than 126, I will cycle the remaining adding it to 32.
	int* additionNumbers = new int[words];
	for (int i = 0; i < words; i++) {
		additionNumbers[i] = (rand() % 90) + 1; //from 1 to 90
		numbersOfPrivateKey[i] += additionNumbers[i];
		if (numbersOfPrivateKey[i] > 126) {
			numbersOfPrivateKey[i] -= 94; //(94 comes from 126-32) | 126 = the last character in ascii that can be printed normally on the console. | 32 = the minimum character in ascii that can be printed on the cmd
		}
		privateKey[i] = numbersOfPrivateKey[i];
		cout << privateKey[i];
	}
	cout << " ";

	//Now I am using the corresponding private key addition and using it for each letter of the private key's corresponding word. - Adding the same numbers I used for each private key. For Exampe: private key = 'a', user's text = "hey I am" Private Keys: a + 30 | a + 26 | a + 69 | Encrypted Text: h+30 | e+30 | y+30 | I + 26 | a + 69 | m + 69
	char* encryptedText = new char[textLength];
	int w = 0;
	for (int i = 0; i < textLength; i++) {
		if (textNum[i] == 32) {
			w += 1;
			encryptedText[i] = 32;
		} else {
			textNum[i] += additionNumbers[w];
			if (textNum[i] > 126) {
				textNum[i] -= 94;
			}
			encryptedText[i] = textNum[i];
		}
	}

	for (int i = 0; i < textLength; i++) {
		cout << encryptedText[i];
	}
	cout << endl << "---------------------------------------------------------";
	cout << "---------------------------------------------------------" << endl;
}

void decryption() {
	string encryptedText;
	cout << "paste the encrypted text that was given to you: " << endl;
	cin.ignore();
	getline(cin, encryptedText);

	int textLength = encryptedText.length();

	cout << "---------------------------------------------------------";
	cout << "---------------------------------------------------------" << endl;

	char* encryptedTextChar = new char[textLength];
	encryptedTextChar = &encryptedText[0];

	char encryptionCharacter = encryptedTextChar[0]; //Getting the first character (encryption character) from the encrypted text.

	int Position_Of_Second_Space = 0;
	for (int i = 2; i < textLength; i++) {
		if (encryptedTextChar[i] == 32) { //locating the second space (after that follows the encryption characters which show by how much each letter's word was added)
			Position_Of_Second_Space = i;
			break;
		}
	}
	char* pointers = new char[Position_Of_Second_Space - 2];
	for (int i = 0; i < Position_Of_Second_Space - 2; i++) {
		pointers[i] = encryptedTextChar[i + 2]; //Getting the encryption characters which show the number by how much each letter's word was added
	}

	//finding the random numbers that were added in each word
	int* additionNumbers = new int[Position_Of_Second_Space - 2];
	for (int i = 0; i < Position_Of_Second_Space - 2; i++) {
		if (pointers[i] > encryptionCharacter) {
			additionNumbers[i] = pointers[i] - encryptionCharacter; //if pointers is greater than encryptionCharacter then the number was not decreased by 94
		}
		if (pointers[i] < encryptionCharacter) {
			additionNumbers[i] = pointers[i] + 94 - encryptionCharacter; //if pointers is smaller than encryptionCharacter then the number was not decreased by 94 so I have to increase it by 94
		}
	}

	//In this section I am decrypting the text
	int w = 0;
	char* decrypted_Text = new char[textLength - (Position_Of_Second_Space + 1)];
	int* decrypted_Text_Int = new int[textLength - (Position_Of_Second_Space + 1)];
	int testingNumbers;
	int i2 = 0;
	for (int i = Position_Of_Second_Space + 1; i < textLength; i++) {

		if (encryptedTextChar[i] == 32) {
			w += 1;
			decrypted_Text_Int[i2] = 32;
		} else {
			if (encryptedTextChar[i] > encryptionCharacter) {
				decrypted_Text_Int[i2] = encryptedTextChar[i] - additionNumbers[w]; //if encryptedTextChar is greater than encryptionCharacter, the number was not increased by 94
			}

			testingNumbers = encryptedTextChar[i] - additionNumbers[w] + 94;
			if (encryptedTextChar[i] < testingNumbers && encryptedTextChar[i] > encryptionCharacter && testingNumbers < 127 && testingNumbers > 32) {
				decrypted_Text_Int[i2] = testingNumbers;
			}

			if (encryptedTextChar[i] <= encryptionCharacter) {
				decrypted_Text_Int[i2] = encryptedTextChar[i] - additionNumbers[w] + 94; //if encryptedTextChar is smaller than encryptionCharacter then the number was not decreased by 94 so I have to increase it by 94
				if (decrypted_Text_Int[i2] > 126) {
					decrypted_Text_Int[i2] = encryptedTextChar[i] - additionNumbers[w];
				}
			}
		}
		decrypted_Text[i2] = decrypted_Text_Int[i2];
		cout << decrypted_Text[i2];
		i2 += 1;
	}
	cout << endl << "---------------------------------------------------------";
	cout << "---------------------------------------------------------" << endl;
}

int main() {

	while (true) {
		cout << "1. Encrypt" << endl;
		cout << "2. Decrypt" << endl;
		cout << "3. Exit" << endl;
		int choice;
		cin >> choice;
		if (choice == 1) {
			encryption();
		}
		if (choice == 2) {
			decryption();
		}
		if (choice == 3) {
			return 0;
		}
	}
}
