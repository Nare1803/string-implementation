#include<iostream>
#include<cstdlib>
#include<cstring>

class Mystring {
private:
	char* data;
	int length;
public:
	Mystring() :
	       	data{nullptr},
		length{} {}
	//ctor with parameters
	Mystring(const char* newdata) {
		length = std::strlen(newdata);
                data = new char[length + 1];
		std::strcpy(data,newdata);

	} 
	//dtor
	~Mystring () {
	  delete[] data;
	}
	//copy ctor
	Mystring (const Mystring & ob ) {
	    length = ob.length;
	    data = new char[ob.length + 1];
            std::strcpy(data,ob.data);
	}
	// Assignment operator
      Mystring& operator=(const Mystring& rhv) {
        if (this != &rhv) {// run from self-assignment 
            delete[] data;//delete old stringy
            length = rhv.length;
            data = new char[rhv.length + 1];//allocate new space 
            std::strcpy(data, rhv.data);//copy new string,that is pointed by data
        }
        return *this;
    }
      //mive assignment
       Mystring& operator=(Mystring&& rhv) noexcept {
        if (this != &rhv) {
            // Release current resources
            delete[] data;

            // Transfer ownership from the source object
            data = rhv.data;
            length = rhv.length;

            // Reset the source object
            rhv.data = nullptr;
            rhv.length = 0;
        }
        return *this;
    }
     //move ctor
      Mystring(Mystring&& other) noexcept : data(other.data), length(other.length) {
        // Transfer ownership from the source object
        other.data = nullptr;
        other.length = 0;
    }

    // Concatenation operator
    Mystring operator+(const Mystring& rhs) const {

	    Mystring result;
	    //create temprory that i want to return for the result
	    
	    result.length = length + rhs.length;
	    //mer nor objecti lengthin veragrum enq thiisi length + erkrord operandi length

            result.data = new char[result.length + 1];
            //+1('/0')

            std::strcpy(result.data, data);
	    //copy old data to new result.data

            std::strcat(result.data, rhs.data);
               
	    return result; 
	   
    }
     Mystring operator+(const char* str) const {
        if (str) {//if str is the nullptr,we cannot dereference 
            int newlength = length + std::strlen(str);
            char* newdata = new char[newlength + 1];

            // Copy the existing data
            std::strcpy(newdata, data);

            // Concatenate the new data
            std::strcat(newdata, str);

            // Create a new string and return it
            Mystring result = newdata;
            return result;
        } else {
            
            return *this;
        }
    }
      Mystring& operator+=(const Mystring& rhs) {
        if (rhs.data) {//if its not nullptr
            int newlength = length + rhs.length;
            char* newdata = new char[newlength + 1];

            // Copy the existing content
            std::strcpy(newdata, data);

            // Concatenate the new content
            std::strcat(newdata, rhs.data);

            // Clean up old data
            delete[] data;

            // Update data and length
            data = newdata;
            length = newlength;
        }

        return *this;
    }

    // Concatenation Assignment operator (+=) with a C-style string
    Mystring& operator+=(const char* rhs) {
        if (rhs) {
            int newlength = length + std::strlen(rhs);
            char* newdata = new char[newlength + 1];

            // Copy the existing content
            std::strcpy(newdata, data);

            // Concatenate the new content
            std::strcat(newdata, rhs);

            // Clean up old data
            delete[] data;

            // Update data and length
            data = newdata;
            length = newlength;
        }

        return *this;
    }


     friend std::ostream& operator<<(std::ostream& , const Mystring&); //prototype of the friend function
     
     friend std::istream& operator>>(std::istream& , Mystring& );

     //overloaded cast operators
     explicit operator const char*() {//has not return type
   	
	     return data;
   
     };//can't define in global scope
  
     explicit operator int() { 
        //atoi?
     	     return std::atoi(data);
	     
     } 
 friend  bool operator== (const Mystring& , const Mystring&);
 friend  bool operator== (const char* , const Mystring&);


     int size ()const  { 
    
	     return length;
     }
      char* c_str() const {
         
	      return data;
	      
    }
    void display() const {
        
	    std::cout << data << std::endl;
    }

  // Append method
    Mystring append(const Mystring& str) {
        if (str.data) {
     
            int newlength = length + std::strlen(c_str());
            char* newData = new char[newlength + 1];

            // Copy the existing content
            std::strcpy(newData, data);

            // Concatenate the new content
            std::strcat(newData, c_str());

            // Clean up old data
            delete[] data;

            // Update data and length
            data = newData;
            length = newlength;
	}
        return *this;
    }
    
