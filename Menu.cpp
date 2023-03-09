#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

int strL(char arr[])
{
	int count = 0;
	while (arr[count] != '\0')
	{
		count++;
	}

	return count;
}

bool EmployeeLogin()
{
	fstream fout;
	char Username[20];
	char password[20];
	char userNameByUser[20];
	char passwordByUser[20];
	char reEnterCheck = 0;
	bool flagStopCheck = 1;

	do {
		cout << "Enter Username : ";
		cin.get(userNameByUser, 20);
		cin.ignore();

		cout << "Enter password : ";
		cin.get(passwordByUser, 20);
		cin.ignore();

		fout.open("EmployeesData.txt", ios::in);

		int count = 0;
		int countText = 0;
		char ch = 'a';
		int countRow = 0;
		flagStopCheck = 1;

		while (!fout.eof() && flagStopCheck)
		{

			fout >> ch;

			if (ch == ',')
			{
				Username[countText] = '\0';
				count++;
				countText = 0;

			}

			if (ch != '^')
			{
				if (ch != ',')
				{
					if (count == 0)
					{
						Username[countText++] = ch;
					}
					else if (count == 1)
					{
						password[countText++] = ch;
					}
				}
			}
			else
			{
				countRow++;

				if (!fout.eof())
				{
					password[countText] = '\0';

					bool flag = 1;

					if (strL(Username) != strL(userNameByUser))
					{
						flag = 0;
					}

					for (int i = 0; Username[i] != '\0' && userNameByUser[i] != '\0' && flag; i++)
					{
						if (Username[i] != userNameByUser[i])
						{
							flag = 0;
						}
					}

					if (flag)
					{
						for (int i = 0; password[i] != '\0' && passwordByUser[i] != '\0' && flag; i++)
						{
							if (password[i] != passwordByUser[i])
							{
								flag = 0;
							}
						}
					}

					if (flag)
					{
						flagStopCheck = 0;
					}

					count = 0;
					countText = 0;
				}
			}
		}

		fout.close();

		if (flagStopCheck == 1)
		{
			cout << endl << "WRONG INPUT!" << endl;

			cout << endl << "Press ESC to exit or Press any Key to continue" << endl;

			reEnterCheck = _getch();

			cout << endl << endl;

		}
	} while (reEnterCheck != 27 && flagStopCheck);

	if (flagStopCheck == 0)
	{
		return true;
	}

	return false;
}

void RenewAllTarrifTaxFile()
{
	fstream fout;
	fout.open("TariffTaxInfo.txt", ios::out);
	char data[10];

	for (int i = 0; i < 4; i++)
	{
		if (i == 0 || i == 1)
		{
			fout << "1Phase" << ",";

			if (i == 0)
			{
				cout << endl << "Enter Info for 1 Phase Domestic" << endl << endl;
			}
			else if (i == 1)
			{
				cout << endl << "Enter Info for 1 Phase Commercial" << endl << endl;
			}
		}
		else
		{
			fout << "3Phase" << ",";

			if (i == 2)
			{
				cout << endl << "Enter Info for 3 Phase Domestic" << endl << endl;
			}
			else if (i == 3)
			{
				cout << endl << "Enter Info for 3 Phase Commercial" << endl << endl;
			}
		}

		cout << "Enter Normal Units Price : ";
		cin.get(data, 10);
		cin.ignore();
		bool flag = 1;

		do {
			flag = 1;
			if (data[0] == '\0')
			{
				flag = 0;
			}
			for (int j = 0; data[j] != '\0' && flag; j++)
			{
				if (data[j] < 48 || data[j] > 57)
				{
					flag = 0;
				}
			}
			if (flag == 0)
			{
				cout << "Enter Normal Units Price : ";
				cin.get(data, 10);
				cin.ignore();
			}

		} while (flag == 0);


		fout << data << ",";

		if (i == 2 || i == 3)
		{
			cout << "Enter Peak Hour Units Price : ";					// Peak Hour
			cin.get(data, 10);
			cin.ignore();
			flag = 1;

			do {
				flag = 1;
				if (data[0] == '\0')
				{
					flag = 0;
				}
				for (int j = 0; data[j] != '\0' && flag; j++)
				{
					if (data[j] < 48 || data[j] > 57)
					{
						flag = 0;
					}
				}
				if (flag == 0)
				{
					cout << "Enter Peak Hour Units Price : ";
					cin.get(data, 10);
					cin.ignore();
				}

			} while (flag == 0);

			fout << data << ",";

		}
		else
		{
			fout << ",";
		}

		cout << "Enter Percentage of tax : ";					//  Percentage of tax
		cin.get(data, 10);
		cin.ignore();
		flag = 1;

		do {
			flag = 1;
			if (data[0] == '\0')
			{
				flag = 0;
			}
			for (int j = 0; data[j] != '\0' && flag; j++)
			{
				if (data[j] < 48 || data[j] > 57)
				{
					flag = 0;
				}
			}
			if (flag == 0)
			{
				cout << "Enter Percentage of tax : ";
				cin.get(data, 10);
				cin.ignore();
			}

		} while (flag == 0);

		fout << data << ",";



		cout << "Enter Fixed Charges : ";					//  Fixed Charges
		cin.get(data, 10);
		cin.ignore();
		flag = 1;

		do {
			flag = 1;
			if (data[0] == '\0')
			{
				flag = 0;
			}
			for (int j = 0; data[j] != '\0' && flag; j++)
			{
				if (data[j] < 48 || data[j] > 57)
				{
					flag = 0;
				}
			}
			if (flag == 0)
			{
				cout << "Enter Fixed Charges : ";
				cin.get(data, 10);
				cin.ignore();
			}

		} while (flag == 0);

		fout << data << "^" << endl;

	}

	fout.close();
}

