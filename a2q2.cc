// takes input from command line or from a list of file (concatenates them)
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>


using std::endl;
using std::setw;
using std::string;
using std::stringstream;
using std::cin;

// argv[-bt, file1,file2 ...]
bool ba = false;
bool bt = false;
bool nrn = false;
bool nrz = false;
// better to be ints
int w = 6;
string s = "\t";

void format_infile(std::istream * inf, int & count, bool ba, bool bt,
  bool nrn, bool nrz, int w, string s) {
    std::string str;
    // ba, bt, s, w, nrn
    std::cout << ba << bt << nrn << nrz << w << s << '\n';
    while (getline(*inf, str)) {
      if (ba) {
        if (nrn) {
          std::cout << setw(w) << count << s << str << std::endl;
        } else if (nrz) {
          std::cout << std::setfill ('0') << setw(w) << count;
          std::cout << s << str << std::endl;
        }
      } else {
        if (str != "") {
          if (nrn) {
            std::cout << setw(w) << count << s << str << std::endl;
          } else if (nrz) {
            std::cout << std::setfill ('0') << setw(w) << count;
            std::cout << s << str << std::endl;
          }
        }
      }
      count++;
    }
  }



bool member(string item, int length, string arr[]){
  for (int i=0; i<length; i++) {
    if (arr[i] == item) return true;
  }
  return false;
}

bool is_digit_greater_than_1(char a) {
  if (a == '2' || a == '3' || a == '4' || a == '5' || a == '6' ||
  a == '7' || a == '8' || a == '9') {
    return true;
  }
  return false;
}

int char_to_int(char a){
  return a - '0';
}

///////////////////////////
// MAIN
///////////////////////////

int main(int argc, char const *argv[]) {

  // error checking
  // default
  bool ba = false;
  bool bt = false;
  bool nrn = false;
  bool nrz = false;
  // better to be ints
  int w = 6;
  string s = "\t";

  string bb_message = "ERROR: -ba and -bt negate each other";
  string nn_message = "ERROR: -nrn and -nrz negate each other";

  // browse the arguments
    for (int i = 1 ; i < argc ; i++) {
      if (argv[i][0] == '-') {
        //////////////////
        // deal with -args
        //////////////////
        for (; (i < argc) && (argv[i][0] == '-') ; i++) {
          string str {argv[i]};

          if (str.substr(0, 2) == "-w") {
            if (is_digit_greater_than_1(str[2])) {
              // will be updated to latest!
              w = char_to_int(str[2]);
            } else {
              std::cout << "ERROR: "<< argv[i] <<" is not a valid formatting argument" << endl;
              return 1; // END
            }
          } else if (str.substr(0,2) == "-s") {
            s = str.substr(2);             // will be updated to latest!
            if (s == "TAB") { s = "\t"; } // hm yup
          } else if (str == "-ba") { // without the string you are comparing the addresses
            ba = true;
          } else if (str == "-bt") {
            bt = true;
          } else if (str == "-nrn") {
            nrn = true;
          } else if (str == "-nrz") {
            nrz = true;
          } else {
            std::cout << "ERROR: "<< argv[i] <<" is not a valid formatting argument" << endl;
            return 1; // END
          }
        }

        // once all analized for validty check for contradictions
        if (ba && bt && nrn && nrz) {
          std::cout << bb_message << endl;
          std::cout << nn_message << endl;
          return 1; // END
        } else if (ba && bt) {
          std::cout << bb_message << endl;
          return 1; // END
        } else if (nrn && nrz) {
          std::cout << nn_message << endl;
          return 1; // END
        }

    } else {
      // default set up
      if (! (ba || bt)) {
        bt = true;
      }
      if (! (nrn || nrz)) {
        nrn = true;
      }
      //////////////////
      // deal with files
      /////////////////
      std::istream *infile = &std::cin; // take from input by default
      int count = 1;
      for (; i < argc; i++) {
        infile = new std::ifstream{ argv[i] };   // FREE at some point
        if ( infile == nullptr || infile->fail() ) {
          delete infile;
          std::cout << "ERROR: " << argv[i] << " cannot be opened for input"<< endl;
          return 1;
        } else {
          format_infile(infile, count, ba, bt, nrn, nrz, w, s); // outputs to stdout
          delete infile;
        }
      }
      return 0;
    }
  } // main for loop
  // default set up
  if (! (ba || bt)) {
    bt = true;
  }
  if (! (nrn || nrz)) {
    nrn = true;
  }
  int count = 1;
  format_infile(&cin, count, ba, bt, nrn, nrz, w, s);
}
