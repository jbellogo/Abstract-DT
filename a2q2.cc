// takes input from command line or from a list of file (concatenates them)
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>


using std::endl;
using std::setw;
using std::string;

// argv[-bt, file1,file2 ...]
void format_infile(std::istream * inf, int & count){
  std::string s;
  while (getline(*inf, s)) {
    std::cout << setw(3) << count << ": \'" << s << "\'" << std::endl;
    count++;
  }
}

bool member(string item, int length, string arr[]){
  for (int i=0; i<length; i++) {
    if (arr[i] = item) return true;
  }
  return false;
}

bool is_digit_greater_than_1(char a) {
  string str{1, a};
  for (int i = 2; i < 10; i++) {
    stringstream ss;
    ss<<i;
    string s;
    ss>>s;
    if (s == str)
  }
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
  int w = -1;
  string s = "";
  bb_message = "ERROR: -ba and -bt negate each other"
  nn_message = "ERROR: -nrn and -nrz negate each other"

  // browse the arguments
  for (int i=1; i < argc; i++) {
    if (argv[i][0] == '-') {
      // deal with -args
      for (; (i < argc) && (argv[i][0] == '-') ; i++) {
        if (argv[i][1] == 'w') {
          if (is_digit_greater_than_1(argv[i][2])) {
            // will be updated to latest! i think
            w = char_to_int(argv[i][2]);
          } else {
            std::cout << "ERROR: "<< argv[i] <<" is not a valid formatting argument" << endl;
            return 1; // END
          }
        } else if (argv[i][1] == 's') {
          // will be updated to latest!
          s = argv[i].substr(2);
        } else if (argv[i] == "-ba") {
          ba = true;
        } else if (argv[i] == "-bt") {
          bt = true;
        } else if (argv[i] == "nrn") {
          nrn = true;
        } else if (argv[i] == "nrz") {
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

    // deal with files
    for (; i < argc ; i++) {
      infile = new std::ifstream{ argv[i] };   // FREE at some point
      if ( infile == nullptr || infile->fail() ) {
        delete infile;
        std::cout << "ERROR: " << argv[i] << " cannot be opened for input"<< endl;
        return 1;
      }
    }

    }
  }


  std::istream *infile = &std::cin; // take from input by default



  // browse args
  int count = 0;
  for (int i=1; i < argc; i++) {

    // if file
    if (argv[i][0] != '-') {
      infile = new std::ifstream{ argv[i] };   // FREE at some point
      // if you can't open it or doesn't exist:
      if ( infile == nullptr || infile->fail() ) {
        delete infile;
        std::cout << "ERROR: " << argv[i] << " cannot be opened for input"<< endl;
        return 1;
      } else {
        format_infile(infile, count); // outputs to stdout
        delete infile;
      }
    } else {
      // not a file
      std::cout << "commands not supported" << '\n';
    }
  }
  return 0;
}
