#include <iostream>
#include <string>
#include <math.h>
#include <fstream>

using namespace std;

int makeEqualLength(string &str1, string &str2)
{
    int len1 = str1.size();
    int len2 = str2.size();
    if (len1 < len2)
    {
        for (int i = 0 ; i < len2 - len1 ; i++)
            str1 = '0' + str1;
        return len2;
    }
    else if (len1 > len2)
    {
        for (int i = 0 ; i < len1 - len2 ; i++)
            str2 = '0' + str2;
    }
    return len1; // If len1 >= len2
}

// The main function that adds two bit sequences and returns the addition
string addStrings( string first, string second )
{
	string result;  // To store the sum bits
 
    // make the lengths same before adding
    int length = makeEqualLength(first, second);
    int carry = 0;  // Initialize carry
     
    // Add all digits one by one
    for (int i = length-1 ; i >= 0 ; i--)
    {
        int firstDigit = first.at(i) - '0';
        int secondDigit = second.at(i) - '0';
         
        int sum = firstDigit + secondDigit + carry;
        carry = sum/10;
        sum = sum%10;
                
		char csum = sum+'0';		
        result = csum + result;        
        
    }
     
    // if overflow, then add a leading 1
    if (carry)  result = '1' + result;
	
 
    return result;
}

// The main function that adds two bit sequences and returns the addition
string subtractStrings( string first, string second )
{
	string result;  // To store the sum of first and second
 
    // make the lengths same before adding
    int length = makeEqualLength(first, second);
    int carry = 0;  // Initialize carry
     
    // Add all digits one by one
    for (int i = length-1 ; i >= 0 ; i--)
    {
        int firstDigit = first.at(i) - '0';
        int secondDigit = second.at(i) - '0';

        if(carry){
        	firstDigit -= 1;
        	carry=0;
		}
		
        if(firstDigit<secondDigit){
        	carry=1;
        	firstDigit += 10;
		}
		
        int sum = firstDigit - secondDigit;
        
		char csum = sum+'0';		
        result = csum + result;        
        
    }
      
    return result;
}

string findProduct(string x, string y){
	
	//Make both the strings of equal length
    int n = makeEqualLength(x, y);
    
    if (n == 0) return "";
    if (n == 1){
		int a=x[0]-'0';
		int b=y[0]-'0';
		int c=a*b;
		string pro="";
		while(c>0){
			int singledigit = c%10;
			char single = singledigit+'0';
			pro = single + pro;
			c/=10;
		}
		return pro;
	}
    
    int fh = n/2;
    int sh = (n-fh);
    
    // Storing the first half, second half of the string x in xl and xr respectively
    string xl = x.substr(0, fh);
    string xr = x.substr(fh, sh);
 
    // Storing the first half, second half of the string y in yl and yr respectively
    string yl = y.substr(0, fh);
    string yr = y.substr(fh, sh);
    
	//adding strings xl and xr
	string xlr=addStrings(xl, xr);

	//adding strings yl and yr
	string ylr=addStrings(yl, yr);
	
	//product of xl and yl
	string P1 = findProduct(xl, yl);    

	//product of xr and yr
	string P2 = findProduct(xr, yr);

	//product of xlr and ylr
	string P3 = findProduct(xlr, ylr);
	
	//P1 + P2
	string P12 = addStrings(P1, P2);
	
	//P3-P1-P2
	string P321 = subtractStrings(P3, P12);
	
	//Adding P1*pow(10, 2*sh) + P2
	for(int i=0; i<2*sh; i++)
		P1 = P1 + '0';	
	string FP12 = addStrings(P1, P2);
	
	//Adding above result + (P3-P1-P2)*pow(10, sh)
	for(int i=0; i<sh; i++)
		P321 = P321 + '0';
	string result = addStrings(FP12, P321);

	return result;
}


int main(void){
	
	string p="3141592653589793238462643383279502884197169399375105820974944592";
	string q="2718281828459045235360287471352662497757247093699959574966967627";

	ofstream out("output.txt");
	string output=findProduct(p,q);
	cout<<output<<endl;
	out<<output;
	out.close();
	
//	cout<<findProduct(p,q)<<endl;
	
	return 0;	
}