void EditTarrifTaxFile()
{
	fstream file1;
	fstream file2;
	int phaseType = 0;
	int choiceSelect = 0;
	int ConnectionType = 0;
	bool flag = 1;
	int calculatedRow = 0;
	char ch = 'a';
	int countText = 0;

	file1.open("TariffTaxInfo.txt", ios::in);
	file2.open("TariffTemp.txt", ios::out);

	do {

		cout << endl << endl;
		cout << "Enter Phase type you want to edit : ";

		cin >> phaseType;

	} while (phaseType != 1 && phaseType != 3);

	do {

		cout << endl << endl;
		cout << "1. Domestic Customer" << endl;
		cout << "2. Commercial Customer" << endl;

		cout << endl << "Enter a choice from above : ";
		cin >> ConnectionType;

	} while (ConnectionType < 1 || ConnectionType > 2);

	if (phaseType == 1 && ConnectionType == 1)
	{
		calculatedRow = 1;
	}
	else if (phaseType == 1 && ConnectionType == 2)
	{
		calculatedRow = 2;
	}
	else if (phaseType == 3 && ConnectionType == 1)
	{
		calculatedRow = 3;
	}
	else if (phaseType == 3 && ConnectionType == 2)
	{
		calculatedRow = 4;
	}

	do {

		cout << endl << endl;
		cout << "1. Normal Units" << endl;
		cout << "2. Peak Hour Units" << endl;
		cout << "3. Tax Percentage" << endl;
		cout << "4. Fixed Charges" << endl;

		cout << endl << "Enter a choice from above : ";
		cin >> choiceSelect;

		if (phaseType == 1)
		{
			if (choiceSelect == 2)
			{
				cout << endl << endl << "1 phase Meter do not have Peak Hour Units" << endl;

				choiceSelect = -1;
			}
		}


	} while (choiceSelect < 1 || choiceSelect > 4);

	char data[10];


	cout << endl << "Enter changed Value : ";
	cin.get();
	cin.get(data, 10);
	cin.ignore();

	flag = 1;

	do {
		if (data[0] == '\0')
		{
			flag = 0;
		}

		for (int i = 0; data[i] != '\0' && flag; i++)
		{
			if (data[i] < 48 || data[i] > 57)
			{
				flag = 0;
			}
		}

		if (!flag)
		{
			cout << endl << "Enter changed Value : ";
			cin.get(data, 10);
			cin.ignore();
		}

	} while (flag == 0);

	char readingData[2000];
	ch = 'a';
	int commaCount = 0;
	int rowCount = 0;
	countText = 0;
	bool flagShit = 1;

	while (!file1.eof())
	{
		file1 >> ch;

		readingData[countText++] = ch;

	}

	readingData[countText] = '\0';

	for (int i = 0; readingData[i] != '\0'; i++)
	{
		if (rowCount != 4)
		{
			if (rowCount == calculatedRow - 1)
			{
				if (commaCount == choiceSelect)
				{
					if (flagShit)
					{
						file2 << data;
						flagShit = 0;
						commaCount++;
					}

				}
				else
				{
					if (flagShit == 0)
					{
						if (readingData[i] == ',' || readingData[i] == '^')
						{
							flagShit = 1;
							file2 << readingData[i];
						}
					}
					else
					{
						file2 << readingData[i];
					}
				}
			}
			else
			{
				file2 << readingData[i];
			}

			if (readingData[i] == '^')
			{

				rowCount++;
				commaCount = 0;

				file2 << endl;
			}

			if (readingData[i] == ',')
			{

				commaCount++;
			}
		}


	}

	file1.close();
	file2.close();

	file1.open("TariffTemp.txt", ios::in);
	file2.open("TariffTaxInfo.txt", ios::out);


	while (!file1.eof())
	{
		file1 >> ch;

		file2 << ch;

		if (ch == '^')
		{
			file2 << endl;
		}
	}

}