  Mystring& append(const char* str) {
       if (str) {
            int newlength = length + std::strlen(str);
            char* newData = new char[newlength + 1];

            // Copy the existing content
            std::strcpy(newData, data);

            // Concatenate the new content
            std::strcat(newData, str);

            // Clean up old data
             delete[] data;

            // Update data and length
            data = newData;
            length = newlength;
       }
       
        return *this;
    }
   // Get character at a specific position
    char& at(int pos) {
        if (pos < length) {
            return data[pos];
        } else {
            // Handle out-of-range access, you might throw an exception here
            // or provide some default behavior
            throw std::invalid_argument("Index out of range");
        }
    }

    // Access last character
    char& back() {
        if (length > 0) {
            return data[length - 1];
        } else {
            // Handle empty string, you might throw an exception here
            // or provide some default behavior
            throw std::invalid_argument("String is empty");//???????
        }
    }

    // Access first character
    char& front() {
        if (length > 0) {
            return data[0];
        } else {
            // Handle empty string, you might throw an exception here
            // or provide some default behavior
      throw std::invalid_argument("String is empty");//????????
        }
    }

    // Erase characters from the string
    void clear() {
        delete[] data;
        data = nullptr;
        length = 0;
    }

    // Test if the string is empty
    bool empty() const noexcept {
        return length == 0;
    }
  

};
 
std::ostream& operator<<(std::ostream& os, const Mystring& mystring) {
 
	os << '(' << mystring.data << ',' << ' ' << mystring.length << ')' ;
	return os;
}

/* std::istream& operator>>(std::istream& is, Mystring& mystring) {
 	is >> mystring ;// >> ' ' >> mystring.length;
	return is;
}*/
 std::istream& operator>>(std::istream& is, Mystring& mystring) { //?
        // Read input from the stream
        char buffer[1024]; // Assuming a maximum input length of 1024 characters
        is >> buffer;

        // Update the MyString object with the input
        mystring = Mystring (buffer);

        return is;
    }
 bool operator== (const Mystring& lhs, const Mystring& rhs) {

         return std::strcmp(lhs.data,rhs.data) == 0;

  }
bool operator== (const char* lhs, const Mystring& rhs) {

        return std::strcmp(lhs,rhs.data) == 0;
  }



int main() {
    // Test your string class here
   Mystring str1;  // Default constructor
   if (str1.c_str() != nullptr){


   	 std::cout << "str1: " << str1.c_str() << ", Size: " << str1.size() << std::endl;
   }

   const char* sample = "Hello";
    Mystring str2(sample);  // Constructor with parameters
    std::cout << "str2: " << str2.c_str() << ", Size: " << str2.size() << std::endl;

   Mystring str3 = str2;  // Copy constructor
   std::cout << "str3: " << str3.c_str() << ", Size: " << str3.size() << std::endl;

    Mystring str4 = std::move(str3);  // Move constructor
    std::cout << "str4: " << str4.c_str() << ", Size: " << str4.size() << std::endl;

    Mystring str5;
    str5 = str4;  // Copy assignment operator
    std::cout << "str5: " << str5.c_str() << ", Size: " << str5.size() << std::endl;

    Mystring str6;
    str6 = std::move(str5);  // Move assignment operator
    std::cout << "str6: " << str6.c_str() << ", Size: " << str6.size() << std::endl;

    str6.append(" World!");  // Append function
    std::cout << "str6 after append: " << str6.c_str() << ", Size: " << str6.size() << std::endl;

    std::cout << "Character at position 4: " << str6.at(4) << std::endl;
     
      
    Mystring stro1 = "hello ";
    const char* stro2 = "world";
    Mystring stro3 = "noric ";
    Mystring stro4 = "hello ";
   
    Mystring stro5 = stro3 + stro4;
    std::cout << "overloaded operator + with char* " << std:: endl;

    stro5.display();
    std::cout << stro5; //overloaded <<
    std::cout << std::endl;

    std::cout << " cin with overloaded >>" << std:: endl;
    Mystring wow;
    std::cin >> wow;//overloadeed >>
    
  
    std::cout << "Cast operators :" << std:: endl;
    Mystring caster("cast");
      
    std::cout << caster << std::endl;
     
    int intValue = static_cast<int>(wow);
    std::cout << "int cast :" << intValue << std::endl;
    Mystring op1 = "alo";
    Mystring op2 = "ala";
    if (op1 == op2) {
	    std::cout << "true" << std::endl;
    } else 
	    std::cout << "false " << std:: endl;
	
    op1 += op2; 
    std::cout << op1 << std:: endl;

    // Concatenate using the + operator
    Mystring resu= stro1 + stro2;
    std::cout << "overloaded operator +  " << std:: endl;

    // Display the result
    resu.display();  // Output: Hello, world

    std::cout << "Front character: " << str6.front() << std::endl;
    std::cout << "Back character: " << str6.back() << std::endl;

    str6.clear();
    if ( str6.c_str() != nullptr) {
   	 std::cout << "str6 after clear: " << str6.c_str() << ", Size: " << str6.size() << std::endl;
    }
    std::cout << "Is str6 empty? " << (str6.empty() ? "Yes" : "No") << std::endl;

    return 0;
}