bool LeapCheck(int year)
{
	// leap year if perfectly divisible by 400
	if (year % 400 == 0) {
		return 1;
	}
	// not a leap year if divisible by 100
	// but not divisible by 400
	else if (year % 100 == 0) {
		return 0;
	}
	// leap year if not divisible by 100
	// but divisible by 4
	else if (year % 4 == 0) {
		return 1;
	}
	// all other years are not leap years
	else {
		return 0;
	}
}

void addCustomerInfoFile()
{
	fstream fout;

	fout.open("CustomersInfo.txt", ios::in);

	char dummy = 'a';
	int count = 0;
	char customerType = 0;

	while (!fout.eof())
	{
		fout >> dummy;

		if (dummy == '^')
		{
			count++;
		}
	}

	//count = count--;

	if (count == 0)
	{
		count = 1;
	}

	fout.close();


	fout.open("CustomersInfo.txt", ios::app);

	char id[5];

	for (int i = 0; i < 4; i++)
	{
		id[i] = '0';
	}

	id[4] = '\0';

	int countDigit = 0;
	int temp = count;

	while (temp > 0)
	{
		temp = temp / 10;
		countDigit++;
	}

	for (int i = 0; i < countDigit; i++)
	{
		id[3 - i] = (count % 10) + 48;
		count = (count / 10);
	}

	cout << endl << "Enter Information of Customer ID " << id << endl << endl;


	// CNIC Input

	char CNIC[20]; // no dashes

	for (int i = 0; i < 13; i++)
	{
		CNIC[i] = 'a';
	}

	CNIC[13] = '\0';

	cout << "Enter CNIC : ";
	cin.get(CNIC, 20);
	cin.ignore();

	CNIC[13] = '\0';

	bool flag = 1;

	do
	{
		flag = 1;

		for (int i = 0; i < 13 && flag; i++)
		{
			if (CNIC[i] < 48 || CNIC[i] > 57)
			{
				flag = 0;
			}
			else if (CNIC[i] == '-')
			{
				flag = 0;
			}
		}

		if (flag == 0)
		{
			for (int i = 0; i < 20; i++)
			{
				CNIC[i] = 'a';
			}

			cout << "Enter CNIC : ";
			cin.get(CNIC, 20);
			cin.ignore();

			if (CNIC[13] >= 48 && CNIC[13] <= 57)
			{
				flag = 0;
			}

			CNIC[13] = '\0';
		}

	} while (flag == 0);

	fstream checkCNIC;
	char checkCNICFromFile[300];
	bool checkCNICflag = 1;
	flag = 1;
	char chh = 'a';
	bool flagStopLine = 1;
	int countCNIC = 0;
	int checkCNICflagCount = 0;

	checkCNIC.open("CustomersInfo.txt", ios::in);

	while (!checkCNIC.eof())
	{
		checkCNICflagCount = 0;
		flagStopLine = 1;

		for (int i = 0; flagStopLine && !checkCNIC.eof(); i++)
		{
			checkCNIC >> chh;

			checkCNICFromFile[i] = chh;

			if (chh == '^')
			{
				flagStopLine = 0;
			}
		}


		if (checkCNICFromFile[0] != '^' && !checkCNIC.eof())
		{
			checkCNICflag = 1;

			for (int i = 5; i < 18 && checkCNICflagCount == 0; i++)
			{
				if (checkCNICFromFile[i] != CNIC[i - 5])
				{
					checkCNICflagCount++;
				}
			}

			if (checkCNICflagCount == 0)
			{
				countCNIC++;
			}
		}
	}

	checkCNIC.close();

	// CNIC Input end

	if (countCNIC < 3)
	{

		// Name Input

		char name[50]; // no numbers

		cout << "Enter Name : ";
		cin.get(name, 50);
		cin.ignore();

		// Name input end

		// Address Input

		char address[100];	// no comma in address // if(address[i] == ',') { cout << "no comma to be used" })

		cout << "Enter Address : ";
		cin.get(address, 100);
		cin.ignore();

		//flag = 1;

		for (int i = 0; address[i] != '\0'; i++)
		{
			if (address[i] == ',')
			{
				address[i] = '%';
			}
		}


		// Adreess input end

		// number Input

		char number[15]; // no alphabets letter

		cout << "Enter Contact Number : ";
		cin.get(number, 15);
		cin.ignore();

		flag = 1;

		do {
			flag = 1;

			for (int i = 0; number[i] != '\0' && flag; i++)
			{
				if (i == 0)
				{
					if (number[i] < 48 || number[i] > 57)
					{
						flag = 0;
					}

					if (number[i] == '+')
					{
						flag = 1;
					}
				}
				else
				{
					if (number[i] < 48 || number[i] > 57)
					{
						flag = 0;
					}
				}
			}

			if (flag == 0)
			{
				cout << "Enter Contact Number : ";
				cin.get(number, 15);
				cin.ignore();
			}

		} while (flag == 0);

		//number input end

		// meter input

		char metertype = 1; // 3 // check if 1 or 3

		cout << "Enter Meter Type : ";
		cin >> metertype;

		flag = 1;

		do {

			flag = 1;

			if (metertype != (48 + 3) && metertype != (48 + 1))
			{
				flag = 0;
			}

			if (flag == 0)
			{
				cout << "Enter Meter Type : ";
				cin >> metertype;
			}

		} while (flag == 0);

		// metertype input end

		//  Connection date input

		char connectionDate[11];

		connectionDate[2] = connectionDate[5] = '/';
		connectionDate[10] = '\0';

		int num = 0;

		cout << "Enter Year of Connection : ";
		cin >> num;
		temp = num;
		countDigit = 0;

		while (temp > 0)
		{
			temp = temp / 10;
			countDigit++;
		}

		if (countDigit != 4)
		{
			do {

				cout << "Enter Year of Connection : ";
				cin >> num;
				temp = num;
				countDigit = 0;

				while (temp > 0)
				{
					temp /= 10;
					countDigit++;
				}

			} while (countDigit != 4);
		}


		bool leapYear = 1;

		if (!LeapCheck(num))
		{
			leapYear = 0;
		}

		for (int i = 0; i < 4; i++)
		{
			connectionDate[9 - i] = (num % 10) + 48;
			num /= 10;
		}

		// year done

		num = 0;

		cout << "Enter Month of Connection : ";
		cin >> num;

		flag = 1;

		do {
			flag = 1;

			if (num < 1 || num > 12)
			{
				flag = 0;
			}

			if (flag == 0)
			{
				cout << "Enter Month of Connection : ";
				cin >> num;
			}
		} while (flag == 0);

		int laterCheck = num;
		temp = num;

		if (num < 10)
		{
			connectionDate[3] = '0';
			connectionDate[4] = (num + 48);
		}
		else
		{
			connectionDate[4] = (num % 10) + 48;
			num /= 10;
			connectionDate[3] = num + 48;
		}

		// month done

		num = 0;

		cout << "Enter Date of Connection : ";
		cin >> num;

		flag = 1;

		if (leapYear && laterCheck == 2)
		{
			do {
				flag = 1;

				if (num < 1 || num > 29)
				{
					flag = 0;
					cout << "Enter Date of Connection : ";
					cin >> num;
				}
			} while (flag == 0);
		}
		else if (!leapYear && laterCheck == 2)
		{
			do {
				flag = 1;

				if (num < 1 || num > 28)
				{
					flag = 0;
					cout << "Enter Date of Connection : ";
					cin >> num;
				}
			} while (flag == 0);
		}
		else if (laterCheck == 4 || laterCheck == 6 || laterCheck == 9 || laterCheck == 11)
		{
			do {
				flag = 1;

				if (num < 1 || num > 30)
				{
					flag = 0;
					cout << "Enter Date of Connection : ";
					cin >> num;
				}
			} while (flag == 0);
		}
		else
		{
			do
			{
				flag = 1;

				if (num < 0 || num > 31)
				{
					flag = 0;
					cout << "Enter Date of Connection : ";
					cin >> num;
				}

			} while (flag == 0);
		}

		if (num < 10)
		{
			connectionDate[0] = '0';
			connectionDate[1] = (num + 48);
		}
		else
		{
			connectionDate[1] = (num % 10) + 48;
			num /= 10;
			connectionDate[0] = (num + 48);
		}

		// date done

		// date month year done with exception handling

		//// normal units consumed INPUT

		//char normalUnits[10];

		//num = 0;

		//cout << "Enter Regular Units Consumed : ";
		//cin >> num;

		//flag = 1;

		//if (num < 0)
		//{
		//	do
		//	{
		//		flag = 1;

		//		if (num < 0)
		//		{
		//			cout << "Enter Regular Units Consumed : ";
		//			cin >> num;

		//			flag = 0;
		//		}
		//	} while (flag == 0);
		//}

		//temp = num;
		//countDigit = 0;

		//while (temp > 0)
		//{
		//	temp /= 10;
		//	countDigit++;
		//}

		//for (int i = 0; i < countDigit; i++)
		//{
		//	normalUnits[countDigit - i - 1] = (num % 10) + 48;
		//	num = num / 10;
		//}
		//normalUnits[countDigit] = '\0';


		//// normal units consumed INPUT done

		//// Peak Hour Units Consumed INPUT

		//char peakUnits[10];


		//if (metertype - 48 == 3)
		//{
		//	num = 0;

		//	cout << "Enter Peak Hour Units Consumed : ";
		//	cin >> num;

		//	flag = 1;

		//	if (num < 0)
		//	{
		//		do
		//		{
		//			flag = 1;

		//			if (num < 0)
		//			{
		//				cout << "Enter Peak Hour Units Consumed : ";
		//				cin >> num;

		//				flag = 0;
		//			}
		//		} while (flag == 0);
		//	}

		//	temp = num;
		//	countDigit = 0;

		//	while (temp > 0)
		//	{
		//		temp /= 10;
		//		countDigit++;
		//	}

		//	for (int i = 0; i < countDigit; i++)
		//	{
		//		peakUnits[countDigit - i - 1] = (num % 10) + 48;
		//		num = num / 10;
		//	}
		//	peakUnits[countDigit] = '\0';
		//}
		//else
		//{
		//	peakUnits[0] = '0';
		//	peakUnits[1] = '\0';
		//}

		cout << endl << "The Regular Units and Peak Units have been set to 0 for new meters" << endl << endl;

		// customer type

		do {
			cout << "Press 1 for Domestic Customer" << endl;
			cout << "Press 2 for Commercial Customer" << endl;
			cout << "Enter from above : ";
			customerType = _getch();
			cout << customerType - 48;
		} while (customerType < 49 || customerType > 50);




		fout << id << "," << CNIC << "," << name << "," << address << "," << number << "," << metertype << "," << connectionDate << "," << "0" << "," << "0" << "," << customerType << '^' << endl;

		fout.close();

		//UserName,Password^
	}
	else
	{
		cout << endl << endl << "Exiting here. Given CNIC has been used 3 times!!!" << endl << endl;
	}


}

void addBillingInfo()
{
	fstream getCustomerID;
	fstream readTaxFile;
	fstream fout;

	fout.open("BillingInfo.txt", ios::app);
	getCustomerID.open("CustomersInfo.txt", ios::in);

	char CustomerID[5];
	char ch = 'a';
	int countTextID = 0;
	int countRow = 0;
	bool flag = 1;
	int countRows = 0;
	int billingMonth = 0;
	int countBillingMonthR = 0;
	int temp = 0;
	int countDigit = 0;
	char ReadingDate[11];
	bool flagReadingDate = 1;
	int commaCount = 0;
	int meterType = 0;
	int regularUnits = 0;
	int peakUnits = 0;
	int CustomerType = 1;
	int costOfElectricity = 0;
	int salesTax = 0;
	int FixedAmount = 0;
	int priceRUnits = 0;
	int pricePUnits = 0;
	int percentageTax = 0;
	int FixedCharges = 0;
	char TaxFile[40];
	int totalAmountE = 0;
	int billPaidStatus = 0;
	char dueDate[11];
	char billPaidDate[11];
	int regularUnitsLast = 0;
	int peakUnitsLast = 0;
	int UnitsRegularE = 0;
	int UnitsPeakE = 0;

	// here we get the billing month

	fstream getBillingMonth;
	getBillingMonth.open("BillingInfo.txt", ios::in);

	getBillingMonth >> ch;

	if (ch == 'a')
	{
		billingMonth = 1;
	}

	getBillingMonth.close();

	if (billingMonth == 0)
	{
		getBillingMonth.open("BillingInfo.txt", ios::in);

		while (!getBillingMonth.eof())
		{
			getBillingMonth >> ch;

			countBillingMonthR++;

			if (countBillingMonthR == 6)
			{
				billingMonth = ch - 48;

				getBillingMonth >> ch;

				countBillingMonthR++;

				if (ch >= 48 && ch <= 57)
				{
					billingMonth = billingMonth * 10;
					billingMonth = billingMonth + (ch - 48);
				}
			}

			if (ch == '^')
			{
				countBillingMonthR = 0;
			}
		}

		billingMonth++;

		getBillingMonth.close();
	}

	if (billingMonth == 13)
	{
		billingMonth = 1;
	}

	switch (billingMonth)
	{
	case 1:
	{
		cout << endl << "\t\t\t\tBilling Info of January" << endl << endl;
	}
	break;
	case 2:
	{
		cout << endl << "\t\t\t\tBilling Info of February" << endl << endl;
	}
	break;
	case 3:
	{
		cout << endl << "\t\t\t\tBilling Info of March" << endl << endl;
	}
	break;
	case 4:
	{
		cout << endl << "\t\t\t\tBilling Info of April" << endl << endl;
	}
	break;
	case 5:
	{
		cout << endl << "\t\t\t\tBilling Info of May" << endl << endl;
	}
	break;
	case 6:
	{
		cout << endl << "\t\t\t\tBilling Info of June" << endl << endl;
	}
	break;
	case 7:
	{
		cout << endl << "\t\t\t\tBilling Info of July" << endl << endl;
	}
	break;
	case 8:
	{
		cout << endl << "\t\t\t\tBilling Info of August" << endl << endl;
	}
	break;
	case 9:
	{
		cout << endl << "\t\t\t\tBilling Info of September" << endl << endl;
	}
	break;
	case 10:
	{
		cout << endl << "\t\t\t\tBilling Info of Octuber" << endl << endl;
	}
	break;
	case 11:
	{
		cout << endl << "\t\t\t\tBilling Info of Novermber" << endl << endl;
	}
	break;
	case 12:
	{
		cout << endl << "\t\t\t\tBilling Info of December" << endl << endl;
	}
	break;
	}

	// billing month done

	while (!getCustomerID.eof())
	{
		getCustomerID >> ch;

		if (commaCount == 5 && ch != ',')
		{
			meterType = ch - 48;
		}


		// to get last reading of customer


		if (commaCount == 7 && ch != ',')
		{
			regularUnitsLast = ch - 48;

			getCustomerID >> ch;

			while (ch != ',')
			{
				regularUnitsLast = regularUnitsLast * 10;
				regularUnitsLast = regularUnitsLast + (ch - 48);

				getCustomerID >> ch;

			}
		}

		// for only 3 phase meter type

		if (meterType == 3 && commaCount == 8 && ch != ',' && ch != '^')
		{
			peakUnitsLast = ch - 48;

			getCustomerID >> ch;

			while (ch != ',' && ch != '^')
			{
				peakUnitsLast = peakUnitsLast * 10;
				peakUnitsLast = peakUnitsLast + (ch - 48);

				getCustomerID >> ch;

			}
		}

		// end of units taking

		// CustomerType Input from CustomerInfo file

		if (commaCount == 9 && ch != ',' && ch != '^')
		{
			CustomerType = ch - 48;
		}

		// end

		if (ch == ',')
		{

			commaCount++;
		}

		if (!getCustomerID.eof())
		{
			if (ch == ',' && flag)
			{
				CustomerID[countTextID] = '\0';
				countRow++;
				flagReadingDate = 0;
				flag = 0;

			}
			else
			{
				if (flag)
				{
					CustomerID[countTextID++] = ch;
				}
			}


			if (ch == '^')
			{

				// nullifying the peak units if meter type is 1 phase


				if (meterType == 1)
				{
					peakUnitsLast = 0;
				}

				// done with above ( was not required but phr bhi kr dya xddddd )

				countTextID = 0;
				flag = 1;
				countRows;
				flagReadingDate = 1;
				commaCount = 0;


				cout << endl << "Enter Billing Info of " << CustomerID << endl << endl;



				// we have successfully got the customerID here

				// now rest of the codes here

				ReadingDate[2] = ReadingDate[5] = '/';
				ReadingDate[10] = '\0';

				int num = 0;

				cout << "Enter Year of Reading : ";
				cin >> num;
				temp = num;
				countDigit = 0;

				while (temp > 0)
				{
					temp = temp / 10;
					countDigit++;
				}

				if (countDigit != 4)
				{
					do {

						cout << "Enter Year of Reading : ";
						cin >> num;
						temp = num;
						countDigit = 0;

						while (temp > 0)
						{
							temp /= 10;
							countDigit++;
						}

					} while (countDigit != 4);
				}


				bool leapYear = 1;

				if (!LeapCheck(num))
				{
					leapYear = 0;
				}

				for (int i = 0; i < 4; i++)
				{
					ReadingDate[9 - i] = (num % 10) + 48;
					num /= 10;
				}

				// year done

				num = 0;

				//cout << "Enter Month of Reading : ";
				//cin >> num;

				//flagReadingDate = 1;

				//do {
				//	flagReadingDate = 1;

				//	if (num < 1 || num > 12)
				//	{
				//		flagReadingDate = 0;
				//	}

				//	if (flagReadingDate == 0)
				//	{
				//		cout << "Enter Month of Reading : ";
				//		cin >> num;
				//	}
				//} while (flagReadingDate == 0);

				cout << "Billing Month : " << billingMonth << endl;

				int laterCheck = billingMonth;
				temp = billingMonth;

				if (num < 10)
				{
					ReadingDate[3] = '0';
					ReadingDate[4] = (temp + 48);
				}
				else
				{
					ReadingDate[4] = (temp % 10) + 48;
					temp /= 10;
					ReadingDate[3] = temp + 48;
				}

				// month done

				num = 0;

				cout << "\nReading Date can not Exceed 20 of the month" << endl << endl;
				cout << "Enter Date of Reading : ";

				cin >> num;

				flagReadingDate = 1;

				if (leapYear && laterCheck == 2)
				{
					do {
						flagReadingDate = 1;

						if (num < 1 || num > 20)
						{
							flagReadingDate = 0;
							cout << "Enter Date of Reading : ";
							cin >> num;
						}
					} while (flagReadingDate == 0);
				}
				else if (!leapYear && laterCheck == 2)
				{
					do {
						flagReadingDate = 1;

						if (num < 1 || num > 20)
						{
							flagReadingDate = 0;
							cout << "Enter Date of Reading : ";
							cin >> num;
						}
					} while (flagReadingDate == 0);
				}
				else if (laterCheck == 4 || laterCheck == 6 || laterCheck == 9 || laterCheck == 11)
				{
					do {
						flagReadingDate = 1;

						if (num < 1 || num > 20)
						{
							flagReadingDate = 0;
							cout << "Enter Date of Reading : ";
							cin >> num;
						}
					} while (flagReadingDate == 0);
				}
				else
				{
					do
					{
						flagReadingDate = 1;

						if (num < 1 || num > 20)
						{
							flagReadingDate = 0;
							cout << "Enter Date of Reading : ";
							cin >> num;
						}

					} while (flagReadingDate == 0);
				}

				int ReadingDateForDue = num;

				if (num < 10)
				{
					ReadingDate[0] = '0';
					ReadingDate[1] = (num + 48);
				}
				else
				{
					ReadingDate[1] = (num % 10) + 48;
					num /= 10;
					ReadingDate[0] = (num + 48);
				}

				// date done

				// date month year done with exception handling

				/* **************************************************************************** */

				// Units Regular input

				do {

					cout << "Enter Regular Units Consumed : ";
					cin >> regularUnits;
				} while (regularUnits < 0 || regularUnits <= regularUnitsLast);

				UnitsRegularE = regularUnits - regularUnitsLast;

				// Regular Unit input end

				/* **************************************************************************** */

				// Units Peak Input

				if (meterType == 3)
				{
					do {
						cout << "Enter Peak Units Consumed : ";
						cin >> peakUnits;
					} while (peakUnits < 0 || peakUnits <= peakUnitsLast);

					UnitsPeakE = peakUnits - peakUnitsLast;
				}

				// Peak Unit input end

				/* **************************************************************************** */

				// read data from TarrifTaxInfo file

				readTaxFile.open("TariffTaxInfo.txt", ios::in);

				int rowcountTax = 0;
				int rowToCheck = 0;

				if (meterType == 1 && CustomerType == 1)
				{
					rowToCheck = 1;
				}
				else if (meterType == 1 && CustomerType == 2)
				{
					rowToCheck = 2;
				}
				else if (meterType == 3 && CustomerType == 1)
				{
					rowToCheck = 3;
				}
				else if (meterType == 3 && CustomerType == 2)
				{
					rowToCheck = 4;
				}

				countRow = 0;
				commaCount = 0;


				while (!readTaxFile.eof())
				{
					readTaxFile >> ch;

					TaxFile[countRow++] = ch;

					if (ch == '^')
					{
						rowcountTax++;
						TaxFile[countRow] = '\0';
						countRow = 0;

						if (rowToCheck == rowcountTax)
						{
							for (int i = 0; TaxFile[i] != '^'; i++)
							{
								if (TaxFile[i] == ',')
								{
									commaCount++;
								}

								if (commaCount == 1 && TaxFile[i] != ',' && TaxFile[i] != '^')
								{
									if (TaxFile[i - 1] != ',')
									{
										priceRUnits = priceRUnits * 10;
										priceRUnits = priceRUnits + (TaxFile[i] - 48);
									}
									else if (TaxFile[i - 1] == ',')
									{
										priceRUnits = TaxFile[i] - 48;
									}
								}

								if (commaCount == 2 && meterType == 3 && TaxFile[i] != ',' && TaxFile[i] != '^')
								{

									if (TaxFile[i - 1] != ',')
									{
										pricePUnits = pricePUnits * 10;
										pricePUnits = pricePUnits + (TaxFile[i] - 48);
									}
									else if (TaxFile[i - 1] == ',')
									{
										pricePUnits = TaxFile[i] - 48;
									}
								}

								if (commaCount == 3 && TaxFile[i] != ',' && TaxFile[i] != '^')
								{

									if (TaxFile[i - 1] != ',')
									{
										percentageTax = percentageTax * 10;
										percentageTax = percentageTax + (TaxFile[i] - 48);
									}
									else if (TaxFile[i - 1] == ',')
									{
										percentageTax = TaxFile[i] - 48;
									}
								}

								if (commaCount == 4 && TaxFile[i] != ',' && TaxFile[i] != '^')
								{

									if (TaxFile[i - 1] != ',')
									{
										FixedCharges = FixedCharges * 10;
										FixedCharges = FixedCharges + (TaxFile[i] - 48);
									}
									else if (TaxFile[i - 1] == ',')
									{
										FixedCharges = TaxFile[i] - 48;
									}
								}
							}
						}

					}


				}

				readTaxFile.close();

				//cout << priceRUnits << " " << pricePUnits << "  " << percentageTax << "  " << FixedCharges << endl;


				// reading end

				// Cost of Electricity

				if (meterType == 1)
				{
					costOfElectricity = (priceRUnits * UnitsRegularE);
					salesTax = ((percentageTax * costOfElectricity) / 100);
					FixedAmount = FixedCharges;
				}
				else if (meterType == 3)
				{
					costOfElectricity = (priceRUnits * UnitsRegularE) + (pricePUnits * UnitsPeakE);
					salesTax = ((percentageTax * costOfElectricity) / 100);
					FixedAmount = FixedCharges;
				}

				totalAmountE = costOfElectricity + salesTax + FixedAmount;

				//cost of electricity done

				// Bill paid Status

				do {

					cout << "\nEnter 1 for paid" << endl;
					cout << "Enter 2 for Un-Paid" << endl;

					cout << "Enter Bill Payment Status : ";
					cin >> billPaidStatus;
				} while (billPaidStatus != 1 && billPaidStatus != 2);



				//Bill paid Status done

				//Due Date copy from reading date

				ReadingDateForDue += 7;

				for (int i = 2; i < 11; i++)
				{
					dueDate[i] = ReadingDate[i];
				}

				if (ReadingDateForDue < 10)
				{
					dueDate[0] = '0';
					dueDate[1] = (ReadingDateForDue + 48);
				}
				else
				{
					dueDate[1] = (ReadingDateForDue % 10) + 48;
					ReadingDateForDue /= 10;
					dueDate[0] = (ReadingDateForDue + 48);
				}



				//due date done


				// bill payment date

				if (billPaidStatus == 1)
				{
					num = 0;

					cout << "Enter Year of Payment : ";
					cin >> num;
					temp = num;
					countDigit = 0;

					while (temp > 0)
					{
						temp = temp / 10;
						countDigit++;
					}

					if (countDigit != 4)
					{
						do {

							cout << "Enter Year of Payment : ";
							cin >> num;
							temp = num;
							countDigit = 0;

							while (temp > 0)
							{
								temp /= 10;
								countDigit++;
							}

						} while (countDigit != 4);
					}



					bool leapYear = 1;

					if (!LeapCheck(num))
					{
						leapYear = 0;
					}

					for (int i = 0; i < 4; i++)
					{
						billPaidDate[9 - i] = (num % 10) + 48;
						num /= 10;
					}

					// year done

					num = 0;

					cout << "Enter Month of Payment : ";
					cin >> num;

					flag = 1;

					do {
						flag = 1;

						if (num < 1 || num > 12)
						{
							flag = 0;
						}

						if (flag == 0)
						{
							cout << "Enter Month of Payment : ";
							cin >> num;
						}
					} while (flag == 0);

					int laterCheck = num;
					temp = num;

					if (num < 10)
					{
						billPaidDate[3] = '0';
						billPaidDate[4] = (num + 48);
					}
					else
					{
						billPaidDate[4] = (num % 10) + 48;
						num /= 10;
						billPaidDate[3] = num + 48;
					}

					// month done

					num = 0;

					cout << "Enter Date of Payment : ";
					cin >> num;

					flag = 1;

					if (leapYear && laterCheck == 2)
					{
						do {
							flag = 1;

							if (num < 1 || num > 29)
							{
								flag = 0;
								cout << "Enter Date of Payment : ";
								cin >> num;
							}
						} while (flag == 0);
					}
					else if (!leapYear && laterCheck == 2)
					{
						do {
							flag = 1;

							if (num < 1 || num > 28)
							{
								flag = 0;
								cout << "Enter Date of Payment : ";
								cin >> num;
							}
						} while (flag == 0);
					}
					else if (laterCheck == 4 || laterCheck == 6 || laterCheck == 9 || laterCheck == 11)
					{
						do {
							flag = 1;

							if (num < 1 || num > 30)
							{
								flag = 0;
								cout << "Enter Date of Payment : ";
								cin >> num;
							}
						} while (flag == 0);
					}
					else
					{
						do
						{
							flag = 1;

							if (num < 0 || num > 31)
							{
								flag = 0;
								cout << "Enter Date of Payment : ";
								cin >> num;
							}

						} while (flag == 0);
					}

					if (num < 10)
					{
						billPaidDate[0] = '0';
						billPaidDate[1] = (num + 48);
					}
					else
					{
						billPaidDate[1] = (num % 10) + 48;
						num /= 10;
						billPaidDate[0] = (num + 48);
					}

					billPaidDate[2] = billPaidDate[5] = '/';

					billPaidDate[10] = '\0';

					// date done

					// date month year done with exception handling

				}
				else if (billPaidStatus == 2)
				{
					billPaidDate[2] = billPaidDate[5] = '/';
					billPaidDate[1] = billPaidDate[0] = billPaidDate[3] = billPaidDate[4] = billPaidDate[6] = billPaidDate[7] = billPaidDate[8] = billPaidDate[9] = '-';
					billPaidDate[10] = '\0';
				}



				//


				// testing cout **** delete later


				fout << CustomerID << "," << billingMonth << "," << UnitsRegularE << "," << UnitsPeakE << "," << ReadingDate << "," << costOfElectricity << ",";
				fout << salesTax << "," << FixedAmount << "," << totalAmountE << "," << dueDate << "," << billPaidStatus << "," << billPaidDate << "^" << endl;

				//Important to put them  equal to zero 
				// Note : very Important

				commaCount = 0;
				costOfElectricity = 0;
				priceRUnits = 0;
				pricePUnits = 0;
				percentageTax = 0;
				FixedCharges = 0;
				regularUnits = 0;
				peakUnits = 0;
				salesTax = 0;
				FixedAmount = 0;
				totalAmountE = 0;
				peakUnitsLast = 0;
				regularUnitsLast = 0;
				UnitsPeakE = 0;
				UnitsRegularE = 0;



			}


		}

	}
}